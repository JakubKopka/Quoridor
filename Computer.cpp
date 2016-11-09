#include "Computer.h"
#include "ctime"
#include <iostream>
#include "Gra.h"
#include <Windows.h>

using namespace std;
extern Gra gra;
Computer::Computer(void)
{
	srand(time(NULL));
}

Computer::Computer(int x, int y, string imie, int _poziom) : Player(x, y, imie), poziom(_poziom)
{
}

Computer::~Computer(void)
{
}


void Computer::ruch()
{
	int losowanie;
	Player * e;				//przeciwnik
	if (gra.gracz1 == this) 
	{
		e = gra.gracz2;
	}
	else 
	{
		e = gra.gracz1;
	}
	losowanie = rand() % 100 + 1;
	if (losowanie > 75)// stawianie scianek, prawdopodobieñstwo 25%
	{
		bool wykonano_ruch = false;
		int x, y;
		int orientacja;
		int lo;//losowanie orientacji
		string wsp;
		// LOSOWANIE WSPÓ£RZÊDNYCH (np. A1)
		while (true) 
		{

			x = (rand() % 8) * 2 + 1;
			y = (rand() % 8) * 2 + 1;
			if (gra.get_pole(x,y) == '.') 
			{
				orientacja = rand() % 2;
				if (orientacja == 0) 
				{
					for (int y2 = y - 2; y2 <= y + 2; y2++) 
					{
						gra.ustaw_scianke(x, y2);
						wykonano_ruch = true;
					}
				}
				else if (orientacja == 1)
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
				continue;
			}
		}
	}
	else if (losowanie <= 75) //wykonaj ruch pionka, prawdopodobieñstwo 75%
	{
		int tmp;
		bool wykonano_ruch = false;
		int ruch = 3;
		
		while (true) {
			int kod_bledu = 0;
			if (ruch == 3) 
			{ // Do do³u
				if (gra.czy_scianka(x, y + 1))
				{
					kod_bledu = 3;
					ruch = rand() % 3;
				}
				else if (y == 16) 
				{
					kod_bledu = 1;
					ruch = rand() % 1 + 3;
				}
				else if (y == 14 && e->get_y() == 16 && x == e->get_x())
				{
					kod_bledu = 2;
					ruch = rand() % 3;
				}
				else if (y + 2 == e->get_y() && x == e->get_x())
				{
					if (gra.czy_scianka(x, y + 3))
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
			else if (ruch == 0) 
			{ // W lewo
				if (gra.czy_scianka(x - 1, y))
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
			else if (ruch == 1) 
			{ // W prawo
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
			else if (ruch == 2)
			{ // Do góry
				if (gra.czy_scianka(x, y - 1))
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
			if (wykonano_ruch) 
			{
				break;
			}
			else 
			{
				continue;
			}
		}
	}
}