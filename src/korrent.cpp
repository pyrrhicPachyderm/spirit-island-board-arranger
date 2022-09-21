#include "korrent.hpp"

static std::string getKorrentBoard(const Board &board) {
	//A Korrent ocean consists of two parts.
	//Firstly, the coordinates of the ocean.
	//Secondly, a facing: the vector from the ocean to the coastal land triangle.
	//Note that Korrent's triangle coordinates treat (0,0,0) as a downward-facing triangle.
	//We treat (1,0,0) as downward-facing, so we subtract 1 from the first component.
	return "String(["
		+ std::to_string(board.ocean.a - 1) + ","
		+ std::to_string(board.ocean.b) + ","
		+ std::to_string(board.ocean.c)
		+ "]),["
		+ std::to_string(board.coast.a - board.ocean.a) + ","
		+ std::to_string(board.coast.b - board.ocean.b) + ","
		+ std::to_string(board.coast.c - board.ocean.c)
		+ "]";
}

std::string getKorrentIsland(const Island &island) {
	std::string result = "{oceans: new Map()";
	for(const Board &board: island.boards) {
		result += ".set(" + getKorrentBoard(board) + ")";
	}
	result += "}";
	return result;
}

std::string getKorrentIslandsOfSize(const std::vector<std::vector<Island>> islands) {
	std::string result = "{\n";
	for(size_t numBoards = 1; numBoards < islands.size(); numBoards++) {
		result += "\t" + std::to_string(numBoards) + ":[\n";
		for(size_t i = 0; i < islands[numBoards].size(); i++) {
			result += "\t\t" + getKorrentIsland(islands[numBoards][i]) + ",\n";
		}
		result += "\t],\n";
	}
	result += "}\n";
	return result;
}
