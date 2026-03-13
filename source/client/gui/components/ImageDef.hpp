/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include <string>

struct ImageDef
{
    std::string m_texture;
    int m_offsetX;
    int m_offsetY;
    int m_width;
    int m_height;
    int m_u;
    int m_v;
    int m_uvWidth;
    int m_uvHeight;
    int m_bFullTexture;

    ImageDef() :
        m_texture(""),
        m_offsetX(0),
        m_offsetY(0),
        m_width(0),
        m_height(0),
        m_u(0),
        m_v(0),
        m_uvWidth(0),
        m_uvHeight(0),
        m_bFullTexture(0)
    {
    }
};