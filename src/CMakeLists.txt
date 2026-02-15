add_library(numalgs STATIC)

target_compile_features(numalgs PUBLIC cxx_std_20)

target_include_directories(numalgs
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_sources(numalgs
    PRIVATE
        functions/operations.cpp
        functions/polynomials.cpp
        results/results.cpp
        root_finding/bisection.cpp
        root_finding/generic.cpp
)