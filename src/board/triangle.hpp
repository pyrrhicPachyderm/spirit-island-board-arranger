#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <array>

//Using the "three lane" implementation outlined in:
//https://www.boristhebrave.com/2021/05/23/triangle-grids
//Except that (0,0,0) is a triangle (pointing down) to make rotation easier.

class Triangle {
	public:
		int a;
		int b;
		int c;
		
		Triangle(int a, int b, int c):
			a(a), b(b), c(c) {};
		
		bool isPointUp() const {
			return a + b + c == 1;
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
		
		//Rotates a triangle about (0,0,0).
		void rotateCW() {
			int tmp = a;
			a = c;
			c = b;
			b = tmp;
		};
		void rotateCCW() {
			int tmp = a;
			a = b;
			b = c;
			c = tmp;
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
