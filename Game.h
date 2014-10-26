#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "precompiledheaders.h"
#include "GameObject.h"
#include "Tile.h"
#include "Message.h"

class Game
{
    public:
        Game();
        static void Start();
        static void GameLoop();
        static void HandleKeys();
        static void RenderAll();
        static void HandleAI();
        static void CreateDungeon();
        static void DrawDungeon();
        static void DrawBars();
        static void DrawMessages();
        static void RenderInventoryScreen();

        static const int SCREEN_WIDTH = 100;
        static const int SCREEN_HEIGHT = 75;
        static const int MAP_WIDTH = 100;
        static const int MAP_HEIGHT = 60;
        static const int PANEL_HEIGHT = 15;
        static const int BAR_WIDTH = 20;
        static TCODConsole* gameConsole;
        static TCODConsole* panel;
        static TCODConsole* inventoryScreen;
        enum States {PlayersTurn, EnemysTurn, UpdateScreen, InventoryScreen};
        static States gameState;

    private:
        static bool _exit;
};


#endif // GAME_H_INCLUDED
