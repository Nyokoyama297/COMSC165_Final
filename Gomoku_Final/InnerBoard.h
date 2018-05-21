#pragma once
#ifndef INNERBOARD_H
#define INNERBOARD_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

const int minValue = 0;
const int maxValue = 14;
const int trial = 500;

class InnerBoard : public Board
{
protected:
	double probability[boardSize][boardSize];
	double tempProbability;
	int innerPlayer;
	int column;
	int row;
	int count;
	int playoutBoard[boardSize][boardSize];
	int innerplayed;
	void innerSearch_horizontal(int, int, int);
	void innerSearch_vertical(int, int, int);
	void innerSearch_slanting_leftToRight(int, int, int);
	void innerSearch_slanting_rightToLeft(int, int, int);
	int tempBoard[boardSize][boardSize];
	
	
	
	
public:
	void copy_Board();
	void innerPlay(int, int);
	double playout(int,int);
	void makeMove();
	int get_column();
	int get_row();
	bool innerCheckWinning();
	int get_boardStatus(int, int);
	void refresh_tempBoard();
	bool checkPlayed;
	bool set_draw();

};

bool InnerBoard::set_draw()
{
	int draw = 0;

	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (playoutBoard[x][y] == 0)
				draw++;
		}
	}

	if (draw == 0)
		return true;
	else
		return false;
	
}
void InnerBoard::refresh_tempBoard()
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (playoutBoard[x][y] != 0)
				tempBoard[x][y] = 1;
			else
				tempBoard[x][y] = 0;
		}
	}
}
void InnerBoard::copy_Board()
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			playoutBoard[x][y] = board[x][y];
		}
	}

	innerPlayer = player;
	
}

int InnerBoard::get_boardStatus(int column, int row) 
{
	return playoutBoard[column][row];
}

void InnerBoard::innerPlay(int column, int row)
{
	if (playoutBoard[column][row] != 0)
	{
		return;
	}

	else
	{
		if (innerPlayer == 1)
		{
			playoutBoard[column][row] = 1;
			innerPlayer = 2;
		}
		else
		{
			playoutBoard[column][row] = 2;
			innerPlayer = 1;
		}
	}

}

double InnerBoard::playout(int column, int row)
{
	
	copy_Board();
	innerPlay(column, row);
	refresh_tempBoard();
	checkPlayed = true;
	int x, y;
	unsigned seed = time(0);
	srand(seed);
	winning = false;
	while (!winning && !set_draw())
	{
		do
		{
			x = (rand() % (maxValue - minValue + 1)) + minValue;
			y = (rand() % (maxValue - minValue + 1)) + minValue;
			if (tempBoard[x][y] != 0)
				checkPlayed = false;
			else
				checkPlayed = true;
		} while (!checkPlayed);
		tempBoard[x][y] = 1;
		innerPlay(x, y);
		winning = innerCheckWinning();
		
		
		
	}


	if (set_draw() && !winning)
		return -10;

	if (innerPlayer == player)
		return -50;
	else
		return 100;
}

void InnerBoard::makeMove()
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			probability[x][y] = 0;
		}
	}
	column = 0;
	row = 0;

	

	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			copy_Board();
			if (playoutBoard[x][y] == 0)
			{
				for (int i = 0; i < trial; i++)
				{
					
					
					probability[x][y] = probability[x][y] + playout(x,y);
					
				}
				probability[x][y] = probability[x][y] / 100;
			}
			

			
		}
	}

	tempProbability = 0;
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (tempProbability < probability[x][y] && board[x][y] == 0)
			{
				tempProbability = probability[x][y];
				column = x;
				row = y;
			}
		}
	}


}

int InnerBoard::get_column()
{
	return column;
}

int InnerBoard::get_row()
{
	return row;
}

// This function see if the chain of five peices is horiaontally created started form at given position.
void InnerBoard::innerSearch_horizontal(int column, int row, int piece)
{
	if (playoutBoard[column][row] != piece)
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
	else if (playoutBoard[column][row] == piece) // This recoursively works as long as the position has a given peices.
	{
		count++;
		innerSearch_horizontal(column, row + 1, piece);
	}
}

// This function see if the chain of five peices is vertically created stared from at given position.
void InnerBoard::innerSearch_vertical(int column, int row, int piece)
{
	if (playoutBoard[column][row] != piece)
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
	else if (playoutBoard[column][row] == piece) // same as above
	{
		count++;
		innerSearch_vertical(column + 1, row, piece);
	}
}

// This function see if the chain of five peices is slantingly from upper left to lower right created stared from at given position.
void InnerBoard::innerSearch_slanting_leftToRight(int column, int row, int piece)
{

	if (playoutBoard[column][row] != piece)
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
	else if (playoutBoard[column][row] == piece)//same as avobe
	{
		count++;
		innerSearch_slanting_leftToRight(column + 1, row + 1, piece);
	}

}

// This function see if the chain of five peices is slantingly from upper right to lower left created stared from at given position.
void InnerBoard::innerSearch_slanting_rightToLeft(int column, int row, int player)
{
	if (playoutBoard[column][row] != player)
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
	else if (playoutBoard[column][row] == player)//same as avobe
	{
		count++;
		innerSearch_slanting_rightToLeft(column - 1, row - 1, player);
	}
}

bool InnerBoard::innerCheckWinning()
{
	// This loop check if the chain is horizontally created at each position on each column.
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)// no need to see the four positions on the right side.
		{
			if (playoutBoard[column][row] == 1)
				innerSearch_horizontal(column, row, 1);
			else if (playoutBoard[column][row] == 2)
				innerSearch_horizontal(column, row, 2);
			if (winning)
				return winning;
		}
	}

	// This loop check if the chain is vertically created at each position on each row.
	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize - 4; column++)
		{
			if (playoutBoard[column][row] == 1)
				innerSearch_vertical(column, row, 1);
			else if (playoutBoard[column][row] == 2)
				innerSearch_vertical(column, row, 2);
			if (winning)
				return winning;
		}
	}

	// This loop check if the chain is slsntigly created at each position.
	for (int column = 0; column < boardSize - 4; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)//from upper left to lower right
		{
			if (playoutBoard[column][row] == 1)
				innerSearch_slanting_leftToRight(column, row, 1);
			else if (playoutBoard[column][row] == 2)
				innerSearch_slanting_leftToRight(column, row, 2);
			if (winning)
				return winning;
		}
		for (int row = 14; row > 4; row--)//from upper right to lower left
		{
			if (playoutBoard[column][row] == 1)
				innerSearch_slanting_rightToLeft(column, row, 1);
			else if (playoutBoard[column][row] == 2)
				innerSearch_slanting_rightToLeft(column, row, 2);
			if (winning)
				return winning;
		}
	}
	return winning; // return false if nothing found.
}


#endif