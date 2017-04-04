#pragma once
#include "player.h"
class Human : public Player
{
public:
	Human(void);
	Human(int x, int y, string imie);
	~Human(void);
	void ruch();
	string toString() { return "Czlowiek"; }
};

