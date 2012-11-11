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
#include "IwGx.h"
#include "IwResManager.h"

#include "game.h"
#include "IwGameSprite.h"
#include "level.h"
#include "Controls.h"
#include "objectcreator.h"
#include "player.h"
#include "ServerPeer.h"

CGame::CGame(int screen_width, int screen_height)
	:ScreenWidth(screen_width)
	,ScreenHeight(screen_height)
	,Level(NULL)
	,Controls(NULL)
	,SpriteManger(NULL)
	,ObjectCreator(NULL) 
{
	g_GameMode = MODE_TITLE;
	bool g_IsServer = true;
	Title = new TitleScreen(this);
}

CGame::~CGame()
{
	Reset();
}

void CGame::Reset()
{
	if(Level) delete Level;
	if(Controls) delete Controls;
	if(SpriteManger) delete SpriteManger;
	if(ObjectCreator) delete ObjectCreator;
	if (Title) delete Title;
	if (g_server) delete g_server;
	if (g_peer) delete g_peer;
}

bool CGame::StartLevel(const char* level_name)
{
	CIwStringS levelGroup(level_name);
	levelGroup+=".group";
	if(NULL == IwGetResManager()->LoadGroup(levelGroup.c_str())) return false;

	CIwResGroup* Level1Group = IwGetResManager()->GetGroupNamed(level_name);
	if(NULL == Level1Group) return false;
	IwGetResManager()->SetCurrentGroup(Level1Group);	

	SpriteManger = new CIwGameSpriteManager();
	
	ObjectCreator = new CObjectCreator(SpriteManger);
	
	Level = CLevel::CreateTestLevel(100, 100, ObjectCreator);
	if(NULL == Level) return false;
	Level->Start();

	return true;
}

bool CGame::CreateControls()
{
	CIwStringS levelGroup("Controls.group");
	if(NULL == IwGetResManager()->LoadGroup(levelGroup.c_str())) return false;

	CIwResGroup* Level1Group = IwGetResManager()->GetGroupNamed("Controls");
	if(NULL == Level1Group) return false;
	IwGetResManager()->SetCurrentGroup(Level1Group);	

	Controls = CControls::CreateControls(ScreenWidth, ScreenHeight);
	if(NULL == Level) return false;
	Level->Start();

	return true;
}

void CGame::CreatePlayer(const char* name)
{
	Players.push_back(new CPlayer(name, ObjectCreator->CreateObjectByName("palyer")));
}

void CGame::Update(float dt)
{
	//Processing title
	if (g_GameMode == MODE_TITLE)
	{
		Title->Update();
		return;
	}

    // game logic goes here
	if(Level)
		Level->Update(dt);
	//update players
	for (CIwArray<CPlayer*>::iterator it = Players.begin(); it != Players.end(); ++it)
		(*it)->Update(dt);
}

void CGame::Render()
{
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

	//Processing title
	if (g_GameMode == MODE_TITLE)
	{
		Title->Render();
		return;
	}

	if(SpriteManger)
	{
		WorldTransform.SetIdentity();
		WorldTransform.SetTrans(CIwSVec2(ScreenWidth / 2, ScreenHeight / 2));
		//WorldTransform.ScaleTrans((IW_GEOM_ONE / 4));

		SpriteManger->setTransform(WorldTransform);
		SpriteManger->Draw();
	}

	Controls->Draw();
    Iw2DSurfaceShow();
}
