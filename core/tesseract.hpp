#ifndef __TESSERACT_HPP
#define __TESSERACT_HPP
#include <array>

class Tesseract {
private:
	std::array<std::array<double, 4>, 16> vertexes = {{
		{-1, -1, -1, -1}, 
		{ 1, -1, -1, -1}, 
		{ 1, -1,  1, -1}, 
		{-1, -1,  1, -1}, 
		{-1,  1, -1, -1}, 
		{ 1,  1, -1, -1}, 
		{ 1,  1,  1, -1}, 
		{-1,  1,  1, -1}, 
		{-1, -1, -1,  1}, 
		{ 1, -1, -1,  1}, 
		{ 1, -1,  1,  1}, 
		{-1, -1,  1,  1}, 
		{-1,  1, -1,  1}, 
		{ 1,  1, -1,  1}, 
		{ 1,  1,  1,  1}, 
		{-1,  1,  1,  1}
	}};
public:
};

#endif