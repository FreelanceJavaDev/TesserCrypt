#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "../core/rotate.hpp"
struct fx_rotMatrix : public RotationMatrix {
	fx_rotMatrix() {};
	~fx_rotMatrix() {};
};

const double pi = std::acos(-1);

const double PI_36 = pi/36.0; // 5 degree angle
const double PI_12 = pi/12.0; // 15 degree angle
const double PI_6 = pi/6.0;

const double sqrt3_2 = std::sqrt(3.0)/2.0;
const double sqrt2_2 = std::sqrt(2.0)/2.0;
const double half = 0.50;
const double _sqrt3_2 = std::sqrt(3.0)/-2.0;
const double _sqrt2_2 = std::sqrt(2.0)/-2.0;
const double _half = -0.50;

const double cos_15_deg = (1.0 + std::sqrt(3.0))/(2.0*std::sqrt(2));
const double _cos_15_deg = -1*cos_15_deg;
const double sin_15_deg = (std::sqrt(3)-1)/(2.0*std::sqrt(2));
const double _sin_15_deg = -1*sin_15_deg;

const double tolerance_norm = 1.5e-13;
const double tolerance_zero = 1.0e-16;
const double tolerance_min = std::numeric_limits<double>::epsilon();
BOOST_AUTO_TEST_SUITE(Core_Test_Suite)
//Unit Tests for Rotation class only
BOOST_FIXTURE_TEST_SUITE(rotSuite, fx_rotMatrix)
namespace tdata = boost::unit_test::data;
namespace tt = boost::test_tools;
std::array<double, 6> test_deg_angle_data = { 0, 15, 30, 45, 60, 90 };
const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 2> expected_XY_15 {{
	{{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }},
	{{ {sqrt3_2, _half, 0, 0}, {half, sqrt3_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}
}};
const std::array< const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_XY =  {{ 
	{{ {1.0, -0.0, 0, 0}, {0.0, 1.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }},
	{{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }},
	{{ {sqrt3_2, _half, 0, 0}, {half, sqrt3_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}},
	{{ {sqrt2_2, _sqrt2_2, 0, 0}, {sqrt2_2, sqrt2_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}},
	{{ {half, _sqrt3_2, 0, 0}, {sqrt3_2, half, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}},
	{{ {0.0, -1.0, 0, 0}, {1.0, 0.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}
}};
const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_XZ = {{ 
	{{ {1.0, 0, 0.0, 0}, {0, 1, 0, 0}, {-0.0, 0, 1.0, 0}, {0, 0, 0, 1} }},
	{{ {cos_15_deg, 0, sin_15_deg, 0}, {0, 1, 0, 0}, {_sin_15_deg, 0, cos_15_deg, 0}, {0, 0, 0, 1} }},
	{{ {sqrt3_2, 0, half, 0}, {0, 1, 0, 0}, {_half, 0, sqrt3_2, 0}, {0, 0, 0, 1} }},
	{{ {sqrt2_2, 0, sqrt2_2, 0}, {0, 1, 0, 0}, {_sqrt2_2, 0, sqrt2_2, 0}, {0, 0, 0, 1} }},
	{{ {half, 0, sqrt3_2, 0}, {0, 1, 0, 0}, {_sqrt3_2, 0, half, 0}, {0, 0, 0, 1} }},
	{{ {0.0, 0, 1.0, 0}, {0, 1, 0, 0}, {-1.0, 0, 0.0, 0}, {0, 0, 0, 1} }}
	 
}}; // XZ
const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_XW = {{ 
	{{ {1.0, 0, 0, 0.0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-0.0, 0, 0, 1.0} }},
	{{ {cos_15_deg, 0, 0, sin_15_deg}, {0, 1, 0, 0}, {0, 0, 1, 0}, {_sin_15_deg, 0, 0, cos_15_deg} }},
	{{ {sqrt3_2, 0, 0, half}, {0, 1, 0, 0}, {0, 0, 1, 0}, {_half, 0, 0, sqrt3_2} }},
	{{ {sqrt2_2, 0, 0, sqrt2_2}, {0, 1, 0, 0}, {0, 0, 1, 0}, {_sqrt2_2, 0, 0, sqrt2_2} }},
	{{ {half, 0, 0, sqrt3_2}, {0, 1, 0, 0}, {0, 0, 1, 0}, {_sqrt3_2, 0, 0, half} }},
	{{ {0.0, 0, 0, 1.0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-1.0, 0, 0, 0.0} }}

}}; // XW
const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_YZ = {{ 
	{{ {1, 0, 0, 0}, {0, 1.0, -0.0, 0}, {0, 0.0, 1.0, 0}, {0, 0, 0, 1} }},
	{{ {1, 0, 0, 0}, {0, cos_15_deg, _sin_15_deg, 0}, {0, sin_15_deg, cos_15_deg, 0}, {0, 0, 0, 1} }},
	{{ {1, 0, 0, 0}, {0, sqrt3_2, _half, 0}, {0, half, sqrt3_2, 0}, {0, 0, 0, 1} }},
	{{ {1, 0, 0, 0}, {0, sqrt2_2, _sqrt2_2, 0}, {0, sqrt2_2, sqrt2_2, 0}, {0, 0, 0, 1} }},
	{{ {1, 0, 0, 0}, {0, half, _sqrt3_2, 0}, {0, sqrt3_2, half, 0}, {0, 0, 0, 1} }},
	{{ {1, 0, 0, 0}, {0, 0.0, -1.0, 0}, {0, 1.0, 0.0, 0}, {0, 0, 0, 1} }}	
}}; //YZ
const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_YW = {{
	{{ {1, 0, 0, 0}, {0, 1.0, 0, -0.0}, {0, 0, 1, 0}, {0, 0.0, 0, 1.0} }},
	{{ {1, 0, 0, 0}, {0, cos_15_deg, 0, _sin_15_deg}, {0, 0, 1, 0}, {0, sin_15_deg, 0, cos_15_deg} }},	
	{{ {1, 0, 0, 0}, {0, sqrt3_2, 0, _half}, {0, 0, 1, 0}, {0, half, 0, sqrt3_2} }},
	{{ {1, 0, 0, 0}, {0, sqrt2_2, 0, _sqrt2_2}, {0, 0, 1, 0}, {0, sqrt2_2, 0, sqrt2_2} }},
	{{ {1, 0, 0, 0}, {0, half, 0, _sqrt3_2}, {0, 0, 1, 0}, {0, sqrt3_2, 0, half} }},
	{{ {1, 0, 0, 0}, {0, 0.0, 0, -1.0}, {0, 0, 1, 0}, {0, 1.0, 0, 0.0} }}
}}; //YW

const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 6> expected_ZW = {{
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1.0, -0.0}, {0, 0, 0.0, 1.0} }},
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, cos_15_deg, _sin_15_deg}, {0, 0, sin_15_deg, cos_15_deg} }},
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, sqrt3_2, _half}, {0, 0, half, sqrt3_2} }},
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, sqrt2_2, _sqrt2_2}, {0, 0, sqrt2_2, sqrt2_2} }},
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, half, _sqrt3_2}, {0, 0, sqrt3_2, half} }},
	{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0.0, -1.0}, {0, 0, 1.0, 0.0} }} 
}}; //ZW

void check_all_rows_equal(std::array<std::array<double, N_AXISES>, N_AXISES> &actual, const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected) {
	for(size_t row = 0; row < N_AXISES; ++row) {
		BOOST_TEST_CHECK(actual[X][row] == expected[X][row]);
		BOOST_TEST_CHECK(actual[Y][row] == expected[Y][row]);
		BOOST_TEST_CHECK(actual[Z][row] == expected[Z][row]);
		BOOST_TEST_CHECK(actual[W][row] == expected[W][row]);
	}
}

void check_all_rows_tolerance(std::array<std::array<double, N_AXISES>, N_AXISES> &actual, const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected, const size_t active_a1, const size_t active_a2, const size_t inactive_a1, const size_t inactive_a2) {
	
	BOOST_CHECK_SMALL(actual[active_a1][active_a1], tolerance_zero);
	BOOST_TEST_CHECK(actual[active_a1][active_a2] == expected[active_a1][active_a2]);
	BOOST_TEST_CHECK(actual[active_a2][active_a1] == expected[active_a2][active_a1]);
	BOOST_CHECK_SMALL(actual[active_a2][active_a2], tolerance_zero);
	
	BOOST_TEST_CHECK(actual[active_a1][inactive_a1] == expected[active_a1][inactive_a1]);
	BOOST_TEST_CHECK(actual[active_a1][inactive_a2] == expected[active_a1][inactive_a2]);
	BOOST_TEST_CHECK(actual[active_a2][inactive_a1] == expected[active_a2][inactive_a1]);
	BOOST_TEST_CHECK(actual[active_a2][inactive_a2] == expected[active_a2][inactive_a2]);

	for(size_t row = 0; row < N_AXISES; ++row) {
		BOOST_TEST_CHECK(actual[inactive_a1][row] == expected[inactive_a1][row]);
		BOOST_TEST_CHECK(actual[inactive_a2][row] == expected[inactive_a2][row]);
	}
}

BOOST_DATA_TEST_CASE(rotZW_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(ZW, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_ZW[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, Z, W, X, Y); }
	else {
		BOOST_CHECK_CLOSE(actual[Z][Z], expected[Z][Z], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][Z], expected[W][Z], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Z][W], expected[Z][W], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][W], expected[W][W], tolerance_norm);
	}
}

BOOST_DATA_TEST_CASE(rotYW_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(YW, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_YW[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, Y, W, X, Z); }
	else {
		BOOST_CHECK_CLOSE(actual[Y][Y], expected[Y][Y], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][Y], expected[W][Y], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Y][W], expected[Y][W], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][W], expected[W][W], tolerance_norm);
	}
}

BOOST_DATA_TEST_CASE(rotYZ_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(YZ, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_YZ[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, Y, Z, X, W); }
	else {
		BOOST_CHECK_CLOSE(actual[Y][Y], expected[Y][Y], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Z][Y], expected[Z][Y], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Y][Z], expected[Y][Z], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Z][Z], expected[Z][Z], tolerance_norm);
	}
}

BOOST_DATA_TEST_CASE(rotXZ_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XZ, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_XZ[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, X, Z, Y, W); }
	else {
		BOOST_CHECK_CLOSE(actual[X][X], expected[X][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Z][X], expected[Z][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[X][Z], expected[X][Z], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Z][Z], expected[Z][Z], tolerance_norm);
	}
}

BOOST_DATA_TEST_CASE(rotXW_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XW, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_XW[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, X, W, Y, Z); }
	else {
		BOOST_CHECK_CLOSE(actual[X][X], expected[X][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][X], expected[W][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[X][W], expected[X][W], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[W][W], expected[W][W], tolerance_norm);
	}
}

BOOST_AUTO_TEST_SUITE(rotXY_deg_Test_Suite)
BOOST_DATA_TEST_CASE(rotXY_deg_test, tdata::xrange(6)^test_deg_angle_data, idx, angle_deg) {
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XY, angle_deg);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_XY[idx];
	if(angle_deg == 0) { check_all_rows_equal(actual, expected); }
	else if(angle_deg == 90) { check_all_rows_tolerance(actual, expected, X, Y, Z, W); }
	else {
		BOOST_CHECK_CLOSE(actual[X][X], expected[X][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[X][Y], expected[X][Y], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Y][X], expected[Y][X], tolerance_norm);
		BOOST_CHECK_CLOSE(actual[Y][Y], expected[Y][Y], tolerance_norm);
	}
}

BOOST_AUTO_TEST_CASE(rotXY_135_Test) {
	std::array<std::array<double, N_AXISES>, N_AXISES> expected_135 =  {
		{{_sqrt2_2, _sqrt2_2, 0, 0}, {sqrt2_2, _sqrt2_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};

	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XY, 135);
	BOOST_CHECK_CLOSE(actual[X][0], expected_135[X][0], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[Y][0], expected_135[Y][0], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[X][1], expected_135[X][1], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[Y][1], expected_135[Y][1], tolerance_norm);
}

BOOST_AUTO_TEST_CASE(rotXY_incrment_Test) {
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected_15 = expected_XY_15[0];
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XY, 15);
	BOOST_CHECK_CLOSE(actual[X][X], expected_15[X][X], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[Y][X], expected_15[Y][X], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[X][Y], expected_15[X][Y], tolerance_norm);
	BOOST_CHECK_CLOSE(actual[Y][Y], expected_15[Y][Y], tolerance_norm);

	std::array<std::array<double, N_AXISES>, N_AXISES> actual_inc = rotateIncrement_deg(XY, 15);
	const std::array<const std::array<double, N_AXISES>, N_AXISES> &expected = expected_XY_15[1];
	BOOST_CHECK_CLOSE(actual_inc[X][X], expected[X][X], tolerance_norm);
	BOOST_CHECK_CLOSE(actual_inc[Y][X], expected[Y][X], tolerance_norm);
	BOOST_CHECK_CLOSE(actual_inc[X][Y], expected[X][Y], tolerance_norm);
	BOOST_CHECK_CLOSE(actual_inc[Y][Y], expected[Y][Y], tolerance_norm);


}

BOOST_AUTO_TEST_CASE(rotXY_increment_x_24_2PI_Test) {
	const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 2> fixed_expected = {{
		{{ {1.0, -0.0, 0, 0}, {0.0, 1.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }},
		{{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }}
	}};
	std::array<std::array<double, N_AXISES>, N_AXISES> dyn_expected = {{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }};
	std::array<std::array<double, N_AXISES>, N_AXISES> &actual = rotateRadian(XY, 0);
	for(size_t row = 0; row < N_AXISES; ++row) {
		BOOST_TEST_CHECK(actual[X][row] == fixed_expected[0][X][row]);
		BOOST_TEST_CHECK(actual[Y][row] == fixed_expected[0][Y][row]);
		BOOST_TEST_CHECK(actual[Z][row] == fixed_expected[0][Z][row]);
		BOOST_TEST_CHECK(actual[W][row] == fixed_expected[0][W][row]);
	}

	double angle_rad, cos_i, sin_i, _sin_i;
	for(int i = 1; i < 25; ++i) {
		angle_rad = PI_12*i;
		cos_i = std::cos(angle_rad);
		sin_i = std::sin(angle_rad);
		_sin_i = -1*sin_i;
		dyn_expected[X][X] = dyn_expected[Y][Y] = cos_i;
		dyn_expected[X][Y] = _sin_i;
		dyn_expected[Y][X] = sin_i;
		actual = rotateIncrement(XY, PI_12);
		if(i == 6 || i == 18) {
			BOOST_CHECK_SMALL(actual[X][0], tolerance_norm);
			BOOST_TEST_CHECK(actual[Y][0] == dyn_expected[Y][0], tt::tolerance(tolerance_norm));
			BOOST_TEST_CHECK(actual[X][1] == dyn_expected[X][1], tt::tolerance(tolerance_norm));
			BOOST_CHECK_SMALL(actual[Y][1], tolerance_norm);
		} 
		else if (i == 12 || i == 24) {
			BOOST_TEST_CHECK(actual[X][0] == dyn_expected[X][0], tt::tolerance(tolerance_norm));
			BOOST_CHECK_SMALL(actual[Y][0], tolerance_norm);
			BOOST_CHECK_SMALL(actual[X][1], tolerance_norm);
			BOOST_TEST_CHECK(actual[Y][1] == dyn_expected[Y][1], tt::tolerance(tolerance_norm));
		}
		else {
			BOOST_CHECK_CLOSE(actual[X][0], dyn_expected[X][0], tolerance_norm);
			BOOST_CHECK_CLOSE(actual[Y][0], dyn_expected[Y][0], tolerance_norm);
			BOOST_CHECK_CLOSE(actual[X][1], dyn_expected[X][1], tolerance_norm);
			BOOST_CHECK_CLOSE(actual[Y][1], dyn_expected[Y][1], tolerance_norm);
		}
	}
}

BOOST_AUTO_TEST_CASE(rotXY_increment_x_24_360_Test) {
	const std::array<const std::array<const std::array<double, N_AXISES>, N_AXISES>, 2> fixed_expected = {{
		{{ {1.0, -0.0, 0, 0}, {0.0, 1.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }},
		{{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }}
	}};
	std::array<std::array<double, N_AXISES>, N_AXISES> dyn_expected = {{ {cos_15_deg, _sin_15_deg, 0, 0}, {sin_15_deg, cos_15_deg, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }};
	std::array<std::array<double, N_AXISES>, N_AXISES> &actual = rotateDegree(XY, 0);
	for(size_t row = 0; row < N_AXISES; ++row) {
		BOOST_TEST_CHECK(actual[X][row] == fixed_expected[0][X][row]);
		BOOST_TEST_CHECK(actual[Y][row] == fixed_expected[0][Y][row]);
		BOOST_TEST_CHECK(actual[Z][row] == fixed_expected[0][Z][row]);
		BOOST_TEST_CHECK(actual[W][row] == fixed_expected[0][W][row]);
	}

	double angle_rad, cos_i, sin_i, _sin_i;
	for(int i = 1; i < 25; ++i) {
		angle_rad = M_PI * ((15*i) / 180.0);
		cos_i = std::cos(angle_rad);
		sin_i = std::sin(angle_rad);
		_sin_i = -1*sin_i;
		dyn_expected[X][X] = dyn_expected[Y][Y] = cos_i;
		dyn_expected[X][Y] = _sin_i;
		dyn_expected[Y][X] = sin_i;
		actual = rotateIncrement_deg(XY, 15);
		BOOST_TEST_CONTEXT("i: " << i) {
		if(i == 6 || i == 18) {
			BOOST_CHECK_SMALL(actual[X][0], tolerance_norm);
			BOOST_TEST_CHECK(actual[Y][0] == dyn_expected[Y][0], tt::tolerance(tolerance_norm));
			BOOST_TEST_CHECK(actual[X][1] == dyn_expected[X][1], tt::tolerance(tolerance_norm));
			BOOST_CHECK_SMALL(actual[Y][1], tolerance_norm);
		} 
		else if (i == 12 || i == 24) {
			BOOST_TEST_CHECK(actual[X][0] == dyn_expected[X][0], tt::tolerance(tolerance_norm));
			BOOST_CHECK_SMALL(actual[Y][0], tolerance_norm);
			BOOST_CHECK_SMALL(actual[X][1], tolerance_norm);
			BOOST_TEST_CHECK(actual[Y][1] == dyn_expected[Y][1], tt::tolerance(tolerance_norm));
		}
		else {
			BOOST_TEST_CHECK(actual[X][0] == dyn_expected[X][0], tt::tolerance(tolerance_norm));
			BOOST_TEST_CHECK(actual[Y][0] == dyn_expected[Y][0], tt::tolerance(tolerance_norm));
			BOOST_TEST_CHECK(actual[X][1] == dyn_expected[X][1], tt::tolerance(tolerance_norm));
			BOOST_TEST_CHECK(actual[Y][1] == dyn_expected[Y][1], tt::tolerance(tolerance_norm));
		}
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()