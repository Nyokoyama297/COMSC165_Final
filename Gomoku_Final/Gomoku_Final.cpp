// Gomoku_Final.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
using namespace std;

void showBoard(Board);
bool LettertoCoordinates(char);
int column, row;

int main()
{
	Board gomoku;
	int playOption;
	int playFirst;
	char letter = 'z';



	cout << "This game is Gomoku" << endl;
	cout << "If you want to play with someone, Enter 1" << endl;
	cout << "If you want to pley with a computer, Enter 2" << endl;
	cin >> playOption;

	if (playOption == 1)
	{
		do
		{
			// Display the board
			showBoard(gomoku);
			
			do
			{
				do
				{
					if (gomoku.currentPlayer() == 1)
					{
						if (!LettertoCoordinates(letter))
							cout << "It's an illegal move" << endl;
						cout << "It's player1's turn." << endl
							<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
						cin >> letter;
						cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
						cin >> column;
					}
					else if (gomoku.currentPlayer() == 2)
					{
						if (!LettertoCoordinates(letter))
							cout << "Is's an illegal move" << endl;
						cout << "It's player2's turn." << endl
							<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
						cin >> letter;
						cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
						cin >> column;
					}
				} while (!LettertoCoordinates(letter));
			} while (!gomoku.play(column - 1, row));
		} while (!gomoku.checkWinning());


		showBoard(gomoku);

		if (gomoku.currentPlayer() == 2)
			cout << "Player1 won!" << endl;
		else
			cout << "Player2 won!" << endl;
	}

	if (playOption == 2)
	{
		cout << "Do you play first? 1 for yes, 2 for no" << endl;
		cin >> playFirst;
		if (playFirst == 1)
		{
			do
			{
				// Display the board
				showBoard(gomoku);

				do
				{
					do
					{
						if (gomoku.currentPlayer() == 1)
						{
							if (!LettertoCoordinates(letter))
								cout << "It's an illegal move" << endl;
							cout << "It's player1's turn." << endl
								<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
							cin >> letter;
							cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
							cin >> column;
						}
						else if (gomoku.currentPlayer() == 2)
						{
							if (!LettertoCoordinates(letter))
								cout << "Is's an illegal move" << endl;
							cout << "It's player2's turn." << endl
								<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
							cin >> letter;
							cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
							cin >> column;
						}
					} while (!LettertoCoordinates(letter));
				} while (!gomoku.play(column - 1, row));
				gomoku.randomPlay();
			} while (!gomoku.checkWinning());

			showBoard(gomoku);

			if (gomoku.currentPlayer() == 2)
				cout << "Player1 won!" << endl;
			else
				cout << "Player2 won!" << endl;

		}

		else if (playFirst == 2)
		do
		{
			gomoku.randomPlay();
			showBoard(gomoku);
			do
			{
				
				do
				{
					if (gomoku.currentPlayer() == 1)
					{
						if (!LettertoCoordinates(letter))
							cout << "It's an illegal move" << endl;
						cout << "It's player1's turn." << endl
							<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
						cin >> letter;
						cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
						cin >> column;
					}
					else if (gomoku.currentPlayer() == 2)
					{
						if (!LettertoCoordinates(letter))
							cout << "Is's an illegal move" << endl;
						cout << "It's player2's turn." << endl
							<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
						cin >> letter;
						cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
						cin >> column;
					}
				} while (!LettertoCoordinates(letter));
			} while (!gomoku.play(column - 1, row));

		} while (!gomoku.checkWinning());

		showBoard(gomoku);

		if (gomoku.currentPlayer() == 2)
			cout << "Player1 won!" << endl;
		else
			cout << "Player2 won!" << endl;

	}

	return 0;
}

//Display the board
void showBoard(Board gomoku)
{
	cout << "   a b c d e f g h i j k l m n o" << endl;
	for (int column = 0; column < boardSize; column++)
	{
		cout << setw(2) << column + 1;
		cout << " ";
		for (int row = 0; row < boardSize; row++)
		{

			if (gomoku.get_BoardStatus(column, row) == 0)
				cout << "･";
			else if (gomoku.get_BoardStatus(column, row) == 1)
				cout << "O";
			else if (gomoku.get_BoardStatus(column, row) == 2)
				cout << "X";
			cout << " ";
		}
		cout << endl;
	}
}

bool LettertoCoordinates(char letter)
{
	if (letter == 'a')
		row = 0;
	else if (letter == 'b')
		row = 1;
	else if (letter == 'c')
		row = 2;
	else if (letter == 'd')
		row = 3;
	else if (letter == 'e')
		row = 4;
	else if (letter == 'f')
		row = 5;
	else if (letter == 'g')
		row = 6;
	else if (letter == 'h')
		row = 7;
	else if (letter == 'i')
		row = 8;
	else if (letter == 'j')
		row = 9;
	else if (letter == 'k')
		row = 10;
	else if (letter == 'l')
		row = 11;
	else if (letter == 'm')
		row = 12;
	else if (letter == 'n')
		row = 13;
	else if (letter == 'o')
		row = 14;
	else
		return false;

	return true;
}

