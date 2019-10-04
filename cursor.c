/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_MALOS 80

typedef struct Enemigos {
    Rectangle body;
    int speed;
}Enemigos;

typedef struct Animacion{
    Rectangle sprite;
    Vector2 auxiliar;
    bool bum;
    int framescounter;
    int currentFrameX;
    int currentFrameY;
}Animacion;
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 450;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Cuadrados descendientes quieren ser clicados");
    
    Enemigos enemy[MAX_MALOS];
    Animacion mov[MAX_MALOS];
    
    
    
    int score = 0;
    
      

    Texture2D jugador = LoadTexture ("resources/mouse.png");
    Rectangle player = {GetMouseX(), GetMouseY(), 5, 5};
    Texture2D explosion = LoadTexture ("resources/explosion.png");
    
    
    for (int i=0; i<MAX_MALOS; i++)
    {
        enemy[i].body.width = 25;
        enemy[i].body.height= 25;
        enemy[i].body.x=GetRandomValue(0, 425);
        enemy[i].body.y=GetRandomValue(0, -screenHeight); 
        enemy[i].speed = 3;
        mov[i].auxiliar.x = 0;
        mov[i].auxiliar.y = 0;
        mov[i].sprite.width = explosion.width/4;
        mov[i].sprite.height = explosion.height/4;
        mov[i].sprite.x = player.x;
        mov[i].sprite.y = player.y;
        mov[i].bum = false;
        mov[i].framescounter = 0;
        mov[i].currentFrameX=0;
        mov[i].currentFrameY=0;
    }
    
    
  

    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //---------------------------------------------------------------------------------- 
        HideCursor ();
        player.x = GetMouseX();
        player.y = GetMouseY();
        for (int i=0; i<MAX_MALOS; i++)
        {
            enemy[i].body.y += enemy[i].speed;
            if(CheckCollisionPointRec(GetMousePosition(), enemy[i].body ))
            {
                if(IsMouseButtonPressed(0))
                {
                    mov[i].auxiliar.x = enemy[i].body.x;
                    mov[i].auxiliar.y = enemy[i].body.y;
                    enemy[i].body.y= GetRandomValue(0, -screenHeight );
                    enemy[i].body.x= GetRandomValue(0,450);
                    score++;
                    mov[i].bum = true;
                }
                    
            }
            if (enemy[i].body.y > 830)
            {
                enemy[i].body.y= GetRandomValue(0, -screenHeight);
                enemy[i].body.x= GetRandomValue(0,450);
            }
           
            if (mov[i].bum)
            {   
                mov[i].framescounter++;
                if (mov[i].framescounter >= 2)
                {
                    mov[i].framescounter = 0;
                    mov[i].currentFrameX++;
                    if (mov[i].currentFrameX >= 4)
                    {
                        mov[i].currentFrameX = 0;
                        mov[i].currentFrameY++;
                        if (mov[i].currentFrameY >= 4)
                        {
                            mov[i].currentFrameY = 0;
                            mov[i].bum = false;
                        }
                    }
                }
            }
            mov[i].sprite.x = mov[i].currentFrameX * explosion.width/4;
            mov[i].sprite.y = mov[i].currentFrameY * explosion.height/4;
        
        }
        
       
        
        
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture (jugador, player.x, player.y, WHITE);
            for (int i=0; i<MAX_MALOS; i++)
                {
                  DrawRectangle (enemy[i].body.x, enemy[i].body.y, enemy[i].body.width, enemy[i].body.height, RED);
                  if (mov[i].bum)
                  {
                    DrawTextureRec (explosion, mov[i].sprite, (Vector2){mov[i].auxiliar.x, mov[i].auxiliar.y}, WHITE);
                    DrawTextureRec (explosion, mov[i].sprite, (Vector2){mov[i].auxiliar.x, mov[i].auxiliar.y}, WHITE);
                  }
                }
                
            DrawText (FormatText ("Score %i", score), 0, 0, 20, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    UnloadTexture (jugador);
    UnloadTexture (explosion);
   
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}