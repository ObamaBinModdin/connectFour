#ifndef __Game_H__
#define __Game_H__

#include "players.h"

class Player;

enum class GameState { TurnP1 = 0, TurnP2 = 1, P1Won = 2, P2Won = 3, Draw = 4 };
enum class BoardField { Empty = 0, Player1 = 1, Player2 = 2 };

class Game
{
public:

    static const int BoardWidth = 7;
    static const int BoardHeight = 6;

    // Constructor which takes the players of the game as arguments.
    Game(Player &p1, Player &p2);

    // A function which returns the current state of the game.
    GameState getState() const;

    // A function which returns true if the game is still running, or false if the game concluded with either a draw or a player winning.
    bool isRunning() const;

    // Overrides the ()-operator. Returns the state at the board at the given coordinate.
    BoardField operator() (int x, int y) const;

    // Function which performs the next turn. 
    void nextTurn();

private:

    Player *p1;
    Player *p2;

    BoardField board[BoardHeight][BoardWidth];

    GameState currentGameState = GameState::TurnP1;
    BoardField currentBoardField;

    int lastMoveX = -1;
    int lastMoveY = -1;

    bool checkWin() const;
};

#endif
