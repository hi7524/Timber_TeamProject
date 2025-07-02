#include "stdafx.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
#include "BackgroundElement.h"
#include "Tree.h"
#include "Player.h"
#include "UiHud.h"
#include "Log.h"
#include "UiHud2.h"
#include "UiMenu.h"

float SceneGame::timerMax = 0.f;
SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::SetTimerMax(const float& time)
{
    timerMax = time;
}

void SceneGame::Init()
{
    texIds.push_back("graphics/background.png");
    texIds.push_back("graphics/cloud.png");
    texIds.push_back("graphics/bee.png");
    texIds.push_back("graphics/log.png");
    texIds.push_back("graphics/tree.png");
    texIds.push_back("graphics/branch.png");
    texIds.push_back(SCENE_MGR.selectedPlayer);
    texIds.push_back("graphics/axe.png");
    texIds.push_back("graphics/rip.png");
    soundIds.push_back("sound/chop.wav");
    soundIds.push_back("sound/death.wav"); 
    soundIds.push_back("sound/out_of_time.wav");
    fontIds.push_back("fonts/KOMIKAP_.ttf");

    AddGameObject(new SpriteGo("graphics/background.png"));
    
    for (int i = 0; i < 3; ++i)
    {
        BackgroundElement* element = (BackgroundElement*)AddGameObject(new BackgroundElement("graphics/cloud.png"));
    }

    tree = (Tree*)AddGameObject(new Tree());

    chopSound = (SoundGo*)AddGameObject(new SoundGo("sound/chop.wav"));
    deathSound = (SoundGo*)AddGameObject(new SoundGo("sound/death.wav"));
    timeSound = (SoundGo*)AddGameObject(new SoundGo("sound/out_of_time.wav"));

    BackgroundElement* element = (BackgroundElement*)AddGameObject(new BackgroundElement("graphics/bee.png"));
    element->minScale = 1.f;
    element->maxScale = 1.f;
    element->minY = 600;
    element->maxY = 800;
    element->minSpeed = 400;
    element->maxSpeed = 600;
    element->SetMoveType(BackgroundElement::MoveType::Wave);

    player = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer));

    log = (Log*)AddGameObject(new Log());
    uiHud = (UiHud*)AddGameObject(new UiHud());
    uiMenu = (UiMenu*)AddGameObject(new UiMenu());

    isShowMenu = false;
    isPlaying = false;
    isMenu = true;
    escape = false;

    Scene::Init();
}

void SceneGame::Enter()
{
    Scene::Enter();
    
    sf::Vector2f pos = tree->GetPosition();
    pos.y = 950.f;
    player->SetPosition(pos);
    log->SetPosition(pos);

    score = 0;
    uiHud->SetScore(score);

    timer = timerMax;
    uiHud->SetTimeBar(timer / timerMax);

    uiHud->SetShowMassage(true);
    uiHud->SetMessage("Enter to Start!");

    chopSound->Reset();
    deathSound->Reset();
    timeSound->Reset();
}

void SceneGame::Exit()
{
    Scene::Exit();
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);
    // ¸Þ´º
    if (escape)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
        {
            isShowMenu = !isShowMenu;
            isPlaying = !isPlaying;
            isMenu = !isMenu;
            log->SetLogAc(isPlaying);
            uiMenu->SetIsShowMenu(isShowMenu);
        }
    }
    if (isShowMenu)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Up))
        {
            uiMenu->ColorSelectedOption("Title");
        }
        if (InputMgr::GetKeyDown(sf::Keyboard::Down))
        {
            uiMenu->ColorSelectedOption("Exit");
        }
        if (InputMgr::GetKeyDown(sf::Keyboard::Return))
        {
            if (uiMenu->GetIsTitle())
            {
                SCENE_MGR.ChangeScene(SceneIds::Title);
            }
            else if (uiMenu->GetIsExit())
            {
                FRAMEWORK.WindowClose();
            }
        }
    }
    if (isPlaying)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Left))
        {
            chopSound->Play();
            tree->UpdateBranches();
            player->SetSide(Sides::Left);
            if (tree->GetSide() == player->GetSide())
            {
                escape = false;
                deathSound->Play();
                isPlaying = false;
                FRAMEWORK.SetTimeScale(0.f);
                player->SetAlive(false);
                uiHud->SetShowMassage(true);
                uiHud->SetMessage("Enter to Restart!");
            }
            else
            {
                score += 10;
                uiHud->SetScore(score);
                timer += 0.5f;
                if (timer > timerMax)
                {
                    timer = timerMax;
                }
            }
        }

        if (InputMgr::GetKeyDown(sf::Keyboard::Right))
        {
            chopSound->Play();
            tree->UpdateBranches();
            player->SetSide(Sides::Right);
            if (tree->GetSide() == player->GetSide())
            {
                escape = false;
                deathSound->Play();
                isPlaying = false;
                FRAMEWORK.SetTimeScale(0.f);
                player->SetAlive(false);
                uiHud->SetShowMassage(true);
                uiHud->SetMessage("Enter to Restart!");
            }
            else
            {
                score += 10;
                uiHud->SetScore(score);
                timer += 0.5f;
                if (timer > timerMax)
                {
                    timer = timerMax;
                }
            }
        }
        player->SetDrawAxe(InputMgr::GetKey(sf::Keyboard::Left) || InputMgr::GetKey(sf::Keyboard::Right));
        
        timer -= dt;

        if (timer <= 0.f)
        {   
            timer = 0.f;
            escape = false;
            isPlaying = false;
            FRAMEWORK.SetTimeScale(0.f);
            player->SetAlive(false);
            timeSound->Play();
            player->SetDrawAxe(false);
            uiHud->SetShowMassage(true);
            uiHud->SetMessage("Enter to Restart!");
        }
        uiHud->SetTimeBar(timer / timerMax);
    }
    else
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Enter) && !isShowMenu)
        {
            FRAMEWORK.SetTimeScale(1.f);
            player->Reset();
            tree->Reset();
            isPlaying = true;
            escape = true;
            score = 0;
            uiHud->SetScore(score);

            timer = timerMax;
            uiHud->SetTimeBar(timer / timerMax);

            uiHud->SetShowMassage(false);
            log->SetLogAc(true);
            log->DisableLog();
        }
    }
}