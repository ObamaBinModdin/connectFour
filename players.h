#ifndef __Player_H__
#define __Player_H__

#include "game.h"

class Game;

class Player
{
public:

    virtual int getNextTurn(const Game& game) = 0;
};

class HumanPlayer : public Player
{
public:

    // Reads an integer from the terminal and returns it.
    int getNextTurn(const Game& game);
};

class AiPlayer : public Player
{
public:

    int getNextTurn(const Game& game);
};

#endif
