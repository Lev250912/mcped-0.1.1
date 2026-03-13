/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "Button.hpp"
#include "ImageDef.hpp"

class ImageButton : public Button
{
public:
    ImageButton(int id, const std::string& text);
    ImageButton(int id, const std::string& text, const ImageDef& def);
    virtual ~ImageButton();

    virtual void setupDefault();
    ImageDef* setImageDef(const ImageDef& def, bool resize = false);
    void render(Minecraft*, int, int);

protected:
    ImageDef m_imageDef;
};