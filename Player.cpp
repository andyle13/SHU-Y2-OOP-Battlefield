#include "Player.h"

Player::Player(std::string p, const int c)
	: playerName(p), colour(c), balance(5000) {}

Player::~Player() {}

const int Player::GetColour() { return colour; }