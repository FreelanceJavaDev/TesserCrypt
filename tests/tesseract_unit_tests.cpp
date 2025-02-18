#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../core/tesseract.hpp"

struct fx_tesseract : public Tesseract {
	fx_tesseract() {};
	~fx_tesseract() {};
};

BOOST_AUTO_TEST_SUITE(Core_Test_Suite)

BOOST_FIXTURE_TEST_SUITE(TesseractUnitTests, fx_tesseract)
const double tolerance_norm = 1.5e-13;
const double tolerance_zero = 1.111e-16;
const double expected_fa_unchanged = 4;
const double expected_ending_unchanged[3] = {2, 2, DEG_90};

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
	BOOST_TEST_CHECKPOINT("Inital Face Area data");
	std::array<std::array<double, 8>, 24> expected_data = {{
		{ 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //CDG
		{ 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //DAH
		{ 2,  0,  0,  0,  0,  0, -2,  0}, {-2,  0,  0,  0,  0,  0,  2,  0}, //FEG
		{ 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //KLO
		{ 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //LIP
		{ 2,  0,  0,  0,  0,  0, -2,  0}, { 0,  0, -2,  0,  2,  0,  0,  0}, //PMO
		{ 2,  0,  0,  0,  0,  0,  0,  2}, { 2,  0,  0,  0,  0,  0,  0,  2}, //DCL
		{ 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0, -2,  0,  0,  0,  0,  2}, //DAL
		{-2,  0,  0,  0,  0,  0,  0,  2}, {-2,  0,  0,  0,  0,  0,  0,  2}, //GHO
		{ 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0,  2,  0,  0,  0,  0,  2}, //EHM
		{ 0, -2,  0,  0,  0,  0,  0,  2}, { 0,  2,  0,  0,  0,  0,  0,  2}, //BFJ
		{ 0,  2,  0,  0,  0,  0,  0,  2}, { 0, -2,  0,  0,  0,  0,  0,  2}, //HDP
	}};
	for(size_t face_idx = 0; face_idx < 24; ++face_idx) {
		std::array<double, 8> &expected_face_data = expected_data[face_idx];
		std::array<double, 11> &actual_data = area_calc_data[face_idx];
		BOOST_TEST_CHECK(face_area[face_idx] == expected_fa_unchanged);
		for(size_t data_idx = 0; data_idx < 8; ++data_idx) 
		{ BOOST_TEST_CHECK(actual_data[data_idx] == expected_face_data[data_idx]); }
		BOOST_CHECK(actual_data[8] == expected_ending_unchanged[0]);
		BOOST_CHECK(actual_data[9] == expected_ending_unchanged[1]);
		BOOST_CHECK(actual_data[10] == expected_ending_unchanged[2]);
	}
}

BOOST_AUTO_TEST_CASE(update_all_face_area_data_test) {
	const double tolerance = 1.5e-13;
	const double tolerance_zero = 1.111e-16;
	update_face_area_all();
	std::array<std::array<double, 8>, 24> expected_data = {{
		{ 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //CDG
		{ 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //DAH
		{ 2,  0,  0,  0,  0,  0, -2,  0}, {-2,  0,  0,  0,  0,  0,  2,  0}, //FEG
		{ 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //KLO
		{ 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //LIP
		{ 2,  0,  0,  0,  0,  0, -2,  0}, { 0,  0, -2,  0,  2,  0,  0,  0}, //PMO
		{ 2,  0,  0,  0,  0,  0,  0,  2}, { 2,  0,  0,  0,  0,  0,  0,  2}, //DCL
		{ 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0, -2,  0,  0,  0,  0,  2}, //DAL
		{-2,  0,  0,  0,  0,  0,  0,  2}, {-2,  0,  0,  0,  0,  0,  0,  2}, //GHO
		{ 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0,  2,  0,  0,  0,  0,  2}, //EHM
		{ 0, -2,  0,  0,  0,  0,  0,  2}, { 0,  2,  0,  0,  0,  0,  0,  2}, //BFJ
		{ 0,  2,  0,  0,  0,  0,  0,  2}, { 0, -2,  0,  0,  0,  0,  0,  2}, //HDP
	}};

	
	for(size_t face_idx = 0; face_idx < 24; ++face_idx) {
		std::array<double, 8> &expected_face_data = expected_data[face_idx];
		std::array<double, 11> &actual_data = area_calc_data[face_idx];
		for(size_t data_idx = 0; data_idx < 8; ++data_idx) 
		{ BOOST_CHECK(actual_data[data_idx] == expected_face_data[data_idx]); }
		BOOST_CHECK(actual_data[8] == expected_ending_unchanged[0]);
		BOOST_CHECK(actual_data[9] == expected_ending_unchanged[1]);
		BOOST_CHECK(actual_data[10] == expected_ending_unchanged[2]);
		BOOST_CHECK_CLOSE(face_area[face_idx], expected_fa_unchanged, tolerance_norm);
	}
}

BOOST_AUTO_TEST_CASE(edge_length_update_test) {
	
	edge_length_update();
	std::array<std::array<double, 8>, 24> expected_data = {{
	 { 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //CDG
	 { 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //DAH
	 { 2,  0,  0,  0,  0,  0, -2,  0}, {-2,  0,  0,  0,  0,  0,  2,  0}, //FEG
	 { 2,  0,  0,  0,  0,  2,  0,  0}, {-2,  0,  0,  0,  0,  2,  0,  0}, //KLO
	 { 0,  0,  2,  0,  0,  2,  0,  0}, { 0,  0, -2,  0,  0,  2,  0,  0}, //LIP
	 { 2,  0,  0,  0,  0,  0, -2,  0}, { 0,  0, -2,  0,  2,  0,  0,  0}, //PMO
	 { 2,  0,  0,  0,  0,  0,  0,  2}, { 2,  0,  0,  0,  0,  0,  0,  2}, //DCL
	 { 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0, -2,  0,  0,  0,  0,  2}, //DAL
	 {-2,  0,  0,  0,  0,  0,  0,  2}, {-2,  0,  0,  0,  0,  0,  0,  2}, //GHO
	 { 0,  0,  2,  0,  0,  0,  0,  2}, { 0,  0,  2,  0,  0,  0,  0,  2}, //EHM
	 { 0, -2,  0,  0,  0,  0,  0,  2}, { 0,  2,  0,  0,  0,  0,  0,  2}, //BFJ
	 { 0,  2,  0,  0,  0,  0,  0,  2}, { 0, -2,  0,  0,  0,  0,  0,  2}, //HDP
	}};

	for(size_t face_idx = 0; face_idx < 24; ++face_idx) {
		std::array<double, 8> &expected_face_data = expected_data[face_idx];
		std::array<double, 11> &actual_data = area_calc_data[face_idx];
		for(size_t data_idx = 0; data_idx < 8; ++data_idx) 
		{ BOOST_CHECK(actual_data[data_idx] == expected_face_data[data_idx]); }
		BOOST_CHECK(actual_data[8] == expected_ending_unchanged[0]);
		BOOST_CHECK(actual_data[9] == expected_ending_unchanged[1]);
		BOOST_CHECK(actual_data[10] == expected_ending_unchanged[2]);
		BOOST_CHECK_CLOSE(face_area[face_idx], expected_fa_unchanged, tolerance_norm);
		BOOST_TEST_CHECK(face_area[face_idx] == expected_fa_unchanged);
	}
}

BOOST_AUTO_TEST_CASE(scalarOperationTest) {
	Tesseract::operator*=(5);
	edge_length_update();
	const double expected_fa = 100;
	std::array<std::array<double, 8>, 24> expected_data = {{
	 { 10,  0,   0,  0,  0,  10,   0,   0}, {-10,   0,   0,  0,   0,  10,   0,   0}, //CDG
	 {  0,  0,  10,  0,  0,  10,   0,   0}, {  0,   0, -10,  0,   0,  10,   0,   0}, //DAH
	 { 10,  0,   0,  0,  0,   0, -10,   0}, {-10,   0,   0,  0,   0,   0,  10,   0}, //FEG
	 { 10,  0,   0,  0,  0,  10,   0,   0}, {-10,   0,   0,  0,   0,  10,   0,   0}, //KLO
	 {  0,  0,  10,  0,  0,  10,   0,   0}, {  0,   0, -10,  0,   0,  10,   0,   0}, //LIP
	 { 10,  0,   0,  0,  0,   0, -10,   0}, {  0,   0, -10,  0,  10,   0,   0,   0}, //PMO
	 { 10,  0,   0,  0,  0,   0,   0,  10}, { 10,   0,   0,  0,   0,   0,   0,  10}, //DCL
	 {  0,  0,  10,  0,  0,   0,   0,  10}, {  0,   0, -10,  0,   0,   0,   0,  10}, //DAL
	 {-10,  0,   0,  0,  0,   0,   0,  10}, {-10,   0,   0,  0,   0,   0,   0,  10}, //GHO
	 {  0,  0,  10,  0,  0,   0,   0,  10}, {  0,   0,  10,  0,   0,   0,   0,  10}, //EHM
	 {  0, -10,  0,  0,  0,   0,   0,  10}, {  0,  10,   0,  0,   0,   0,   0,  10}, //BFJ
	 {  0,  10,  0,  0,  0,   0,   0,  10}, {  0, -10,   0,  0,   0,   0,   0,  10}, //HDP
	}};

	double expected_ending[3] = {10, 10, DEG_90};
	for(size_t face_idx = 0; face_idx < 24; ++face_idx) {
		BOOST_CHECK_CLOSE(face_area[face_idx], expected_fa, tolerance_norm);
		std::array<double, 8> &expected_face_data = expected_data[face_idx];
		std::array<double, 11> &actual_data = area_calc_data[face_idx];
		for(size_t data_idx = 0; data_idx < 8; ++data_idx) 
		{ BOOST_CHECK(actual_data[data_idx] == expected_face_data[data_idx]); }
		BOOST_CHECK(actual_data[8] == expected_ending[0]);
		BOOST_CHECK(actual_data[9] == expected_ending[1]);
		BOOST_CHECK(actual_data[10] == expected_ending[2]);
	}
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
