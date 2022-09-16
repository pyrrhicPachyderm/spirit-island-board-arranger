#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>
#include <algorithm>
#include "board.hpp"

class Island {
	public:
		std::vector<Board> boards;
		
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
	public:
		//Rearranges the board, by translation, rotation, and sorting the vector, into a canonical form.
		void canonicalise();
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

//Canonicalisation functions defined here, as they use the comparison functions.
void Island::canonicaliseWithoutRotation() {
	std::sort(boards.begin(), boards.end());
	Triangle refTri = boards[0].inland;
	translate(-refTri.a, -refTri.b);
}

void Island::canonicalise() {
	canonicaliseWithoutRotation();
	
	Island copyCW = *this;
	copyCW.rotateCW();
	copyCW.canonicaliseWithoutRotation();
	Island copyCCW = *this;
	copyCCW.rotateCCW();
	copyCCW.canonicaliseWithoutRotation();
	
	if(copyCW < *this) boards = copyCW.boards;
	if(copyCCW < *this) boards = copyCCW.boards;
}

#endif
