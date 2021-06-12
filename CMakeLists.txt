cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(MarchingSquares)

# picks all the source files from the src directory
file(GLOB SOURCE_FILES "src/*.cpp" "src/*h")
message(${SOURCE_FILES})

# add the source files to the project executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# links the sfml library (i don't know if works on windows)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
