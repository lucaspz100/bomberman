#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "game.h"
#include "menu.h"

#define SCREEN_W 64*15
#define SCREEN_H 1080
#define CELULA 64
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5



typedef enum GameScreen { LOGO = 0, TITLE, MENU, GAMEPLAY, ENDING, RESUME } GameScreen;


int main (){

    int mapa[ALTURA][LARGURA] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    
    int fase=2;
    Jogador pedro;
    CriarPersonagem(&pedro);

    GameScreen currentScreen = LOGO;


    InitWindow(SCREEN_W, SCREEN_H, "Mini Bomberman");
    //SetExitKey(0);
    SetTargetFPS(60); //verificar ainda quantos fps devem ter
    
    srand(time(NULL));

    Tijolos(&mapa[0][0], fase);

    while(!WindowShouldClose())
    {
        switch (currentScreen)
        {
            case LOGO:
            {
                currentScreen=TITLE;
            } break;
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = MENU;
                }
            } break;
            case MENU:
            {
                MenuOption choice = ShowMenu();
                if (choice == MENU_START)   currentScreen = GAMEPLAY;
                else if (choice == MENU_OPTIONS) {/* submenu de opções */}
                else if (choice == MENU_EXIT)   CloseWindow();

            } break;
            case GAMEPLAY:
            {
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = RESUME;
            } break;
            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER)) currentScreen = TITLE;
            } break;
            case RESUME:
            {
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = GAMEPLAY;
            } break;
            default: break;
        }

        #define CENTER_X(txt, size) (SCREEN_W/2 - MeasureText(txt, size)/2)

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        switch (currentScreen)
        {
            case LOGO:
            {
                DrawText("LOGO SCREEN", CENTER_X("LOGO S`CREEN", 40), SCREEN_H/2 - 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", CENTER_X("WAIT for 2 SECONDS...", 20), SCREEN_H/2 + 30, 20, GRAY);
            } break;
            case TITLE:
            {
                const char *t1 = "TITLE SCREEN";
                const char *t2 = "PRESS ENTER to go to MENU";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, GREEN);
                DrawText(t1, CENTER_X(t1, 40), SCREEN_H/2 - 30, 40, DARKGREEN);
                DrawText(t2, CENTER_X(t2, 20), SCREEN_H/2 + 30, 20, DARKGREEN);
            } break;
            case MENU:
            {
             MenuOption ShowMenu();
            } break;
            case GAMEPLAY:
            {
                AtualizarPersonagem(&pedro, mapa);
                Construir(&mapa[0][0]);
                DesenharPersonagem(pedro);
            } break;
            case ENDING:
            {
                const char *e1 = "ENDING SCREEN";
                const char *e2 = "PRESS ENTER to RETURN to TITLE";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLUE);
                DrawText(e1, CENTER_X(e1, 40), SCREEN_H/2 - 30, 40, DARKBLUE);
                DrawText(e2, CENTER_X(e2, 20), SCREEN_H/2 + 30, 20, DARKBLUE);
            } break;
            case RESUME:
            {
                const char *r1 = "PAUSE MENU";
                const char *r2 = "PRESS ESC TO RESUME GAMEPLAY";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLACK);
                DrawText(r1, CENTER_X(r1, 40), SCREEN_H/2 - 30, 40, WHITE);
                DrawText(r2, CENTER_X(r2, 20), SCREEN_H/2 + 30, 20, WHITE);
            } break;
            default: break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}