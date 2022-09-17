#include "draw.hpp"

#define SVG_DIMENSION 40
#define DISPLAY_DIMENSION "1000px"

#define STROKE_WIDTH "0.01px"
#define STROKE_COLOUR "#000000"
#define OCEAN_COLOUR "#226e93"
#define LAND_COLOUR "#dedede"

#define TRIANGLE_SIDE_LENGTH 2
#define TRIANGLE_HEIGHT (TRIANGLE_SIDE_LENGTH*sqrt(3)/2)
#define TRIANGLE_RADIUS (TRIANGLE_SIDE_LENGTH/sqrt(3))

//NB: Must remember throughout that the SVG y-axis is reversed: positive is downwards.

static const BezierPath HALF_EDGE_CURVE = BezierPath(
	std::vector<Coord>({
		Coord(0.209689, -0.0348797),
		Coord(0.104781, 0.00287341),
		Coord(0.0292377, 0.0243585),
		Coord(0.0135609, 0.0323406),
		Coord(0.0276751, 0.0363252),
		Coord(0.0633092, 0.0372937),
		Coord(0.167919, 0.0492395),
		Coord(0.0848846, -0.00986544),
		Coord(0.0286009, -0.0457103),
		Coord(0.0236031, -0.0363335),
		Coord(0.0950283, -0.0427871),
		Coord(0.151711, -0.01285487)
	}),
	std::vector<Coord>({
		Coord(0,0),
		Coord(0.160225, -0.0313781),
		Coord(0.0933104, -0.00649522),
		Coord(0.0203176, 0.0107248),
		Coord(0.00942151, 0.0235768),
		Coord(0.017433, 0.0300943),
		Coord(0.0347535, 0.0246245),
		Coord(0.113328, 0.0463912),
		Coord(0.0737458, -0.00113563),
		Coord(0.0252352, -0.0270791),
		Coord(0.0153874, -0.0306438),
		Coord(0.0623204, -0.0380503),
		Coord(0.151711, -0.01285487)
	})
);

static const BezierPath OCEAN_INNER = BezierPath(
	std::vector<Coord>({
		Coord(-0.0244142, -0.0219468),
		Coord(-0.0302301, -0.0209329),
		Coord( -0.0489013, 0.0293877),
		Coord(-0.139988, -0.0385226),
		Coord(-0.0173319, 0.0017774),
		Coord(-0.126937, 0.0685661),
		Coord(-0.0515361, -0.00264262),
		Coord(-0.184731, -0.0519184),
		Coord(-0.0456512, 0.00272949),
		Coord(-0.216059, 0.0542701),
		Coord(-0.0859009, -9.39181e-05),
		Coord(-0.0721006, -0.0264586),
		Coord(-0.216798, 0.0988727),
		Coord(-0.0985414, 0.00554539),
		Coord(-0.113048, -0.0480607),
		Coord(-0.0621076, -0.00107301),
		Coord(-0.144729, 0.0272099),
		Coord(-0.0652357, -0.0572705),
		Coord(-0.0172083, -0.10352),
		Coord(-0.0191417, -0.0520393),
		Coord(-0.21941, 0.136139)
	}),
	std::vector<Coord>({
		Coord(0,0),
		Coord(-0.0116146, -0.013443),
		Coord(-0.0296499, -0.0209797),
		Coord(-0.0160691, 0.0291536),
		Coord(-0.131336, -0.0375318),
		Coord(-0.0137656, 0.000373324),
		Coord(-0.114437, 0.0651418),
		Coord(-0.0317643, 0.00267854),
		Coord(-0.174766, -0.0507301),
		Coord(-0.0263649, -0.00660948),
		Coord(-0.18449, 0.0470837),
		Coord(-0.0537687, 0.0132678),
		Coord(-0.0495719, -0.0245098),
		Coord(-0.187745, 0.0927347),
		Coord(-0.0782287, 0.00817087),
		Coord(-0.0964148, -0.0438663),
		Coord(-0.0434399, -0.00743291),
		Coord(-0.109424, 0.0326105),
		Coord(-0.0517955, -0.0304882),
		Coord(-0.0148602, -0.0899853),
		Coord(-0.0185593, -0.0519926),
		Coord(-0.152223, 0.082167)
	})
);

static const BezierPath OCEAN_OUTER = BezierPath(
	std::vector<Coord>({
		Coord(-0.024414, -0.0219468),
		Coord(-0.03023, -0.0209329),
		Coord(-0.222691, -0.137524),
		Coord(-0.057044, -0.0595566),
		Coord(-0.024961, -0.0465448),
		Coord(-0.175539, 0.0118282),
		Coord(-0.179727, -0.007126),
		Coord(-0.0409272, -0.0432331),
		Coord(-0.25211662, 0.13443464),
		Coord(-0.10207301, -0.051869),
		Coord(-0.122514, 0.0173154),
		Coord(-0.15260324, 0.0339472),
		Coord(-0.044393, -0.0403538),
		Coord( -0.12127293, -0.002863),
		Coord(-0.12400938, 0.0447317),
		Coord(-0.1060753, 0.0535716),
		Coord(-0.21941, 0.13613883)
	}),
	std::vector<Coord>({
		Coord(0,0),
		Coord(-0.0116145, -0.0134429),
		Coord(-0.0294696, -0.0204852),
		Coord(-0.196415, -0.118545),
		Coord( -0.045537, -0.0456326),
		Coord(-0.017039, -0.0380879),
		Coord(-0.107666, 0.00085637),
		Coord(-0.150995, 0.0075049),
		Coord(-0.0258234, -0.0363658),
		Coord(-0.1653918, 0.13482424),
		Coord(-0.0785759, -0.0436849),
		Coord(-0.0766267, 0.005914),
		Coord(-0.13007449, 0.0358962),
		Coord(-0.0182549, -0.0248894),
		Coord(-0.0888453, -0.0117086),
		Coord(-0.0719661, 0.0216675),
		Coord(-0.10563578, 0.0533475),
		Coord(-0.152223, 0.082167)
	})
);

static BezierPath fullEdgeCurve() {
	BezierPath path = HALF_EDGE_CURVE;
	BezierPath secondHalf = HALF_EDGE_CURVE;
	secondHalf.reverse();
	secondHalf.rotate(M_PI);
	path.append(secondHalf);
	return path;
}

static BezierPath threeEdgeCurve() {
	BezierPath edge = fullEdgeCurve();
	BezierPath path = edge;
	edge.rotate(-M_PI/3);
	path.append(edge);
	edge.rotate(-2*M_PI/3);
	path.append(edge);
	return path;
}

static BezierPath boardCurve(bool isInner) {
	BezierPath path = threeEdgeCurve();
	BezierPath ocean = isInner ? OCEAN_INNER : OCEAN_OUTER;
	ocean.rotate(-M_PI/3);
	path.append(ocean);
	return path;
}

//With angle = 0, the coast on the left facing slightly upwards,
//such that the letter in the ocean is upright.
//Origin is the bottom edge of the ocean, the land 3 corner.
SVGElement drawBoard(Coord origin, double angle) {
	SVGElement innerPathElement = SVGElement("path");
	innerPathElement.setAttribute("stroke", STROKE_COLOUR);
	innerPathElement.setAttribute("stroke-width", STROKE_WIDTH);
	SVGElement outerPathElement = innerPathElement;
	innerPathElement.setAttribute("fill", LAND_COLOUR);
	outerPathElement.setAttribute("fill", OCEAN_COLOUR);
	
	BezierPath innerPath = boardCurve(true);
	BezierPath outerPath = boardCurve(false);
	innerPath.rotate(angle);
	outerPath.rotate(angle);
	innerPathElement.setAttribute("d", innerPath.getPathString(origin));
	outerPathElement.setAttribute("d", outerPath.getPathString(origin));
	
	SVGElement element = SVGElement("g");
	element.addChild(outerPathElement);
	element.addChild(innerPathElement);
	return element;
}

Coord getCentre(const Triangle &tri) {
	double x = (0.5 * tri.a - 0.5 * tri.c) * TRIANGLE_SIDE_LENGTH;
	double y = (tri.b * -TRIANGLE_HEIGHT) + (TRIANGLE_HEIGHT/2 - TRIANGLE_RADIUS) * (tri.isPointUp() ? -1 : 1);
	return Coord(x, y);
}

SVGElement drawBoard(const Board &board) {
	std::array<Triangle, 3> coastNeighbours = board.coast.getNeighbours();
	Board::Direction oceanDirection = coastNeighbours[0] == board.ocean ? 0 : (coastNeighbours[1] == board.ocean ? 1 : 2);
	double boardDirection = (board.coast.isPointUp() ? 0 : M_PI) - 2 * M_PI / 3 * oceanDirection;
	double cornerDirection = boardDirection + 5 * M_PI / 6;
	
	Coord centre = getCentre(board.coast);
	Coord corner = centre + Coord(TRIANGLE_RADIUS, 0).rotated(cornerDirection);
	
	return drawBoard(corner, boardDirection);
}

SVG drawIsland(const Island &island) {
	SVG result = SVG(-SVG_DIMENSION/2, -SVG_DIMENSION/2, SVG_DIMENSION, SVG_DIMENSION, DISPLAY_DIMENSION, DISPLAY_DIMENSION);
	for(const Board &board: island.boards) {
		result.addElement(drawBoard(board));
	}
	return result;
}
