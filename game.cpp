#include "game.h"
#include <stdlib.h>

Game::Game(Player& p1, Player& p2)
{
    this->p1 = &p1;
    this->p2 = &p2;

    for (int x = 0; x < this->BoardHeight; x++)
    {
        for (int y = 0; y < this->BoardWidth; y++)
        {
            this->board[x][y] = BoardField::Empty;
        }
    }

    nextTurn();
}

GameState Game::getState() const
{
    return this->currentGameState;
}

//Checks the stones near the last move to determine if the last move caused a win.
bool Game::isRunning() const
{
    if (checkWin() == true)
    {
        return false;
    }

    for (int row = 0; row < BoardHeight; row++)
    {
        for (int col = 0; row < BoardWidth; col++)
        {
            if (board[row][col] == BoardField::Empty)
            {
                return true;
            }
        }
    }

    return false;
}

BoardField Game::operator() (int x, int y) const
{
    if (x >= BoardWidth || y >= BoardHeight || x < 0 || y < 0)
    {
        return BoardField::Empty;
    }

    return this->board[y][x];
}

void Game::nextTurn()
{
    int col;
    bool validMove = false;
    
    do
    {
        if (getState() == GameState::TurnP1)
        {
            col = p1->getNextTurn(*this);
        }
        else if (getState() == GameState::TurnP2)
        {
            col = p2->getNextTurn(*this);
        }

        col--;

        if (col >= BoardWidth || col < 0)
        {
            continue;
        }

        if (board[0][col] == BoardField::Empty)
        {
            validMove = true;
        }
    } while (validMove == false);

    for (int row = BoardHeight - 1; row >= 0; row--)
    {
        if (board[row][col] == BoardField::Empty)
        {
            if (getState() == GameState::TurnP1)
            {
                board[row][col] = BoardField::Player1;
            }
            else
            {
                board[row][col] = BoardField::Player2;
            }

            lastMoveX = col;
            lastMoveY = row;

            break;
        }
    }

    if (isRunning() == false && checkWin() == true)
    {
        if (getState() == GameState::TurnP1)
        {
            currentGameState = GameState::P1Won;
        }
        else
        {
            currentGameState = GameState::P2Won;
        }
    }
    else if (isRunning() == false && checkWin() == false)
    {
        currentGameState = GameState::Draw;
    }
    else
    {
        if (getState() == GameState::TurnP1)
        {
            currentGameState = GameState::TurnP2;
        }
        else
        {
            currentGameState = GameState::TurnP1;
        }
    }
}

bool Game::checkWin() const
{
    // Check horizontal win
    for (int row = 0; row < BoardHeight - 3; row++)
    {
        for (int col = 0; col < BoardWidth; col++)
        {
            if (board[col][row] == BoardField::Player1 && board[col][row + 1] == BoardField::Player1 && board[col][row + 2] == BoardField::Player1 && board[col][row + 3] == BoardField::Player1)
            {
                return true;
            }
            else if (board[col][row] == BoardField::Player2 && board[col][row + 1] == BoardField::Player2 && board[col][row + 2] == BoardField::Player2 && board[col][row + 3] == BoardField::Player2)
            {
                return true;
            }
        }
    }

    // Check vertical win
    for (int col = 0; col < BoardWidth - 3; col++)
    {
        for (int row = 0; row < BoardHeight; row++)
        {

            if (board[col][row] == BoardField::Player1 && board[col + 1][row] == BoardField::Player1 && board[col + 2][row] == BoardField::Player1 && board[col + 3][row] == BoardField::Player1)
            {
                return true;
            }
            else if (board[col][row] == BoardField::Player2 && board[col + 1][row] == BoardField::Player2 && board[col + 2][row] == BoardField::Player2 && board[col + 3][row] == BoardField::Player2)
            {
                return true;
            }
        }
    }

    // Diagonal check (\)
    for (int col = 3; col < BoardWidth; col++)
    {
        for (int row = 0; row < BoardHeight - 3; row++)
        {
            if (board[col][row] == BoardField::Player1 && board[col - 1][row + 1] == BoardField::Player1 && board[col - 2][row + 2] == BoardField::Player1 && board[col - 3][row + 3] == BoardField::Player1)
            {
                return true;
            }
            else if (board[col][row] == BoardField::Player2 && board[col - 1][row + 1] == BoardField::Player2 && board[col - 2][row + 2] == BoardField::Player2 && board[col - 3][row + 3] == BoardField::Player2)
            {
                return true;
            }
        }
    }

    // Diagonal check (/)
    for (int col = 3; col < BoardWidth; col++)
    {
        for (int row = 3; row < BoardHeight; row++)
        {
            if (board[col][row] == BoardField::Player1 && board[col - 1][row - 1] == BoardField::Player1 && board[col - 2][row - 2] == BoardField::Player1 && board[col - 3][row - 3] == BoardField::Player1)
            {
                return true;
            }
            else if (board[col][row] == BoardField::Player2 && board[col - 1][row - 1] == BoardField::Player2 && board[col - 2][row - 2] == BoardField::Player2 && board[col - 3][row - 3] == BoardField::Player2)
            {
                return true;
            }
        }
    }
}

