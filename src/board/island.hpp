#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>
#include <algorithm>
#include "board.hpp"

class Island {
	public:
		std::vector<Board> boards;
		
		Island():
			boards({Board()}) {};
		
		Island(std::vector<Board> boards):
			boards(boards) {};
	protected:
		void translate(int aOffset, int bOffset) {
			for(size_t i = 0; i < boards.size(); i++) boards[i].translate(aOffset, bOffset);
		};
		
		//Rotates an island about (0,0,0).
		void rotateCW() {
			for(size_t i = 0; i < boards.size(); i++) boards[i].rotateCW();
		};
		void rotateCCW() {
			for(size_t i = 0; i < boards.size(); i++) boards[i].rotateCCW();
		};
		
		void canonicaliseWithoutRotation();
		
		bool doesBoardCollide(const Board &board) const {
			for(size_t i = 0; i < boards.size(); i++) {
				if(doBoardsCollide(board, boards[i])) return true;
			}
			return false;
		}
	public:
		//Rearranges the board, by translation, rotation, and sorting the vector, into a canonical form.
		void canonicalise();
		
		//Returns all the boards (not necessarily unique) that can be obtained by adding one board to this board.
		std::vector<Island> expand() const {
			std::vector<Island> result;
			for(size_t i = 0; i < boards.size(); i++) {
				std::array<Board, 9> newBoards = boards[i].getNeighbours();
				for(size_t j = 0; j < newBoards.size(); j++) {
					if(doesBoardCollide(newBoards[j])) continue;
					result.push_back(*this);
					result.back().boards.push_back(newBoards[j]);
				}
			}
			return result;
		}
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

//Impose a total order on islands.
//It means nothing, but will be used in canonicalising.
inline bool operator<(const Island &lhs, const Island &rhs) {
	if(lhs.boards.size() < rhs.boards.size()) return true;
	if(lhs.boards.size() > rhs.boards.size()) return false;
	for(size_t i = 0; i < lhs.boards.size(); i++) {
		if(lhs.boards[i] < rhs.boards[i]) return true;
		if(lhs.boards[i] > rhs.boards[i]) return false;
	}
	return false;
}

inline bool operator<=(const Island &lhs, const Island &rhs) {
	return lhs < rhs || lhs == rhs;
}

inline bool operator>(const Island &lhs, const Island &rhs) {
	return !(lhs <= rhs);
}

inline bool operator>=(const Island &lhs, const Island &rhs) {
	return !(lhs < rhs);
}

#endif
