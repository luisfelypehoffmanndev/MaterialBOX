#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "MaterialBox.h"
#define W 800
#define H 600



int main(){
    
    int scapacity = 100;    //Sand capacity
    int sinstances = 0;     //Sand instances

    int wcapacity = 100;    // Water instances  
    int winstances = 0;     // Water capacity

    int cinstances = 0;     // Concrete instances
    int ccapacity = 100;    // Concrete capacity
    
    int finstances = 0;     // Fire instances
    int fcapacity = 100;    // Fire capacity


    Texture2D tex; // Using a iimage and texture to display game graphics
    Image img = GenImageColor(W, H, BLACK);
    Color *pixels;
    pixels = LoadImageColors(img);


    struct Sand *sand;
    struct Water *water;
    struct Concrete *concrete;
    struct Fire *fire;

    // Allocation of structures that represents materials
    sand = malloc(scapacity * sizeof(struct Sand));
    water = malloc(wcapacity * sizeof(struct Water));
    concrete = malloc(ccapacity * sizeof(struct Water));
    fire = malloc(fcapacity * sizeof(struct Fire));

    int **mat;      // Allocation of matrix that used for colisions
    mat = malloc(H* sizeof(int*));
    for(int i = 0; i<H; i++){
        mat[i] = malloc(W*sizeof(int));
    }
    for(int i = 0; i<H; i++){
        for(int j = 0; j<W; j++){
           mat[i][j] = 0;
       }
    }
    
    SetTargetFPS(240); // Setting target FPS
    InitWindow(W, H, "MaterialBox"); //Init game window with height and width H,
    tex = LoadTextureFromImage(img);
    while (!WindowShouldClose())  //gameloop
    {
        
        // Reading inputs and creating materials
        if(IsMouseButtonDown(0)){
            createSand(&sinstances, &scapacity, &sand, mat);
        }

        if(IsMouseButtonDown(1)){
            createWater(&winstances, &wcapacity, &water, mat);
            createWater(&winstances, &wcapacity, &water, mat);
            createWater(&winstances, &wcapacity, &water, mat);
        }

        if(IsKeyDown(KEY_A)){
            createConcrete(&cinstances, &ccapacity, &concrete, mat);
        }

        if(IsKeyDown(KEY_F)){
            createFire(&finstances, &fcapacity, &fire, mat, GetMouseX(), GetMouseY());
        }

        if(IsKeyPressed(KEY_ESCAPE)){
            CloseWindow();
        }



        // Updating the game phisics
        moveSand(&sinstances, &sand, mat);
        moveWater(&winstances, &water, mat);
        moveFire(&finstances, &fcapacity, &fire, mat);


        // Setting pixels on texture to display game graphics
        for (int y = 0; y < H - 1; y++)
        {
            for (int x = 0; x < W - 1; x++)
            {
                if (mat[y][x] == 1)
                {
                    pixels[y * W + x] = randomSandColor();
                }
                else if (mat[y][x] == 0)
                {
                    pixels[y * W + x] = BLACK;
                } 
                else if (mat[y][x] == 2)
                {
                    pixels[y * W + x] = DARKBLUE;  
                }
                else if (mat[y][x] == 4)
                {
                    pixels[y * W + x] = BROWN;               
                } 
                else if (mat[y][x] == 5){
                    pixels[y * W + x] = RED;
                }
            }
        }
        UpdateTexture(tex, pixels);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(tex, 0, 0, WHITE); // Drawing the game graphics
            DrawFPS(10, 10);
        EndDrawing();
    }
    

    // Free allocated memory
    for(int i = 0; i<W; i++){
       free(mat[i]);
    }
    free(mat);
    free(fire);
    free(sand);
    free(water);
    UnloadImage(img);
    UnloadTexture(tex);
    UnloadImageColors(pixels);

    return 0;
}

