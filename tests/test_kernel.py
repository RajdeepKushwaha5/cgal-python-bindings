"""Tests for the CGAL kernel Python bindings prototype."""

import cgal_kernel as ck


def test_point2_basics():
    p = ck.Point_2(1.0, 2.0)
    assert p.x() == 1.0
    assert p.y() == 2.0
    print(f"Point_2: {p}")

    q = ck.Point_2(4.0, 6.0)
    v = q - p  # → Vector_2
    assert v.x() == 3.0
    assert v.y() == 4.0

    # point + vector → point
    r = p + v
    assert r == q
    print("  Point_2 arithmetic OK")


def test_point3_basics():
    p = ck.Point_3(1.0, 2.0, 3.0)
    assert p.x() == 1.0 and p.y() == 2.0 and p.z() == 3.0
    print(f"Point_3: {p}")

    q = ck.Point_3(4.0, 6.0, 8.0)
    v = q - p
    assert v.x() == 3.0 and v.y() == 4.0 and v.z() == 5.0
    print("  Point_3 arithmetic OK")


def test_vector2():
    v = ck.Vector_2(3.0, 4.0)
    assert v.squared_length() == 25.0
    assert (-v).x() == -3.0

    w = v * 2.0
    assert w.x() == 6.0
    assert w.y() == 8.0

    assert v.dot(ck.Vector_2(1.0, 0.0)) == 3.0
    print("  Vector_2 OK")


def test_vector3_cross():
    u = ck.Vector_3(1.0, 0.0, 0.0)
    v = ck.Vector_3(0.0, 1.0, 0.0)
    w = u.cross(v)
    assert w.x() == 0.0 and w.y() == 0.0 and w.z() == 1.0
    print("  Vector_3 cross product OK")


def test_segment():
    p = ck.Point_2(0.0, 0.0)
    q = ck.Point_2(3.0, 4.0)
    s = ck.Segment_2(p, q)
    assert s.source() == p
    assert s.target() == q
    assert s.squared_length() == 25.0
    print(f"  Segment_2: {s}")


def test_triangle2():
    t = ck.Triangle_2(
        ck.Point_2(0, 0),
        ck.Point_2(4, 0),
        ck.Point_2(0, 3),
    )
    assert t.area() == 6.0
    assert t.orientation() == ck.Orientation.POSITIVE
    assert t[0] == ck.Point_2(0, 0)
    print("  Triangle_2 OK")


def test_orientation_2d():
    p = ck.Point_2(0, 0)
    q = ck.Point_2(1, 0)
    r = ck.Point_2(0, 1)

    # LEFT_TURN == POSITIVE == COUNTERCLOCKWISE (all value 1 in CGAL)
    o = ck.orientation(p, q, r)
    assert o == ck.Orientation.POSITIVE  # also LEFT_TURN
    o2 = ck.orientation(p, r, q)
    assert o2 == ck.Orientation.NEGATIVE  # also RIGHT_TURN
    o3 = ck.orientation(p, q, ck.Point_2(2, 0))
    assert o3 == ck.Orientation.ZERO  # also COLLINEAR
    print("  orientation (2D) OK")


def test_orientation_3d():
    # Standard tetrahedron orientation
    p = ck.Point_3(0, 0, 0)
    q = ck.Point_3(1, 0, 0)
    r = ck.Point_3(0, 1, 0)
    s = ck.Point_3(0, 0, 1)
    assert ck.orientation(p, q, r, s) == ck.Orientation.POSITIVE
    print("  orientation (3D) OK")


def test_collinear():
    assert ck.collinear(
        ck.Point_2(0, 0), ck.Point_2(1, 1), ck.Point_2(2, 2)
    )
    assert not ck.collinear(
        ck.Point_2(0, 0), ck.Point_2(1, 1), ck.Point_2(2, 3)
    )

    assert ck.collinear(
        ck.Point_3(0, 0, 0), ck.Point_3(1, 1, 1), ck.Point_3(2, 2, 2)
    )
    print("  collinear OK")


def test_coplanar():
    assert ck.coplanar(
        ck.Point_3(0, 0, 0), ck.Point_3(1, 0, 0),
        ck.Point_3(0, 1, 0), ck.Point_3(1, 1, 0),
    )
    assert not ck.coplanar(
        ck.Point_3(0, 0, 0), ck.Point_3(1, 0, 0),
        ck.Point_3(0, 1, 0), ck.Point_3(0, 0, 1),
    )
    print("  coplanar OK")


def test_midpoint():
    m2 = ck.midpoint(ck.Point_2(0, 0), ck.Point_2(4, 6))
    assert m2.x() == 2.0 and m2.y() == 3.0

    m3 = ck.midpoint(ck.Point_3(0, 0, 0), ck.Point_3(2, 4, 6))
    assert m3.x() == 1.0 and m3.y() == 2.0 and m3.z() == 3.0
    print("  midpoint OK")


def test_squared_distance():
    d = ck.squared_distance(ck.Point_2(0, 0), ck.Point_2(3, 4))
    assert d == 25.0

    d3 = ck.squared_distance(ck.Point_3(0, 0, 0), ck.Point_3(1, 2, 2))
    assert d3 == 9.0
    print("  squared_distance OK")


def test_do_intersect():
    s1 = ck.Segment_2(ck.Point_2(0, 0), ck.Point_2(2, 2))
    s2 = ck.Segment_2(ck.Point_2(0, 2), ck.Point_2(2, 0))
    s3 = ck.Segment_2(ck.Point_2(3, 3), ck.Point_2(4, 4))

    assert ck.do_intersect(s1, s2)      # X-crossing
    assert not ck.do_intersect(s1, s3)   # disjoint
    print("  do_intersect OK")


if __name__ == "__main__":
    tests = [
        test_point2_basics,
        test_point3_basics,
        test_vector2,
        test_vector3_cross,
        test_segment,
        test_triangle2,
        test_orientation_2d,
        test_orientation_3d,
        test_collinear,
        test_coplanar,
        test_midpoint,
        test_squared_distance,
        test_do_intersect,
    ]

    passed = 0
    for t in tests:
        try:
            t()
            passed += 1
        except Exception as e:
            print(f"  FAIL {t.__name__}: {e}")

    print(f"\n{passed}/{len(tests)} tests passed")
