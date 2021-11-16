#ifndef FACTORY_H
#define FACTORY_H
#include<iostream>
#include <sstream>
#include "macros.h"
#include <stdlib.h>
#include "rlutil.h"


using namespace std;

class Factory {
    private:
        vector<Tile> tiles;
        static int fid;
        int id;
    public:
        Factory() {
            this->id = fid++;
        }

        void addTile(Tile tile) {
            tiles.push_back(tile);
        }

        bool containsTile(Tile tile) {
            for (int i = tiles.size()-1; i >= 0; i--) { 
                if (tiles[i] == tile) {
                    return true;
                }
            }
            return false;
        }

        pair<int, vector<Tile>> takeTile(Tile tile) {
            vector<Tile> rem;
            int count = 0;
            if (tiles.size() > 0) {
                for (int i = tiles.size()-1; i >= 0; i--) { 
                    if (tiles[i] == tile) {
                        tiles.erase(tiles.begin()+i);
                        count += 1;
                    } 
                    else {
                        if (tiles[i] != F)
                            rem.push_back(tiles[i]);
                    }
                }
            }
            return {count, rem};
        }

        vector<Tile>& getTiles() {
            return tiles;
        }

        void print(ostream& out) {
            out << id << ": ";
            for (int i = 0; i < tiles.size(); i++) {
                if(tileToChar(tiles[i]) == 'Y')
                    rlutil::setColor(6);
                else if (tileToChar(tiles[i]) == 'B')
                    rlutil::setColor(1);
                else if (tileToChar(tiles[i]) == 'R')
                    rlutil::setColor(4);
                else if (tileToChar(tiles[i]) == 'L')
                     rlutil::setColor(2);
                else if (tileToChar(tiles[i]) == 'U')
                    rlutil::setColor(7);
                out << tileToChar(tiles[i]) << " ";
                rlutil::setColor(7);
            }
        }

        stringstream dumps() {
            stringstream out;

            out << id << " " << tiles.size()  << " ";
            for (Tile tile : tiles) {
                if (tileToChar(tile) == 'Y')
                    rlutil::setColor(6);
                else if (tileToChar(tile) == 'B')
                    rlutil::setColor(1);
                else if (tileToChar(tile) == 'R')
                    rlutil::setColor(4);
                else if (tileToChar(tile) == 'L')
                    rlutil::setColor(2);
                else if (tileToChar(tile) == 'U')
                    rlutil::setColor(7);
                out << tileToChar(tile) << " ";
                rlutil::setColor(15);
                
            }
            return out;
        }

        void loads(stringstream& in) {
            tiles.clear();

            in >> id;

            int size;
            in >> size;

            char c;
            for (int i = 0;  i < size; i++) {
                in >> c;
                tiles.push_back(charToTile(c));
            }
        }
};

int Factory::fid = 0;

#endif