#include <iostream>
#include <random>
#include <cmath>
#include <limits>
#include <conio.h>
#include <cstdlib>
#include <locale.h>
#include <chrono>
#include <thread>
//#include <cctype>
#include <fstream>
#include <string>
#include <cstring>
//#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <windows.h>

int PT{}; //poziom trudnosci dla PvC
int poX = -1, poY = -1, kieru{}; //wspó³rzêdne poprzedniego strza³u komputera
using namespace std;

bool koniecGry{ 0 };

//rozmieszczanie masztowcow
void rozmiesc(int maszt, int plansza[10][10], bool czy3)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> kierunek(0, 3);
	uniform_int_distribution<int> pole(0, 9);
	int yr{}, xr{}, k{};
	bool czy_nar = 1;
	int blad = 0;

	while (czy_nar)
	{
		blad = 0;
		k = kierunek(generator);
		yr = pole(generator);
		xr = pole(generator);
		if (plansza[yr][xr] == 0)
		{

			if (k == 0) //gora
			{
				if (yr >= maszt - 1)
				{
					//sprawdzenie czy pole jest puste
					for (int a{}; a < maszt; a++)
					{
						if (plansza[yr - a][xr] != 0)
						{
							blad = 1;
						}
					}
					//rysowanie masztowca
					if (blad == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							if (czy3 == 1)
								plansza[yr - a][xr] = maszt + 3;
							else if (czy3 == 0)
								plansza[yr - a][xr] = maszt;
						}

						//obudowa -1

						if (xr != 0)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr - f][xr - 1] = -1;
							}
						}
						if (xr != 9)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr - f][xr + 1] = -1;
							}
						}
						if (yr != 9)
						{
							plansza[yr + 1][xr] = -1;
							if (xr != 0)
								plansza[yr + 1][xr - 1] = -1;
							if (xr != 9)
								plansza[yr + 1][xr + 1] = -1;
						}
						if (yr != maszt - 1)
						{
							plansza[yr - maszt][xr] = -1;
							if (xr != 0)
								plansza[yr - maszt][xr - 1] = -1;
							if (xr != 9)
								plansza[yr - maszt][xr + 1] = -1;
						}
						czy_nar = 0;
					}
				}
			}

			if (k == 1) //dol
			{
				if (yr <= 9 - maszt + 1)
				{
					for (int a{}; a < maszt; a++)
					{
						//sprawdzanie czy pole na którym ma staæ masztowiec jest puste
						if (plansza[yr + a][xr] != 0)
						{
							blad = 1;
						}

					}

					//rysowanie masztowca
					if (blad == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							if (czy3 == 1)
								plansza[yr + a][xr] = maszt + 3;
							else if (czy3 == 0)
								plansza[yr + a][xr] = maszt;

						}

						//obudowa -1

						if (xr != 0)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr + f][xr - 1] = -1;
							}
						}
						if (xr != 9)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr + f][xr + 1] = -1;
							}
						}
						if (yr != 0)
						{
							plansza[yr - 1][xr] = -1;
							if (xr != 0)
								plansza[yr - 1][xr - 1] = -1;
							if (xr != 9)
								plansza[yr - 1][xr + 1] = -1;
						}
						if (yr != 9 - maszt + 1)
						{
							plansza[yr + maszt][xr] = -1;
							if (xr != 0)
								plansza[yr + maszt][xr - 1] = -1;
							if (xr != 9)
								plansza[yr + maszt][xr + 1] = -1;
						}
						czy_nar = 0;
					}
				}
			}

			if (k == 2) //prawo
			{
				if (xr <= 9 - maszt + 1)
				{
					for (int a{}; a < maszt; a++)
					{
						if (plansza[yr][xr + a] != 0)
						{
							blad = 1;
						}
					}

					//rysowanie masztowca
					if (blad == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							if (czy3 == 1)
								plansza[yr][xr + a] = maszt + 3;
							else if (czy3 == 0)
								plansza[yr][xr + a] = maszt;
						}
						czy_nar = 0;
						//rysowanie -1
						if (yr != 0)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr - 1][xr + f] = -1;

							}
						}
						if (yr != 9)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr + 1][xr + f] = -1;
							}
						}
						if (xr != 0)
						{
							plansza[yr][xr - 1] = -1;
							if (yr != 0)
								plansza[yr - 1][xr - 1] = -1;
							if (yr != 9)
								plansza[yr + 1][xr - 1] = -1;
						}
						if (xr != 9 - maszt + 1)
						{
							plansza[yr][xr + maszt] = -1;
							if (yr != 0)
								plansza[yr - 1][xr + maszt] = -1;
							if (yr != 9)
								plansza[yr + 1][xr + maszt] = -1;
						}
					}
				}
			}

			if (k == 3) //lewo
			{
				if (xr >= maszt - 1)
				{
					for (int a{}; a < maszt; a++)
					{
						if (plansza[yr][xr - a] != 0)
						{
							blad = 1;
						}
					}

					//rysowanie masztowca
					if (blad == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							if (czy3 == 1)
								plansza[yr][xr - a] = maszt + 3;
							else if (czy3 == 0)
								plansza[yr][xr - a] = maszt;
						}
						czy_nar = 0;
						//rysowanie -1
						if (yr != 0)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr - 1][xr - f] = -1;

							}
						}
						if (yr != 9)
						{
							for (int f = 0; f < maszt; f++)
							{
								plansza[yr + 1][xr - f] = -1;
							}
						}
						if (xr != maszt - 1)
						{
							plansza[yr][xr - maszt] = -1;
							if (yr != 0)
								plansza[yr - 1][xr - maszt] = -1;
							if (yr != 9)
								plansza[yr + 1][xr - maszt] = -1;
						}
						if (xr != 9)
						{
							plansza[yr][xr + 1] = -1;
							if (yr != 0)
								plansza[yr - 1][xr + 1] = -1;
							if (yr != 9)
								plansza[yr + 1][xr + 1] = -1;
						}
					}
				}
			}
		}
	}
}

void loading()
{
	system("cls");
	cout << "loading.";
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	system("cls");
	cout << "loading..";
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	system("cls");
	cout << "loading...";
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	system("cls");
}

void dalej()
{
	cout << endl;
	cout << "wciœnij dowolny przycisk, aby przejœæ dalej";
	_getch();
	cout << endl;
}

//generowanie planszy
void generuj(int plansza[10][10])
{
	rozmiesc(4, plansza, 0);
	rozmiesc(3, plansza, 0);
	rozmiesc(3, plansza, 1);
	for (int i = 0; i < 3; i++)
		rozmiesc(2, plansza, 0);
	for (int i = 0; i < 4; i++)
		rozmiesc(1, plansza, 0);

}

int pieknaZmiennaGlobalna{};

//sprawdzenie czy masztowiec w przypadku manualnego rozstawu zosta³ umieszczony poprawnie
bool czyPoprawnie(int plansza[10][10], int xp, int yp, int maszt, int kierunek)
{
	int yr{}, xr{}, k{};
	bool czy_nar = 1;
	int blad = 0;


	blad = 0;
	k = kierunek - 1;
	yr = xp;
	xr = yp;
	if (plansza[yr][xr] == 0)
	{
		if (k == 0) //gora
		{
			if (yr >= maszt - 1)
			{
				//sprawdzenie czy pole jest puste
				for (int a{}; a < maszt; a++)
				{
					if (plansza[yr - a][xr] != 0)
					{
						blad = 1;
					}
				}
				//rysowanie masztowca
				if (blad == 0)
				{


					if (maszt == 3 && pieknaZmiennaGlobalna == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr - a][xr] = maszt + 3;
						}
						pieknaZmiennaGlobalna = 1;
					}
					else
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr - a][xr] = maszt;
						}
					}

					//obudowa -1

					if (xr != 0)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr - f][xr - 1] = -1;
						}
					}
					if (xr != 9)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr - f][xr + 1] = -1;
						}
					}
					if (yr != 9)
					{
						plansza[yr + 1][xr] = -1;
						if (xr != 0)
							plansza[yr + 1][xr - 1] = -1;
						if (xr != 9)
							plansza[yr + 1][xr + 1] = -1;
					}
					if (yr != maszt - 1)
					{
						plansza[yr - maszt][xr] = -1;
						if (xr != 0)
							plansza[yr - maszt][xr - 1] = -1;
						if (xr != 9)
							plansza[yr - maszt][xr + 1] = -1;
					}
					czy_nar = 0;
				}
			}
			else
				blad = 1;
		}



		if (k == 1) //dol
		{
			if (yr <= 9 - maszt + 1)
			{
				for (int a{}; a < maszt; a++)
				{
					//sprawdzanie czy pole na którym ma staæ masztowiec jest puste
					if (plansza[yr + a][xr] != 0)
					{
						blad = 1;
					}

				}

				//rysowanie masztowca
				if (blad == 0)
				{

					if (maszt == 3 && pieknaZmiennaGlobalna == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr + a][xr] = maszt + 3;
						}
						pieknaZmiennaGlobalna = 1;
					}
					else
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr + a][xr] = maszt;
						}
					}

					//obudowa -1

					if (xr != 0)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr + f][xr - 1] = -1;
						}
					}
					if (xr != 9)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr + f][xr + 1] = -1;
						}
					}
					if (yr != 0)
					{
						plansza[yr - 1][xr] = -1;
						if (xr != 0)
							plansza[yr - 1][xr - 1] = -1;
						if (xr != 9)
							plansza[yr - 1][xr + 1] = -1;
					}
					if (yr != 9 - maszt + 1)
					{
						plansza[yr + maszt][xr] = -1;
						if (xr != 0)
							plansza[yr + maszt][xr - 1] = -1;
						if (xr != 9)
							plansza[yr + maszt][xr + 1] = -1;
					}
					czy_nar = 0;
				}
			}
			else
				blad = 1;
		}


		if (k == 2) //prawo
		{
			if (xr <= 9 - maszt + 1)
			{
				for (int a{}; a < maszt; a++)
				{
					if (plansza[yr][xr + a] != 0)
					{
						blad = 1;
					}
				}

				//rysowanie masztowca
				if (blad == 0)
				{
					if (maszt == 3 && pieknaZmiennaGlobalna == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr][xr + a] = maszt + 3;
						}
						pieknaZmiennaGlobalna = 1;
					}
					else
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr][xr + a] = maszt;
						}
					}

					czy_nar = 0;
					//rysowanie -1
					if (yr != 0)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr - 1][xr + f] = -1;

						}
					}
					if (yr != 9)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr + 1][xr + f] = -1;
						}
					}
					if (xr != 0)
					{
						plansza[yr][xr - 1] = -1;
						if (yr != 0)
							plansza[yr - 1][xr - 1] = -1;
						if (yr != 9)
							plansza[yr + 1][xr - 1] = -1;
					}
					if (xr != 9 - maszt + 1)
					{
						plansza[yr][xr + maszt] = -1;
						if (yr != 0)
							plansza[yr - 1][xr + maszt] = -1;
						if (yr != 9)
							plansza[yr + 1][xr + maszt] = -1;
					}
				}
			}
			else
				blad = 1;
		}

		if (k == 3) //lewo
		{
			if (xr >= maszt - 1)
			{
				for (int a{}; a < maszt; a++)
				{
					if (plansza[yr][xr - a] != 0)
					{
						blad = 1;
					}
				}

				//rysowanie masztowca
				if (blad == 0)
				{
					if (maszt == 3 && pieknaZmiennaGlobalna == 0)
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr][xr - a] = maszt + 3;
						}
						pieknaZmiennaGlobalna = 1;
					}
					else
					{
						for (int a{}; a < maszt; a++)
						{
							plansza[yr][xr - a] = maszt;
						}
					}
					czy_nar = 0;
					//rysowanie -1
					if (yr != 0)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr - 1][xr - f] = -1;

						}
					}
					if (yr != 9)
					{
						for (int f = 0; f < maszt; f++)
						{
							plansza[yr + 1][xr - f] = -1;
						}
					}
					if (xr != maszt - 1)
					{
						plansza[yr][xr - maszt] = -1;
						if (yr != 0)
							plansza[yr - 1][xr - maszt] = -1;
						if (yr != 9)
							plansza[yr + 1][xr - maszt] = -1;
					}
					if (xr != 9)
					{
						plansza[yr][xr + 1] = -1;
						if (yr != 0)
							plansza[yr - 1][xr + 1] = -1;
						if (yr != 9)
							plansza[yr + 1][xr + 1] = -1;
					}
				}
			}
			else
				blad = 1;
		}
	}
	else
		blad = 1;


	return !blad;

}

//rysowanie danej planszy
void rysujP(int plansza[10][10])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int y = -1; y < 10; y++)
	{
		for (int x = -1; x < 10; x++)
		{
			if (y >= 0 && x >= 0)
			{
				cout.width(2);
				if (plansza[y][x] > 0 && plansza[y][x] != 10 && plansza[y][x] != 5 && plansza[y][x] != 11 && plansza[y][x] != 13)
				{
					SetConsoleTextAttribute(hConsole, 14);
					cout << "#";
				}
				else if (plansza[y][x] == 11 || plansza[y][x] == 5)
				{
					SetConsoleTextAttribute(hConsole, 12);
					cout << "x";
				}
				else if (plansza[y][x] == 10 || plansza[y][x] == 13)
				{
					SetConsoleTextAttribute(hConsole, 3);
					cout << "~";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 9);
					cout << "-";
				}
			}
			else
			{
				cout.width(2);
				SetConsoleTextAttribute(hConsole, 15);
				if (y == -1 && x == -1)
				{
					cout << " ";
				}
				if (y == -1 && x != -1)
				{
					cout << char(65 + x);
				}
				if (y != -1 && x == -1)
				{
					cout << y + 1;
				}

			}

		}
		SetConsoleTextAttribute(hConsole, 15);
		cout << endl;

	}
}

//kontynuacja rozstawienia manualnego
void dalszyRozstawM(int plansza[10][10], int maszt, string nazwa)
{
	int xp{}, yp{}, i{}, k;
	bool error2{ 1 };
	char wspolrzedne[1000]{};
	char kierunek[1000]{};

	bool error{ 1 };
	cout << nazwa << " twoja plansza wyglada nastepujaco: " << endl;
	rysujP(plansza);
	cout << "Podaj wspó³rzêdne pocz¹tku statku (wpisz np. A5 lub a4)" << endl;
	cin.getline(wspolrzedne, 1000);
	for (i; wspolrzedne[i] != 0; i++);
	if (i == 2)
	{
		if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
		{
			if (int(wspolrzedne[1] - 48) > 0 && int(wspolrzedne[1] - 48) < 11)
			{
				error = 0;
			}
		}
	}
	if (i == 3)
	{
		if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
		{
			if (int(wspolrzedne[1] - 48) == 1 && int(wspolrzedne[2] - 48) == 0)
			{
				error = 0;
			}
		}
	}
	while (error)
	{
		cout << "Podano niepoprawne wspó³rzêdne." << endl;
		cout << "Podaj poprawne wspó³rzêdne pocz¹tku statku (wpisz np. A5 lub a4)" << endl;

		cin.getline(wspolrzedne, 1000);
		i = 0;
		for (i; wspolrzedne[i] != 0; i++);
		if (i == 2)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
			{
				if (int(wspolrzedne[1] - 48) > 0 && int(wspolrzedne[1] - 48) < 11)
				{
					error = 0;
				}
			}
		}
		if (i == 3)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
			{
				if (int(wspolrzedne[1] - 48) == 1 && int(wspolrzedne[2] - 48) == 0)
				{
					error = 0;
				}
			}
		}
	}
	if (i == 2)
	{
		if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75))
			xp = int(wspolrzedne[0]) - 65 + 1;
		else
			xp = int(wspolrzedne[0]) - 97 + 1;
		yp = int(wspolrzedne[1] - 48);
	}
	if (i == 3)
	{
		if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75))
			xp = int(wspolrzedne[0]) - 65 + 1;
		else
			xp = int(wspolrzedne[0]) - 97 + 1;
		yp = 10;
	}

	i = 0;
	if (maszt != 1)
	{
		cout << "Wybierz kierunek ustawienia masztowca (1-góra, 2-dó³, 3-prawo, 4-lewo)" << endl;
		cin.getline(kierunek, 1000);
		for (i; kierunek[i] != 0; i++);
		while (i != 1 || (int(kierunek[0]) < 49 || int(kierunek[0]) > 52))
		{
			i = 0;
			cout << "Podaj poprawn¹ wartoœæ!! (1-góra, 2-dó³, 3-prawo, 4-lewo)" << endl;
			cin.getline(kierunek, 1000);
			for (i; kierunek[i] != 0; i++);
		}
		i = 0;
		k = int(kierunek[0]) - 48;
	}
	if (maszt == 1)
		k = 1;
	i = 0;
	/*cout << czyPoprawnie(plansza, yp - 1, xp - 1, maszt, kierunek) << " !!!!!!!!!!" << endl;*/

	while (czyPoprawnie(plansza, yp - 1, xp - 1, maszt, k) == 0)
	{
		bool error{ 1 };
		char wspolrzedne[1000]{};
		system("cls");
		cout << "Pole na którym chcesz umiejscowiæ swój statek jest ju¿ zajête lub statek wychodzi poza obszar gry" << endl;
		cout << "Pamiêtaj, ¿e statki nie mog¹ na siebie nachodziæ, stykaæ siê, ani wychodziæ poza mapê" << endl;
		cout << "Podaj poprawne wspó³rzêdne pocz¹tku statku (wpisz np. A5 lub a4)" << endl;
		rysujP(plansza);
		cout << "Podaj wspó³rzêdne pocz¹tku statku (wpisz np. A5 lub a4)" << endl;
		cin.getline(wspolrzedne, 1000);
		int i = 0;
		for (i; wspolrzedne[i] != 0; i++);
		if (i == 2)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
			{
				if (int(wspolrzedne[1] - 48) > 0 && int(wspolrzedne[1] - 48) < 11)
				{
					cout << "Podano poprawne wspolrzêdne" << endl;
					error = 0;
				}
			}
		}
		if (i == 3)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
			{
				if (int(wspolrzedne[1] - 48) == 1 && int(wspolrzedne[2] - 48) == 0)
				{
					cout << "Podano poprawne wspo³rzêdne" << endl;
					error = 0;
				}
			}
		}
		while (error)
		{
			system("cls");
			cout << nazwa << " Twoja plansza wygl¹da nastepuj¹co: " << endl;
			rysujP(plansza);
			cout << "Podaj poprawne wspolrzêdne!! (wpisz np. C4 lub c4)" << endl;
			cin.getline(wspolrzedne, 1000);
			i = 0;
			for (i; wspolrzedne[i] != 0; i++);
			if (i == 2)
			{
				if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
				{
					if (int(wspolrzedne[1] - 48) > 0 && int(wspolrzedne[1] - 48) < 11)
					{
						cout << "Podano poprawne wspo³rzêdne" << endl;
						error = 0;
					}
				}
			}
			if (i == 3)
			{
				if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75) || (int(wspolrzedne[0]) > 96 && int(wspolrzedne[0]) < 107))
				{
					if (int(wspolrzedne[1] - 48) == 1 && int(wspolrzedne[2] - 48) == 0)
					{
						cout << "Podano poprawne wspolrzêdne" << endl;
						error = 0;
					}
				}
			}
		}
		if (i == 2)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75))
				xp = int(wspolrzedne[0]) - 65 + 1;
			else
				xp = int(wspolrzedne[0]) - 97 + 1;
			yp = int(wspolrzedne[1] - 48);
		}
		if (i == 3)
		{
			if ((int(wspolrzedne[0]) > 64 && int(wspolrzedne[0]) < 75))
				xp = int(wspolrzedne[0]) - 65 + 1;
			else
				xp = int(wspolrzedne[0]) - 97 + 1;
			yp = 10;
		}

		i = 0;
		if (maszt != 1)
		{
			cout << "Wybierz kierunek ustawienia masztowca (1-góra, 2-dó³, 3-prawo, 4-lewo)" << endl;
			cin.getline(kierunek, 1000);
			for (i; kierunek[i] != 0; i++);
			while (i != 1 || (int(kierunek[0]) < 49 || int(kierunek[0]) > 52))
			{
				i = 0;
				cout << "Podaj poprawn¹ wartoœæ!! (1-góra, 2-dó³, 3-prawo, 4-lewo)" << endl;
				cin.getline(kierunek, 1000);
				for (i; kierunek[i] != 0; i++);
			}
			i = 0;
			k = int(kierunek[0]) - 48;
		}
		if (maszt == 1)
			k = 1;
	}

	cout << "Poprawnie dodano masztowiec do floty!!" << endl;
}

//pocz¹tek rozstawu manualnego, 
void rozstawienieM(int plansza[10][10], string nazwa)
{
	cout << "Zacznijmy od 4-masztowca" << endl;
	dalszyRozstawM(plansza, 4, nazwa);
	system("cls");
	cout << "4 masztowiec zasili³ Twoj¹ flotê!!" << endl;
	cout << "Teraz pora na dwa 3-masztowce,  kapitanie!!" << endl;
	dalszyRozstawM(plansza, 3, nazwa);
	system("cls");
	cout << "Pora na drugi 3-masztowiec" << endl;
	dalszyRozstawM(plansza, 3, nazwa);
	system("cls");
	cout << "Przyszed³ czas na trzy 2-masztowce" << endl;
	cout << "Najpierw pierwszy " << endl;
	dalszyRozstawM(plansza, 2, nazwa);
	system("cls");
	cout << "Teraz drugi " << endl;
	dalszyRozstawM(plansza, 2, nazwa);
	system("cls");
	cout << "Pora na trzeci 2-masztowiec" << endl;
	dalszyRozstawM(plansza, 2, nazwa);
	system("cls");
	cout << "I jeszcze cztery 1-masztowce" << endl;
	cout << "Rozstaw pierwszy 1-masztowiec" << endl;
	dalszyRozstawM(plansza, 1, nazwa);
	system("cls");
	cout << "Rozstaw drugi 1-masztowiec" << endl;
	dalszyRozstawM(plansza, 1, nazwa);
	system("cls");
	cout << "Rozstaw trzeci 1-masztowiec" << endl;
	dalszyRozstawM(plansza, 1, nazwa);
	system("cls");
	cout << "Pora na ostatni - czwarty 1-masztowiec" << endl;
	dalszyRozstawM(plansza, 1, nazwa);
	system("cls");
	pieknaZmiennaGlobalna = 0;
	cout << "Poprawnie rozmieszczono wszystkie masztowce kapitanie " << nazwa << "!!" << endl;
	cout << "Tak prezentuje siê Twoja flota: " << endl;

	rysujP(plansza);
	cout << "Wciœnij dowolny przycisk, aby kontynuowaæ" << endl;
	_getch();
	cout << endl;
	cout << endl;

}

//pomocnicza funkcja
bool zatopionoMasztowiec(int plansza[10][10], int sy, int sx, int maszt)
{
	int kierunek{};
	/*if (plansza[sy-1][sx]!=-1&&)*/
	return 0;
}

//funkcja sprawdzaj¹ca czy dany statek zosta³ zatopiony
bool czyZatop(int plansza[10][10], int sy, int sx)
{
	if (plansza[sy][sx] == 1) //warunek 1-masztowca
	{
		return 1;
	}
	else if (plansza[sy][sx] == 2) //warunek 2-masztowca
	{
		if ((sy > 0 && sy < 9) && (sx < 9 && sx>0))
		{
			if (plansza[sy - 1][sx] == 5 || plansza[sy + 1][sx] == 5 || plansza[sy][sx - 1] == 5 || plansza[sy][sx + 1] == 5)
			{
				return 1;
			}
		}
		else
		{
			if (sy == 0 && (sx < 9 && sx>0)) //gorny pasek
			{
				if (plansza[sy + 1][sx] == 5 || plansza[sy][sx - 1] == 5 || plansza[sy][sx + 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 9 && (sy < 9 && sy>0)) //prawy pasek
			{
				if (plansza[sy - 1][sx] == 5 || plansza[sy + 1][sx] == 5 || plansza[sy][sx - 1] == 5)
				{
					return 1;
				}
			}
			if (sy == 9 && (sx < 9 && sx>0)) //dolny pasek
			{
				if (plansza[sy - 1][sx] == 5 || plansza[sy][sx - 1] == 5 || plansza[sy][sx + 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 0 && (sy < 9 && sy>0)) //lewy pasek
			{
				if (plansza[sy - 1][sx] == 5 || plansza[sy + 1][sx] == 5 || plansza[sy][sx + 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 0 && sy == 0) //lewy górny róg
			{
				if (plansza[sy + 1][sx] == 5 || plansza[sy][sx + 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 9 && sy == 0) //prawy górny róg
			{
				if (plansza[sy + 1][sx] == 5 || plansza[sy][sx - 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 9 && sy == 9) //prawy dolny róg
			{
				if (plansza[sy - 1][sx] == 5 || plansza[sy][sx - 1] == 5)
				{
					return 1;
				}
			}
			if (sx == 0 && sy == 9) //lewy dolny róg
			{
				if (plansza[sy - 1][sx] == 5 || plansza[sy][sx + 1] == 5)
				{
					return 1;
				}
			}
		}
	}
	else if (plansza[sy][sx] == 3)
	{
		plansza[sy][sx] = 5;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (plansza[i][j] == 3)
					return 0;
			}
		}
		return 1;
	}
	else if (plansza[sy][sx] == 6)
	{
		plansza[sy][sx] = 5;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (plansza[i][j] == 6)
					return 0;
			}
		}
		return 1;
	}
	else if (plansza[sy][sx] == 4)
	{
		plansza[sy][sx] = 5;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (plansza[i][j] == 4)
					return 0;
			}
		}
		return 1;
	}
	else
	{
		if (zatopionoMasztowiec(plansza, sy, sx, plansza[sy][sx]))
			return 1;
		else
			return 0;
	}
	return 0;

}

//czyszczenie tablicy strzal
void czysc(char strzal[1000])
{
	for (int i = 0; i < 1000; i++)
		strzal[i] = 0;
}

//sprawdzenie czy na planszy zosta³y jeszcze jakieœ statki
bool czyPusta(int plansza[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (plansza[i][j] == 1 || plansza[i][j] == 2 || plansza[i][j] == 3 || plansza[i][j] == 4 || plansza[i][j] == 6)
				return 0;
		}
	}
	return 1;
}

//strza³
bool strzal(int plansza[10][10], int plansza2[10][10], int strzelnica[10][10], string kapitan, int& oddane, int& trafione)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	int sx{}, sy{}; // wspó³rzêdna x i y oddanego strza³u
	bool error{ 1 }; // poprawnoœæ wprowadzonych wspó³rzêdnych
	char strzal1[1000]{}; // ci¹g znaków reprezentuj¹cy wspó³rzêdne oddanego strza³u
	system("cls");
	cout << "Witaj kapitanie " << kapitan << endl;
	cout << "Oto Twoja plansza:" << endl;
	rysujP(plansza);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "W jakie pole chcesz strzeliæ? (wpisz np. B5 lub b5)" << endl;
	rysujP(strzelnica);
	czysc(strzal1);
	SetConsoleTextAttribute(hConsole, 15);
	cin.getline(strzal1, 1000);
	int i = 0;
	cout << endl;
	for (i; strzal1[i] != 0; i++);
	if (i == 2)
	{
		if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
		{
			if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Podano poprawne wspólrzêdne" << endl;
				error = 0;
			}
		}
	}
	if (i == 3)
	{
		if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
		{
			if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << "podano poprawne wspolrzedne" << endl;
				error = 0;
			}
		}
	}
	while (error)
	{
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Podaj poprawne wspó³rzêdne!! (wpisz np. C4 lub c4)" << endl;
		cin.getline(strzal1, 1000);
		i = 0;
		for (i; strzal1[i] != 0; i++);
		if (i == 2)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
			{
				if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
				{
					cout << "Podano poprawne wspolrzedne" << endl;
					error = 0;
				}
			}
		}
		if (i == 3)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
			{

				if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
				{
					cout << "Podano poprawne wspolrzedne" << endl;
					error = 0;
				}
			}
		}
	}
	if (i == 2)
	{
		if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
			sx = int(strzal1[0]) - 65 + 1;
		else
			sx = int(strzal1[0]) - 97 + 1;
		sy = int(strzal1[1] - 48);
	}
	if (i == 3)
	{
		if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
			sx = int(strzal1[0]) - 65 + 1;
		else
			sx = int(strzal1[0]) - 97 + 1;
		sy = 10;
	}
	sx -= 1;
	sy -= 1;
	
	sf::SoundBuffer traf;
	traf.loadFromFile("traf.wav");
	sf::Sound traf2;
	traf2.setBuffer(traf);

	sf::SoundBuffer splash;
	splash.loadFromFile("splash.wav");
	sf::Sound splash2;
	splash2.setBuffer(splash);

	
	/*system("cls");*/

	while (strzelnica[sy][sx] == 5 || strzelnica[sy][sx] == 10 || strzelnica[sy][sx] == 11)
	{
		system("cls");
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Ju¿ strzela³eœ w to pole!! Wybierz inne" << endl;
		cout << "Oto Twoja plansza:" << endl;
		rysujP(plansza);
		SetConsoleTextAttribute(hConsole, 15);
		cout << "W jakie pole chcesz strzeliæ? (wpisz np. B5 lub b5)" << endl;
		rysujP(strzelnica);
		czysc(strzal1);
		SetConsoleTextAttribute(hConsole, 15);
		cin.getline(strzal1, 1000);
		int i = 0;
		cout << endl;
		for (i; strzal1[i] != 0; i++);
		if (i == 2)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
			{
				if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << "Podano poprawne wspólrzêdne" << endl;
					error = 0;
				}
			}
		}
		if (i == 3)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
			{
				if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << "podano poprawne wspolrzedne" << endl;
					error = 0;
				}
			}
		}
		while (error)
		{
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Podaj poprawne wspó³rzêdne!! (wpisz np. C4 lub c4)" << endl;
			cin.getline(strzal1, 1000);
			i = 0;
			for (i; strzal1[i] != 0; i++);
			if (i == 2)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
				{
					if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
					{
						cout << "Podano poprawne wspolrzedne" << endl;
						error = 0;
					}
				}
			}
			if (i == 3)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
				{

					if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
					{
						cout << "Podano poprawne wspolrzedne" << endl;
						error = 0;
					}
				}
			}
		}
		if (i == 2)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
				sx = int(strzal1[0]) - 65 + 1;
			else
				sx = int(strzal1[0]) - 97 + 1;
			sy = int(strzal1[1] - 48);
		}
		if (i == 3)
		{
			if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
				sx = int(strzal1[0]) - 65 + 1;
			else
				sx = int(strzal1[0]) - 97 + 1;
			sy = 10;
		}
		sx -= 1;
		sy -= 1;

	}

	int kolejkiKoniec{};

	if (plansza2[sy][sx] != 0 && plansza2[sy][sx] != -1)
	{
		
		bool zatop = czyZatop(plansza2, sy, sx);
		plansza2[sy][sx] = 5;
		strzelnica[sy][sx] = 11;
		while (!kolejkiKoniec) // bonusowe strzaly przy trafieniu
		{
			oddane++;
			trafione++;
			/*system("cls");*/
			traf2.play();
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Trafiony!!" << endl;
			if (zatop == 1)
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout << "Zatopiony!!" << endl;
				if (czyPusta(plansza2))
					return 1;
			}
			SetConsoleTextAttribute(hConsole, 14);
			cout << "Bonusowy strza³ za trafienie!!" << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Tak wygl¹da Twoja plansza kapitanie: " << endl;
			rysujP(plansza);
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Gdzie chcesz oddaæ strza³?" << endl;
			rysujP(strzelnica);
			SetConsoleTextAttribute(hConsole, 15);
			cin.getline(strzal1, 1000);
			int i = 0;
			for (i; strzal1[i] != 0; i++);
			error = 1;
			if (i == 2)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
				{

					if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
					{
						error = 0;
					}
				}
			}
			if (i == 3)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
				{

					if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
					{
						error = 0;
					}
				}
			}
			while (error)
			{
				cout << "Podaj poprawne wspó³rzêdne!! (wpisz np. C4 lub c4)" << endl;
				cin.getline(strzal1, 1000);
				i = 0;
				for (i; strzal1[i] != 0; i++);
				if (i == 2)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
					{
						if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
						{
							error = 0;
						}
					}
				}
				if (i == 3)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
					{

						if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
						{
							error = 0;
						}
					}
				}
			}
			if (i == 2)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
					sx = int(strzal1[0]) - 65 + 1;
				else
					sx = int(strzal1[0]) - 97 + 1;
				sy = int(strzal1[1] - 48);
			}
			if (i == 3)
			{
				if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
					sx = int(strzal1[0]) - 65 + 1;
				else
					sx = int(strzal1[0]) - 97 + 1;
				sy = 10;
			}
			sx -= 1;
			sy -= 1;

			while (strzelnica[sy][sx] == 5 || strzelnica[sy][sx] == 10 || strzelnica[sy][sx] == 11)
			{
				system("cls");
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Ju¿ strzela³eœ w to pole!! Wybierz inne" << endl;
				cout << "Oto Twoja plansza:" << endl;
				rysujP(plansza);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "W jakie pole chcesz strzeliæ? (wpisz np. B5 lub b5)" << endl;
				rysujP(strzelnica);
				czysc(strzal1);
				SetConsoleTextAttribute(hConsole, 15);
				cin.getline(strzal1, 1000);
				int i = 0;
				cout << endl;
				for (i; strzal1[i] != 0; i++);
				if (i == 2)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
					{
						if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
						{
							SetConsoleTextAttribute(hConsole, 15);
							cout << "Podano poprawne wspólrzêdne" << endl;
							error = 0;
						}
					}
				}
				if (i == 3)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
					{
						if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
						{
							SetConsoleTextAttribute(hConsole, 15);
							cout << "podano poprawne wspolrzedne" << endl;
							error = 0;
						}
					}
				}
				while (error)
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << "Podaj poprawne wspó³rzêdne!! (wpisz np. C4 lub c4)" << endl;
					cin.getline(strzal1, 1000);
					i = 0;
					for (i; strzal1[i] != 0; i++);
					if (i == 2)
					{
						if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
						{
							if (int(strzal1[1] - 48) > 0 && int(strzal1[1] - 48) < 11)
							{
								cout << "Podano poprawne wspolrzedne" << endl;
								error = 0;
							}
						}
					}
					if (i == 3)
					{
						if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75) || (int(strzal1[0]) > 96 && int(strzal1[0]) < 107))
						{

							if (int(strzal1[1] - 48) == 1 && int(strzal1[2] - 48) == 0)
							{
								cout << "Podano poprawne wspolrzedne" << endl;
								error = 0;
							}
						}
					}
				}
				if (i == 2)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
						sx = int(strzal1[0]) - 65 + 1;
					else
						sx = int(strzal1[0]) - 97 + 1;
					sy = int(strzal1[1] - 48);
				}
				if (i == 3)
				{
					if ((int(strzal1[0]) > 64 && int(strzal1[0]) < 75))
						sx = int(strzal1[0]) - 65 + 1;
					else
						sx = int(strzal1[0]) - 97 + 1;
					sy = 10;
				}
				sx -= 1;
				sy -= 1;

			}


			if (plansza2[sy][sx] != 0 && plansza2[sy][sx] != -1)
			{
				zatop = czyZatop(plansza2, sy, sx);
				plansza2[sy][sx] = 5;
				strzelnica[sy][sx] = 11;
				system("cls");
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Trafiony!!" << endl;
				if (zatop == 1)
				{
					SetConsoleTextAttribute(hConsole, 14);
					cout << "Zatopiony!!" << endl;
				}
				if (czyPusta(plansza2))
					return 1;
				SetConsoleTextAttribute(hConsole, 15);
			}
			else
			{
				oddane++;
				system("cls");
				splash2.play();
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Pud³o!! Koniec tury gracza " << kapitan << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				strzelnica[sy][sx] = 10;
				kolejkiKoniec = 1;
				return 0;
			}
		}
	}
	else
	{
		oddane++;
		system("cls");
		splash2.play();
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Pud³o!! Koniec tury gracza " << kapitan << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
		strzelnica[sy][sx] = 10;
		return 0;
	}
}

//funkcja PvP
void PvP()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	setlocale(LC_CTYPE, "Polish");
	int oddane1 = 0;
	int oddane2 = 0;
	int trafione1 = 0;
	int trafione2 = 0;
	int plansza1[10][10]{}, plansza2[10][10]{}, dec{};
	string gracz1 = "stasiek", gracz2 = "witek"; //ustawienie psedonimów graczy
	system("cls");
	cout << "Wpisz nazwê pierwszego gracza: ";
	getline(cin, gracz1);
	system("cls");
	cout << "Wpisz nazwê drugiego gracza: ";
	getline(cin, gracz2);
	system("cls");
	cout << "Wasze nazwy to: " << gracz1 << " i " << gracz2 << endl;
	cout << "Jak¹ opcjê rozstawienia masztowców wybieracie: " << endl; //wybór opcji rozstawienia
	cout << "1. Manualna" << endl;
	cout << "2. Losowa" << endl;
	cin >> dec;
	cin.ignore();
	while (dec != 1 && dec != 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Podaj poprawn¹ wartoœæ!! (1 - Rozstaw Manualny, 2 - Losowy)" << endl;
		cin >> dec;
		cin.ignore();
	}
	if (dec == 1)
	{
		system("cls");
		cout << "Wybraliœcie opcje manualnego rozstawiania" << endl;
		cout << "Proszê gracza " << gracz1 << " o przygotowanie, zaraz rozpoczniemy sekwencjê rozstawiania masztowców" << endl;
		loading();
		system("cls");
		rozstawienieM(plansza1, gracz1); //przejscie do manualnego rozstawienia masztowcow
		system("cls");
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "Proszê gracza " << gracz2 << " o przygotowanie, zaraz rozpoczniemy sekwencjê rozstawiania masztowców" << endl;
		loading();
		rozstawienieM(plansza2, gracz2);
		system("cls");
		cout << "Manualne rozstawienie zakoñczono pomyœlnie" << endl;
		dalej();
	}
	else
	{
		cout << "Wybraliœcie opcjê losowego rozstawienia masztowców" << endl;
		generuj(plansza1); //losowy rozstaw masztwoców na planszach obu graczy
		generuj(plansza2);
		cout << "Usi¹dŸcie wygodnie, zaraz zaczynamy!" << endl;
		loading();
	}
	
	// ---------------------------------------------------------
	bool kolejkiKoniec{};
	int strzalyGracza1{}, strzalyGracza2{}, trafieniaGracza1{}, trafieniaGracza2{}, ZMGracza1{}, ZMGracza2{};
	int strzelnica[10][10]{}, strzelnica2[10][10]{};
	int sx{}, sy{};
	koniecGry = 0;
	while (!koniecGry)
	{
		system("cls");
		cout << "Kapitan " << gracz1 << " proszony o podejscie do planszy" << endl;
		cout << "Wciœnij dowolny przycisk, aby zacz¹æ swoj¹ turê" << endl;
		_getch();

		if (strzal(plansza1, plansza2, strzelnica, gracz1,oddane1, trafione1) == 1)
		{
			system("cls");
			
			SetConsoleTextAttribute(hConsole, 14);
			cout << "ZBITO WSZYTSKIE MASZTOWCE PRZECIWNIKA!!! KONIEC GRY!!!" << endl;
			string p1 = gracz1, p2 = gracz2;
			transform(gracz1.begin(), gracz1.end(), gracz1.begin(), ::toupper);
			cout << "WYGRYWA " << gracz1 << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Liczba oddanych strza³ów przez gracza " << p1 << " to: " << oddane1 << endl;
			cout << "Liczba oddanych strza³ów przez gracza " << p2 << " to: " << oddane2 << endl;
			cout << "Liczba trafionych strza³ów przez gracza " << p1 << " to: " << trafione1 << endl;
			cout << "Liczba trafionych strza³ów przez gracza " << p2 << " to: " << trafione2 << endl;
			dalej();
			koniecGry = 1;
		}


		if (!koniecGry)
		{
			system("cls");
			cout << "Kapitan " << gracz2 << " proszony o podejœcie do planszy" << endl;
			cout << "Wciœnij dowolny przycisk, aby zacz¹æ swoj¹ turê" << endl;
			_getch();

			if (strzal(plansza2, plansza1, strzelnica2, gracz2,oddane2,trafione2) == 1)
			{
				system("cls");
				SetConsoleTextAttribute(hConsole, 14);
				cout << "ZBITO WSZYTSKIE MASZTOWCE PRZECIWNIKA!!! KONIEC GRY!!!" << endl;
				string p1 = gracz1, p2 = gracz2;
				transform(gracz2.begin(), gracz2.end(), gracz2.begin(), ::toupper);
				cout << "WYGRYWA " << gracz2 << endl;
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Liczba oddanych strza³ów przez gracza " << p1 << " to: " << oddane1 << endl;
				cout << "Liczba oddanych strza³ów przez gracza " << p2 << " to: " << oddane2 << endl;
				cout << "Liczba trafionych strza³ów przez gracza " << p1 << " to: " << trafione1 << endl;
				cout << "Liczba trafionych strza³ów przez gracza " << p2 << " to: " << trafione2 << endl;
				koniecGry = 1;
				dalej();
			}
		}

	}

}

//AI komputera
int turaKomputera(int planszaG[10][10], int& oddane, int& trafione)
{
	// PIERWSZY POZIOM TRUDNOŒCI
	if (PT == 0)
	{
		random_device device;
		mt19937 generator(device());
		uniform_int_distribution<int> w(0, 9);
		int ilosc_trafien{};
		int wx = w(generator), wy = w(generator);
		int koniecKolejki{};
		int ZATOP{};
		while (planszaG[wx][wy] == 5 || planszaG[wx][wy] == 13)
		{
			wx = w(generator);
			wy = w(generator);
		}
		if (planszaG[wx][wy] == 1 || planszaG[wx][wy] == 2 || planszaG[wx][wy] == 3 || planszaG[wx][wy] == 4)
		{
			oddane++;
			trafione++;
			if (czyZatop(planszaG, wx, wy))
				ZATOP = 1;
			if (czyPusta(planszaG))
				return 1;

			planszaG[wx][wy] = 5;
			ilosc_trafien++;
			while (planszaG[wx][wy] == 5 || planszaG[wx][wy] == 13)
			{
				wx = w(generator);
				wy = w(generator);
			}
			while (!koniecKolejki)
			{
				if (planszaG[wx][wy] == 1 || planszaG[wx][wy] == 2 || planszaG[wx][wy] == 3 || planszaG[wx][wy] == 4)
				{
					oddane++;
					trafione++;
					if (czyZatop(planszaG, wx, wy))
						ZATOP = 1;
					if (czyPusta(planszaG))
						return 1;
					planszaG[wx][wy] = 5;
					ilosc_trafien++;
				}
				else
				{
					oddane++;
					planszaG[wx][wy] = 13;
					koniecKolejki = 1;
				}
				while (planszaG[wx][wy] == 5 || planszaG[wx][wy] == 13)
				{
					wx = w(generator);
					wy = w(generator);
				}
			}
		}
		else
		{
			oddane++;
			planszaG[wx][wy] = 13;
			system("cls");
			cout << "W tej rundzie Ci siê upiek³o, nic nie trafi³em... " << endl;
		}
		if (ilosc_trafien == 1)
		{
			system("cls");
			if (ZATOP)
				cout << "ZATOPI£EM STATEK!!" << endl;

			cout << "Jedno trafienie, zawsze coœ" << endl;
		}
		if (ilosc_trafien > 1)
		{
			system("cls");
			if (ZATOP)
				cout << "KOLEJNY NA DNO!!" << endl;

			cout << "W tej turze trafi³em " << ilosc_trafien << " razy. " << "Przygotuj siê na wiêcej!!" << endl;
		}
		if (czyPusta(planszaG))
			return 1;
		dalej();
	}
	else // 2 POZIOM TRUDNOŒCI
	{
		random_device device;
		mt19937 generator(device());
		uniform_int_distribution<int> w(0, 9);
		int ilosc_trafien{};
		int wx = w(generator), wy = w(generator);
		int koniecKolejki{};
		int ZATOP{};
		bool eot{};
		bool nietraf{};
		eot = 0;
		while (!nietraf)
		{
			int ilosc1{}, ilosc2{}, ilosc3{}, ilosc6{}, ilosc4{};
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (planszaG[i][j] == 1)
					{
						ilosc1++;
					}
					if (planszaG[i][j] == 2)
					{
						ilosc2++;
					}
					if (planszaG[i][j] == 3)
					{
						ilosc3++;
					}
					if (planszaG[i][j] == 6)
					{
						ilosc6++;
					}
					if (planszaG[i][j] == 4)
					{
						ilosc4++;
					}
				}
			}
			if (ilosc3 == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (planszaG[i][j] == 3)
						{
							oddane += 2;
							trafione += 2;
							eot = 1;
							planszaG[i][j] = 5;
							if (czyPusta(planszaG))
								return 1;
						}
					}
				}
			}
			if (ilosc6 == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (planszaG[i][j] == 6)
						{
							oddane += 2;
							trafione += 2;
							eot = 1;
							planszaG[i][j] = 5;
							if (czyPusta(planszaG))
								return 1;
						}
					}
				}
			}
			if (ilosc4 == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (planszaG[i][j] == 4)
						{
							oddane += 2;
							trafione += 2;
							eot = 1;
							planszaG[i][j] = 5;
							if (czyPusta(planszaG))
								return 1;
						}
					}
				}
			}


			if (ilosc1 == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (planszaG[i][j] == 1)
						{
							oddane += 2;
							trafione += 2;
							planszaG[i][j] = 5;
							if (czyPusta(planszaG))
								return 1;
						}
					}
				}
			}

			if (ilosc2 == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (planszaG[i][j] == 2)
						{
							oddane += 2;
							trafione += 2;
							planszaG[i][j] = 5;
							if (czyPusta(planszaG))
								return 1;
						}
					}
				}
			}

			

			if (poX != -1 && poY != -1)
			{
				if (kieru == 1)
				{
					if (poX - 1 > -1)
					{
						if (planszaG[poX - 1][poY] == 13)
						{
							kieru = 2;
						}
						else
						{
							if (planszaG[poX - 1][poY] == 2 || planszaG[poX - 1][poY] == 3 || planszaG[poX - 1][poY] == 6 || planszaG[poX - 1][poY] == 4)
							{
								planszaG[poX - 1][poY] = 5;
								if (czyPusta(planszaG))
									return 1;
								ilosc_trafien++;
								poX = -1;
								poY = -1;
								kieru = 0;
								eot = 1;
								nietraf = 0;
							}
							else
							{
								planszaG[poX - 1][poY] = 13;
								kieru = 2;
								nietraf = 1;
								eot = 1;
							}
						}
					}
					else
					{
						kieru = 2;
					}
				}
				if (kieru == 2 && !eot)
				{

					if (poX + 1 < 10)
					{
						if (planszaG[poX + 1][poY] == 13)
						{
							kieru = 3;
						}
						else
						{
							if (planszaG[poX + 1][poY] == 2 || planszaG[poX + 1][poY] == 3 || planszaG[poX + 1][poY] == 6 || planszaG[poX + 1][poY] == 4)
							{
								planszaG[poX + 1][poY] = 5;

								if (czyPusta(planszaG))
									return 1;

								ilosc_trafien++;
								poX = -1;
								poY = -1;
								kieru = 0;
								eot = 1;
								nietraf = 0;
							}
							else
							{
								kieru = 3;
								eot = 1;
								nietraf = 1;
							}
						}
					}
					else
					{
						kieru = 3;
					}
				}
				if (kieru == 3 && !eot)
				{
					if (poY - 1 > 0)
					{
						if (planszaG[poX][poY - 1] == 13)
						{
							kieru = 4;
						}
						else
						{
							if (planszaG[poX][poY - 1] == 2 || planszaG[poX][poY - 1] == 3 || planszaG[poX][poY - 1] == 6 || planszaG[poX][poY - 1] == 4)
							{
								planszaG[poX][poY - 1] = 5;

								if (czyPusta(planszaG))
									return 1;

								ilosc_trafien++;
								poX = -1;
								poY = -1;
								kieru = 0;
								eot = 1;
								nietraf = 0;
							}
							else
							{
								kieru = 4;
								eot = 1;
								nietraf = 1;
							}
						}
					}
					else
					{
						kieru = 4;
					}
				}
				if (kieru == 4 && !eot)
				{
					if (poY + 1 < 10)
					{
						if (planszaG[poX][poY + 1] == 13)
						{
							kieru = 0;
						}
						else
						{
							if (planszaG[poX][poY + 1] == 2 || planszaG[poX][poY + 1] == 3 || planszaG[poX][poY + 1] == 6 || planszaG[poX][poY + 1] == 4)
							{
								planszaG[poX][poY + 1] = 5;
								if (czyPusta(planszaG))
									return 1;
								ilosc_trafien++;
								poX = -1;
								poY = -1;
								kieru = 0;
								eot = 1;
								nietraf = 0;
							}
							else
							{
								kieru = 0;
								eot = 1;
								nietraf = 1;
							}
						}
					}
					else
					{
						kieru = 0;
					}
				}
			}
			if (!nietraf)
			{
				do
				{
					wx = w(generator);
					wy = w(generator);
				} while (planszaG[wx][wy] == 5 || planszaG[wx][wy] == 13);

				if (planszaG[wx][wy] == 1)
				{
					trafione++;
					oddane++;
					ilosc_trafien++;
					planszaG[wx][wy] = 5;
					if (czyPusta(planszaG))
						return 1;
					poX = -1;
					poY = -1;
					nietraf = 0;
				}
				else if (planszaG[wx][wy] == 2)
				{
					trafione++;
					oddane++;
					planszaG[wx][wy] = 5;
					if (czyPusta(planszaG))
						return 1;
					ZATOP = czyZatop(planszaG, wx, wy);
					if (!ZATOP)
					{
						poX = wx;
						poY = wy;
						kieru = 1;
						nietraf = 0;
					}
					else
					{
						poX = -1;
						poY = -1;
						nietraf = 0;
					}
					ilosc_trafien++;
				}
				else if (planszaG[wx][wy] == 3 || planszaG[wx][wy] == 6 || planszaG[wx][wy] == 4)
				{
					trafione++;
					oddane++;
					planszaG[wx][wy] = 5;
					if (czyPusta(planszaG))
						return 1;
					ZATOP = czyZatop(planszaG, wx, wy);
					if (!ZATOP)
					{
						poX = wx;
						poY = wy;
						kieru = 1;
						nietraf = 0;
					}
					else
					{
						poX = -1;
						poY = -1;
						nietraf = 0;
					}
					ilosc_trafien++;
				}
				else
				{
					oddane++;
					planszaG[wx][wy] = 13;
					poX = -1;
					poY = -1;
					nietraf = 1;
					cout << "PUD£O" << endl;
				}
			}
			else
			{
				cout << "PUD£O AHHHH" << endl;
			}
		}
	}
}

void PvC()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_CTYPE, "Polish");
	system("cls");
	string kapitan;
	int oddaneG = 0;
	SetConsoleTextAttribute(hConsole, 15);
	int planszaG[10][10]{}, strzelnicaG[10][10]{}, planszaK[10][10]{}, dec{};
	cout << "Wybra³eœ tryb gry przeciwko mnie, komputerowi." << endl;
	cout << "Zanim zaczniemy chcia³bym poznaæ Twoje imiê, kapitanie: " << endl;
	getline(cin,kapitan);
	system("cls");
	cout << kapitan << ", có¿ za cudne imiê!" << endl;
	cout << "Ale ale, my tu gadu gadu, a szykuje siê niez³a jatka!" << endl;
	cout << "Chcesz rozstawiæ swoje okrêty manualnie, czy mam je rozstawiæ za Ciebie?" << endl;
	cout << "1. Manualnie" << endl << "2. Losowo" << endl;;
	cin >> dec;
	while (dec != 1 && dec != 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Podaj poprawn¹ wartoœæ!! (1 - Manualne lub 2 - Losowe)" << endl;
		cin >> dec;
		system("cls");
	}
	cin.ignore();
	if (dec == 1)
	{
		system("cls");
		cout << "Wybra³eœ manualn¹ opcjê rozstawienia statków, zatem zaczynamy!!" << endl;
		rozstawienieM(planszaG, kapitan);
	}
	else
	{
		system("cls");
		cout << "Wybra³eœ opcje losowego rozmieszczenia Twojej floty" << endl;
		cout << "Rozpoczynam procedurê rozstawienia" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		loading();
		generuj(planszaG);
	}
	dec = 0;
	generuj(planszaK);

	cout << "Jeszcze zostaje kwestia poziomu trudnoœci" << endl;
	cout << "Mam Ci daæ fory, czy gramy jak równi sobie?" << endl;
	cout << "1. Lepiej mnie oszczêdŸ!" << endl;
	cout << "2. Idziemy na ca³oœæ!" << endl;
	cin >> dec;
	while (dec != 1 && dec != 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Podaj poprawn¹ wartoœæ!! (1 - £atwiej lub 2 - Po ludzku)" << endl;
		cin >> dec;
		system("cls");
	}
	cin.ignore();

	if (dec == 1)
		PT = 0;
	else
		PT = 1;

	dec = 0;
	system("cls");
	cout << "Jak sobie ¿yczysz, zaraz zaczynamy" << endl;
	cout << "Czy chcesz podejrzeæ na chwilê moj¹ planszê przed rozpoczêciem gry??" << endl;
	cout << "1. Nie" << endl << "2. Tak" << endl;
	cin >> dec;
	while (dec != 1 && dec != 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Podaj prosze poprawn¹ wartosc!!(1 - Nie lub 2 - Tak)" << endl;
		cin >> dec;
		cin.clear();
		system("cls");
	}
	cin.ignore();

	if (dec == 1)
	{
		system("cls");
		cout << "Odwa¿nie!! Zatem pora zacz¹æ bitwê" << endl;
		dalej();
	}
	else
	{
		system("cls");
		cout << "Nie ma problemu. Oto moja plansza" << endl;
		rysujP(planszaK);
		dalej();
		cout << "Pora zacz¹æ bitwê!" << endl;
	}
	bool koniecGry{};
	cout << kapitan << ", Ty zaczynasz rozgrywkê, powodzenia!!" << endl;
	int trafioneG{};
	int oddaneK{};
	int trafioneK{};
	while (!koniecGry)
	{

		if (strzal(planszaG, planszaK, strzelnicaG, kapitan, oddaneG, trafioneG) == 1)
		{
			system("cls");
			string p = kapitan;
			transform(kapitan.begin(), kapitan.end(), kapitan.begin(), ::toupper);
			SetConsoleTextAttribute(hConsole, 14);
			cout << "ZBI£EŒ WSZYSTKIE MOJE MASZTOWCE!! WYGRYWASZ!!" << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Liczba oddanych strza³ów przez gracza " << p << " to: " << oddaneG+1 << endl;
			cout << "Liczba oddanych strza³ów przez komputer to: " << oddaneK << endl;
			cout << "Liczba trafionych strza³ów przez gracza " << p << " to: " << trafioneG+1 << endl;
			cout << "Liczba trafionych strza³ów przez komputer to: " << trafioneK << endl;
			dalej();
			koniecGry = 1;
		}
		loading();
		/*strzal(planszaG, planszaK, strzelnicaG, kapitan);*/
		cout << "Przysz³a kolej na mnie" << endl;
		/*this_thread::sleep_for(chrono::milliseconds(1000));*/
		/*loading();*/
		if (!koniecGry)
		{
			if (turaKomputera(planszaG, oddaneK,trafioneK)==1)
			{
				system("cls");
				SetConsoleTextAttribute(hConsole, 12);
				cout << "ZBI£EM WSZYSTKIE TWOJE MASZTOWCE!!! PRZEGRA£EŒ!!!" << endl;
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Liczba oddanych strza³ów przez gracza " << kapitan << " to: " << oddaneG << endl;
				cout << "Liczba oddanych strza³ów przez komputer to: " << oddaneK << endl;
				cout << "Liczba trafionych strza³ów przez gracza " << kapitan << " to: " << trafioneG << endl;
				cout << "Liczba trafionych strza³ów przez komputer to: " << 20 << endl;
				dalej();
				koniecGry = 1;
			}
		}
		

	}

}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_CTYPE, "Polish");
	sf::Music muzyka;
	muzyka.openFromFile("8bit.wav");
	muzyka.play();
	muzyka.setLoop(1);
	while (1)
	{
		bool muz{1};
		int dec{};
		
		while (dec != 1 && dec != 2)
		{

			if (muz == 1)
			{
				muzyka.play();
				muzyka.setLoop(1);
			}
			else if (muz==0)
			{
				muzyka.stop();
			}

			system("cls");
			cout.width(1);
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Witaj w grze " << endl;
			SetConsoleTextAttribute(hConsole, 9);
			cout << "     _        _   _    _ " << endl;
			cout << "    | |      | | | |  (_)" << endl;
			cout << " ___| |_ __ _| |_| | ___ " << endl;
			cout << "/ __| __/ _` | __| |/ / |" << endl;
			cout << "\\__ \\ || (_| | |_|   <| |" << endl;
			cout << "|___/\\__\\__,_|\\__|_|\\_\\_|" << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Wybierz tryb gry lub zapoznaj siê z instrukcj¹:" << endl;
			cout << "1. Tryb dla dwóch graczy" << endl;
			cout << "2. Tryb dla jednego gracza (przeciwko komputerowi)" << endl;
			cout << "3. Instrukcja" << endl;
			cout << "4. Wy³¹cz/w³¹cz muzykê" << endl;
			cout << "5. WyjdŸ z programu" << endl;
			cin >> dec;
			while (dec != 1 && dec != 2 && dec != 3 && dec != 4 && dec != 5)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "Podaj poprawn¹ wartoœæ!! (1 - PvP,  2 - PvC, 3 - Instrukcja, 4 - Wy³¹cz/w³¹cz muzykê, 5 - Wyjœcie)" << endl;
				cin >> dec;
				system("cls");
			}
			cin.ignore();

			if (dec == 1)
				PvP();
			else if (dec == 2)
				PvC();
			else if (dec == 3)
			{
				string odczyt;
				ifstream plik("instrukcja.txt");
				if (plik.is_open())
				{
					system("cls");
					while (!plik.eof())
					{
						getline(plik, odczyt);
						cout << odczyt << endl;
					}
					dalej();
					system("cls");

				}
				else
				{
					cout << "B³¹d przy próbie otwarcia instrukcji, musisz radziæ sobie sam, sorry" << endl;
				}
			}
			else if(dec==4)
			{
				if (muz == 1)
					muz = 0;
				else
					muz = 1;
			}
			else
			{
				exit(0);
			}
		}
		cout << endl;
		cout << endl;
	}
}