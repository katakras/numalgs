include(FetchContent)

# catch2
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(numalgs_tests
    test_functions.cpp
)

target_link_libraries(numalgs_tests
    PRIVATE
        numalgs
        Catch2::Catch2WithMain
)

add_test(NAME numalgs_tests COMMAND numalgs_tests)