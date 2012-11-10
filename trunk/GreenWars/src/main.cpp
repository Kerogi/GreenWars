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

// "main" is the S3E entry point
int main()
{
    Iw2DInit();


    // create game object
    CGame* pGame = new CGame;

    uint64 lastUpdateTime = s3eTimerGetMs();
	uint64 currentTime;

    // to exit correctly, applications should poll for quit requests
    while(!s3eDeviceCheckQuitRequest())
    {
		currentTime = s3eTimerGetMs();
	
		// Update game state
        pGame->Update(currentTime - lastUpdateTime);
		
		lastUpdateTime = currentTime;

        // render the results
        pGame->Render();

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
