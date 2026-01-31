nanobind_add_module(numalgs_py
    module.cpp
    bind_functions.cpp
)

set_target_properties(numalgs_py PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_link_libraries(numalgs_py
    PRIVATE
        numalgs
        Python::Module
)