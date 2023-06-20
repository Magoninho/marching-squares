cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(MarchingSquares)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

# picks all the source files from the src directory
file(GLOB SOURCE_FILES "src/*.cpp" "src/*h")
message(${SOURCE_FILES})

# add the source files to the project executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML 
            COMPONENTS
              system window graphics network audio REQUIRED)
# links the sfml library (i don't know if works on windows)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
