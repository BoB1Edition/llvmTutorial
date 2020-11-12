cmake_minimum_required(VERSION 3.10)


project(llmvtutorial)

set(SOURCE_EXE main.cpp)
#if(WIN32)
#    include_directories(SYSTEM "c:/msys64/mingw64/x86_64-w64-mingw32/include")
#endif()
set(SOURCE_LIB CApp.cpp)
add_library(CApp STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})
target_link_libraries(main CApp)	