nanobind_add_module(numalgs_py
    NB_SUPPRESS_WARNINGS
    module.cpp
    bind_functions.cpp
    bind_results.cpp
    bind_root_finding.cpp
)

set_target_properties(numalgs_py PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

target_link_libraries(numalgs_py
    PRIVATE
        numalgs
        Python::Module
)

nanobind_add_stub(
    numalgs_py_stub
    MODULE numalgs_py
    OUTPUT "../numalgs_py.pyi"
    PYTHON_PATH "$<TARGET_FILE_DIR:numalgs_py>"
    DEPENDS numalgs_py
)

numalgs_enable_warnings_as_errors(numalgs_py)
