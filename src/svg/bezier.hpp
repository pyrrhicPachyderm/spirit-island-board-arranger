#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <assert.h>
#include <vector>
#include "coord.hpp"

//A BezierPath is assumed to start at (0,0).
//Starting elsewhere is achieved by the origin argument to getPathString.
//A BezierPath consists of N points excluding (0,0),
//and N+1 handles, including a handle for (0,0).
//It uses a smooth path (s in SVG), hence only one handle per point.
//Everything is stored as relative coordinates (lowercase path instruction in SVG).

class BezierPath {
	protected:
		std::vector<Coord> points;
		std::vector<Coord> handles;
		
		bool isValid() {
			if(points.size() <= 1) return false;
			if(handles.size() != points.size() + 1) return false;
			return true;
		}
	public:
		BezierPath(std::vector<Coord> points, std::vector<Coord> handles):
			points(points), handles(handles)
		{
			assert(isValid() && "Invalid BezierPath constructed");
		};
		
		std::string getPathString(Coord origin) const {
			std::string result = "M " + origin.asString() + " ";
			result += "c " + handles[0].asString() + " " + handles[1].asString() + " " + points[0].asString() + " ";
			for(size_t i = 1; i < points.size(); i++) {
				result += "s " + handles[i+1].asString() + " " + points[i].asString() + " ";
			}
			result.pop_back(); //Remove final space;
			return result;
		}
		
		Coord getLength() const {
			Coord result = Coord(0,0);
			for(size_t i = 0; i < points.size(); i++) result += points[i];
			return result;
		}
		
		void reverse() {
			for(size_t i = 0; i < points.size(); i++) handles[i+1] -= points[i];
			for(size_t i = 0; i < handles.size(); i++) handles[i] *= -1;
			for(size_t i = 0; i < points.size(); i++) {
				points[i] *= -1;
				handles[i] += points[i];
			}
			std::reverse(points.begin(), points.end());
			std::reverse(handles.begin(), handles.end());
		}
		
		void rotate(double angle) {
			for(size_t i = 0; i < points.size(); i++) points[i] = points[i].rotated(angle);
			for(size_t i = 0; i < handles.size(); i++) handles[i] = handles[i].rotated(angle);
		}
		
		void append(BezierPath extension) {
			points.push_back(Coord(0,0));
			points.insert(points.end(), extension.points.begin(), extension.points.end());
			handles.insert(handles.end(), extension.handles.begin(), extension.handles.end());
		}
};

#endif
