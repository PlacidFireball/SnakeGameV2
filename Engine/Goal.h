#pragma once

#include "Snake.h"
#include "Board.h"
#include <random> 

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Draw(Board& brd) const; 
	const Location& GetLocation() const; 

private:
	Location loc; 
	static constexpr Color c = Colors::Red; 
};