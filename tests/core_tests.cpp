#define BOOST_TEST_MODULE "Core Tests"
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "../core/coreDef.hpp"
#include "../core/tesseract.hpp"

struct fx_tesseract : public Tesseract {
	fx_tesseract() {};
	~fx_tesseract() {};
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