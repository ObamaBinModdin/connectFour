#include "players.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int HumanPlayer::getNextTurn(const Game& game)
{
    int col;

    std::cin >> col;

    return col;
}

int AiPlayer::getNextTurn(const Game& game)
{
    int col = rand() % game.BoardWidth + 1;

    std::cout << col << std::endl;

    return col;
}
