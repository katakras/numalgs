cmake_minimum_required(VERSION 3.20)
project(numalgs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(NUMALGS_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

function(numalgs_enable_warnings_as_errors target)
    if (NUMALGS_WARNINGS_AS_ERRORS)
        target_compile_options(${target}
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
                $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
        )
    endif()
endfunction()

include (FetchContent)

# find python
if (EXISTS "${CMAKE_SOURCE_DIR}/.venv/bin/python")
    set(Python_EXECUTABLE
        "${CMAKE_SOURCE_DIR}/.venv/bin/python"
        CACHE FILEPATH "Python executable" FORCE
    )
endif()
find_package(Python 3.14.2 REQUIRED COMPONENTS Interpreter Development.Module)

# nanobind
FetchContent_Declare(
    nanobind
    GIT_REPOSITORY https://github.com/wjakob/nanobind.git
    GIT_TAG v1.8.0
)
FetchContent_MakeAvailable(nanobind)

add_subdirectory(src)
add_subdirectory(python)

include(CTest)
enable_testing()

add_subdirectory(tests)
