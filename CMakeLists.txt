cmake_minimum_required(VERSION 4.3)
project(numalgs LANGUAGES CXX)

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

include(FetchContent)

# find python
if (EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/python")
    set(Python_EXECUTABLE
        "${PROJECT_SOURCE_DIR}/.venv/bin/python"
        CACHE FILEPATH "Python executable" FORCE
    )
endif()
find_package(Python 3.14.2 REQUIRED COMPONENTS Interpreter Development.Module)

# nanobind
FetchContent_Declare(
    nanobind
    GIT_REPOSITORY https://github.com/wjakob/nanobind.git
    GIT_TAG v2.9.1
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(nanobind)

add_subdirectory(src)
add_subdirectory(python)

include(CTest)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
