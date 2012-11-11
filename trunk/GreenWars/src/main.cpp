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
#include "IwGameSprite.h"
#include "level.h"
#include "IwResManager.h"
#include "objectcreator.h"
#include "IwGx.h"

// "main" is the S3E entry point
int main()
{
    Iw2DInit();


    // create game object
    CGame* pGame = new CGame;

    uint64 lastUpdateTime = s3eTimerGetMs();
	uint64 currentTime;
	
	int surface_width = Iw2DGetSurfaceWidth();
	int surface_height = Iw2DGetSurfaceHeight();

	// Load our Level1 resource group into the resource manager
	IwGetResManager()->LoadGroup("Level1.group");
	// Create two images from PNG resource files
	CIwResGroup* Level1Group = IwGetResManager()->GetGroupNamed("Level1");
	IwGetResManager()->SetCurrentGroup(Level1Group);		// Ensure that Level1 is the current resource group

	// Create a sprite manager and a bunch of sprites
	CIwGameSpriteManager* sprite_manager = new CIwGameSpriteManager();
	CObjectCreator*  object_creator = new CObjectCreator(sprite_manager);
	CLevel* level = CLevel::CreateTestLevel(surface_width, surface_height, object_creator);
	level->Start();


	CIwMat2D	WorldTransform;
    while(!s3eDeviceCheckQuitRequest())
    {
		// Clear the screen
		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		currentTime = s3eTimerGetMs();
		uint64 dt_ms = currentTime - lastUpdateTime;
		// Update game state
        //pGame->Update(dt_ms);

		float dt_sec = dt_ms/1000.0f;

		level->Update(dt_sec);

		lastUpdateTime = currentTime;

        // render the results
        //pGame->Render();
		// Spin and scale the sprite manager
		WorldTransform.SetIdentity();
		//WorldTransform.SetRot(WorldAngle);
		WorldTransform.SetTrans(CIwSVec2(surface_width / 2, surface_height / 2));
		//WorldTransform.ScaleTrans((IW_GEOM_ONE / 4));
		sprite_manager->setTransform(WorldTransform);
		// Draw our sprite manager
		sprite_manager->Draw();

		Iw2DSurfaceShow();
        // if an application uses polling input the application
        // must call update once per frame
        s3ePointerUpdate();
        s3eKeyboardUpdate();

        // S3E applications should yield frequently
        s3eDeviceYield();
    }

    // clear up game object
	delete level;
	delete object_creator;
	delete sprite_manager;
    delete pGame;

    Iw2DTerminate();

    return 0;
}
