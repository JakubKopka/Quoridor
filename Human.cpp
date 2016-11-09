#include "Human.h"
#include "Gra.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

#include <fstream>





using namespace std;

extern Gra gra;

Human::Human(void)
{
}

Human::Human(int x, int y, string imie) : Player(x, y, imie) 
{

}

Human::~Human(void)
{
}


void Human::ruch() 
{

	Player * e;				//przeciwnik 
	if (gra.gracz1 == this) 
	{
		e = gra.gracz2;
		cout << "Ruch gracza: " << gra.gracz1->get_imie() << endl;
	}
	else 
	{
		e = gra.gracz1;
		cout << "Ruch gracza: " << gra.gracz2->get_imie() << endl;
	}
	cout << "Co chcesz zrobic?" << endl;
	cout << "1 - Ustaw scianke," << endl;
	cout << "2 - Rusz sie pionkiem" << endl;
	cout << "3 - Zapisz gre" << endl;
	int wybor = 0;
	cout << "Twoj wybor: ";
	while (!(cin >> wybor) || wybor < 1 || wybor > 3 || getchar() != '\n')
	{
		cout << "BLAD! Podaj jeszcze raz: ";
		while (getchar() != '\n');
		cin.clear();
		cin.sync();
	}
	if (wybor == 1) // postaw scianke
	{
		bool wykonano_ruch = false;
		while (true) 
		{
			int x, y;
			int orientacja;
			string wsp;
			cout << "Podaj wspolrzedne gdzie chcesz postawic scianke (np. A1): ";
			while (!(cin >> wsp) || wsp[0] < 'A' || wsp[0] > 'H' || wsp[1] < '1' || wsp[1]> '8' || getchar() != '\n')
			{
				cin.clear();
				cin.sync();
				cout << "BLAD! Podaj jeszcze raz: ";
				while (getchar() != '\n');
			}

			x = (wsp[0] - 'A') * 2 + 1;
			y = (wsp[1] - '1') * 2 + 1;
			if (gra.get_pole(x,y) == '.') 
			{
				cout << "Jaka to ma byc scianka?" << endl;
				cout << "1. Pionowa" << endl;
				cout << "2. Pozioma" << endl;
				cout << "Twoj wybor: ";
				while (!(cin >> orientacja) || orientacja < 1 || orientacja > 2 || getchar() != '\n')
				{
					cout << "BLAD! Podaj jeszcze raz: ";
					while (getchar() != '\n');
					cin.clear();
					cin.sync();
				}
				if (orientacja == 1) 
				{
					for (int y2 = y - 2; y2 <= y + 2; y2++) 
					{
						gra.ustaw_scianke(x, y2);
						wykonano_ruch = true;
					}
				}
				else if (orientacja == 2) 
				{
					for (int x2 = x - 2; x2 <= x + 2; x2++) 
					{
						gra.ustaw_scianke(x2, y);
						wykonano_ruch = true;
					}
				}
				if (wykonano_ruch) 
				{
					break;
				}
			}
			else
			{
				cout << "Tutaj juz nie mozna postawic scianki!" << endl;
				continue;
			}

		}



	}
	else if (wybor == 2) // ruch
	{
		int tmp;
		clock_t timer = clock();	//po jakim czasie wysweitli siê znowu error 

		bool wykonano_ruch = false;
		while (true) 
		{
			int kod_bledu = 0;


			if (GetKeyState(VK_LEFT) < 0) {
				if (gra.czy_scianka(x -1 , y))
				{
					kod_bledu = 3;
				}
				else if (x == 0) 
				{
					kod_bledu = 1;
				}
				else if (x == 2 && e->get_x() == 0 && y == e->get_y())
				{
					kod_bledu = 2;
				}
				else if (x - 2 == e->get_x() && y == e->get_y())
				{
					if (gra.czy_scianka(x - 3, y))
					{
						kod_bledu = 3;
					}
					else
					{
						x -= 4;
						wykonano_ruch = true;
					}
				}
				else 
				{
					x -= 2;
					wykonano_ruch = true;
				}

			}
			else if (GetKeyState(VK_RIGHT) < 0) 
			{
				if (gra.czy_scianka(x + 1, y))
				{
					kod_bledu = 3;
				}
				else if (x == 16) 
				{
					kod_bledu = 1;
				}
				else if (x == 14 && e->get_x() == 16 && y == e->get_y())
				{
					kod_bledu = 2;
				}
				else if (x + 2 == e->get_x() && y == e->get_y())
				{
					if (gra.czy_scianka(x + 3, y))
					{
						kod_bledu = 3;
					}
					else
					{
						x += 4;
						wykonano_ruch = true;
					}
				}
				else
				{
					x += 2;
					wykonano_ruch = true;
				}

			}
			else if (GetKeyState(VK_UP) < 0)
			{
				if (gra.czy_scianka(x , y - 1))
				{
					kod_bledu = 3;
				}
				else if (y == 0)
				{
					kod_bledu = 1;
				}
				else if (y == 2 && e->get_y() == 0 && x == e->get_x())
				{
					kod_bledu = 2;
				}
				else if (y - 2 == e->get_y() && x == e->get_x())
				{
					if (gra.czy_scianka(x , y - 3))
					{
						kod_bledu = 3;
					}
					else
					{
						y -= 4;
						wykonano_ruch = true;
					}
				}
				else 
				{
					y -= 2;
					wykonano_ruch = true;
				}

			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				if (gra.czy_scianka(x, y + 1))
				{
					kod_bledu = 3;
				}
				else if (y == 16) 
				{
					kod_bledu = 1;
				}
				else if (y == 14 && e->get_y() == 16 && x == e->get_x())
				{
					kod_bledu = 2;
				}
				else if (y + 2 == e->get_y() && x == e->get_x())
				{
					if (gra.czy_scianka(x , y + 3 ))
					{
						kod_bledu = 3;
					}
					else
					{
						y += 4;
						wykonano_ruch = true;
					}
				}
				else 
				{
					y += 2;
					wykonano_ruch = true;
				}

			}
			
			if (wykonano_ruch) 
			{
				break;
			}
			else
			{
				if (clock() < timer) 
				{
					continue;
				}
				else 
				{
					timer = clock() + 300;
				}

				if (kod_bledu == 1) 
				{
					cout << "Nie mozesz wykonac tego ruchu, poniewaz wyjdziesz z planszy!" << endl;
				}
				else if (kod_bledu == 2) 
				{
					cout << "Nie mozesz przeskoczyc pionka przeciwnka, poniewaz wyjdziesz z planszy!" << endl;
				}
				else if (kod_bledu == 3) 
				{
					cout << "Nie mozna wykonac ruchu poniewaz jest scianka!" << endl;
				}
				continue;
			}

		}



	}
	else if (wybor == 3) // Zapis gry
	{
		gra.zrob_save();
		exit(1);
	}
}