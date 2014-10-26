#include "Game.h"
#include "Map.h"
#include "FileHandling.h"
#include "Character.h"
#include "TypesOfCharacters.h"
#include "Item.h"

std::vector< std::vector<Tile> > dungeonMap;
std::vector<Enemy> NPCs;
std::vector<Item> items;
std::vector<Message> messageLog;

Player player(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2, '@', TCODColor::white, "Player", 15, 10, 3);
Enemy monster(10, 10, 'M', TCODColor::lightGreen, "Enemy",10, 5, 1);
Item healingPotion(50, 50, '0', TCODColor::lightRed, "Healing Potion", 5, 0, 0);

Game::Game()
{
}

void Game::Start()
{
    NPCs.push_back(monster);
    NPCs.push_back(monster);
    NPCs.push_back(monster);
    NPCs.push_back(monster);
    NPCs.push_back(monster);
    NPCs.push_back(monster);
    items.push_back(healingPotion);

    Message testMessage("This is testing a very long string to see if the wrap function in Message is working correctly, it it is then this should fill up more then one line", TCODColor::yellow);
    messageLog.push_back(testMessage);

    TCODConsole::setCustomFont("arial12x12.png", TCOD_FONT_TYPE_GREYSCALE | TCOD_FONT_LAYOUT_TCOD);
    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Rogue Like", false);
    CreateDungeon();
    DrawDungeon();
    gameState = Game::UpdateScreen;
    GameLoop();
}

void Game::GameLoop()
{
    while(!_exit)
    {
        switch (gameState)
        {
            case Game::UpdateScreen:
                RenderAll();
                gameState = Game::PlayersTurn;
                break;

            case Game::PlayersTurn:
                RenderAll();
                HandleKeys();
                break;

            case Game::EnemysTurn:
                HandleAI();
                break;

            case Game::InventoryScreen:
                RenderInventoryScreen();
                HandleKeys();
                break;
        }
    }
}

void Game::RenderAll()
{
    //Draw Items
    for(int i = 0; i < items.size(); i++)
    {
        items[i].Draw();
    }

    //Draw NPCs
    for(int i = 0; i < NPCs.size(); i++)
    {
        NPCs[i].Draw();
    }

    player.Draw();

    panel->setBackgroundColor(TCODColor::black);
    panel->clear();
    DrawBars();
    DrawMessages();
    TCODConsole::blit(Game::gameConsole, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TCODConsole::root, 0, 0);
    TCODConsole::blit(Game::panel, 0, 0, SCREEN_WIDTH, PANEL_HEIGHT, TCODConsole::root, 0, SCREEN_HEIGHT-PANEL_HEIGHT);
    TCODConsole::flush();
    player.Clear();

    //Clear NPCs
    for(int i = 0; i < NPCs.size(); i++)
    {
        NPCs[i].Clear();
    }

    //Clear Items
    for(int i = 0; i < items.size(); i++)
    {
        items[i].Clear();
    }
}

void Game::HandleKeys()
{
    TCOD_key_t key = TCODConsole::waitForKeypress(true);

    if(key.vk == TCODK_ESCAPE || TCODConsole::isWindowClosed())
    {
        _exit = true;
    }

    else if(key.lalt && key.vk == TCODK_ENTER)
    {
        TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
        RenderAll();
    }

    else if(key.vk == TCODK_F5)
    {
        FileHandling::SaveMap(dungeonMap);
    }

    else if(key.vk == TCODK_F9)
    {
        FileHandling::LoadMap(dungeonMap);
        DrawDungeon();
        RenderAll();
    }

    if(gameState == Game::PlayersTurn)
    {
        if(key.vk == TCODK_KP4 || key.vk == TCODK_LEFT)
        {
            player.Move(-1, 0);
            gameState = Game::EnemysTurn;
        }

        else if(key.vk == TCODK_KP6 || key.vk == TCODK_RIGHT)
        {
            player.Move(1, 0);
            gameState = Game::EnemysTurn;
        }

        else if(key.vk == TCODK_KP8 || key.vk == TCODK_UP)
        {
            player.Move(0, -1);
            gameState = Game::EnemysTurn;
        }

        else if(key.vk == TCODK_KP2 || key.vk == TCODK_DOWN)
        {
            player.Move(0, 1);
            gameState = Game::EnemysTurn;
        }
        else if(key.vk == TCODK_KP3)
        {
            player.Move(1, 1);
            gameState = Game::EnemysTurn;
        }
        else if(key.vk == TCODK_KP1)
        {
            player.Move(-1, 1);
            gameState = Game::EnemysTurn;
        }
        else if(key.vk == TCODK_KP9)
        {
            player.Move(1, -1);
            gameState = Game::EnemysTurn;
        }
        else if(key.vk == TCODK_KP7)
        {
            player.Move(-1, -1);
            gameState = Game::EnemysTurn;
        }
        else if(key.vk == TCODK_KP5)
        {
            gameState = Game::EnemysTurn;
        }
        else if(key.c == 'g')
        {
            player.PickUp();
            gameState = Game::EnemysTurn;
        }

        else if(key.c == 'i')
        {
            gameState = Game::InventoryScreen;
            return;
        }
    }

    else if(gameState == Game::InventoryScreen)
    {
        if(key.vk == TCODK_TAB || key.c == 'i')
        {
            gameState = Game::PlayersTurn;
            inventoryScreen->clear();
            return;
        }
    }
}

void Game::CreateDungeon()
{
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        std::vector<Tile> row;
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(x == 0 || x == MAP_WIDTH-1 || y == 0 || y == MAP_HEIGHT-1)
            {
                row.push_back(Tile(true, true));
            }
            else
            {
                row.push_back(Tile(false, false));
            }
        }
        dungeonMap.push_back(row);
    }
}

void Game::DrawDungeon()
{
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(dungeonMap[x][y].tileBlocked == false)
            {
                Game::gameConsole->setBack(x, y, TCODColor::desaturatedBlue, TCOD_BKGND_SET);
            }
            else
            {
                Game::gameConsole->setBack(x, y, TCODColor::darkerBlue, TCOD_BKGND_SET);
            }
        }
    }
}

void Game::HandleAI()
{
    if(gameState == Game::EnemysTurn)
    {
        for(int i = 0; i < NPCs.size(); i++)
        {
            NPCs[i].ChooseMove();
        }
        gameState = Game::UpdateScreen;
    }
}

void Game::DrawBars()
{
    //HP bar
    int actualWidth = int(player._hp / player._maxHP * BAR_WIDTH);
    panel->setBackgroundColor(TCODColor::darkRed);
    panel->rect(1, 1, BAR_WIDTH, 1, false);
    panel->setBackgroundColor(TCODColor::lightRed);
    if(actualWidth > 0)
    {
        panel->rect(1, 1, actualWidth, 1, false);
    }
    std::stringstream text;
    text << "HP : " << player._hp << " / " << player._maxHP;
    std::string stringText = text.str();
    panel->setForegroundColor(TCODColor::white);
    panel->printCenter(1 + BAR_WIDTH/2, 1, TCOD_BKGND_NONE, stringText.c_str());
}

void Game::DrawMessages()
{
    int startingLine = 0;
    for(int i = 0; i < messageLog.size(); i++)
    {
        if(startingLine >= PANEL_HEIGHT - 2)
        {
            startingLine = 0;
            panel->setBackgroundColor(TCODColor::black);
            panel->clear();
            DrawBars();
        }
        panel->setForegroundColor(messageLog[i]._messageColor);
        panel->printLeft(30, startingLine, TCOD_BKGND_NONE, messageLog[i]._message.c_str());
        startingLine = startingLine + messageLog[i]._numberOfLines;
    }
}

void Game::RenderInventoryScreen()
{
    for(int i = 0; i < player.inventory.size(); i++)
    {
        inventoryScreen->printLeft(0, i, TCOD_BKGND_NONE, player.inventory[i]._name.c_str());
    }
    inventoryScreen->setBackgroundColor(TCODColor::black);
    TCODConsole::blit(Game::inventoryScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TCODConsole::root, 0, 0);
    TCODConsole::flush();
}

TCODConsole* Game::gameConsole = new TCODConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
TCODConsole* Game::panel = new TCODConsole(SCREEN_WIDTH, PANEL_HEIGHT);
TCODConsole* Game::inventoryScreen = new TCODConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
bool Game::_exit = false;
Game::States Game::gameState = Game::PlayersTurn;
