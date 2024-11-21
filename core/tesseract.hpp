#ifndef __TESSERACT_HPP
#define __TESSERACT_HPP
#include <array>
#include "coreDef.hpp"

class Tesseract {
private: 
	static const size_t N_POINTS = 16;
	//(m×n)(nxp)×=m×p
	// std::array<std::array<double, 4>, 16> vertexes = {{ //change to 16x4
	// 	{-1, -1, -1, -1}, 
	// 	{ 1, -1, -1, -1}, 
	// 	{ 1, -1,  1, -1}, 
	// 	{-1, -1,  1, -1}, 
	// 	{-1,  1, -1, -1}, 
	// 	{ 1,  1, -1, -1}, 
	// 	{ 1,  1,  1, -1}, 
	// 	{-1,  1,  1, -1}, 
	// 	{-1, -1, -1,  1}, 
	// 	{ 1, -1, -1,  1}, 
	// 	{ 1, -1,  1,  1}, 
	// 	{-1, -1,  1,  1}, 
	// 	{-1,  1, -1,  1}, 
	// 	{ 1,  1, -1,  1}, 
	// 	{ 1,  1,  1,  1}, 
	// 	{-1,  1,  1,  1}
	// }};
	std::array<std::array<double, N_POINTS>, N_AXISES> vertexes = {{ // X, Y, Z, W
		{-1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1},
		{-1, -1, -1, -1,  1,  1,  1,  1, -1, -1, -1, -1,  1,  1,  1,  1},
		{-1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1, -1, -1,  1,  1},
		{-1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1}
	}};
public:
	Tesseract() = default;

	//Uniform Scalar multiplication
	Tesseract& operator*=(int32_t scalar_i) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_i;
			vertexes[Y][i] *= scalar_i;
			vertexes[Z][i] *= scalar_i;
			vertexes[W][i] *= scalar_i;
		}
		return *this;
	};

	Tesseract& operator*=(float scalar_f) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_f;
			vertexes[Y][i] *= scalar_f;
			vertexes[Z][i] *= scalar_f;
			vertexes[W][i] *= scalar_f;
		}
		return *this;
	};
	Tesseract& operator*=(double scalar_d) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_d;
			vertexes[Y][i] *= scalar_d;
			vertexes[Z][i] *= scalar_d;
			vertexes[W][i] *= scalar_d;
		}
		return *this;
	};

};

#endif