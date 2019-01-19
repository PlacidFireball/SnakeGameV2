/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	snek({ 2, 2 }),
	rng( std::random_device()() ),
	goal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{   
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isStarted = true; 
	}
	framecheck++;
	if (framecheck == 60)
	{
		seconds++;
		framecheck = 0; 
	}

	if (!gameIsOver)
	{
		if (lastKey != 2)
		{
			if (wnd.kbd.KeyIsPressed('W'))
			{
				delta_loc = { 0, -1 };
				lastKey = 1; 
			}
		}
		if (lastKey != 1)
		{
			if (wnd.kbd.KeyIsPressed('S'))
			{
				delta_loc = { 0, 1 };
				lastKey = 2; 
			}
		}
		if (lastKey != 4)
		{
			if (wnd.kbd.KeyIsPressed('A'))
			{
				delta_loc = { -1, 0 };
				lastKey = 3; 
			}
		}
		if (lastKey != 3)
		{
			if (wnd.kbd.KeyIsPressed('D'))
			{
				delta_loc = { 1, 0 };
				lastKey = 4; 
			}
		}
		++snekMoveCounter;
		if (seconds == 20)
		{
			if (snekMovePeriod <= 2)
			{
				snekMovePeriod = 3; 
			}
			snekMovePeriod--; 
			seconds = 0; 
		}
		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;
			const Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || 
				snek.IsInTileExceptEnd(next))
			{
				gameIsOver = true;
			}
			else
			{
				const bool eating = next == goal.GetLocation(); 
				if (eating)
				{
					snek.Grow();
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{
					goal.Respawn(rng, brd, snek); 
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (isStarted == false)
	{
		SpriteCodex::DrawTitle(300, 200, gfx); 
	}
	if(isStarted == true)
	{ 	
		snek.Draw(brd); 
		goal.Draw(brd); 
		brd.DrawBorder();
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(200, 200, gfx); 
		}
	}
}
