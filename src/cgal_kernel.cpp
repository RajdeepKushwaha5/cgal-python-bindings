// cgal_kernel.cpp — nanobind Python bindings for the CGAL Kernel
//
// Wraps: Point_2, Point_3, Vector_2, Vector_3, Segment_2, Segment_3,
//        Triangle_2, orientation(), collinear(), squared_distance(),
//        do_intersect(), midpoint(), CGAL::Orientation enum.

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <sstream>

namespace nb = nanobind;
using namespace nb::literals;   // for "arg_name"_a

using K  = CGAL::Exact_predicates_inexact_constructions_kernel;
using FT = K::FT;  // double

// Concrete types from the kernel
using Point_2    = K::Point_2;
using Point_3    = K::Point_3;
using Vector_2   = K::Vector_2;
using Vector_3   = K::Vector_3;
using Segment_2  = K::Segment_2;
using Segment_3  = K::Segment_3;
using Triangle_2 = K::Triangle_2;

// ---------------------------------------------------------------------------
// Helper: generic __repr__ via CGAL's ostream operator<<
// ---------------------------------------------------------------------------
template <typename T>
static std::string cgal_repr(const T& obj) {
    std::ostringstream os;
    os << obj;
    return os.str();
}

// ---------------------------------------------------------------------------
NB_MODULE(cgal_kernel, m) {
    m.doc() = "Python bindings for the CGAL 2D/3D Kernel (EPIC)";

    // ── Orientation enum ───────────────────────────────────────────
    nb::enum_<CGAL::Sign>(m, "Orientation")
        .value("POSITIVE",         CGAL::POSITIVE)
        .value("NEGATIVE",         CGAL::NEGATIVE)
        .value("ZERO",             CGAL::ZERO)
        .value("LEFT_TURN",        CGAL::LEFT_TURN)
        .value("RIGHT_TURN",       CGAL::RIGHT_TURN)
        .value("COLLINEAR",        CGAL::COLLINEAR)
        .value("COUNTERCLOCKWISE", CGAL::COUNTERCLOCKWISE)
        .value("CLOCKWISE",        CGAL::CLOCKWISE)
        .value("COPLANAR",         CGAL::COPLANAR);

    // ── Point_2 ────────────────────────────────────────────────────
    nb::class_<Point_2>(m, "Point_2")
        .def(nb::init<>())
        .def(nb::init<FT, FT>(), "x"_a, "y"_a)
        .def("x", [](const Point_2& p) { return CGAL::to_double(p.x()); })
        .def("y", [](const Point_2& p) { return CGAL::to_double(p.y()); })
        .def("__repr__", &cgal_repr<Point_2>)
        .def("__eq__", [](const Point_2& a, const Point_2& b) { return a == b; })
        .def("__sub__", [](const Point_2& a, const Point_2& b) { return a - b; })
        .def("__add__", [](const Point_2& p, const Vector_2& v) { return p + v; })
        .def("__sub__", [](const Point_2& p, const Vector_2& v) { return p - v; });

    // ── Point_3 ────────────────────────────────────────────────────
    nb::class_<Point_3>(m, "Point_3")
        .def(nb::init<>())
        .def(nb::init<FT, FT, FT>(), "x"_a, "y"_a, "z"_a)
        .def("x", [](const Point_3& p) { return CGAL::to_double(p.x()); })
        .def("y", [](const Point_3& p) { return CGAL::to_double(p.y()); })
        .def("z", [](const Point_3& p) { return CGAL::to_double(p.z()); })
        .def("__repr__", &cgal_repr<Point_3>)
        .def("__eq__", [](const Point_3& a, const Point_3& b) { return a == b; })
        .def("__sub__", [](const Point_3& a, const Point_3& b) { return a - b; })
        .def("__add__", [](const Point_3& p, const Vector_3& v) { return p + v; })
        .def("__sub__", [](const Point_3& p, const Vector_3& v) { return p - v; });

    // ── Vector_2 ───────────────────────────────────────────────────
    nb::class_<Vector_2>(m, "Vector_2")
        .def(nb::init<>())
        .def(nb::init<FT, FT>(), "x"_a, "y"_a)
        .def("x", [](const Vector_2& v) { return CGAL::to_double(v.x()); })
        .def("y", [](const Vector_2& v) { return CGAL::to_double(v.y()); })
        .def("squared_length", [](const Vector_2& v) { return CGAL::to_double(v.squared_length()); })
        .def("__repr__", &cgal_repr<Vector_2>)
        .def("__eq__", [](const Vector_2& a, const Vector_2& b) { return a == b; })
        .def("__add__", [](const Vector_2& a, const Vector_2& b) { return a + b; })
        .def("__sub__", [](const Vector_2& a, const Vector_2& b) { return a - b; })
        .def("__neg__", [](const Vector_2& v) { return -v; })
        .def("__mul__", [](const Vector_2& v, FT s) { return v * s; })
        .def("__rmul__", [](const Vector_2& v, FT s) { return v * s; })
        .def("__truediv__", [](const Vector_2& v, FT s) { return v / s; })
        .def("dot", [](const Vector_2& a, const Vector_2& b) { return CGAL::to_double(a * b); });

    // ── Vector_3 ───────────────────────────────────────────────────
    nb::class_<Vector_3>(m, "Vector_3")
        .def(nb::init<>())
        .def(nb::init<FT, FT, FT>(), "x"_a, "y"_a, "z"_a)
        .def("x", [](const Vector_3& v) { return CGAL::to_double(v.x()); })
        .def("y", [](const Vector_3& v) { return CGAL::to_double(v.y()); })
        .def("z", [](const Vector_3& v) { return CGAL::to_double(v.z()); })
        .def("squared_length", [](const Vector_3& v) { return CGAL::to_double(v.squared_length()); })
        .def("__repr__", &cgal_repr<Vector_3>)
        .def("__eq__", [](const Vector_3& a, const Vector_3& b) { return a == b; })
        .def("__add__", [](const Vector_3& a, const Vector_3& b) { return a + b; })
        .def("__sub__", [](const Vector_3& a, const Vector_3& b) { return a - b; })
        .def("__neg__", [](const Vector_3& v) { return -v; })
        .def("__mul__", [](const Vector_3& v, FT s) { return v * s; })
        .def("__rmul__", [](const Vector_3& v, FT s) { return v * s; })
        .def("__truediv__", [](const Vector_3& v, FT s) { return v / s; })
        .def("dot", [](const Vector_3& a, const Vector_3& b) { return CGAL::to_double(a * b); })
        .def("cross", [](const Vector_3& a, const Vector_3& b) {
            return CGAL::cross_product(a, b);
        });

    // ── Segment_2 ──────────────────────────────────────────────────
    nb::class_<Segment_2>(m, "Segment_2")
        .def(nb::init<Point_2, Point_2>(), "source"_a, "target"_a)
        .def("source", &Segment_2::source)
        .def("target", &Segment_2::target)
        .def("squared_length", [](const Segment_2& s) { return CGAL::to_double(s.squared_length()); })
        .def("is_degenerate", &Segment_2::is_degenerate)
        .def("__repr__", &cgal_repr<Segment_2>);

    // ── Segment_3 ──────────────────────────────────────────────────
    nb::class_<Segment_3>(m, "Segment_3")
        .def(nb::init<Point_3, Point_3>(), "source"_a, "target"_a)
        .def("source", &Segment_3::source)
        .def("target", &Segment_3::target)
        .def("squared_length", [](const Segment_3& s) { return CGAL::to_double(s.squared_length()); })
        .def("is_degenerate", &Segment_3::is_degenerate)
        .def("__repr__", &cgal_repr<Segment_3>);

    // ── Triangle_2 ─────────────────────────────────────────────────
    nb::class_<Triangle_2>(m, "Triangle_2")
        .def(nb::init<Point_2, Point_2, Point_2>(), "p"_a, "q"_a, "r"_a)
        .def("vertex", &Triangle_2::vertex, "i"_a)
        .def("area", [](const Triangle_2& t) { return CGAL::to_double(t.area()); })
        .def("orientation", &Triangle_2::orientation)
        .def("is_degenerate", &Triangle_2::is_degenerate)
        .def("__repr__", &cgal_repr<Triangle_2>)
        .def("__getitem__", [](const Triangle_2& t, int i) {
            if (i < 0 || i > 2) throw nb::index_error();
            return t.vertex(i);
        });

    // ── Global predicates ──────────────────────────────────────────

    // orientation
    m.def("orientation",
          [](const Point_2& p, const Point_2& q, const Point_2& r) {
              return CGAL::orientation(p, q, r);
          }, "p"_a, "q"_a, "r"_a,
          "Returns LEFT_TURN, RIGHT_TURN, or COLLINEAR for three 2D points.");

    m.def("orientation",
          [](const Point_3& p, const Point_3& q,
             const Point_3& r, const Point_3& s) {
              return CGAL::orientation(p, q, r, s);
          }, "p"_a, "q"_a, "r"_a, "s"_a,
          "Returns POSITIVE, NEGATIVE, or COPLANAR for four 3D points.");

    // collinear
    m.def("collinear",
          [](const Point_2& p, const Point_2& q, const Point_2& r) {
              return CGAL::collinear(p, q, r);
          }, "p"_a, "q"_a, "r"_a);

    m.def("collinear",
          [](const Point_3& p, const Point_3& q, const Point_3& r) {
              return CGAL::collinear(p, q, r);
          }, "p"_a, "q"_a, "r"_a);

    // coplanar
    m.def("coplanar",
          [](const Point_3& p, const Point_3& q,
             const Point_3& r, const Point_3& s) {
              return CGAL::coplanar(p, q, r, s);
          }, "p"_a, "q"_a, "r"_a, "s"_a);

    // midpoint
    m.def("midpoint",
          [](const Point_2& p, const Point_2& q) {
              return CGAL::midpoint(p, q);
          }, "p"_a, "q"_a);

    m.def("midpoint",
          [](const Point_3& p, const Point_3& q) {
              return CGAL::midpoint(p, q);
          }, "p"_a, "q"_a);

    // squared_distance
    m.def("squared_distance",
          [](const Point_2& p, const Point_2& q) {
              return CGAL::to_double(CGAL::squared_distance(p, q));
          }, "p"_a, "q"_a);

    m.def("squared_distance",
          [](const Point_3& p, const Point_3& q) {
              return CGAL::to_double(CGAL::squared_distance(p, q));
          }, "p"_a, "q"_a);

    // do_intersect — segment × segment (2D)
    m.def("do_intersect",
          [](const Segment_2& a, const Segment_2& b) {
              return CGAL::do_intersect(a, b);
          }, "a"_a, "b"_a);
}
