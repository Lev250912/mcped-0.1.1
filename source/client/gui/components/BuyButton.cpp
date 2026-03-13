/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "BuyButton.hpp"

BuyButton::BuyButton() :
    ImageButton(5, "Buy")
{
    ImageDef def;
    def.m_texture = "";
    def.m_offsetX = 0;
    def.m_offsetY = 0;

    // Эти значения пока реконструированы приближённо из дизасма.
    // Если потом вытащишь более точный кусок по BuyButton, просто подменим.
    def.m_width = 190;
    def.m_height = 55;
    def.m_u = 64;
    def.m_v = 182;
    def.m_uvWidth = 190;
    def.m_uvHeight = 55;
    def.m_bFullTexture = 0;

    setImageDef(def, true);
}

BuyButton::~BuyButton()
{
}