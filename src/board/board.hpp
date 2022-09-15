#ifndef BOARD_HPP
#define BOARD_HPP

#include "triangle.hpp"

class Board {
	public:
		Triangle inland;
		Triangle coast;
		Triangle ocean;
		
		Board(Triangle inland, Triangle coast, Triangle ocean):
			inland(inland), coast(coast), ocean(ocean) {};
};

inline bool operator==(const Board &lhs, const Board &rhs) {
	return lhs.inland == rhs.inland && lhs.coast == rhs.coast && lhs.ocean == rhs.ocean;
}

inline bool operator!=(const Board &lhs, const Board &rhs) {
	return !(lhs == rhs);
}

#endif
