#ifndef COORD_HPP
#define COORD_HPP

#include <math.h>
#include <string>

class Coord {
	public:
		double x;
		double y;
		
		Coord():
			x(0), y(0) {};
		Coord(double x, double y):
			x(x), y(y) {};
		
		std::string asString() const {
			return std::to_string(x) + "," + std::to_string(y);
		}
		
		//Returns a coordinate rotated anticlockwise about (0,0); argument in radians.
		//Note that the reversed y axis of SVGs makes this visually clockwise rotation.
		Coord rotated(double angle) {
			return Coord(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
		}
};

inline bool operator==(const Coord &lhs, const Coord &rhs) {
	return lhs.x == rhs.y && lhs.x == rhs.y;
}

inline bool operator!=(const Coord &lhs, const Coord &rhs) {
	return !(lhs == rhs);
}

inline Coord &operator*=(Coord &coord, double scalar) {
	coord.x *= scalar;
	coord.y *= scalar;
	return coord;
}

inline Coord operator*(Coord coord, double scalar) {
	return coord *= scalar;
}

inline Coord operator*(double scalar, Coord coord) {
	return coord *= scalar;
}

inline Coord &operator+=(Coord &lhs, const Coord &rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

inline Coord operator+(Coord lhs, const Coord &rhs) {
	return lhs += rhs;
}

inline Coord operator-(const Coord &coord) {
	return coord * -1;
}

inline Coord &operator-=(Coord &lhs, const Coord &rhs) {
	return lhs += -rhs;
}

inline Coord operator-(Coord lhs, const Coord &rhs) {
	return lhs -= rhs;
}

#endif
