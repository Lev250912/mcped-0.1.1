/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "StartMenuScreen.hpp"
#include "InvalidLicenseScreen.hpp"
#include "OptionsScreen.hpp"
#include "ProgressScreen.hpp"
#include "SelectWorldScreen.hpp"
#include "JoinGameScreen.hpp"

#include <cmath>
#include <algorithm>

StartMenuScreen::StartMenuScreen() :
    m_startButton(2, "Start Game"),
    m_joinButton(3, "Join Game"),
    m_optionsButton(4, "Options"),
    m_buyButton()
{
    ImageDef def;
    def.m_texture = "gui/menubuttons.png";
    def.m_offsetX = 0;
    def.m_offsetY = 0;
    def.m_width = 75;
    def.m_height = 75;
    def.m_u = 0;
    def.m_v = 0;
    def.m_uvWidth = 75;
    def.m_uvHeight = 75;
    def.m_bFullTexture = 0;

    // Порядок по реальному atlas:
    // Join | Start | Options
    m_joinButton.setImageDef(def, false);

    def.m_u += 75;
    m_startButton.setImageDef(def, false);

    def.m_u += 75;
    m_optionsButton.setImageDef(def, false);
}
void StartMenuScreen::_updateLicense()
{
    int licenseID = m_pMinecraft->getLicenseId();

    if (licenseID < 0)
    {
        m_optionsButton.m_bEnabled = false;
        m_startButton.m_bEnabled = false;
        m_joinButton.m_bEnabled = false;
    }
    else if (licenseID <= 1)
    {
        m_optionsButton.m_bEnabled = true;
        m_startButton.m_bEnabled = true;
        m_joinButton.m_bEnabled = true;
    }
    else
    {
        m_pMinecraft->setScreen(new InvalidLicenseScreen(
            licenseID,
            m_pMinecraft->platform()->hasBuyButtonWhenInvalidLicense()
        ));
    }
}

void StartMenuScreen::setupPositions()
{
    int buttonWidth = m_startButton.m_width;
    int y = m_height / 3 + 2;

    float gapF = (float(m_width) - float(buttonWidth) * 3.0f) / 4.0f;
    int gap = int(std::round(gapF));

    m_startButton.m_yPos = y;
    m_joinButton.m_yPos = y;
    m_optionsButton.m_yPos = y;

    m_joinButton.m_xPos = gap;
    m_startButton.m_xPos = gap * 2 + buttonWidth;
    m_optionsButton.m_xPos = gap * 3 + buttonWidth * 2;

    // небольшой визуальный сдвиг вправо
    int nudgeX = 3;
    m_joinButton.m_xPos += nudgeX;
    m_startButton.m_xPos += nudgeX;
    m_optionsButton.m_xPos += nudgeX;

    m_buyButton.m_xPos = (m_width - m_buyButton.m_width) / 2;
    m_buyButton.m_yPos = m_height - m_buyButton.m_height - 3;

    field_16C = m_width - 1 - m_pFont->width(field_154);
    field_188 = (m_width - m_pFont->width(field_170)) / 2;
}

void StartMenuScreen::buttonClicked(Button* pButton)
{
    if (pButton->field_30 == m_startButton.field_30)
    {
#if defined(DEMO)
        m_pMinecraft->selectLevel("_DemoLevel", "_DemoLevel", int(getEpochTimeS()));
        m_pMinecraft->hostMultiplayer();
        m_pMinecraft->setScreen(new ProgressScreen);
#else
        m_pMinecraft->setScreen(new SelectWorldScreen);
#endif
    }

    if (pButton->field_30 == m_joinButton.field_30)
    {
        m_pMinecraft->locateMultiplayer();
        m_pMinecraft->setScreen(new JoinGameScreen);
    }

    if (pButton->field_30 == m_optionsButton.field_30)
    {
        m_pMinecraft->setScreen(new OptionsScreen);
    }

    if (pButton->field_30 == m_buyButton.field_30)
    {
        m_pMinecraft->platform()->buyGame();
    }
}

void StartMenuScreen::init()
{
    m_buttons.clear();
    m_buttonTabList.clear();

    m_buttons.push_back(&m_startButton);
    m_buttons.push_back(&m_joinButton);
    m_buttons.push_back(&m_optionsButton);

    m_buttonTabList.push_back(&m_startButton);
    m_buttonTabList.push_back(&m_joinButton);
    m_buttonTabList.push_back(&m_optionsButton);

#ifdef DEMO
    m_buttons.push_back(&m_buyButton);
    m_buttonTabList.push_back(&m_buyButton);
#endif

    field_154 = "\xFFMojang AB";

    field_170 = "v0.1.1 alpha"
#ifdef DEMO
        " (Demo)"
#endif
        ;

    setupPositions();
    _updateLicense();
}

bool StartMenuScreen::isInGameScreen()
{
    return false;
}

void StartMenuScreen::render(int a, int b, float c)
{
    renderBackground();

    Textures* tx = m_pMinecraft->m_pTextures;
    int id = tx->loadTexture("gui/title.png", true);
    Texture* pTex = tx->getTemporaryTextureData(id);

    if (pTex)
    {
        if (id != tx->m_currBoundTex)
        {
            glBindTexture(GL_TEXTURE_2D, id);
            tx->m_currBoundTex = id;
        }

        float centerX = float(m_width) * 0.5f;
        float halfScreenW = float(m_width) * 0.5f;
        float halfTexW = float(pTex->m_width) * 0.5f;
        float halfBase = (halfScreenW < halfTexW) ? halfScreenW : halfTexW;
        float halfW = halfBase * 0.5f;
        float drawW = halfW * 2.0f;
        float drawH = float(pTex->m_height) * (drawW / float(pTex->m_width));

        Tesselator& t = Tesselator::instance;
        glColor4f(1, 1, 1, 1);

        t.begin();
        t.vertexUV(centerX - halfW, drawH + 4.0f, field_4, 0.0f, 1.0f);
        t.vertexUV(centerX + halfW, drawH + 4.0f, field_4, 1.0f, 1.0f);
        t.vertexUV(centerX + halfW, 4.0f, field_4, 1.0f, 0.0f);
        t.vertexUV(centerX - halfW, 4.0f, field_4, 0.0f, 0.0f);
        t.draw();

        drawString(m_pFont, field_170, field_188, int(std::round(drawH + 6.0f)), 0xFFCCCCCC);
    }

    drawString(m_pFont, field_154, field_16C, m_height - 10, 0x00FFFFFF);

    Screen::render(a, b, c);
}

void StartMenuScreen::tick()
{
    _updateLicense();
}