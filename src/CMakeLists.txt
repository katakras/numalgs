add_library(numalgs STATIC)

target_compile_features(numalgs PUBLIC cxx_std_20)

target_include_directories(numalgs
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_sources(numalgs
    PRIVATE
        functions/exponential.cpp
        functions/operations.cpp
        functions/polynomials.cpp
        functions/trigonometrics.cpp
        results/results.cpp
        root_finding/bisection.cpp
        root_finding/generic.cpp
)

numalgs_enable_warnings_as_errors(numalgs)
