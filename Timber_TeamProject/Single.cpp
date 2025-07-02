#include "stdafx.h"
#include "Single.h"
#include "SpriteGo.h"
#include "SceneTitle.h"

Single::Single() : Scene(SceneIds::Single)
{
}

void Single::ChangeScene()
{
}


void Single::Init()
{
    sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
    sf::Vector2f choosePos = { bounds.width * 0.5f, bounds.height * 0.2f };

    texIds = {
        "graphics/background.png",
        "graphics/player.png",
        "graphics/player1.png",
        "graphics/player2.png"
    };

    fontIds.push_back("fonts/KOMIKAP_.ttf");

    choose = new TextGo("fonts/KOMIKAP_.ttf");
    choose->SetString("Choose!");
    choose->SetCharacterSize(100);
    choose->SetFillColor(sf::Color::White);
    choose->SetOrigin(Origins::MC);
    choose->SetPosition(choosePos);
    AddGameObject(choose);

    AddGameObject(new SpriteGo("graphics/background.png"));

    std::vector<std::string> characterNames = { "Player", "Player1", "Player2" };
    playerTextures = {
        "graphics/player.png",
        "graphics/player1.png",
        "graphics/player2.png"
    };

    sf::Vector2f playerPos = { bounds.width * 0.5f - 300.f, bounds.height * 0.5f };

    playerNames.clear();
    playerSprites.clear();

    for (int i = 0; i < playerTextures.size(); ++i)
    {
        auto* sprite = new SpriteGo(playerTextures[i]);
        sprite->SetOrigin(Origins::MC);
        sprite->SetPosition({ playerPos.x + i * 300.f, playerPos.y });
        AddGameObject(sprite);
        playerSprites.push_back(sprite);

        auto* nameText = new TextGo("fonts/KOMIKAP_.ttf");
        nameText->SetString(characterNames[i]);
        nameText->SetCharacterSize(50);
        nameText->SetOrigin(Origins::MC);
        nameText->SetFillColor(sf::Color::White);
        nameText->SetPosition({ playerPos.x + i * 300.f, playerPos.y + 150.f });
        AddGameObject(nameText);
        playerNames.push_back(nameText);
    }

    selectedIndex = 0;

    Scene::Init();
}


void Single::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Left)) 
    {
        if (selectedIndex > 0) selectedIndex--;
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::Right)) 
    {
        if (selectedIndex < playerNames.size() - 1) selectedIndex++;
    }

    for (int i = 0; i < playerNames.size(); ++i) 
    {
        if (i == selectedIndex) 
        {
            playerNames[i]->SetFillColor(sf::Color::Red);
        }
        else 
        {
            playerNames[i]->SetFillColor(sf::Color::White);
        }
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::Return)) 
    {
        if (selectedIndex >= 0 && selectedIndex < playerTextures.size()) 
        {
            SCENE_MGR.selectedPlayer = playerTextures[selectedIndex];
            SCENE_MGR.ChangeScene(SceneIds::Difficulty);
        }
    }
}
