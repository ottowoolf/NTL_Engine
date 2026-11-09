#[[------------------------------------------------------------------------------
// Project : NTLEngine
------------------------------------------------------------------------------
// Author  : Otman Ouali with the Guidance of Adel Hales
------------------------------------------------------------------------------
// Development Start Date    : 09/11/2026
------------------------------------------------------------------------------
// Engine Description : NTLEngine is a C++ game engine that utilizes the SFML library for graphics and audio functionalities. It provides a framework for developing 2D games with ease. The engine is a passion and learning project designed to be modular, allowing developers to extend its capabilities as needed.
------------------------------------------------------------------------------]]

#[[------------------------------------------------------------------------------
    This CMakeLists.txt file is used to configure the build process for a C++ project that uses the SFML library.
------------------------------------------------------------------------------]]


#[[------------------------------------------------------------------------------
// Specify the minimum required version of CMake. This ensures that the project can be built with a compatible version of CMake.
------------------------------------------------------------------------------]]
cmake_minimum_required(VERSION 3.28)
project (NTLEngine CXX) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    #[[------------------------------------------------------------------------------
// Disable building the SFML network module, as it is not needed for this project.
------------------------------------------------------------------------------]]

set(SFML_BUILD_NETWORK OFF) 

#[[------------------------------------------------------------------------------
// FetchContent is a CMake module that allows you to download and include external content in your project.
------------------------------------------------------------------------------]]

include(FetchContent)

#[[------------------------------------------------------------------------------
// Specify the version of SFML you want to use. You can change this to a different version if needed.
------------------------------------------------------------------------------]]

FetchContent_Declare(SFML URL https://github.com/SFML/SFML/archive/refs/tags/3.1.0.zip)

#[[------------------------------------------------------------------------------
// This command downloads and makes the SFML library available for your project.
------------------------------------------------------------------------------]]
 
FetchContent_MakeAvailable(SFML)

#[[------------------------------------------------------------------------------
// This command collects all the .cpp source files in the "Source" directory and stores their paths in the SOURCES variable. The CONFIGURE_DEPENDS option ensures that CMake re-evaluates the list of source files if any changes occur in the specified directory.
------------------------------------------------------------------------------]]

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/Source/*.cpp) 

#[[------------------------------------------------------------------------------
// Create an executable target named "NTLEngine" using the source files specified in the SOURCES variable.
------------------------------------------------------------------------------]]

add_executable(NTLEngine ${SOURCES})
#[[------------------------------------------------------------------------------
// Add the "Include" directory to the include path for the "NTLEngine" target. This allows the compiler to find header files located in the "Include" directory when compiling the source files.
------------------------------------------------------------------------------]]
target_include_directories(NTLEngine PRIVATE Engine/Include)

#[[------------------------------------------------------------------------------
// This line specifies that the target "NTLEngine" requires C++20 features. It ensures that the compiler uses the appropriate standard when compiling the source files.
------------------------------------------------------------------------------]]

target_compile_features(NTLEngine PRIVATE cxx_std_20)

#[[------------------------------------------------------------------------------
// Set compiler warning flags based on the compiler being used (MSVC or others).
------------------------------------------------------------------------------]]

target_compile_options(NTLEngine PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>, /W4, -Wall -Wextra>) 

#[[------------------------------------------------------------------------------
// This line links the SFML libraries (Graphics and Audio) to the "NTLEngine" target. It allows your project to use SFML's graphics and audio functionalities.
------------------------------------------------------------------------------]]

target_link_libraries(NTLEngine PRIVATE SFML::Graphics SFML::Audio)
