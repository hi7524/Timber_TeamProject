#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"

class Single : public Scene
{
protected:
    TextGo* choose = new TextGo("fonts/KOMIKAP_.ttf");
    std::vector<std::string> playerTextures; 
    std::vector<TextGo*> playerNames;
    std::vector<SpriteGo*> playerSprites;

    int selectedIndex = 0; 
public:
    Single();

    void ChangeScene();
    void Init() override;
    void Update(float dt) override;
};