cmake_minimum_required(VERSION 3.5)
project(FinalWork VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

include_directories(include)
add_executable(main src/main.cpp src/dataProcessor.cpp)
add_executable(test_executable src/test.cpp src/dataProcessor.cpp)

add_test(NAME data_processor COMMAND test_executable)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)