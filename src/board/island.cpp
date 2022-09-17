#include "island.hpp"

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
