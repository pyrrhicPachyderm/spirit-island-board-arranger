#include <stdio.h>
#include <fstream>
#include <filesystem>
#include "board/island.hpp"
#include "draw.hpp"

#define MIN_NUM_ARGS 1
#define MAX_NUM_ARGS 2

//Prints the usage spiel to stderr.
static void printUsage(int argc, const char **argv) {
	//Making of use of concatenated string literals in the following:
	fprintf(stderr, "Usage: %s MAX_NUM_BOARDS [OUTPUT_DIR]\n\n"
		"\tFinds all island layouts with up to MAX_NUM_BOARDS.\n"
		"\tIf given OUTPUT_DIR, prints each layout as an SVG.\n"
		,
		argv[0]
	);
}

std::string paddedNumString(size_t num, size_t maxNum) {
	size_t width = std::to_string(maxNum).size();
	std::string result = std::to_string(num);
	if(result.size() < width) result.insert(0, width - result.size(), '0');
	return result;
}

void printBoardSVGs(std::vector<std::vector<Island>> islands, std::string outputDir) {
	std::filesystem::create_directory(outputDir);
	for(size_t numBoards = 1; numBoards < islands.size(); numBoards++) {
		std::string dirName = paddedNumString(numBoards, islands.size()-1) + "-board";
		std::filesystem::path dirPath = std::filesystem::path(outputDir);
		dirPath /= std::filesystem::path(dirName);
		std::filesystem::create_directory(dirPath);
		for(size_t i = 0; i < islands[numBoards].size(); i++) {
			std::string fileName = paddedNumString(i, islands[numBoards].size()-1) + ".svg";
			std::filesystem::path filePath = dirPath / std::filesystem::path(fileName);
			std::ofstream fileStream = std::ofstream(filePath);
			
			SVG svg = drawIsland(islands[numBoards][i]);
			fileStream << svg.asString();
		}
	}
}

int main(int argc, const char **argv) {
	if(argc-1 < MIN_NUM_ARGS || argc-1 > MAX_NUM_ARGS) {
		printUsage(argc, argv);
		exit(1);
	}
	size_t maxNumBoards = strtoll(argv[1], NULL, 0);
	std::string outputDir;
	if(argc-1 >= 2) outputDir = argv[2];
	
	std::vector<std::vector<Island>> islands = {{}, {Island()}};
	
	for(size_t numBoards = 2; numBoards <= maxNumBoards; numBoards++) {
		islands.push_back(std::vector<Island>());
		for(size_t i = 0; i < islands[numBoards-1].size(); i++) {
			std::vector<Island> newIslands = islands[numBoards-1][i].expand();
			islands[numBoards].insert(islands[numBoards].end(), newIslands.begin(), newIslands.end());
		}
		for(size_t i = 0; i < islands[numBoards].size(); i++) {
			islands[numBoards][i].canonicalise();
		}
		std::sort(islands[numBoards].begin(), islands[numBoards].end());
		auto last = std::unique(islands[numBoards].begin(), islands[numBoards].end());
		islands[numBoards].erase(last, islands[numBoards].end());
		
		printf("%lu: %lu\n", numBoards, islands[numBoards].size());
	}
	
	if(!outputDir.empty()) printBoardSVGs(islands, outputDir);
	
	return 0;
}
