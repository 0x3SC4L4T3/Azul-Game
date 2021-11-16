#ifndef STORAGE_H
#define STORAGE_H

#include "macros.h"
#include <sstream>
#include "rlutil.h"

class Storage {
    private:
        vector<Tile> rows[COLORED_TILES];
        int rowCapacity[COLORED_TILES];
        vector<Tile> broken;
        int brokenPenalty[BROKEN_PENALTY_LEN] = {-1, -1, -2, -2, -2, -3};


    public:

        Storage() {
            
            for (int i = 0; i < COLORED_TILES; i++) {
                rowCapacity[i] = i+1;
            }

        }

        int lineTilesCount(int row) {
            return rows[row].size();
        }

        vector<Tile>* getLines() {
            return rows;
        }

        bool isFull(int row) {
            return rows[row].size() == rowCapacity[row];
        }

        bool insertable(int row, Tile tile) {
            return row >= 0 && row < COLORED_TILES && tile != E && tile != F && !isFull(row) && (rows[row].size() == 0 || tile == (rows[row].back()));
        }

        bool insert(int row, Tile tile, int count) {
            if (insertable(row, tile)) {
                int i;
                for (i = 0; i < count && !isFull(row); i++) {
                    rows[row].push_back(tile);
                }
                while (i < count) {
                    broken.push_back(tile);
                    i++;
                }
                return true;
            } else {
                return false;
            }
        }

        

        void emptyLine(int row) {
            rows[row].clear();
        }

        void printRow(ostream& out, int row) {

            int n = COLORED_TILES;

            for (int i = 0; i < n-rowCapacity[row]; i++) {
                out << "  ";
            }

            for (int i = 0; i < rowCapacity[row]-rows[row].size(); i++) {
                out << ". ";
            }

            for (auto it = rows[row].begin(); it != rows[row].end(); it++) {
                if (tileToChar(*it) == 'Y')
                    rlutil::setColor(6);
                else if (tileToChar(*it) == 'B')
                    rlutil::setColor(1);
                else if (tileToChar(*it) == 'R')
                    rlutil::setColor(4);
                else if (tileToChar(*it) == 'L')
                    rlutil::setColor(2);
                else if (tileToChar(*it) == 'U')
                    rlutil::setColor(7);
                out << tileToChar(*it) << " ";
                rlutil::setColor(7);
            }

        }

        void printBroken(ostream& out) {
            out << "Broken: ";
            for (auto it = broken.begin(); it != broken.end(); it++) {
                out << tileToChar(*it) << " ";
            }
        }

        vector<Tile>& getBroken() {
            return broken;
        }

        int getPenalty() {
            int penalty = 0;
            int i = 0;
            int len = sizeof(brokenPenalty)/sizeof(int);
            for (auto it = broken.begin(); it != broken.end(); it++, i++) {
                if (i < len)
                    penalty += brokenPenalty[i];
                else
                    penalty += -3;
            }

            return penalty;
        }

        void storeFirstTile() {
            broken.insert(broken.begin(), F);
        }

        
        Tile getTile(int row) {
            if (rows[row].size() > 0)
                return rows[row].back();
            else
                return E;
        }

        void reset() {
            broken.clear();
        }

        stringstream dumps() {
            stringstream out;

            for (int i = 0; i < COLORED_TILES; i++) {
                out << rows[i].size() << " ";
                for (int j = 0; j < rows[i].size(); j++) {
                    char c =  tileToChar(rows[i][j]);
                    out << c << " ";
                }
            }

            out << broken.size() << " ";
            for (int i = 0; i < broken.size(); i++) {
                char c = tileToChar(broken[i]);
                out << c << " ";
            }
            return out;
        }

        void loads(stringstream& in) {

            int size;
            char c;
            for (int i = 0; i < COLORED_TILES; i++) {
                rows[i].clear();
                in >> size;
                for (int j = 0; j < size; j++) {
                    in >> c;
                    rows[i].push_back(charToTile(c));
                }
            }

            in >> size;
            broken.clear();
            for (int i = 0; i < size; i++) {
                in >> c;
                broken.push_back(charToTile(c));
            }
        }
};



#endif

