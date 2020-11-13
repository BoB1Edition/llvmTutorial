cmake_minimum_required(VERSION 3.10)


project(llmvtutorial)

set(PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
set(SOURCE_EXE main.cpp)
set(CAPP_LIB CApp.cpp)
add_library(CApp STATIC ${CAPP_LIB})

add_executable(main ${SOURCE_EXE})
target_link_libraries(main CApp)	
if(WIN32)
    set(LTOOLS_LIB ltools/ltools.cpp)
    add_library(ltools STATIC ${LTOOLS_LIB})
    target_link_libraries(main ltools)	
endif()