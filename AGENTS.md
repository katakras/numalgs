# Repository Guidelines

## Project Structure & Module Organization

This repository is a C++20 numerical algorithms library with Python bindings. Public headers live in `include/numalgs/`; implementation files live in `src/`, grouped by domain such as `functions/`, `results/`, and `root_finding/`. Python binding code is in `python/` and builds the `numalgs_py` extension into `build/`. C++ tests are in `tests/` and Python tests are in `pytests/`. Generated outputs, local virtual environments, and caches belong outside version control; `build/`, `.venv/`, `.pytest_cache/`, and `*.pyc` are ignored.

## Build, Test, and Development Commands

- `cmake -S . -B build`: configure the project and fetch CMake dependencies, including nanobind and Catch2.
- `cmake --build build`: compile the static library, Python extension, and C++ test executable.
- `ctest --test-dir build --output-on-failure`: run the Catch2 C++ test suite.
- `PYTHONPATH=build pytest pytests`: run Python binding tests against the built `numalgs_py` module.
- `python -m venv .venv && . .venv/bin/activate && pip install -r requirements.txt`: create a local Python environment for pytest and NumPy.

The top-level CMake file prefers `.venv/bin/python` when present and currently requires Python `3.14.2` development components.

## Coding Style & Naming Conventions

Use the repository `.clang-format` for C++: LLVM base style, 4-space indentation, Allman braces, sorted includes, 100-column limit, left-aligned pointers and references. C++ types use `PascalCase` (`Polynomial`, `ComposedFunction`); free functions and accessors use `snake_case` (`add_functions`, `coefficients`). Keep public APIs under the existing namespaces, such as `functions`.

Python tests follow standard pytest naming: files named `test_*.py`, functions named `test_*`, and direct assertions.

## Testing Guidelines

Add or update C++ Catch2 tests in `tests/` for library behavior and Python pytest cases in `pytests/` for binding behavior. Prefer small deterministic numeric examples, and compare floating-point results with a tolerance when exact equality is not guaranteed. Run both `ctest --test-dir build --output-on-failure` and `PYTHONPATH=build pytest pytests` before submitting changes that affect algorithms, headers, or bindings.

## Commit & Pull Request Guidelines

Recent commits use short, lower-case, imperative summaries such as `added bindings for root finding` or `replaced linear polynomial by generic polynomial`. Keep commit messages concise and focused on one logical change.

Pull requests should describe the algorithm or API change, list affected C++ and Python surfaces, include test commands run, and link any relevant issue. Include screenshots only when documentation or visual output is changed.
