/********************************************************************
Minecraft: Pocket Edition - Decompilation Project
Copyright (C) 2023 iProgramInCpp
The following code is licensed under the BSD 1 clause license.
SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "../Screen.hpp"
#include "../components/LargeImageButton.hpp"
#include "../components/BuyButton.hpp"

class StartMenuScreen : public Screen
{
public:
    StartMenuScreen();

    void _updateLicense();
    void setupPositions();

    void init() override;
    void buttonClicked(Button*) override;
    bool isInGameScreen() override;
    void render(int, int, float) override;
    void tick() override;

private:
    LargeImageButton m_startButton;
    LargeImageButton m_joinButton;
    LargeImageButton m_optionsButton;
    BuyButton m_buyButton;

    std::string field_154;
    int field_16C;
    std::string field_170;
    int field_188;
};