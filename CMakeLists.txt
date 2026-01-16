cmake_minimum_required(VERSION 4.0)

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

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(
  termcolor
  GIT_REPOSITORY https://github.com/ikalnytskyi/termcolor
  GIT_TAG        89f20096bef51de347ec6f99345f65147359bd7c
)

FetchContent_Declare(
  sqlitecpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
  GIT_TAG        9ec14deb24377cd24f381ff1ab1ef59228cd261b
)

FetchContent_MakeAvailable(termcolor)
FetchContent_MakeAvailable(sqlitecpp)

add_executable(termlander
    src/main.cpp
    src/date_util.cpp
    src/formatter.cpp
)
set_project_warnings(termlander)

target_link_libraries(termlander PRIVATE SQLiteCpp
  sqlite3 
  termcolor
)
