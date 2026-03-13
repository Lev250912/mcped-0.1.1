/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "ImageButton.hpp"
#include "../../Minecraft.hpp"
#include "../../renderer/Textures.hpp"
#include "../../renderer/Tesselator.hpp"

#include <cmath>

ImageButton::ImageButton(int id, const std::string& text) :
    Button(id, text)
{
    setupDefault();
}

ImageButton::ImageButton(int id, const std::string& text, const ImageDef& def) :
    Button(id, text),
    m_imageDef(def)
{
    setupDefault();
}

ImageButton::~ImageButton()
{
}

void ImageButton::setupDefault()
{
    m_width = 80;
    m_height = 90;
}

ImageDef* ImageButton::setImageDef(const ImageDef& def, bool resize)
{
    m_imageDef = def;

    if (resize)
    {
        m_width = int(std::round(float(m_imageDef.m_width)));
        m_height = int(std::round(float(m_imageDef.m_height)));
    }

    return &m_imageDef;
}

void ImageButton::render(Minecraft* minecraft, int mouseX, int mouseY)
{
    if (!m_bVisible)
        return;

    glColor4f(1, 1, 1, 1);

    bool hovered =
        m_bEnabled &&
        mouseX >= m_xPos &&
        mouseY >= m_yPos &&
        mouseX < m_xPos + m_width &&
        mouseY < m_yPos + m_height;

    int texId = minecraft->m_pTextures->loadAndBindTexture(
        m_imageDef.m_texture.empty() ? "gui/menubuttons.png" : m_imageDef.m_texture
    );

    if (texId >= 0)
    {
        Texture* tex = minecraft->m_pTextures->getTemporaryTextureData(texId);
        if (tex)
        {
            Tesselator& t = Tesselator::instance;
            t.begin();

            if (m_bEnabled)
                t.color(0xFFFFFFFF);
            else
                t.color(0xFFA0A0A0);

            int halfW = int(float(m_imageDef.m_width) * 0.5f);
            int halfH = int(float(m_imageDef.m_height) * 0.5f);
            int centerX = m_xPos + m_imageDef.m_offsetX + halfW;
            int centerY = m_yPos + m_imageDef.m_offsetY + halfH;

            if (hovered)
            {
                halfW = int(float(halfW) * 0.95f);
                halfH = int(float(halfH) * 0.95f);
            }

            if (!m_imageDef.m_bFullTexture)
            {
                float u0 = float(m_imageDef.m_u) / float(tex->m_width);
                float u1 = float(m_imageDef.m_u + m_imageDef.m_uvWidth) / float(tex->m_width);
                float v0 = float(m_imageDef.m_v) / float(tex->m_height);
                float v1 = float(m_imageDef.m_v + m_imageDef.m_uvHeight) / float(tex->m_height);

                t.vertexUV(float(centerX - halfW), float(centerY - halfH), field_4, u0, v0);
                t.vertexUV(float(centerX - halfW), float(centerY + halfH), field_4, u0, v1);
                t.vertexUV(float(centerX + halfW), float(centerY + halfH), field_4, u1, v1);
                t.vertexUV(float(centerX + halfW), float(centerY - halfH), field_4, u1, v0);
            }
            else
            {
                t.vertexUV(float(centerX - halfW), float(centerY - halfH), field_4, 0.0f, 0.0f);
                t.vertexUV(float(centerX - halfW), float(centerY + halfH), field_4, 0.0f, 1.0f);
                t.vertexUV(float(centerX + halfW), float(centerY + halfH), field_4, 1.0f, 1.0f);
                t.vertexUV(float(centerX + halfW), float(centerY - halfH), field_4, 1.0f, 0.0f);
            }

            t.draw();
        }
    }

    int color;
    int yText = m_yPos + 16;

    if (!m_bEnabled)
        color = 0xFFA0A0A0;
    else if (hovered || field_36)
        color = 0x00FFFFA0;
    else
        color = 0x00E0E0E0;

    drawCenteredString(
        minecraft->m_pFont,
        field_18,
        m_xPos + m_width / 2,
        yText,
        color
    );
}