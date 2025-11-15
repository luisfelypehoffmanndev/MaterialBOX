#ifndef MATERIALBOX_H
#define MATERIALBOX_H

#include "C:/raylib/raylib/src/raylib.h"

// Estruturas de materiais
struct Sand {
    Vector2 pos;
    Color color;
};

struct Water {
    Vector2 pos;
};

struct Fire {
    Vector2 pos;
    bool atv;
};

struct Concrete {
    Vector2 pos;
};

// Funções utilitárias
Color randomSandColor(void);

// Funções de criação
void createSand(int *ins, int *cap, struct Sand **sand, int **mat);
void createWater(int *ins, int *cap, struct Water **water, int **mat);
void createFire(int *ins, int *cap, struct Fire **fire, int **mat, int x, int y);
void createConcrete(int *ins, int *cap, struct Concrete **concrete, int **mat);

// Funções de movimento
void moveSand(int *instances, struct Sand **sand, int **mat);
void moveWater(int *instances, struct Water **water, int **mat);
void moveFire(int *instances, int *capacity, struct Fire **fire, int **mat);

#endif
