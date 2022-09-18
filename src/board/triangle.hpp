#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <array>

//Using the "three lane" implementation outlined in:
//https://www.boristhebrave.com/2021/05/23/triangle-grids

class Triangle {
	public:
		int a;
		int b;
		int c;
		
		Triangle(int a, int b, int c):
			a(a), b(b), c(c) {};
		
		bool isPointUp() const {
			return a + b + c == 2;
		}
		
		//NB: Neighbours are always given in anti-clockwise order.
		//NB: t.getNeighbours()[i].getNeighbours()[i] == t, for any i in [0,2].
		std::array<Triangle, 3> getNeighbours() const {
			if(isPointUp()) {
				return {
					Triangle(a-1, b, c),
					Triangle(a, b-1, c),
					Triangle(a, b, c-1)
				};
			} else {
				return {
					Triangle(a+1, b, c),
					Triangle(a, b+1, c),
					Triangle(a, b, c+1)
				};
			}
		}
		
		void translate(int aOffset, int bOffset) {
			//To avoid flipping triangles or creating invalid triangles:
			//aOffset + bOffset + cOffset = 0.
			int cOffset = - aOffset - bOffset;
			a += aOffset;
			b += bOffset;
			c += cOffset;
		}
		
		//Rotates a triangle about (0,0,0).
		void rotateCW() {
			if(isPointUp()) {
				*this = Triangle((a + b - c) / 2, (b + c - a) / 2, (c + a - b) / 2);
			} else {
				*this = Triangle(a + b, b + c, c + a);
			}
		};
		void rotateCCW() {
			if(isPointUp()) {
				*this = Triangle((a + c - b) / 2, (b + a - c) / 2, (c + b - a) / 2);
			} else {
				*this = Triangle(a + c, b + a, c + b);
			}
		};
};

inline bool operator==(const Triangle &lhs, const Triangle &rhs) {
	return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}

inline bool operator!=(const Triangle &lhs, const Triangle &rhs) {
	return !(lhs == rhs);
}

//Impose a total order on triangles.
//It means nothing, but will be used in canonicalising islands.
inline bool operator<(const Triangle &lhs, const Triangle &rhs) {
	if(lhs.a < rhs.a) return true;
	if(lhs.a > rhs.a) return false;
	if(lhs.b < rhs.b) return true;
	if(lhs.b > rhs.b) return false;
	return lhs.c < rhs.c;
}

inline bool operator<=(const Triangle &lhs, const Triangle &rhs) {
	return lhs < rhs || lhs == rhs;
}

inline bool operator>(const Triangle &lhs, const Triangle &rhs) {
	return !(lhs <= rhs);
}

inline bool operator>=(const Triangle &lhs, const Triangle &rhs) {
	return !(lhs < rhs);
}

#endif
