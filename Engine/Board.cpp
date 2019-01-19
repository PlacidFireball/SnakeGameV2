#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx( gfx )
{}



void Board::DrawCell(const Location & loc, Color c)
{
	//assert(loc.x > 0);
	//assert(loc.x < width);
	//assert(loc.y > 0);
	//assert(loc.y < height); 
	gfx.DrawRectDim(loc.x * dimension + offset, loc.y*dimension + offset, dimension, dimension, c);
}

void Board::DrawBorder() const
{
	gfx.DrawRectDim(0, 0, dimension, dimension*height, borderColor);
	gfx.DrawRectDim(0, 0, dimension*width, dimension, borderColor); 
	gfx.DrawRectDim(width*dimension, 0, dimension, dimension*height, borderColor); 
	gfx.DrawRectDim(0, height*dimension, dimension*width + dimension, dimension, borderColor); 
}


int Board::GridWidth() const
{
	return width;
}

int Board::GridHeight() const
{
	return height; 
}

bool Board::IsInsideBoard(const Location & loc) const 
{
	return loc.x >= 0  && loc.x < width - 1  &&
		loc.y >= 0 && loc.y < height - 1; 
}
