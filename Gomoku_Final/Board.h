#pragma once
#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// This file has Board class.

const int boardSize = 15;


class Board
{
private:

	
	int count = 0; // This holds how many peoaces are connected.
	int board[boardSize][boardSize]; //The board has a intger as a status
	int player = 1; //This determins the player to play, 1 = player1 , 2 = player2
	bool winning = false; //This determins if the current position meets the winning condtion.
	void search_horizontal(int, int, int);
	void search_vertical(int, int, int);
	void search_slanting_leftToRight(int, int, int);
	void search_slanting_rightToLeft(int, int, int);
public:
	Board();
	int get_BoardStatus(int, int) const;
	bool play(int, int);
	int currentPlayer() const;
	bool checkWinning();
	void randomPlay();
};

// This constractor initialize the borad posiiton.
Board::Board()
{
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize; row++)
		{
			board[column][row] = 0;
		}
	}
}

// This gets a status of the board at given coordinates.
int Board::get_BoardStatus(int column, int row) const
{
	return board[column][row];
}

// This allow the move to be played at given coordinates.
// If an illegal move is played, It return false.
bool Board::play(int column, int row)
{
	bool played = true;
	if (board[column][row] != 0 || (column >= boardSize || row >= boardSize || column < 0 || row < 0))
	{
		cout << "This move is illegal" << endl;
		played = false;
	}
	else
	{
		if (player == 1)
		{
			board[column][row] = 1;
			player = 2;
		}
		else
		{
			board[column][row] = 2;
			player = 1;
		}

	}
	return played;
}

// This returns which player is to play.
int Board::currentPlayer() const
{
	return player;
}

// This function see if the chain of five peices is horiaontally created started form at given position.
void Board::search_horizontal(int column, int row, int piece)
{
	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			winning = true;
			count = 0;
		}
		else
		{
			winning = false;
			count = 0;
		}
	}
	else if (board[column][row] == piece) // This recoursively works as long as the position has a given peices.
	{
		count++;
		search_horizontal(column, row + 1, piece);
	}
}

// This function see if the chain of five peices is vertically created stared from at given position.
void Board::search_vertical(int column, int row, int piece)
{
	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			winning = true;
			count = 0;
		}
		else
		{
			winning = false;
			count = 0;
		}
	}
	else if (board[column][row] == piece) // same as above
	{
		count++;
		search_vertical(column + 1, row, piece);
	}
}

// This function see if the chain of five peices is slantingly from upper left to lower right created stared from at given position.
void Board::search_slanting_leftToRight(int column, int row, int piece)
{

	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			winning = true;
			count = 0;
		}
		else
		{
			winning = false;
			count = 0;
		}
	}
	else if (board[column][row] == piece)//same as avobe
	{
		count++;
		search_slanting_leftToRight(column + 1, row + 1, piece);
	}

}

// This function see if the chain of five peices is slantingly from upper right to lower left created stared from at given position.
void Board::search_slanting_rightToLeft(int column, int row, int player)
{
	if (board[column][row] != player)
	{
		if (count >= 5)
		{
			winning = true;
			count = 0;
		}
		else
		{
			winning = false;
			count = 0;
		}
	}
	else if (board[column][row] == player)//same as avobe
	{
		count++;
		search_slanting_rightToLeft(column - 1, row - 1, player);
	}
}

bool Board::checkWinning()
{
	// This loop check if the chain is horizontally created at each position on each column.
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)// no need to see the four positions on the right side.
		{
			if (board[column][row] == 1)
				search_horizontal(column, row, 1);
			else if (board[column][row] == 2)
				search_horizontal(column, row, 2);
			if (winning)
				return winning;
		}
	}

	// This loop check if the chain is vertically created at each position on each row.
	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize - 4; column++)
		{
			if (board[column][row] == 1)
				search_vertical(column, row, 1);
			else if (board[column][row] == 2)
				search_vertical(column, row, 2);
			if (winning)
				return winning;
		}
	}

	// This loop check if the chain is slsntigly created at each position.
	for (int column = 0; column < boardSize - 4; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)//from upper left to lower right
		{
			if (board[column][row] == 1)
				search_slanting_leftToRight(column, row, 1);
			else if (board[column][row] == 2)
				search_slanting_leftToRight(column, row, 2);
			if (winning)
				return winning;
		}
		for (int row = 14; row > 4; row--)//from upper right to lower left
		{
			if (board[column][row] == 1)
				search_slanting_rightToLeft(column, row, 1);
			else if (board[column][row] == 2)
				search_slanting_rightToLeft(column, row, 2);
			if (winning)
				return winning;
		}
	}
	return winning; // return false if nothing found.
}

void Board::randomPlay()
{
	const int minValue = 0;
	const int maxValue = 14;
	int x, y;
	unsigned seed = time(0);
	srand(seed);
	do
	{
		x = (rand() % (maxValue - minValue + 1)) + minValue;
		y = (rand() % (maxValue - minValue + 1)) + minValue;
	} while (board[x][y] != 0);

	play(x, y);
}
#endif 
