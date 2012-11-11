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
#ifndef GAME_H
#define GAME_H

#include "IwGeom.h"
#include "IwArray.h"

class CLevel;
class CControls;
class CIwGameSpriteManager;
class CObjectCreator;
class CPlayer;

class CGame
{
	CControls * Controls;
	CLevel* Level;
	CIwGameSpriteManager* SpriteManger;
	CObjectCreator*  ObjectCreator; 

	int ScreenWidth;
	int ScreenHeight;
	CIwMat2D	WorldTransform;

	CIwArray<CPlayer*> Players;
public:
    CGame(int screen_width, int screen_height);
    ~CGame();

	void CreatePlayer(const char* name);
	bool StartLevel(const char* level_name);
	bool CreateControls();
	void Reset();

    // update will be called a fixed number of times per second
    // regardless of visual framerate
    void Update(float dt);
    // render will be called as fast as possible (but not faster
    // than the update rate)
    void Render();
};

#endif
