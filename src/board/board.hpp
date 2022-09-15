#ifndef BOARD_HPP
#define BOARD_HPP

#include "triangle.hpp"

class Board {
	public:
		Triangle inland;
		Triangle coast;
		Triangle ocean;
		//NB: With respect to coast, ocean must be anticlockwise of inland.
		//i.e. If coast.getNeighbours()[i] == inland, then coast.getNeighbours()[(i+1)%3] == ocean.
		
		Board(Triangle inland, Triangle coast, Triangle ocean):
			inland(inland), coast(coast), ocean(ocean) {};
};

inline bool operator==(const Board &lhs, const Board &rhs) {
	return lhs.inland == rhs.inland && lhs.coast == rhs.coast && lhs.ocean == rhs.ocean;
}

inline bool operator!=(const Board &lhs, const Board &rhs) {
	return !(lhs == rhs);
}

inline bool doBoardsCollide(const Board &lhs, const Board &rhs) {
	return lhs.inland == rhs.inland || lhs.inland == rhs.coast || lhs.inland == rhs.ocean
		|| lhs.coast == rhs.inland || lhs.coast == rhs.coast || lhs.coast == rhs.ocean
		|| lhs.ocean == rhs.inland || lhs.ocean == rhs.coast || lhs.ocean == rhs.ocean;
}

#endif
