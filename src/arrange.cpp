#include <stdio.h>
#include "board/island.hpp"

#define NUM_MANDATORY_ARGS 1

//Prints the usage spiel to stderr.
static void printUsage(int argc, const char **argv) {
	//Making of use of concatenated string literals in the following:
	fprintf(stderr, "Usage: %s MAX_NUM_BOARDS\n\n"
		"\tFinds all island layouts with up to MAX_NUM_BOARDS.\n"
		,
		argv[0]
	);
}

int main(int argc, const char **argv) {
	if(argc-1 != NUM_MANDATORY_ARGS) {
		printUsage(argc, argv);
		exit(1);
	}
	size_t maxNumBoards = strtoll(argv[1], NULL, 0);
	
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
	
	return 0;
}
