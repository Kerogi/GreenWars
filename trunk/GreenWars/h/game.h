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
#include "Iw2D.h"
#include "s3eOSReadString.h"
#include "ServerPeer.h"

enum GameMode
{
    MODE_TITLE,
    MODE_GAMEPLAY,
};

class CLevel;
class CControls;
class CIwGameSpriteManager;
class CObjectCreator;
class CPlayer;
class CGameCommand;
class TitleScreen;

class CGame
{
	TitleScreen* Title;

	CControls * Controls;
	CLevel* Level;
	CIwGameSpriteManager* SpriteManger;
	CObjectCreator*  ObjectCreator; 

	int ScreenWidth;
	int ScreenHeight;
	CIwMat2D	WorldTransform;

	CIwArray<CPlayer*> Players;
public:
	GameMode g_GameMode;
	bool g_IsServer;
	sServer* g_server;
	sPeer* g_peer;

    CGame(int screen_width, int screen_height);
    ~CGame();

	bool ProcessCommand(CGameCommand* cmd);

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


class TitleScreen
{
private:
    int hbX,hbY,hbW,hbH;
	int jbX,jbY,jbW,jbH;

	CGame* m_game;

public:
    TitleScreen(CGame* pGame)
    {
		m_game= pGame;

        hbY = 80;
		hbH = 50;

		jbY = 200;
		jbH = 50;
    }

    void Update()
    {
        if ((s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_PRESSED))
        {
            // Quit
            s3eDeviceRequestQuit();
        }

		if ((s3eKeyboardGetState(s3eKey1) & S3E_KEY_STATE_PRESSED))
        {
			m_game->g_IsServer = true;
			m_game->g_server = new sServer();
			m_game->g_peer = NULL;
            // Start game
            m_game->g_GameMode = MODE_GAMEPLAY;
        } else if ((s3eKeyboardGetState(s3eKey2) & S3E_KEY_STATE_PRESSED))
		{
			m_game->g_IsServer = false;
			m_game->g_server = NULL;
			m_game->g_peer = new sPeer();
			const char* host = s3eOSReadStringUTF8("Enter hostname or IP");
			if (m_game->g_peer->Connect((char*)host))
			{
				m_game->g_GameMode = MODE_GAMEPLAY;
			}
			else
			{
				s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "Host not found");
			}
		}
    }

    void Render()
    {
        int displayWidth  = Iw2DGetSurfaceWidth();
        int displayHeight = Iw2DGetSurfaceHeight();

		hbX = displayWidth/2;
		hbW = displayWidth - 50;

		jbX = displayWidth/2;
		jbW = displayWidth - 50;

		Iw2DDrawRect(CIwSVec2(hbX-hbW/2, hbY-hbH/2), CIwSVec2(hbW, hbH));
		Iw2DDrawRect(CIwSVec2(jbX-jbW/2, jbY-jbH/2), CIwSVec2(jbW, jbH));
        
		Iw2DSurfaceShow();
    }
};

#endif
