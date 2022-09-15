#ifndef BOARD_HPP
#define BOARD_HPP

#include <stdint.h>
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
	protected:
		typedef uint8_t Direction;
		
		static Board getNeighbourOverEdge0(const Triangle &tri, Direction edge) {
			Triangle newCoast = tri.getNeighbours()[edge];
			Triangle newInland = newCoast.getNeighbours()[(edge+1)%3];
			Triangle newOcean = newCoast.getNeighbours()[(edge+2)%3];
			return Board(newInland, newCoast, newOcean);
		}
		static Board getNeighbourOverEdge1(const Triangle &tri, Direction edge) {
			Triangle newInland = tri.getNeighbours()[edge];
			Triangle newCoast = newInland.getNeighbours()[(edge+2)%3];
			Triangle newOcean = newCoast.getNeighbours()[edge];
			return Board(newInland, newCoast, newOcean);
		}
		static Board getNeighbourOverEdge2(const Triangle &tri, Direction edge) {
			Triangle newInland = tri.getNeighbours()[edge];
			Triangle newCoast = newInland.getNeighbours()[(edge+1)%3];
			Triangle newOcean = newCoast.getNeighbours()[(edge+2)%3];
			return Board(newInland, newCoast, newOcean);
		}
		static std::array<Board, 3> getNeighboursOverEdge(const Triangle &tri, Direction edge) {
			//Edge is an index 0-2, the neighbour of tri to generate boards in.
			return {getNeighbourOverEdge0(tri, edge), getNeighbourOverEdge1(tri, edge), getNeighbourOverEdge2(tri, edge)};
		}
		
		std::array<std::pair<Triangle, Direction>, 3> getOpenEdges() {
			std::array<Triangle, 3> inlandNeighbours = inland.getNeighbours();
			Direction inlandToCoastEdge = inlandNeighbours[0] == coast ? 0 : (inlandNeighbours[1] == coast ? 1 : 2);
			return {
				std::make_pair(inland, (inlandToCoastEdge + 1) % 3),
				std::make_pair(inland, (inlandToCoastEdge + 2) % 3),
				std::make_pair(coast, (inlandToCoastEdge + 2) % 3)
			};
		}
	public:
		std::array<Board, 9> getNeighbours() {
			std::array<std::pair<Triangle, Direction>, 3> openEdges = getOpenEdges();
			std::array<Board, 3> neighbours0 = getNeighboursOverEdge(openEdges[0].first, openEdges[0].second);
			std::array<Board, 3> neighbours1 = getNeighboursOverEdge(openEdges[1].first, openEdges[1].second);
			std::array<Board, 3> neighbours2 = getNeighboursOverEdge(openEdges[2].first, openEdges[2].second);
			return {
				neighbours0[0], neighbours0[1], neighbours0[2],
				neighbours1[0], neighbours1[1], neighbours1[2],
				neighbours2[0], neighbours2[1], neighbours2[2]
			};
		}
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
