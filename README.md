# X si 0
Proiectul de fata este un joc de X si 0 pentru unul sau doi jucatori in care se poate alege daca se joaca pe un tabel de 3 pe 3 sau de 4 pe 4.

In primul rand, folosesc o functie *gametype* pentru a afisa utilizatorului optiunile pe care le are in joc:
```cpp
void gameType() // noughts and crosses
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
	case 2: {onePlayerGame(); startTwo(); } break;
	}
}
```
Tabelul cu care se lucreaza va fi numit *game*, declarat global, care isi schimba valoarea unui element in 1 (pentru X/ user1) sau 2 (pentru 0/ user2/ valoare random - PC) atunci cand este introdusa linia si coloana elementului.    

Pentru a alege tipul de tabel am afisat un mesaj utilizatorului si printr-o structura *if* am atribuit unei variabile * tableElements * ce contine numarul de linii si de coloane ale tabelului, numarul 3 sau 4 in functie de alegerea utilizatorului. Aceasta variabila este declarata global la inceputul programului deoarece urmeaza sa lucrez cu ea in mai multe functii (cea de afisare a matricei, cele doua de schimbare a matricei pentru x si 0 respectiv si cele doua care verifica daca vreun utilizator a castigat sau nu). 
```cpp
void tableSelection()
{
	int tableOption;
	cout << "What kind of table do you want to play on? 3 by 3 (1) or 4 by 4 (2) ?";
	cin >> tableOption;
	if (tableOption == 1) tableElements = 3;
	else tableElements = 4;
}```
Pentru a salva in memorie numele jucatorilor am optat in folosirea a doua siruri de caractere (* user1 * si * user 2 *) pe care le-am citit in functia * twoPlayerGame *. In cazul unui singur jucator folosesc functia *onePlayerGame* ce atribuie o valoare doar in prima variabila *user1*.
```cpp
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
}```

Pentru functionarea propriu-zisa a jocului am optat sa folosesc doua functii: *startOne* pentru alegerea de a juca cu o alta persoana si *startTwo* pentru a juca contra calculatorului. 
```cpp
void startOne()
{
	int progress = 0;
	tableSelection();
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
}```
Functia ce afiseaza jocul curent se numeste *gameProgress* si aceasta, prin doua structuri *for* si printr-o structura *switch* mascheaza tabelul propriu-zis si afiseaza "- , x , 0" pentru valorile de 0, 1 si 2, respectiv, ale matricei. 
```cpp
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
```
Pentru a avansa jocul ma folosesc de doua functii, una pentru X (*gameChangeX*) si una pentru 0 (*gameChange0*), ca sa schimb valorile de pe elementul al carei linie si coloana sunt introduse de utilizator. In cazul in care spatiul ales este deja ocupat de un alt element, functia afiseaza un mesaj si reciteste linia si colona pana cand sunt introduse valori valabile. Atunci cand utilizatorul joaca impotriva caluclatorului se vor folosi alte functii, *randomNr* si *gameChangePc*.
```cpp 
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
}```

Functia *randomNr* verifica numarul de elemente ale tabelului folosit (*tableElements*) si genereaza o valoare aleatorie intre 1 si numarul de elemente curente. *gameChangePC* se foloseste de aceasta functie pentru a genera valori introduse de calculator, pe care ulterior le verifica si le introduce in tabel, afisand intr-un final tabelul propriu-zis, precedat de un mesaj.
```cpp
void randomNr()
{
	switch (tableElements)
	{
	case 3: {inputLine = rand() % 3 + 1; inputColumn = rand() % 3 + 1; } break;
	case 4: {inputLine = rand() % 4 + 1; inputColumn = rand() % 4 + 1; } break;
	}
}
void gameChangePC(int game[5][5])
{
	int ok = 0;
	srand(time(NULL));
	randomNr();
	while (ok == 0)
		if (game[inputLine][inputColumn] == 0)
			game[inputLine][inputColumn] = 2, ok = 1;
		else
			randomNr();
	cout << "PC's move is : \n";
	gameProgress(game);
}```

Functiile de *checkX* sau *check0* sunt aproape identice, folosite dupa fiecare modificare facuta in matrice pentru a vedea daca exista un utilizator ce a castigat. In functia data mai jos sunt numarate elementele de pe fiecare linie sau coloana care sunt egale cu 1 (elementele de X).

Daca numarul de elemente de pe o linie/ o coloana / o diagonala este egal cu *tableElements* (numarul de linii/ coloane ale matricei patratice) atunci se returneaza 1 semnificand ca jocul s-a terminat si ca exista un castigator, altfel se returneaza 0 si jocul continua. La final, daca nu a castigat nimeni jocul, se verifica in functia *start* daca *checkX* si *check0* sunt diferite de 1 si se afiseaza mesajul "It's a draw!" daca da.

```cpp
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
}```
Cum am considerat 0 ca fiind mutarea facuta de PC (in cazul unui singur jucator), nu mai este nevoie sa creez o alta functie pentru a verifica castigul calculatorului, ci dosar o folosesc pe *check0*.

