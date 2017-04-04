#include "Player.h"


Player::Player(void)
{
}


Player::Player(int _x, int _y, string _imie) : x(_x), y(_y), imie(_imie)
{
}

Player::~Player(void)
{
}

string Player::get_imie()
{
	return imie;
}


void Player::set_imie(string imie)
{
	this->imie = imie;
}

int Player::get_x()
{ 
	return x;
}
int Player::get_y()
{
	return y;
}
void Player::set_x(int x)
{
	this->x = x;
}
void Player::set_y(int y)
{
	this->y = y;
}
