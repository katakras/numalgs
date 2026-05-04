FetchContent_MakeAvailable(Catch2)

add_executable(numalgs_tests
    test_functions.cpp
    test_root_finding.cpp
)

target_link_libraries(numalgs_tests
    PRIVATE
        numalgs
        Catch2::Catch2WithMain
)

numalgs_enable_warnings_as_errors(numalgs_tests)

add_test(NAME numalgs_tests COMMAND numalgs_tests)
