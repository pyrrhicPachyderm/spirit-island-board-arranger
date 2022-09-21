#ifndef KORRENT_HPP
#define KORRENT_HPP

#include <string>
#include "board/island.hpp"

//Outputs boards and islands in JavaScript format for importing into Korrent's board arranger:
//https://spirit-board.tiiny.site

extern std::string getKorrentIsland(const Island &island);

extern std::string getKorrentIslandsOfSize(const std::vector<std::vector<Island>> islands);

#endif
