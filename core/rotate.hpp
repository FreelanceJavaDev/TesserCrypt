#ifndef __ROTATE_HPP
#define __ROTATE_HPP
#include <cmath>
#include <array>
#include <cstdint>
#include "coreDef.hpp"

class RotationMatrix {
private:
	double degreeToRadian(double degreeAngle) { return M_PI * (degreeAngle / 180.0); }
	std::array<std::array<std::array<double, N_AXISES>, N_AXISES>, N_PLAINS> rotPlains {{ // XY, XZ, XW, YZ, YW, ZW
		{{ {HUGE_VAL, HUGE_VAL, 0, 0}, {HUGE_VAL, HUGE_VAL, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }}, // XY
		{{ {HUGE_VAL, 0, HUGE_VAL, 0}, {0, 1, 0, 0}, {HUGE_VAL, 0, HUGE_VAL, 0}, {0, 0, 0, 1} }}, // XZ
		{{ {HUGE_VAL, 0, 0, HUGE_VAL}, {0, 1, 0, 0}, {0, 0, 1, 0}, {HUGE_VAL, 0, 0, HUGE_VAL} }}, // XW
		{{ {1, 0, 0, 0}, {0, HUGE_VAL, HUGE_VAL, 0}, {0, HUGE_VAL, HUGE_VAL, 0}, {0, 0, 0, 1} }}, //YZ
		{{ {1, 0, 0, 0}, {0, HUGE_VAL, 0, HUGE_VAL}, {0, 0, 1, 0}, {0, HUGE_VAL, 0, HUGE_VAL} }}, //YW
		{{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, HUGE_VAL, HUGE_VAL}, {0, 0, HUGE_VAL, HUGE_VAL} }} //ZW

	}};

	std::array<std::array<std::array<size_t, 2>, N_AXISES>, N_PLAINS> trig_rc_idx {{ //cos, sin, cos, -sin
		{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}}, //XY
		{{{0, 0}, {0, 2}, {2, 2}, {2, 0}}}, //XZ
		{{{0, 0}, {0, 3}, {3, 3}, {3, 0}}}, //XW
		{{{1, 1}, {2, 1}, {2, 2}, {1, 2}}}, //YZ
		{{{1, 1}, {3, 1}, {3, 3}, {1, 3}}}, //YW
		{{{2, 2}, {3, 2}, {3, 3}, {2, 3}}}  //ZW
	}};

public:
	RotationMatrix() = default;
	std::array<std::array<double, N_AXISES>, N_AXISES>& rotateDegree(const size_t plain, double theta) {
		double angle_rad = degreeToRadian(theta);
		double val_cos = cos(angle_rad);
		double val_sine = sin(angle_rad);
		std::array<std::array<double, N_AXISES>, N_AXISES> &rotMatrix = rotPlains[plain];
		std::array<std::array<size_t, 2>, N_AXISES> &trig_rc = trig_rc_idx[plain];
		rotMatrix[trig_rc[0][0]][trig_rc[0][1]] = rotMatrix[trig_rc[2][0]][trig_rc[2][1]] = val_cos;
		rotMatrix[trig_rc[1][0]][trig_rc[1][1]] = val_sine;
		rotMatrix[trig_rc[3][0]][trig_rc[3][1]] = -1*val_sine;
		return rotMatrix;
	}

	std::array<std::array<double, N_AXISES>, N_AXISES>& rotateRadian(const size_t plain, double theta) {
		double val_cos = cos(theta);
		double val_sine = sin(theta);
		std::array<std::array<double, N_AXISES>, N_AXISES> &rotMatrix = rotPlains[plain];
		std::array<std::array<size_t, 2>, N_AXISES> &trig_rc = trig_rc_idx[plain];
		rotMatrix[trig_rc[0][0]][trig_rc[0][1]] = rotMatrix[trig_rc[2][0]][trig_rc[2][1]] = val_cos;
		rotMatrix[trig_rc[1][0]][trig_rc[1][1]] = val_sine;
		rotMatrix[trig_rc[3][0]][trig_rc[3][1]] = -1*val_sine;
		return rotMatrix;
	}

	/** 
	 * Uses angle addition formulas for cosine and sine.
	 * cos(a+b) = cos(a)*cos(b) - sin(a)*sin(b)
	 * sin(a+b) = sin(a)*cos(b) + sin(b)*cos(a)
	 */
	std::array<std::array<double, N_AXISES>, N_AXISES>& rotateIncrement(const size_t plain, double angle_rad) {
		double cos_b = cos(angle_rad);
		double sin_b = sin(angle_rad);
		std::array<std::array<double, N_AXISES>, N_AXISES> &rotMatrix = rotPlains[plain];
		std::array<std::array<size_t, 2>, N_AXISES> &trig_rc = trig_rc_idx[plain];
		double cos_a = rotMatrix[trig_rc[0][0]][trig_rc[0][1]]; 
		double sin_a = rotMatrix[trig_rc[1][0]][trig_rc[1][1]];
		double val_cos = (cos_a*cos_b) - (sin_a*sin_b);
		double val_sin = (sin_a*cos_b) + (sin_b*cos_a); 
		rotMatrix[trig_rc[0][0]][trig_rc[0][1]] = val_cos; 
		rotMatrix[trig_rc[2][0]][trig_rc[2][1]] = val_cos;
		rotMatrix[trig_rc[1][0]][trig_rc[1][1]] = val_sin;
		rotMatrix[trig_rc[3][0]][trig_rc[3][1]] = -1*val_sin;
		return rotMatrix;
	}

	/** 
	 * Uses angle addition formulas for cosine and sine.
	 * cos(a+b) = cos(a)*cos(b) - sin(a)*sin(b)
	 * sin(a+b) = sin(a)*cos(b) + sin(b)*cos(a)
	 */
	std::array<std::array<double, N_AXISES>, N_AXISES>& rotateIncrement_deg(const size_t plain, double incr_deg) {
		double angle_rad = degreeToRadian(incr_deg);
		double cos_b = cos(angle_rad);
		double sin_b = sin(angle_rad);
		std::array<std::array<double, N_AXISES>, N_AXISES> &rotMatrix = rotPlains[plain];
		std::array<std::array<size_t, 2>, N_AXISES> &trig_rc = trig_rc_idx[plain];
		double cos_a = rotMatrix[trig_rc[0][0]][trig_rc[0][1]]; 
		double sin_a = rotMatrix[trig_rc[1][0]][trig_rc[1][1]];
		double val_cos = (cos_a*cos_b) - (sin_a*sin_b);
		double val_sin = (sin_a*cos_b) + (sin_b*cos_a); 
		rotMatrix[trig_rc[0][0]][trig_rc[0][1]] = val_cos; 
		rotMatrix[trig_rc[2][0]][trig_rc[2][1]] = val_cos;
		rotMatrix[trig_rc[1][0]][trig_rc[1][1]] = val_sin;
		rotMatrix[trig_rc[3][0]][trig_rc[3][1]] = -1*val_sin;
		return rotMatrix;
	}


};

#endif