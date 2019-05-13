# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Pool-Table)

find_package(OpenGL REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
add_subdirectory (lib/external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
		lib/external/AntTweakBar-1.16/include/
		lib/external/glfw-3.1.2/include/
		lib/external/glm-0.9.7.1/
		lib/external/glew-1.13.0/include/
		lib/external/assimp-3.0.1270/include/
		lib/external/bullet-2.81-rev2613/src/
		.
)

set(ALL_LIBS
		${OPENGL_LIBRARY}
		glfw
		GLEW_1130
		)

add_definitions(
		-DTW_STATIC
		-DTW_NO_LIB_PRAGMA
		-DTW_NO_DIRECT3D
		-DGLEW_STATIC
		-D_CRT_SECURE_NO_WARNINGS
)

# The game
add_executable(TheGame Main.cpp
		lib/common/shader.cpp
		lib/common/shader.hpp
		Ball.h
		Ball.cpp
		Drawable.h
		Drawable.cpp
		Drawables.cpp
		Drawables.h
		Collidables.cpp
		Collidables.h
		Color.cpp
		Color.h
		Wall.cpp
		Wall.h
        Pocket.h Pocket.cpp)
target_link_libraries(TheGame
		${ALL_LIBS}
		)
# Xcode and Visual working directories
set_target_properties(TheGame PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(TheGame WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


add_custom_command(
		TARGET TheGame POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
)