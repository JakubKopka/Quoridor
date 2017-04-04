#pragma once
#include "Player.h"

#define W 17
#define K 17

template <typename T>
string str(T * t)
{
	return t->toString();
}

class Gra
{
private:
	string nazwaGracza1;
	string nazwaGracza2;
	int ruch_gracza;
	char mapa[W][K];
public:
	Player * gracz1;
	Player * gracz2;

	Gra(void);
	~Gra(void);
	void rysuj_plansze();
	void menu();
	void rozgrywka();
	int ktoWygral();
	void ustaw_scianke(int x, int y);
	int czy_scianka(int x, int y);
	void zrob_save();
	bool wczytaj_save();
	bool tablica_wynikow();
	void dodanie_wyniku_do_tablicy(string nazwa);
	void set_pole(int x, int y, char c);
	char get_pole(int x, int y);
};

