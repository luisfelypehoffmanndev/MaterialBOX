#include "MaterialBox.h"
#include <stdio.h>
#include <stdlib.h>

#define W 800
#define H 600

// ---- Função utilitária ----
Color randomSandColor(void) {
    int r = GetRandomValue(180, 235);
    int g = GetRandomValue(140, 190);
    int b = GetRandomValue(60, 100);
    return (Color){r, g, b, 255};
}

// ---- Criação de elementos ----
void createFire(int *ins, int *cap, struct Fire **fire, int **mat, int x, int y) {
    if (*ins < *cap / 2) {
        (*ins)++;
    } else {
        (*cap) *= 2;
        *fire = realloc(*fire, (*cap) * sizeof(struct Fire));
    }
    if (*fire == NULL) {
        printf("ERROR: Insufficient memory");
        return;
    }

    (*fire)[*ins].atv = true;
    (*fire)[*ins].pos.x = x;
    (*fire)[*ins].pos.y = y;
    mat[y][x] = 5;
}

void createSand(int *ins, int *cap, struct Sand **sand, int **mat) {
    if (*ins >= *cap) {
        (*cap) *= 2;
        *sand = realloc(*sand, (*cap) * sizeof(struct Sand));
    }
    if (*sand == NULL) {
        printf("ERROR: Insufficient memory");
        return;
    }

    (*sand)[*ins].pos.x = GetMouseX();
    (*sand)[*ins].pos.y = GetMouseY();
    (*sand)[*ins].color = randomSandColor();
    mat[GetMouseY()][GetMouseX()] = 1;

    (*ins)++;
}

void createConcrete(int *ins, int *cap, struct Concrete **concrete, int **mat) {
    if (*ins < *cap - 24) {
        (*ins) += 25;
    } else {
        (*cap) *= 2;
        *concrete = realloc(*concrete, (*cap) * sizeof(struct Concrete));
    }
    if (*concrete == NULL) {
        printf("ERROR: Insufficient memory");
        return;
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    int index = *ins - 1;
    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
            (*concrete)[index].pos.x = mouseX + dx;
            (*concrete)[index].pos.y = mouseY + dy;
            mat[mouseY + dy][mouseX + dx] = 4;
            index--;
        }
    }
}

void createWater(int *ins, int *cap, struct Water **water, int **mat) {
    if (*ins >= *cap / 2) {
        (*cap) *= 2;
        *water = realloc(*water, (*cap) * sizeof(struct Water));
    }
    if (*water == NULL) {
        printf("ERROR: Insufficient memory");
        return;
    }

    (*water)[*ins].pos.x = GetMouseX();
    (*water)[*ins].pos.y = GetMouseY();
    mat[GetMouseY()][GetMouseX()] = 2;

    (*ins)++;
}

// ---- Movimento ----
void moveWater(int *instances, struct Water **water, int **mat) {
    int ordem = GetRandomValue(1, 2);
    for (int i = 0; i < (*instances); i++) {
        int x = (int)(*water)[i].pos.x;
        int y = (int)(*water)[i].pos.y;
        if (y > 0 && y < H - 1) {
            if ((mat[y + 1][x] == 0) || (mat[y][x - 1] == 0) || (mat[y][x + 1] == 0)) {
                if ((x > 0) && (x < W - 1) && (mat[y + 1][x] == 0)) {
                    (*water)[i].pos.y += 1;
                    mat[y][x] = 0;
                    mat[y + 1][x] = 2;
                } else if (ordem == 1) {
                    if ((x > 0) && (mat[y][x - 1] == 0)) {
                        (*water)[i].pos.x -= 1;
                        mat[y][x] = 0;
                        mat[y][x - 1] = 2;
                    } else if ((x < W - 1) && (mat[y][x + 1] == 0)) {
                        (*water)[i].pos.x += 1;
                        mat[y][x] = 0;
                        mat[y][x + 1] = 2;
                    }
                } else {
                    if ((x < W - 1) && (mat[y][x + 1] == 0)) {
                        (*water)[i].pos.x += 1;
                        mat[y][x] = 0;
                        mat[y][x + 1] = 2;
                    } else if ((x > 0) && (mat[y][x - 1] == 0)) {
                        (*water)[i].pos.x -= 1;
                        mat[y][x] = 0;
                        mat[y][x - 1] = 2;
                    }
                }
            }
        }
    }
}

void moveFire(int *instances, int *capacity, struct Fire **fire, int **mat) {
    int inst = (*instances);
    int burnchance = GetRandomValue(1, 4);
    for (int i = 0; i <= inst; i++) {
        int x = (int)(*fire)[i].pos.x;
        int y = (int)(*fire)[i].pos.y;
        if (y > 0 && y < H - 1) {
            if (((mat[y + 1][x] == 4) || (mat[y - 1][x] == 4) || (mat[y][x - 1] == 4) || (mat[y][x + 1] == 4)) && (*fire)[i].atv) {
                if ((mat[y + 1][x] == 4) && burnchance == 1)
                    createFire(instances, capacity, fire, mat, x, y + 1);
                if ((mat[y - 1][x] == 4) && burnchance == 2)
                    createFire(instances, capacity, fire, mat, x, y - 1);
                if ((mat[y][x + 1] == 4) && burnchance == 3)
                    createFire(instances, capacity, fire, mat, x + 1, y);
                if ((mat[y][x - 1] == 4) && burnchance == 4)
                    createFire(instances, capacity, fire, mat, x - 1, y);
            }

            if (((mat[y + 2][x] == 4) || (mat[y - 2][x] == 4) || (mat[y][x - 2] == 4) || (mat[y][x + 2] == 4)) && (*fire)[i].atv) {
                if ((mat[y + 2][x] == 4) && burnchance == 1)
                    createFire(instances, capacity, fire, mat, x, y + 1);
                if ((mat[y - 2][x] == 4) && burnchance == 2)
                    createFire(instances, capacity, fire, mat, x, y - 1);
                if ((mat[y][x + 2] == 4) && burnchance == 3)
                    createFire(instances, capacity, fire, mat, x + 1, y);
                if ((mat[y][x - 2] == 4) && burnchance == 4)
                    createFire(instances, capacity, fire, mat, x - 1, y);
            }

            if (((mat[y + 1][x + 1] == 4) || (mat[y - 1][x -1] == 4) || (mat[y + 1][x - 1] == 4) || (mat[y - 1][x + 1] == 4)) && (*fire)[i].atv) {
                if ((mat[y + 1][x + 1] == 4) && burnchance == 1)
                    createFire(instances, capacity, fire, mat, x + 1, y + 1);
                if ((mat[y - 1][x - 1] == 4) && burnchance == 2)
                    createFire(instances, capacity, fire, mat, x - 1, y - 1);
                if ((mat[y + 1][x - 1] == 4) && burnchance == 3)
                    createFire(instances, capacity, fire, mat, x + 1, y  - 1);
                if ((mat[y - 1][x + 1] == 4) && burnchance == 4)
                    createFire(instances, capacity, fire, mat, x - 1, y + 1);
            }

            if ((mat[y + 1][x] != 4) && (mat[y - 1][x] != 4) && (mat[y][x - 1] != 4) && (mat[y][x + 1] != 4) && (*fire)[i].atv == true){
                mat[y][x] = 0;
                (*fire)[i].atv = false;
            }

            // if ((mat[y + 1][x] != 4) && (mat[y - 1][x] != 4) && (mat[y][x - 1] != 4) && (mat[y][x + 1] != 4)) {
            //     mat[y][x] = 0;
            //     (*fire)[i].atv = false;
            // } else if ((mat[y + 1][x + 1] != 4) && (mat[y - 1][x  - 1] != 4) && (mat[y + 1][x - 1] != 4) && (mat[y - 1][x + 1] != 4)) {
            //     mat[y][x] = 0;
            // } else if ((mat[y + 2][x] != 4) && (mat[y - 2][x] != 4) && (mat[y][x - 2] != 4) && (mat[y][x + 2] != 4)) {
            //     mat[y][x] = 0;
            // }
        }
    }
}

void moveSand(int *instances, struct Sand **sand, int **mat) {
    int ordem = GetRandomValue(1, 2);
    for (int i = 0; i < (*instances); i++) {
        int x = (int)(*sand)[i].pos.x;
        int y = (int)(*sand)[i].pos.y;
        if (y > 0 && y < H - 1) {
            if ((mat[y + 1][x] == 0) || (mat[y + 1][x - 1] == 0) || (mat[y + 1][x + 1] == 0)) {
                if ((mat[y + 1][x] == 0)) {
                    (*sand)[i].pos.y += 1;
                    mat[y][x] = 0;
                    mat[y + 1][x] = 1;
                } else if (ordem == 1) {
                    if (mat[y + 1][x - 1] == 0) {
                        (*sand)[i].pos.y += 1;
                        (*sand)[i].pos.x -= 1;
                        mat[y][x] = 0;
                        mat[y + 1][x - 1] = 1;
                    } else if (mat[y + 1][x + 1] == 0) {
                        (*sand)[i].pos.y += 1;
                        (*sand)[i].pos.x += 1;
                        mat[y][x] = 0;
                        mat[y + 1][x + 1] = 1;
                    }
                } else {
                    if (mat[y + 1][x + 1] == 0) {
                        (*sand)[i].pos.y += 1;
                        (*sand)[i].pos.x += 1;
                        mat[y][x] = 0;
                        mat[y + 1][x + 1] = 1;
                    } else if (mat[y + 1][x - 1] == 0) {
                        (*sand)[i].pos.y += 1;
                        (*sand)[i].pos.x -= 1;
                        mat[y][x] = 0;
                        mat[y + 1][x - 1] = 1;
                    }
                }
            }
        }
    }
}
