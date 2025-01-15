//// readme
// posibilitatea de a juca pe o matrice 3 pe 3 sau 4 pe 4 (ce table vrei...)
//*poate fi facut peste 2 sapt* - un meniu in care sa aleg matrice 3/3, 4/4, sa joc vs persoana (user 1 / user 2), 
// random player (math.h are functia random sau vector cu valori)
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int game[5][5], tableElements;
int inputLine, inputColumn;
char user1[20], user2[20];
int checkX()
{
	int nrLine, nrColumn, line, column;
	for (line = 1; line <= tableElements; line++)
	{
		nrLine = nrColumn = 0;
		for (column = 1; column <= tableElements; column++)
		{
			if (game[line][column] == 1)
				nrLine++;
			if (game[column][line] == 1)
				nrColumn++;
		}
		if (nrLine == tableElements || nrColumn == tableElements) return 1;
	}
	nrLine = nrColumn = 0;
	for (line = 1; line <= tableElements; line++)
	{
		if (game[line][line] == 1)
			nrLine++;
		if (game[line][tableElements + 1 - line] == 1)
			nrColumn++;
	}
	if (nrLine == tableElements || nrColumn == tableElements) return 1;
	return 0;
}
int check0()
{
	int nrLine, nrColumn, line, column;
	for (line = 1; line <= tableElements; line++)
	{
		nrLine = nrColumn = 0;
		for (column = 1; column <= tableElements; column++)
		{
			if (game[line][column] == 2)
				nrLine++;
			if (game[column][line] == 2)
				nrColumn++;
		}
		if (nrLine == tableElements || nrColumn == tableElements) return 1;
	}
	nrLine = nrColumn = 0;
	for (line = 1; line <= tableElements; line++)
	{
		if (game[line][line] == 2)
			nrLine++;
		if (game[line][tableElements + 1 - line] == 2)
			nrColumn++;
	}
	if (nrLine == tableElements || nrColumn == tableElements) return 1;
	return 0;
}
void gameProgress(int game[5][5])
{
	for (int line = 1; line <= tableElements; line++)
	{
		for (int column = 1; column <= tableElements; column++)
			switch (game[line][column])
			{
			case 0: cout << "- "; break;
			case 1: cout << "x "; break;
			case 2: cout << 0 << " "; break;
			}
		cout << endl;
	}
}
void gameChangeX(int game[5][5])
{
	int inputLine, inputColumn, ok = 0;
	cout << user1 << ", choose the line and column for x: ";
	cin >> inputLine >> inputColumn;
	while (ok == 0)
		if (game[inputLine][inputColumn] == 0)
			game[inputLine][inputColumn] = 1, ok = 1;
		else
		{
			cout << "space already filled, pick another slot: ";
			cin >> inputLine >> inputColumn;
		}
	gameProgress(game);
}
void gameChange0(int game[5][5])
{
	int inputLine, inputColumn, ok = 0;
	cout << user2 << ", choose the line and column for 0: ";
	cin >> inputLine >> inputColumn;
	while (ok == 0)
		if (game[inputLine][inputColumn] == 0)
			game[inputLine][inputColumn] = 2, ok = 1;
		else
		{
			cout << "space already filled, pick another slot: ";
			cin >> inputLine >> inputColumn;
		}
	gameProgress(game);
}
void random()
{
	switch (tableElements)
		{
		case 3: {inputLine = rand() % 3 + 1; inputColumn = rand() % 3 + 1; } break;
		case 4: {inputLine = rand() % 4 + 1; inputColumn = rand() % 4 + 1;} break;
		}
}
void gameChangePC(int game[5][5])
{
	int ok = 0;
	srand(time(NULL));
	random();
	while (ok == 0)
		if (game[inputLine][inputColumn] == 0)
			game[inputLine][inputColumn] = 2, ok = 1;
		else
			random();
	cout << "PC's move is : \n";
	gameProgress(game);
}
void twoPlayerGame()
{
	int space, len, foundUser = 0, ok = 0;
	while (foundUser == 0)
	{
		cout << "Enter player 1 name : \n";
		cin.get(user1, 20);
		cin.get();
		len = strlen(user1);
		foundUser = 1;
		for (space = 0; space < len; space++)
			if (user1[space] < 'A' || user1[space] > 'z' || (user1[space] > 'Z' && user1[space] < 'a'))
				foundUser = 0;
		if (foundUser == 0)
			cout << "name contains invalid characters, try another one \n";
	}
	foundUser = 0;
	while (foundUser == 0)
	{
		cout << "Enter player 2 name : \n";
		cin.get(user2, 20);
		cin.get();
		len = strlen(user2);
		foundUser = 1;
		for (space = 0; space < len; space++)
			if (user2[space] < 'A' || user2[space] > 'z' || (user2[space] > 'Z' && user2[space] < 'a'))
				foundUser = 0;
		if (foundUser == 0)
			cout << "name contains invalid characters, try another one \n";
	}
}
void onePlayerGame()
{
	int foundUser = 0, len, space;
	while (foundUser == 0)
	{
		cout << "Enter name : \n";
		cin.get(user1, 20);
		cin.get();
		len = strlen(user1);
		foundUser = 1;
		for (space = 0; space < len; space++)
			if (user1[space] < 'A' || user1[space] > 'z' || (user1[space] > 'z' && user1[space] < 'a'))
				foundUser = 0;
		if (foundUser == 0)
			cout << "name contains invalid characters, try another one \n";
	}
}
void tableSelection()
{
	int tableOption;
	cout << "What kind of table do you want to play on? 3 by 3 (1) or 4 by 4 (2) ?";
	cin >> tableOption;
	if (tableOption == 1) tableElements = 3;
	else tableElements = 4;
}
void startOne()
{
	int progress = 0;
	tableSelection();
	//menu();
	//twoPlayerGame();
	while (progress < tableElements * tableElements - 1)
	{
		gameChangeX(game);
		progress++;
		if (checkX() == 1)
		{
			cout << user1 << " wins!" << endl << endl;
			break;
		}
		gameChange0(game);
		if (check0() == 1)
		{
			cout << user2 << " wins!" << endl << endl;
			break;
		}
		progress++;
	}
	if (check0() != 1 && checkX() != 1) cout << "It's a draw!" << endl;
	cout << "Final result is :" << endl;
	gameProgress(game);
}
void startTwo()
{
	int progress = 0, inputLine, inputColumn;
	tableSelection();
	while (progress < tableElements * tableElements - 1)
	{
		gameChangeX(game);
		progress++;
		if (checkX() == 1)
		{
			cout << user1 << " wins!\n \n";
			break;
		}
		gameChangePC(game);
		if (check0() == 1)
		{
			cout << "You lose... :( \n \n";
			break;
		}
		progress++;
	}
	if (check0() != 1 && checkX() != 1) cout << "It's a draw!\n";
	cout << "Final result is : \n";
	gameProgress(game);
}
void menu()
{
	int tableOption, playerOption;
	cout << "Welcome to noughts and crosses! What kind of game do you want to play?\n";
	cout << "1. player vs player (PVP)\n";
	cout << "2. player versus enviroment/PC (PVE)\n";
	cin >> playerOption;
	cin.get();
	switch (playerOption)
	{
	case 1: {twoPlayerGame(); startOne(); } break;
	case 2: {onePlayerGame(); startTwo(); }break;
	}
}
int main()
{
	menu();
	return 0;
}