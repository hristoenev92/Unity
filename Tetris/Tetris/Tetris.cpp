// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int main()
{
	IO IO;
	int screenHeight = IO.GetScreenHeight();

	Pieces pieces;

	Board board(pieces, screenHeight);

	// Game
	Game game(board, pieces, &IO, screenHeight);

	// Get the actual clock milliseconds (SDL)
	unsigned long time1 = SDL_GetTicks();

	while (!IO.IsKeyDown(SDLK_ESCAPE))
	{
		// ----- Draw -----

		IO.ClearScreen(); 		// Clear screen
		game.DrawScene();			// Draw staff
		IO.UpdateScreen();		// Put the graphic context in the screen

								// ----- Input -----

		int mKey = IO.Pollkey();

		switch (mKey)
		{
		case (SDLK_RIGHT):
		{
			if (board.IsPossibleMovement(game.posX + 1, game.posY, game.piece, game.rotation))
				game.posX++;
			break;
		}

		case (SDLK_LEFT):
		{
			if (board.IsPossibleMovement(game.posX - 1, game.posY, game.piece, game.rotation))
				game.posX--;
			break;
		}

		case (SDLK_DOWN):
		{
			if (board.IsPossibleMovement(game.posX, game.posY + 1, game.piece, game.rotation))
				game.posY++;
			break;
		}

		case (SDLK_x):
		{
			// Check collision from up to down
			while (board.IsPossibleMovement(game.posX, game.posY, game.piece, game.rotation)) { game.posY++; }

			board.StorePiece(game.posX, game.posY - 1, game.piece, game.rotation);

			board.DeletePossibleLines();

			if (board.IsGameOver())
			{
				IO.Getkey();
				exit(0);
			}

			game.CreateNewPiece();

			break;
		}

		case (SDLK_z):
		{
			if (board.IsPossibleMovement(game.posX, game.posY, game.piece, (game.rotation + 1) % 4))
				game.rotation = (game.rotation + 1) % 4;

			break;
		}
		}

		// ----- Vertical movement -----

		unsigned long time2 = SDL_GetTicks();

		if ((time2 - time1) > WAIT_TIME)
		{
			if (board.IsPossibleMovement(game.posX, game.posY + 1, game.piece, game.rotation))
			{
				game.posY++;
			}
			else
			{
				board.StorePiece(game.posX, game.posY, game.piece, game.rotation);

				board.DeletePossibleLines();

				if (board.IsGameOver())
				{
					IO.Getkey();
					exit(0);
				}

				game.CreateNewPiece();
			}

			time1 = SDL_GetTicks();
		}
	}

	return 0;
}


