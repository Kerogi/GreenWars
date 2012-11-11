/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * Copyright (C) 2001-2012 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This source code is intended only as a supplement to Ideaworks Labs
 * Development Tools and/or on-line documentation.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */
#include "s3e.h"
#include "Iw2D.h"
#include "game.h"
#include "GameCommand.h"

// "main" is the S3E entry point
int main()
{
    Iw2DInit();
	char buffer[64];
	CMovePlayerCommand cmd1;
	cmd1.Target_x = 100.0;
	cmd1.Target_y = 0;
	cmd1.PlayerName = "player1";

	CMovePlayerCommand cmd2;
	cmd1.Target_x = -100.0;
	cmd1.Target_y = -50;
	cmd1.PlayerName = "player2";

    // create game object
    uint64 lastUpdateTime = s3eTimerGetMs();
	uint64 currentTime;
	
	int surface_width = Iw2DGetSurfaceWidth();
	int surface_height = Iw2DGetSurfaceHeight();
   
	CGame* pGame = new CGame(surface_width, surface_height);
	pGame->StartLevel("Level1");

	pGame->CreatePlayer("player1", 100, 50, 0,0);
	pGame->CreatePlayer("player2", -20, -20, 80,10);

	pGame->ProcessCommand(&cmd1);
	pGame->ProcessCommand(&cmd2);

	pGame->CreateControls();

    while(!s3eDeviceCheckQuitRequest())
    {
		// Clear the screen
		currentTime = s3eTimerGetMs();
		uint64 dt_ms = currentTime - lastUpdateTime;

		float dt_sec = dt_ms/1000.0f;

		pGame->Update(dt_sec);
        pGame->Render();

		Iw2DSurfaceShow();
 		lastUpdateTime = currentTime;  
		
		// if an application uses polling input the application
        // must call update once per frame
        s3ePointerUpdate();
        s3eKeyboardUpdate();

        // S3E applications should yield frequently
        s3eDeviceYield();
    }

    // clear up game object
    delete pGame;

    Iw2DTerminate();

    return 0;
}
