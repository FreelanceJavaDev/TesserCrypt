#define BOOST_TEST_MODULE "Core Tests"
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "../core/coreDef.hpp"
// #include "tesseract_unit_tests.cpp" //Unit Tests for Tesseract class only

#include "../core/rotate.hpp"
#include "../core/tesseract.hpp"
struct fx_tesseract : public Tesseract {
	fx_tesseract() {};
	~fx_tesseract() {};
};

struct fx_rotMatrix : public RotationMatrix {
	fx_rotMatrix() {};
	~fx_rotMatrix() {};
};

std::array<std::array<double, 11>, 24> generate_expected_face_data_update(std::array<std::array<size_t, 3>, 24> &f_vectors, std::array<std::array<double, N_POINTS>, N_AXISES> &points) {
	double temp;
	std::array<std::array<double, 11>, 24> expected_data;
	for(int i = 0; i < 24; ++i) {
		expected_data[i][0] = points[X][f_vectors[i][1]] - points[X][f_vectors[i][0]];
		expected_data[i][1] = points[Y][f_vectors[i][1]] - points[Y][f_vectors[i][0]];
		expected_data[i][2] = points[Z][f_vectors[i][1]] - points[Z][f_vectors[i][0]];
		expected_data[i][3] = points[W][f_vectors[i][1]] - points[W][f_vectors[i][0]];
		
		expected_data[i][4] = points[X][f_vectors[i][2]] - points[X][f_vectors[i][0]];
		expected_data[i][5] = points[Y][f_vectors[i][2]] - points[Y][f_vectors[i][0]];
		expected_data[i][6] = points[Z][f_vectors[i][2]] - points[Z][f_vectors[i][0]];
		expected_data[i][7] = points[W][f_vectors[i][2]] - points[W][f_vectors[i][0]];
		
		expected_data[i][8] = sqrt(pow(expected_data[i][0], 2) + pow(expected_data[i][1], 2) + pow(expected_data[i][2], 2) + pow(expected_data[i][3], 2));
		expected_data[i][9] = sqrt(pow(expected_data[i][4], 2) + pow(expected_data[i][5], 2) + pow(expected_data[i][6], 2) + pow(expected_data[i][7], 2));
		temp = expected_data[i][0]*expected_data[i][4] + expected_data[i][1]*expected_data[i][5] + expected_data[i][2]*expected_data[i][6] + expected_data[i][3]*expected_data[i][7];
	
		expected_data[i][10] = std::acos(temp/(expected_data[i][8]*expected_data[i][9]));
	}
	return expected_data;
}

BOOST_AUTO_TEST_SUITE(Core_Test_Suite)


//Unit Tests for rotating Tesseract
BOOST_FIXTURE_TEST_SUITE(OpSuite, fx_tesseract)

BOOST_AUTO_TEST_CASE(rotXYOperationTest) {
	const double sqrt2_2 = std::sqrt(2.0)/2.0;
	const double sqrt2 = std::sqrt(2.0);
	const double nsqrt2 = -1*std::sqrt(2.0);
	double tolerance = 1.5e-13;
	double tolerance_zero = 1.111e-16;
	fx_rotMatrix r;

	// std::array<std::array<double, N_POINTS>, N_AXISES> expected_p = {{
	// //    A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P
	// 	{-1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1}, // X
	// 	{-1, -1, -1, -1,  1,  1,  1,  1, -1, -1, -1, -1,  1,  1,  1,  1}, // Y
	// 	{-1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1}, // Z
	// 	{-1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1}  // W
	// }};
	// std::array<std::array<double, N_AXISES>, N_AXISES> expected_135 =  {
	// 	{{-1*sqrt2_2, -1*sqrt2_2, 0, 0}, {sqrt2_2, -1*sqrt2_2, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	// }};

	std::array<std::array<double, N_POINTS>, N_AXISES> expected_ret45 = {{
	//    A 	 B   	  C      D   	 E   	 F   	 G   	 H   	 I   	 J   	 K   	 L   	 M   	 N  	 O  	 P
		{sqrt2,  0.0,     0.0,  sqrt2, 	0.0,  	nsqrt2, nsqrt2,  0.0,   sqrt2,   0.0,    0.0,   sqrt2, 	 0.0,   nsqrt2, nsqrt2,  0.0}, // X
		{ 0.0,  sqrt2, 	 sqrt2,  0.0,   nsqrt2,  0.0,    0.0,   nsqrt2,  0.0,   sqrt2, 	sqrt2, 	 0.0,   nsqrt2,  0.0,    0.0,  nsqrt2}, // Y
		{-1,	-1,  	  1,  	 1, 	-1, 	-1,  	 1,  	 1, 	-1, 	-1, 	 1, 	 1, 	-1, 	-1,  	 1, 	 1}, // Z
		{-1, 	-1, 	 -1, 	-1, 	-1, 	-1, 	-1, 	-1, 	 1, 	 1, 	 1, 	 1, 	 1, 	 1,  	 1, 	 1}  // W
	}};
	

	std::array<std::array<double, N_AXISES>, N_AXISES> rot45Mat = r.rotateDegree(XY, 135);
	std::array<std::array<double, 11>, 24> expected_data = generate_expected_face_data_update(face_vectors, expected_ret45);
	rotateSimple(rot45Mat, 45, XY);
	update_face_area_all();
	std::array<size_t, 24> face_plain = { YZ, YZ, XZ, XZ, XY, XY, YZ, YZ, XZ, XZ, XY, XY, 
	YW, YW, XW, XW, YW, YW, XW, XW, ZW, ZW, ZW, ZW };
	const double fa_expected = 4.0;
	for(uint8_t i = 0; i < 24; ++i) {
		BOOST_CHECK(area_calc_data[i][10] == expected_data[i][10]);
		BOOST_CHECK_CLOSE(face_area[i], fa_expected, tolerance);
		std::array<double, 11> &expected_face_data = expected_data[i];
		std::array<double, 11> &actual_data = area_calc_data[i];
		for(size_t data_idx = 0; data_idx < 10; ++data_idx) 
		{ BOOST_CHECK_CLOSE(actual_data[data_idx], expected_face_data[data_idx], tolerance); }
	}
	for(int i = 0; i < N_POINTS; ++i) {
		switch(i) {
			case A:
			case D:
			case F:
			case G:
			case I:
			case L:
			case N:
			case O: BOOST_CHECK_CLOSE(vertexes[X][i], expected_ret45[X][i], tolerance);
			BOOST_CHECK_SMALL(vertexes[Y][i], tolerance_zero);
			break;
			default: BOOST_CHECK_CLOSE(vertexes[Y][i], expected_ret45[Y][i], tolerance);
			BOOST_CHECK_SMALL(vertexes[X][i], tolerance_zero);
			break;
		}
		BOOST_CHECK(vertexes[Z][i] == expected_ret45[Z][i]);
		BOOST_CHECK(vertexes[W][i] == expected_ret45[W][i]);
	}
	
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
