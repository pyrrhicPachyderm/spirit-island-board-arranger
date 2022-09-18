#include "island.hpp"

void Island::canonicaliseWithoutRotation() {
	std::sort(boards.begin(), boards.end());
	Triangle refTri = boards[0].inland;
	translate(-refTri.a, -refTri.b);
}

void Island::canonicalise() {
	canonicaliseWithoutRotation();
	
	Island copy = *this;
	for(size_t i = 0; i < 5; i++) {
		copy.rotateCW();
		copy.canonicaliseWithoutRotation();
		if(copy < *this) boards = copy.boards;
	}
}
