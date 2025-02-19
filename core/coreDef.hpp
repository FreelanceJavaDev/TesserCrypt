#ifndef __CORE_DEFS_HPP
#define __CORE_DEFS_HPP
#if __cplusplus >= 202002L
#include <numbers>
#elif __cplusplus <= 201703L
#define _USE_MATH_DEFINES
#include <cmath>
const double pi_d = std::acos(-1.0);
const double DEG_90 = M_PI/2.0;
#endif
enum AXISES : size_t { X, Y, Z, W, N_AXISES };
enum PLAINS : size_t {XY, XZ, XW, YZ, YW, ZW, N_PLAINS};
enum POINTS : size_t {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, N_POINTS};


#endif