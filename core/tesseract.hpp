#ifndef __TESSERACT_HPP
#define __TESSERACT_HPP
#include <array>
#include <cstdint>
#include "coreDef.hpp"

class Tesseract {
protected: 
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
	std::array<std::array<size_t, 4>, 24> faces= {{
		{A,B,F,E}, {C,D,H,G}, {B,C,G,F}, {D,A,E,H}, {D,C,B,A}, {F,E,H,G},
		{I,J,N,M}, {K,L,P,O}, {J,K,O,N}, {L,I,M,P}, {L,K,J,I}, {P,M,N,O},
		{A,B,J,I}, {D,C,K,L}, {B,C,K,J}, {D,A,I,L}, {F,E,M,N}, {G,H,P,O}, 
		{F,G,O,N}, {E,H,P,M}, {E,A,I,M}, {B,F,N,J}, {C,G,O,K}, {H,D,L,P} 
	}};
	std::array<std::array<size_t, 3>, 24> face_vectors= {{ //p0->p1, p0->p2
		{A,B,E}, {C,D,G}, {B,C,F}, {D,A,H}, {D,C,A}, {F,E,G},
		{I,J,M}, {K,L,O}, {J,K,N}, {L,I,P}, {L,K,I}, {P,M,O},
		{A,B,I}, {D,C,L}, {B,C,J}, {D,A,L}, {F,E,N}, {G,H,O}, 
		{F,G,N}, {E,H,M}, {E,A,M}, {B,F,J}, {C,G,K}, {H,D,P} 
	}};
	std::array<double, 24> face_area = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
	std::array<size_t, 24> face_plain = { YZ, YZ, XZ, XZ, XY, XY, YZ, YZ, XZ, XZ, XY, XY, 
	YW, YW, XW, XW, YW, YW, XW, XW, ZW, ZW, ZW, ZW };

	std::array<std::array<double, 11>, 24> area_calc_data = {{ //p0->p1(4), p0->p2(4), mag(2), angle
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
public:
	Tesseract() = default;
	//Uses the dot product and a*b*sin(x)
	void update_face_area_all();
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

	Tesseract& operator*=(std::array<int32_t, N_AXISES> scalar_vi) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_vi[X];
			vertexes[Y][i] *= scalar_vi[Y];
			vertexes[Z][i] *= scalar_vi[Z];
			vertexes[W][i] *= scalar_vi[W];
		}
		return *this;
	};

	Tesseract& operator*=(std::array<float, N_AXISES> scalar_vf) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_vf[X];
			vertexes[Y][i] *= scalar_vf[Y];
			vertexes[Z][i] *= scalar_vf[Z];
			vertexes[W][i] *= scalar_vf[W];
		}
		return *this;
	};

	Tesseract& operator*=(std::array<double, N_AXISES> scalar_vd) {
		for(uint8_t i = 0; i < N_POINTS; ++i) {
			vertexes[X][i] *= scalar_vd[X];
			vertexes[Y][i] *= scalar_vd[Y];
			vertexes[Z][i] *= scalar_vd[Z];
			vertexes[W][i] *= scalar_vd[W];
		}
		return *this;
	};

	void rotateSimple(std::array<std::array<double, N_AXISES>, N_AXISES> &rotMatrix, double angle, size_t plain) {
		for(uint8_t i = 0; i < 24; ++i) {
			if(plain == face_plain[i]) {
				area_calc_data[i][10] += angle;
				if(area_calc_data[i][10] > 180.0) { area_calc_data[i][10] -= 180.0; }
			}
		}
		// 4x4 * 4x16
		std::array<double, N_AXISES> col_src;
		for(uint8_t ret_col = 0; ret_col < N_POINTS; ++ret_col) {
			col_src[X] = vertexes[X][ret_col];
			col_src[Y] = vertexes[Y][ret_col];
			col_src[Z] = vertexes[Z][ret_col];
			col_src[W] = vertexes[W][ret_col];
			
			vertexes[X][ret_col] = rotMatrix[0][0]*col_src[X] + rotMatrix[0][1]*col_src[Y] + rotMatrix[0][2]*col_src[Z] + rotMatrix[0][3]*col_src[W];
			vertexes[Y][ret_col] = rotMatrix[1][0]*col_src[X] + rotMatrix[1][1]*col_src[Y] + rotMatrix[1][2]*col_src[Z] + rotMatrix[1][3]*col_src[W];
			vertexes[Z][ret_col] = rotMatrix[2][0]*col_src[X] + rotMatrix[2][1]*col_src[Y] + rotMatrix[2][2]*col_src[Z] + rotMatrix[2][3]*col_src[W];
			vertexes[W][ret_col] = rotMatrix[3][0]*col_src[X] + rotMatrix[3][1]*col_src[Y] + rotMatrix[3][2]*col_src[Z] + rotMatrix[3][3]*col_src[W];
		}
	}
};

#endif