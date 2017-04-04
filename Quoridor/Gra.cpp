#include "Gra.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <typeinfo>
#include <Windows.h>
#include <fstream>
#include <time.h>



using namespace std;




Gra::Gra(void) : ruch_gracza(1)
{

	for (int w = 0; w < W; w++)
	{
		for (int k = 0; k < K; k++)
		{
			mapa[w][k] = '.';
			if (k % 2 == 0 && w % 2 == 0) 
			{
				mapa[w][k] = ' ';
			}
		}
	}
}


Gra::~Gra(void)
{
	delete gracz1;
	delete gracz2;
}

void Gra::set_pole(int x, int y, char c)
{
	mapa[y][x] = c;
}
char Gra::get_pole(int x, int y)
{
	return mapa[y][x];
}


void Gra::rysuj_plansze()
{
	// # - symbol scianek, pionek nie moze przez nie przejsc 

	cout << "    ";
	for (int k = 0; k < K / 2; k++)
	{
		cout << char('A' + k) << "   ";
	}
	cout << endl;


	for (int w = 0; w < W; w++)
	{
		if (w % 2) 
		{
			cout << (w / 2) + 1 << " ";
		}
		else 
		{
			cout << "  ";
		}

		for (int k = 0; k < K; k++)
		{
			if (k == gracz1->get_x() && w == gracz1->get_y()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << 'o'<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else if (k == gracz2->get_x() && w == gracz2->get_y()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << 'o'<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
			{
				cout << mapa[w][k] << " ";
			}

		}
		cout << endl;
	}
}



void Gra::menu()
{
	int wybor = 0;
	cout << "========================" << endl;
	cout << "======  QUORIDOR  ======" << endl;
	cout << "========================" << endl;
	cout << "Wybierz tryb gry: " << endl;
	cout << "1- Czlowiek vs. Komputer" << endl;
	cout << "2- Czlowiek vs. Czlowiek" << endl;
	cout << "3- Wczytaj zapis z pliku" << endl;
	cout << "4- Tablica wynikow" << endl;
	cout << "========================" << endl;
	cout << "Twoj wybor: ";
	while (!(cin >> wybor) || wybor < 1 || wybor > 4 || getchar() != '\n')
	{
		cout << "BLAD! Podaj jeszcze raz: ";
		while (getchar() != '\n');
		cin.clear();
		cin.sync();
	}

	if (wybor == 1) // Czlowiek vs. Komputer
	{
		cout << "Podaj nazwe gracza: ";
		cin >> nazwaGracza1;
		gracz1 = new Human(8, 16, nazwaGracza1);
		gracz2 = new Computer(8, 0, "Komputer", 1);
		rozgrywka();
	}
	else if (wybor == 2)// Czlowiek vs. Czlowiek
	{
		cout << "Podaj nazwe gracza(gracz1): ";
		cin >> nazwaGracza1;
		cout << "Podaj nazwe gracza(gracz2): ";
		cin >> nazwaGracza2;
		gracz1 = new Human(8, 16, nazwaGracza1);
		gracz2 = new Human(8, 0, nazwaGracza2);
		rozgrywka();
	}
	else if (wybor == 3) //wczytanie z pliku
	{
		if (wczytaj_save() == false)
		{
			exit(1);
		}
		else
		{
			rozgrywka();
		}
	}

	else if (wybor == 4) // Tablica wynikow
	{
		tablica_wynikow();
	}
}

void Gra::rozgrywka()
{
	while (true)
	{
		system("cls");
		rysuj_plansze();
		if (ruch_gracza == 1)
		{
			gracz1->ruch();
			system("cls");
			rysuj_plansze();
			if (ktoWygral() == 1)
			{
				cout << "Gracz 1 (" << str(gracz1)  << "-" << gracz1->get_imie() << ") wygral!" << endl;
				dodanie_wyniku_do_tablicy(gracz1->get_imie());
				break;
			}
			ruch_gracza = 2;
		}
		else if (ruch_gracza == 2)
		{
			gracz2->ruch();
			system("cls");
			rysuj_plansze();
			if (ktoWygral() == 2)
			{
				/*
				string typ;
				
				if (typeid(*gracz2) == typeid(Computer))
				{
					typ = "Komputer";
				}
				else
				{
					typ = "Czlowiek";
				}
				*/
				cout << "Gracz 2 (" << str(gracz2) << "-" << gracz2->get_imie() << ") wygral!" << endl;
				dodanie_wyniku_do_tablicy(gracz2->get_imie());
				break;
			}
			ruch_gracza = 1;
		}
	}
}

int Gra::ktoWygral()
{
	if (gracz2->get_y() == 16)
	{
		return 2;
	}
	else if (gracz1->get_y() == 0)
	{
		return 1;
	}
	return 0;
}



void Gra::ustaw_scianke(int x, int y)
{
	if (x >= 0 && x < K && y >= 0 && y < W)
	{
		mapa[y][x] = '#';
	}
}

int Gra::czy_scianka(int x, int y)
{
	if (mapa[y][x] == '#')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Gra::zrob_save()
{
	ofstream plik;
	plik.open("save.txt");
	plik.clear();

	string typ1;
	if (typeid(*gracz1) == typeid(Computer))
	{
		typ1 = "Computer";
	}
	else
	{
		typ1 = "Human";
	}
	string typ2;
	if (typeid(*gracz2) == typeid(Computer))
	{
		typ2 = "Computer";
	}
	else
	{
		typ2 = "Human";
	}
	plik << ruch_gracza << endl;
	plik << typ1 << " " << gracz1->get_imie() << " " << gracz1->get_x() << " " << gracz1->get_y() << endl;
	plik << typ2 << " " << gracz2->get_imie() << " " << gracz2->get_x() << " " << gracz2->get_y() << endl;
	for (int w = 0; w < W; w++)
	{
		for (int k = 0; k < K; k++)
		{
			plik << mapa[w][k];
		}
		plik << endl;
	}
	plik.close();
}

bool Gra::wczytaj_save()
{
	string komunikat = "Blad pliku";
	ifstream plik;
	plik.open("save.txt");
	string imie1;
	string imie2;
	string typ1;
	string typ2;
	int x1, y1, x2, y2;
	plik >> ruch_gracza;
	plik >> typ1 >> imie1 >> x1 >> y1;
	plik >> typ2 >> imie2 >> x2 >> y2;

	//Sprawdzenie poprawnosci pliku save
	if (plik.fail()) 
	{
		cout << komunikat << endl;;
		return false;
	}
	if (typ1 != "Human" && typ1 != "Computer" || typ2 != "Human" && typ2 != "Computer")
	{
		cout << komunikat << endl;
		return false;
	}

	if (!(ruch_gracza == 1 || ruch_gracza == 2)) 
	{
		cout << komunikat << endl;
		return false;
	}

	if (x1 >=K || x2>=K || x1 < 0 || x2 < 0 || y1 >= W || y2 >= W || y1 < 0 || y2 < 0)
	{
		cout << komunikat << endl;
		return false;
	}


	// typ1 jest zawsze HUMAN
	gracz1 = new Human(x1, y1, imie1);
	if (typ2 == "Human")
	{
		gracz2 = new Human(x2, y2, imie2);
	}
	else if (typ2 == "Computer")
	{
		gracz2 = new Computer(x2, y2, "Komputer", 1);
	}
	
	plik.get();
	for (int w = 0; w < W; w++)
	{
		for (int k = 0; k < K; k++)
		{
			mapa[w][k] = plik.get();
			
			
		}
		plik.get();
	}

	plik.close();
	return true;
}

bool Gra::tablica_wynikow()
{
	string komunikat = "Blad pliku";
	ifstream plik;
	plik.open("wyniki.txt");
	string nazwa;
	string data;
	string godzina;
	system("cls");
	cout << "Tablica wynikow gry:" << endl;
	if (plik.good())
	{
		while (plik >> data >> godzina >> nazwa)
		{

			if (data.size() != 10)
			{
				cout << komunikat << endl;
				return false;
			}
			if(godzina.size()!= 8)
			{
				cout << komunikat << endl;
				return false;
			}
			if (plik.good())
			{
				cout << data << " " << godzina << " Wygrana: " << nazwa << endl;
			}
			else
			{
				cout << komunikat << endl;
				return false;
			}

		}
	}
	else
	{
		cout << komunikat << endl;
		return false;
	}
	cout << endl;
	plik.close();
	return true;
}

void Gra::dodanie_wyniku_do_tablicy(string nazwa)
{
	ofstream plik;
	plik.open("wyniki.txt", ios::app);
	char data[30];
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(data, 90, "%Y.%m.%d %H:%M:%S ", timeinfo);

	plik << data << " " << nazwa << endl;


	plik.close();
}
