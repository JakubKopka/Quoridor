#pragma once
#include "player.h"
class Computer : public Player
{
public:
	int poziom; //1 - kompletny random, 2 - lekka strategia, 3 - lekki oszust
public:

	Computer(void);
	Computer(int x, int y, string imie, int poziom);
	~Computer(void);
	void ruch();
	string toString() { return "Komputer"; }
};

