#ifndef __ENCODER_HPP
#define __ENCODER_HPP
#include <cstdint>
#include <queue>
#include <vector>
#include <variant>
#include <optional>
struct encoderNode {
	int8_t faceIDs[3];  //current[0], prev[1], next[2]
	uint64_t opCode;
	uint8_t arg_type;
	uint8_t arg_count;
	std::optional<std::variant<std::vector<int32_t>, std::vector<float>, std::vector<double>, int32_t, float, double, uint64_t>> args; 
	encoderNode(int8_t currID, int8_t prevID, int8_t nextID) : faceIDs({currID, prevID, nextID}), opCode(0), arg_type(0), arg_count(0) {}
	encoderNode(int8_t currID, int8_t prevID, int8_t nextID, uint64_t op, uint8_t t_arg, uint8_t n_arg) : faceIDs({currID, prevID, nextID}), opCode(op), arg_type(t_arg), arg_count(n_arg) {}
};

class Encoder {
public:
	Encoder() = default;
protected:
	//std::queue<uint64_t>
	enum class opCodes : uint64_t {
		SECT = 0x00000000,
		RSPI = 0x52535049,
		RSPF = 0x52535046,
		RSPD = 0x52535044,
		SCIU = 0x53434955, 
		SCFU = 0x53434655,
		SCDU = 0x53434455,
		SCVI = 0x53435649,
		SCVF = 0x53435646,
		SCVU = 0x53435644,
		DATA = 0x44415441
	};

};

#endif