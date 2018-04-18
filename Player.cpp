#include "Player.h"

Player::Player(const wchar_t p, const int c)
	: playerName(p), colour(c), balance(5000) {}

Player::~Player() {}

const int Player::GetColour() { return colour; }
const wchar_t Player::GetName() { return playerName; }
const int Player::GetBalance() { return balance; }

void Player::Buy(const int price) 
{
	balance -= price;
}
	