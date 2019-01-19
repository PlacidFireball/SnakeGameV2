#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder() const; 
	int GridWidth() const; 
	int GridHeight() const; 
	bool IsInsideBoard(const Location& loc) const; 
private:
	static constexpr int dimension = 20; 
	static constexpr int width = 32;
	static constexpr int height = 24; 
	Graphics& gfx; 
	static constexpr int offset = dimension;
	Color borderColor = Colors::Blue; 
};