/*
Name: Joel Jacob
Student ID: s3660851

Name: Ali Redha
Student ID: s3661626

Name: Julian Gencarelli
Student ID: s3661422
*/

#ifndef TILEBAG_H
#define TILEBAG_H

#include "factory.h"
#include <cstdlib>


class TileBag {

    int tilesPerFactory = 4;

    public:
        TileBag(int seed = 1) {
            srand(seed);
        }

        void fillFactory(Factory& factory) {
            for (int i = 0; i < tilesPerFactory; i++) {
                Tile tile = static_cast<Tile>(rand()%COLORED_TILES+1);
                factory.addTile(tile);
            }
        }
};

#endif