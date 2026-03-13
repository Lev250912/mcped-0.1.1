/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "ImageButton.hpp"

class LargeImageButton : public ImageButton
{
public:
    LargeImageButton(int id, const std::string& text);
    LargeImageButton(int id, const std::string& text, const ImageDef& def);
    virtual ~LargeImageButton();

    virtual void setupDefault();
    void render(Minecraft*, int, int);

private:
    float field_74;
};