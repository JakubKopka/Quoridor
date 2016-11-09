#pragma once
#include <string>
using std::string;

class Player
{
protected:
	int x;
	int y;
	string imie;

public:
	Player(void);
	Player(int x, int y, string imie);
	~Player(void);
	virtual void ruch() = 0;
	virtual string toString() = 0;

	string get_imie();
	void set_imie(string imie);
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
};

