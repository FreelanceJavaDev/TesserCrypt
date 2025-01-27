#define BOOST_TEST_MODULE "Core Tests"
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "../core/coreDef.hpp"
#include "../core/tesseract.hpp"
#include "../core/rotate.hpp"

struct fx_tesseract : public Tesseract {
	fx_tesseract() {};
	~fx_tesseract() {};
};

struct fx_rotMatrix : public RotationMatrix {
	fx_rotMatrix() {};
	~fx_rotMatrix() {};
};

BOOST_FIXTURE_TEST_SUITE(initSuite, fx_tesseract)

BOOST_AUTO_TEST_CASE(initCheck) {
	BOOST_TEST_CHECKPOINT("Inital Points");
	std::array<std::array<double, N_POINTS>, N_AXISES> expected_p = {{
	//    A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P
		{-1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1}, // X
		{-1, -1, -1, -1,  1,  1,  1,  1, -1, -1, -1, -1,  1,  1,  1,  1}, // Y
		{-1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1}, // Z
		{-1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1}  // W
	}};
	for(int it = 0; it < N_AXISES; ++it) {
		BOOST_TEST_CHECK(vertexes[X][it] == expected_p[X][it]);
		BOOST_TEST_CHECK(vertexes[Y][it] == expected_p[Y][it]);
		BOOST_TEST_CHECK(vertexes[Z][it] == expected_p[Z][it]);
		BOOST_TEST_CHECK(vertexes[W][it] == expected_p[W][it]);
	}
	BOOST_TEST_CHECKPOINT("Inital Face Areas");
	double expected_fa = 4;
	for(double &actual : face_area) { BOOST_TEST_CHECK(actual == expected_fa); } 
	BOOST_TEST_CHECKPOINT("Inital Face Area Calculation data");
	std::array<std::array<double, 11>, 24> expected_data = {{
	 { 2,  0,  0,  0,  0,  2,  0,  0, 2, 2, 90}, {-2,  0,  0,  0,  0,  2,  0,  0, 2, 2, 90}, //CDG
	 { 0,  0,  2,  0,  0,  2,  0,  0, 2, 2, 90}, { 0,  0,  2,  0,  0,  2,  0,  0, 2, 2, 90}, //DAH
	 { 2,  0,  0,  0,  0,  0, -2,  0, 2, 2, 90}, {-2,  0,  0,  0,  0,  0,  2,  0, 2, 2, 90}, //FEG
	 { 2,  0,  0,  0,  0,  2,  0,  0, 2, 2, 90}, {-2,  0,  0,  0,  0,  2,  0,  0, 2, 2, 90}, //KLO
	 { 0,  0,  2,  0,  0,  2,  0,  0, 2, 2, 90}, { 0,  0, -2,  0,  0,  2,  0,  0, 2, 2, 90}, //LIP
	 { 2,  0,  0,  0,  0,  0, -2,  0, 2, 2, 90}, { 0,  0, -2,  0,  2,  0,  0,  0, 2, 2, 90}, //PMO
	 { 2,  0,  0,  0,  0,  0,  0,  2, 2, 2, 90}, { 2,  0,  0,  0,  0,  0,  0,  2, 2, 2, 90}, //DCL
	 { 0,  0,  2,  0,  0,  0,  0,  2, 2, 2, 90}, { 0,  0, -2,  0,  0,  0,  0,  2, 2, 2, 90}, //DAL
	 {-2,  0,  0,  0,  0,  0,  0,  2, 2, 2, 90}, {-2,  0,  0,  0,  0,  0,  0,  2, 2, 2, 90}, //GHO
	 { 2,  0,  0,  0,  0,  0,  0,  2, 2, 2, 90}, { 0,  0,  2,  0,  0,  0,  0,  2, 2, 2, 90}, //EHM
	 { 0, -2,  0,  0,  0,  0,  0,  2, 2, 2, 90}, { 0,  2,  0,  0,  0,  0,  0,  2, 2, 2, 90}, //BFJ
	 { 0,  2,  0,  0,  0,  0,  0,  2, 2, 2, 90}, { 0, -2,  0,  0,  0,  0,  0,  2, 2, 2, 90}, //HDP
	}};
	double expected_ending[3] = {2, 2, 90};
	for(size_t face_idx = 0; face_idx < 24; ++face_idx) {
		std::array<double, 11> &expected_face_data = expected_data[face_idx];
		std::array<double, 11> &actual_data = area_calc_data[face_idx];
		for(size_t data_idx = 0; data_idx < 8; ++data_idx) 
		{ BOOST_TEST_CHECK(actual_data[data_idx] == expected_face_data[data_idx]); }
		BOOST_CHECK(actual_data[8] == expected_ending[0]);
		BOOST_CHECK(actual_data[9] == expected_ending[1]);
		BOOST_CHECK(actual_data[10] == expected_ending[2]);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(rotSuite, fx_rotMatrix)
BOOST_AUTO_TEST_CASE(rotXYTest) {
	const double sqrt3_2 = std::sqrt(3.0)/2.0;
	const double sqrt2_2 = std::sqrt(2.0)/2.0;
	const double half = 0.50;
	std::array<std::array<double, N_AXISES>, N_AXISES> expected_0 =  {
		{{1.0, -0.0, 0, 0}, {0.0, 1.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};

	std::array<std::array<double, N_AXISES>, N_AXISES> expected_30 =  {
		{{sqrt3_2, -1*half, 0, 0}, {half, sqrt3_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};

	std::array<std::array<double, N_AXISES>, N_AXISES> expected_45 =  {
		{{sqrt2_2, -1*sqrt2_2, 0, 0}, {sqrt2_2, sqrt2_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};

	std::array<std::array<double, N_AXISES>, N_AXISES> expected_60 =  {
		{{half, -1*sqrt3_2, 0, 0}, {sqrt3_2, half, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};

	std::array<std::array<double, N_AXISES>, N_AXISES> expected_90 =  {
		{{0.0, -1.0, 0, 0}, {1.0, 0.0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	}};
	std::array<std::array<double, N_AXISES>, N_AXISES> actual = rotateDegree(XY, 0);
	double tolerance = 0.00000000000015;
	double tolerance_zero = 0.0000000000000001;
	for(size_t row = 0; row < N_AXISES; ++row) {
		BOOST_TEST_CHECK(actual[X][row] == expected_0[X][row]);
		BOOST_TEST_CHECK(actual[Y][row] == expected_0[Y][row]);
		BOOST_TEST_CHECK(actual[Z][row] == expected_0[Z][row]);
		BOOST_TEST_CHECK(actual[W][row] == expected_0[W][row]);
	}

	actual = rotateDegree(XY, 30);
	BOOST_CHECK_CLOSE(actual[X][0], expected_30[X][0], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][0], expected_30[Y][0], tolerance);
	BOOST_CHECK_CLOSE(actual[X][1], expected_30[X][1], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][1], expected_30[Y][1], tolerance);

	actual = rotateDegree(XY, 45);
	BOOST_CHECK_CLOSE(actual[X][0], expected_45[X][0], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][0], expected_45[Y][0], tolerance);
	BOOST_CHECK_CLOSE(actual[X][1], expected_45[X][1], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][1], expected_45[Y][1], tolerance);

	actual = rotateDegree(XY, 60);
	BOOST_CHECK_CLOSE(actual[X][0], expected_60[X][0], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][0], expected_60[Y][0], tolerance);
	BOOST_CHECK_CLOSE(actual[X][1], expected_60[X][1], tolerance);
	BOOST_CHECK_CLOSE(actual[Y][1], expected_60[Y][1], tolerance);

	actual = rotateDegree(XY, 90.0);
	BOOST_CHECK_SMALL(actual[X][0], tolerance_zero);
	BOOST_TEST_CHECK(actual[Y][0] == expected_90[Y][0]);
	BOOST_TEST_CHECK(actual[X][1] ==expected_90[X][1]);
	BOOST_CHECK_SMALL(actual[Y][1], tolerance_zero);
}

BOOST_AUTO_TEST_SUITE_END()
