# CGAL Python Bindings Prototype

Python bindings for the [CGAL](https://www.cgal.org/) computational geometry library, built with [nanobind](https://github.com/wjakob/nanobind).

This is a proof-of-concept wrapping the CGAL 2D/3D Kernel using the `Exact_predicates_inexact_constructions_kernel` (EPIC).

## Wrapped Types & Functions

| Type | Description |
|------|-------------|
| `Point_2`, `Point_3` | 2D/3D points with arithmetic (`+`, `-` with vectors), equality |
| `Vector_2`, `Vector_3` | 2D/3D vectors with `+`, `-`, `*`, `/`, `dot()`, `cross()` (3D) |
| `Segment_2`, `Segment_3` | Line segments with `source()`, `target()`, `squared_length()` |
| `Triangle_2` | Triangle with `area()`, `orientation()`, vertex access via `[]` |
| `Orientation` | Enum: `POSITIVE`/`NEGATIVE`/`ZERO` (aliases: `LEFT_TURN`, `RIGHT_TURN`, `COLLINEAR`, etc.) |

| Global Function | Description |
|-----------------|-------------|
| `orientation(p, q, r)` | 2D orientation of three points |
| `orientation(p, q, r, s)` | 3D orientation of four points |
| `collinear(p, q, r)` | Collinearity test (2D and 3D) |
| `coplanar(p, q, r, s)` | Coplanarity test (3D) |
| `midpoint(p, q)` | Midpoint of two points (2D and 3D) |
| `squared_distance(p, q)` | Squared distance between two points (2D and 3D) |
| `do_intersect(s1, s2)` | Intersection test for 2D segments |

## Why nanobind?

[nanobind](https://github.com/wjakob/nanobind) is the successor to pybind11, by the same author (Wenzel Jakob). Key advantages for CGAL bindings:

- **Small binaries** — This module compiles to ~920 KB vs multi-MB for SWIG or pybind11
- **Fast compilation** — Significantly faster than pybind11 (~2-3x in practice)
- **Modern C++17** — Clean lambda syntax for wrapping CGAL's `decltype(auto)` return types
- **Function overloading** — Natural dispatch on argument types (e.g., `orientation()` works with both `Point_2` and `Point_3`)

## Prerequisites

- **CMake** >= 3.18
- **C++17 compiler** (GCC, Clang, or MSVC)
- **CGAL** >= 6.0 (header-only mode works)
- **Python** >= 3.8
- **nanobind**: `pip install nanobind`

## Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DPython_EXECUTABLE=$(which python3)
make -j$(nproc)
```

On Windows with MinGW:

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DPython_EXECUTABLE="C:/path/to/python.exe" -DCGAL_DIR="D:/path/to/cgal"
mingw32-make -j4
```

> **Note:** `-DCMAKE_BUILD_TYPE=Release` is required with MinGW — non-Release builds produce linker errors due to CGAL kernel functions that only get inlined with optimizations enabled.

The compiled module (`cgal_kernel.*.pyd` or `cgal_kernel.*.so`) will be in the `build/` directory.

## Usage

```python
import cgal_kernel as ck

# Points and vectors
p = ck.Point_2(0.0, 0.0)
q = ck.Point_2(3.0, 4.0)
v = q - p                    # Vector_2(3, 4)
print(v.squared_length())    # 25.0

# Orientation test
r = ck.Point_2(0.0, 1.0)
print(ck.orientation(p, q, r))  # Orientation.POSITIVE (left turn)

# 3D geometry
a = ck.Point_3(0, 0, 0)
b = ck.Point_3(1, 0, 0)
c = ck.Point_3(0, 1, 0)
d = ck.Point_3(0, 0, 1)
print(ck.orientation(a, b, c, d))  # Orientation.POSITIVE
print(ck.coplanar(a, b, c, d))    # False

# Intersection test
s1 = ck.Segment_2(ck.Point_2(0, 0), ck.Point_2(2, 2))
s2 = ck.Segment_2(ck.Point_2(0, 2), ck.Point_2(2, 0))
print(ck.do_intersect(s1, s2))    # True
```

## Tests

```bash
cd build
python -m pytest ../tests/ -v
```

All 13 tests should pass.

## License

This prototype is released under the terms of the [LGPL-3.0](https://www.gnu.org/licenses/lgpl-3.0.html), consistent with CGAL's licensing.
