#include <cmath>
#include "tesseract.hpp"

void Tesseract::update_face_area_all() {
	double temp;
	for(int i = 0; i < 24; ++i) {
		area_calc_data[i][0] = vertexes[X][face_vectors[i][1]] - vertexes[X][face_vectors[i][0]];
		area_calc_data[i][1] = vertexes[Y][face_vectors[i][1]] - vertexes[Y][face_vectors[i][0]];
		area_calc_data[i][2] = vertexes[Z][face_vectors[i][1]] - vertexes[Z][face_vectors[i][0]];
		area_calc_data[i][3] = vertexes[W][face_vectors[i][1]] - vertexes[W][face_vectors[i][0]];
		
		area_calc_data[i][4] = vertexes[X][face_vectors[i][2]] - vertexes[X][face_vectors[i][0]];
		area_calc_data[i][5] = vertexes[Y][face_vectors[i][2]] - vertexes[Y][face_vectors[i][0]];
		area_calc_data[i][6] = vertexes[Z][face_vectors[i][2]] - vertexes[Z][face_vectors[i][0]];
		area_calc_data[i][7] = vertexes[W][face_vectors[i][2]] - vertexes[W][face_vectors[i][0]];

		area_calc_data[i][8] = sqrt(pow(area_calc_data[i][0], 2) + pow(area_calc_data[i][1], 2) + pow(area_calc_data[i][2], 2) + pow(area_calc_data[i][3], 2));
		area_calc_data[i][9] = sqrt(pow(area_calc_data[i][4], 2) + pow(area_calc_data[i][5], 2) + pow(area_calc_data[i][6], 2) + pow(area_calc_data[i][7], 2));
		temp = area_calc_data[i][0]*area_calc_data[i][4] + area_calc_data[i][1]*area_calc_data[i][5] + area_calc_data[i][2]*area_calc_data[i][6] + area_calc_data[i][3]*area_calc_data[i][7];
		area_calc_data[i][10] = acos(temp/(area_calc_data[i][8]*area_calc_data[i][9]));
		face_area[i] = area_calc_data[i][8]*area_calc_data[i][9]*sin(area_calc_data[i][10]);
	}
}