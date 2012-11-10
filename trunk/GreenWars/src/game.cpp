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

CGame::CGame()
: m_Position(0,0)
, m_Size(Iw2DGetSurfaceHeight() / 10, Iw2DGetSurfaceHeight() / 10)
{
}


CGame::~CGame()
{
}


void CGame::Update()
{
    // game logic goes here

    // for example, move a red square towards any touch event...
    if( s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN )
    {
        CIwFVec2 target((float)s3ePointerGetX(), (float)s3ePointerGetY());

        m_Position += (target - m_Position) * 0.05f;
    }
}


void CGame::Render()
{
    // game render goes here

    // for example, clear to black (the order of components is ABGR)
    Iw2DSurfaceClear(0xff000000);

    // draw a red square
    Iw2DSetColour(0xff0000ff);

    // note conversion to pixel coordinates
    Iw2DFillRect(CIwSVec2((iwsfixed)m_Position.x, (iwsfixed)m_Position.y) - m_Size/IW_FIXED(2), m_Size);

    // show the surface
    Iw2DSurfaceShow();
}
