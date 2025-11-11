#include "raylib.h"
#include <stdlib.h>
#define W 800
#define H 600

struct Sand
{
    Vector2 pos;
    Color color;
};

struct Water
{
    Vector2 pos;
    Color color;
};

struct Concrete
{
    Vector2 pos;
};


Color randomSandColor() {
    int r = GetRandomValue(180, 235);
    int g = GetRandomValue(140, 190);
    int b = GetRandomValue(60, 100);
    return (Color){r, g, b, 255};
}

void createSand(int *ins, int *cap, struct Sand **sand, int **mat){
        if(*ins<*cap){
            (*ins)++;
        } else {
            (*cap) *= 2;
            *sand = realloc(*sand,(*cap)*sizeof(struct Sand));
        }
        (*sand)[*ins-1].pos.x = GetMouseX();
        (*sand)[*ins-1].pos.y = GetMouseY();
        (*sand)[*ins-1].color = randomSandColor();
        mat[GetMouseY()][GetMouseX()] = 1;
}

void createConcrete(int *ins, int *cap, struct Concrete **concrete, int **mat){
        if(*ins<*cap-3){
            (*ins)+=5;
        } else {
            (*cap) *= 2;
            *concrete = realloc(*concrete,(*cap)*sizeof(struct Concrete));
        }
        (*concrete)[*ins-1].pos.x = GetMouseX();
        (*concrete)[*ins-1].pos.y = GetMouseY();
        mat[GetMouseY()][GetMouseX()] = 3;

        (*concrete)[*ins-2].pos.x = GetMouseX();
        (*concrete)[*ins-2].pos.y = GetMouseY()+2;
        mat[GetMouseY()+2][GetMouseX()] = 3;

        (*concrete)[*ins-3].pos.x = GetMouseX();
        (*concrete)[*ins-3].pos.y = GetMouseY()-2;
        mat[GetMouseY()-2][GetMouseX()] = 3;

        (*concrete)[*ins-4].pos.x = GetMouseX()+2;
        (*concrete)[*ins-4].pos.y = GetMouseY();
        mat[GetMouseY()][GetMouseX()+2] = 3;

        (*concrete)[*ins-5].pos.x = GetMouseX()-2;
        (*concrete)[*ins-5].pos.y = GetMouseY();
        mat[GetMouseY()][GetMouseX()-2] = 3;
}

void createWater(int *ins, int *cap, struct Water **water, int **mat){
        if(*ins<*cap/2){
            (*ins)++;
        } else {
            (*cap) *= 2;
            *water = realloc(*water,(*cap)*sizeof(struct Sand));
        }
        (*water)[*ins-1].pos.x = GetMouseX();
        (*water)[*ins-1].pos.y = GetMouseY();
        (*water)[*ins-1].color = randomSandColor();
        mat[GetMouseY()][GetMouseX()] = 1;
}

void moveWater(int *instances, struct Water **water, int **mat){
            int ordem = GetRandomValue(1, 2);
            for(int i = 0; i<(*instances); i++){
            int x = (int)(*water)[i].pos.x;
            int y = (int)(*water)[i].pos.y;
            if(y>0&&y<H-1){
                if((mat[y+1][x]==0) || (mat[y][x-1]==0)||(mat[y][x+1]==0)){
                    if((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y+1][x] == 0){
                        (*water)[i].pos.y += 1;
                        mat[y][x] = 0;
                        mat[y+1][x] = 2;
                    } else if(ordem == 1){
                        if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y][x-1] == 0){
                            (*water)[i].pos.x -= 1;
                            mat[y][x] = 0;
                            mat[y][x-1] = 2;
                        } 
                        else if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y][x+1] == 0){
                            (*water)[i].pos.x += 1;
                            mat[y][x] = 0;
                            mat[y][x+1] = 2;
                        }
                    } else {
                        if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y][x+1] == 0){
                            (*water)[i].pos.x += 1;
                            mat[y][x] = 0;
                            mat[y][x+1] = 2;
                        }
                        else if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y][x-1] == 0){
                            (*water)[i].pos.x -= 1;
                            mat[y][x] = 0;
                            mat[y][x-1] = 2;
                        }
                     }
                }
            }
        }
    }   

void moveSand(int *instances, struct Sand **sand, int **mat){
            int ordem = GetRandomValue(1, 2);
            for(int i = 0; i<(*instances); i++){
            int x = (int)(*sand)[i].pos.x;
            int y = (int)(*sand)[i].pos.y;
            if(y>0&&y<H-1){
                if((mat[y+1][x]==0) || (mat[y+1][x-1]==0)||(mat[y+1][x+1]==0)){
                    if((x>0)&&(x<W-1)&&(y<H-3)&&(y>0)&&(mat[y+1][x] == 0)){
                        (*sand)[i].pos.y += 1;
                        mat[y][x] = 0;
                        mat[y+1][x] = 1;
                    } else if ((x>0)&&(x<W-1)&&(y<H-3)&&(y>0)&&(mat[y+1][x] == 2)) {
                        (*sand)[i].pos.y += 1;
                        (*sand)[i].color.b += 20;
                        mat[y][x] = 0;
                        mat[y+1][x] = 1;
                    } else if(ordem == 1){
                        if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y+1][x-1] == 0){
                            (*sand)[i].pos.y += 1;
                            (*sand)[i].pos.x -= 1;
                            mat[y][x] = 0;
                            mat[y+1][x-1] = 1;
                        } else if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y+1][x+1] == 0){
                            (*sand)[i].pos.y += 1;
                            (*sand)[i].pos.x += 1;
                            mat[y][x] = 0;
                            mat[y+1][x+1] = 1;
                        }
                    } else {
                        if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y+1][x+1] == 0){
                            (*sand)[i].pos.y += 1;
                            (*sand)[i].pos.x += 1;
                            mat[y][x] = 0;
                            mat[y+1][x+1] = 1;
                        } else if ((x>0)&&(x<W-1)&&(y<H-1)&&(y>0)&&mat[y+1][x-1] == 0){
                            (*sand)[i].pos.y += 1;
                            (*sand)[i].pos.x -= 1;
                            mat[y][x] = 0;
                            mat[y+1][x-1] = 1;
                        }
                    }
                }
            }
        }
    }



int main(){
    
    int scapacity = 100;
    int sinstances = 0;
    int wcapacity = 1000;
    int winstances = 0;
    int cinstances = 0;
    int ccapacity = 100;
    Vector2 mouse;
    Image img = GenImageColor(W, H, BLACK);
    Texture2D tex;
    Color *pixels;
    pixels = LoadImageColors(img);
    int **mat;
    struct Sand *sand;
    struct Water *water;
    struct Concrete *concrete;

    sand = malloc(scapacity * sizeof(struct Sand));
    water = malloc(wcapacity * sizeof(struct Water));
    concrete = malloc(wcapacity * sizeof(struct Water));
    mat = malloc(H* sizeof(int*));
    for(int i = 0; i<H; i++){
        mat[i] = malloc(W*sizeof(int));
    }

    for(int i = 0; i<H; i++){
        for(int j = 0; j<W; j++){
           mat[i][j] = 0;
       }
    }
    
    SetTargetFPS(240);
    InitWindow(W, H, "MaterialBox");
    //sprite = LoadTexture("sprite.png");
    tex = LoadTextureFromImage(img);

    while (!WindowShouldClose())  //gameloop
    {
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
        
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
        moveSand(&sinstances, &sand, mat);
        moveWater(&winstances, &water, mat);

for (int y = 0; y < H - 1; y++)
{
    for (int x = 0; x < W - 1; x++)
    {
        if (mat[y][x] == 1)
        {
            pixels[y * W + x] = randomSandColor();  // ← Mudou de H para W
        }
        else if (mat[y][x] == 0)
        {
            pixels[y * W + x] = BLACK;              // ← Mudou de H para W
        } 
        else if (mat[y][x] == 2)
        {
            pixels[y * W + x] = DARKBLUE;           // ← Mudou de H para W
        }
        else if (mat[y][x] == 3)
        {
            pixels[y * W + x] = GRAY;               // ← Mudou de H para W
        }
    }
}
        UpdateTexture(tex, pixels);

        BeginDrawing();
            
            ClearBackground(BLACK);
            DrawTexture(tex, 0, 0, WHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }
    
    for(int i = 0; i<W; i++){
        free(mat[i]);
    }
    free(mat);
    free(sand);
    free(water);
    UnloadImage(img);
    UnloadTexture(tex);
    UnloadImageColors(pixels);

    return 0;
}

