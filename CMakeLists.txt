cmake_minimum_required(VERSION 3.18...3.31)
project(cgal_python_bindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── CGAL (header-only) ──────────────────────────────────────────────
find_package(CGAL REQUIRED)

# ── nanobind ────────────────────────────────────────────────────────
find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

# ── Extension module ────────────────────────────────────────────────
nanobind_add_module(cgal_kernel src/cgal_kernel.cpp)

target_link_libraries(cgal_kernel PRIVATE CGAL::CGAL)
