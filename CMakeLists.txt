cmake_minimum_required(VERSION 3.10)


project(llmvtutorial)


set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
set(SOURCE_EXE main.cpp)
set(SOURCE_LIB CApp.cpp)
add_library(CApp STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})
target_link_libraries(main CApp)	
