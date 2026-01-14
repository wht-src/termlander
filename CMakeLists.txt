cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

function(set_project_warnings target_name)
    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wno-unused-parameter
    )

    set(GCC_WARNINGS ${CLANG_WARNINGS})

    set(MSVC_WARNINGS
        /W4
        /permissive-
    )

    set(ERROR_FLAGS
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>

        $<$<CXX_COMPILER_ID:MSVC>:/WX>
    )

    target_compile_options(${target_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
        $<$<CXX_COMPILER_ID:Clang>:${CLANG_WARNINGS}>
        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
        ${ERROR_FLAGS}
    )
endfunction()

project(termlander
    VERSION 0.1.0
    LANGUAGES CXX
)

add_subdirectory(thirdparty/sqlitecpp)
add_subdirectory(thirdparty/termcolor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(termlander
    src/main.cpp
    src/date_util.cpp
    src/formatter.cpp
)
set_project_warnings(termlander)

target_link_libraries(termlander PRIVATE SQLiteCpp
  sqlite3 
  pthread
  dl
  termcolor
)
