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
};

inline bool operator==(const Triangle &lhs, const Triangle &rhs) {
	return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}

inline bool operator!=(const Triangle &lhs, const Triangle &rhs) {
	return !(lhs == rhs);
}

#endif
