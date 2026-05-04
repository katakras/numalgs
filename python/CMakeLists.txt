nanobind_add_module(numalgs_py
    module.cpp
    bind_functions.cpp
    bind_results.cpp
    bind_root_finding.cpp
)

set_target_properties(numalgs_py PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

target_include_directories(numalgs_py
    SYSTEM PRIVATE
        "${nanobind_SOURCE_DIR}/include"
)

target_link_libraries(numalgs_py
    PRIVATE
        numalgs
        Python::Module
)

numalgs_enable_warnings_as_errors(numalgs_py)
