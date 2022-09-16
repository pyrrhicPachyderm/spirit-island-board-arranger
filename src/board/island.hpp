#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>
#include "board.hpp"

class Island {
	public:
		std::vector<Board> boards;
		
		Island(std::vector<Board> boards):
			boards(boards) {};
	protected:
		//Rotates an island about (0,0,0).
		void rotateCW() {
			for(size_t i = 0; i < boards.size(); i++) boards[i].rotateCW();
		};
		void rotateCCW() {
			for(size_t i = 0; i < boards.size(); i++) boards[i].rotateCCW();
		};
};

inline bool operator==(const Island &lhs, const Island &rhs) {
	if(lhs.boards.size() != rhs.boards.size()) return false;
	for(size_t i = 0; i < lhs.boards.size(); i++) {
		if(lhs.boards[i] != rhs.boards[i]) return false;
	}
	return true;
}

inline bool operator!=(const Island &lhs, const Island &rhs) {
	return !(lhs == rhs);
}

#endif
