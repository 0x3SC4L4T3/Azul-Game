/*
Name: Joel Jacob
Student ID: s3660851

Name: Ali Redha
Student ID: s3661626

Name: Julian Gencarelli
Student ID: s3661422
*/

#ifndef WALL_H
#define WALL_H

#include "macros.h"


class Wall{
    private:
        // 2d portugese wall
        Tile wall[COLORED_TILES][COLORED_TILES];
        int rows = COLORED_TILES;
        int cols = COLORED_TILES;

        string places[COLORED_TILES];
        int score;
    
    public:
        Wall() {

            score = 0;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    wall[i][j] = E;
                }
            }

            // clockwise circulate 
            string str = "RYBLU";
            for (int i = 0; i < rows; i++) {
                places[i] = str;
                str = str.back()+str.substr(0, str.length()-1);
            }

        }

        bool insert(int row, Tile tile) {
            int index = -1;
            for (int i = 0; i < cols; i++) {
                if (tileToChar(tile) == places[row][i] && wall[row][i] == E) {
                    index = i;
                }
            }
            if (index == -1)
                return false;
            else {
                wall[row][index] = tile; 
                score += calculateScore(row, index);
                return true;
            }
        }

        int calculateScore(int r, int c) {
            int scoreCount = 1;
            
            int i = r-1, j = c;
            while (i >= 0 && wall[i][j] != E) {
                scoreCount++;
                i--;
            }
            
            i = r+1, j = c;
            while (i < rows && wall[i][j] != E) {
                scoreCount++;
                i++;
            }

            i = r, j = c-1;
            while (j >= 0 && wall[i][j] != E) {
                scoreCount++;
                j--;
            }

            i = r, j = c+1;
            while (j < cols && wall[i][j] != E) {
                scoreCount++;
                j++;
            }

            return scoreCount;
        }

        bool isAnyRowFilled() {
            for (int i = 0; i < rows; i++) {
                int count = 0;
                for (int j = 0; j < cols; j++) {
                    if (wall[i][j] != E)
                        count++;
                }
                if (count == cols)
                    return true;
            }
            return false;
        }

        bool rowContains(int row, Tile tile) {
            for (int i = 0; i < cols; i++) {
                if (wall[row][i] == tile)
                    return true;
            }
            return false;
        }

        void printRow(ostream& out, int row) {
            for (int i = 0; i < cols; i++)
                out << tileToChar(wall[row][i]) << " ";
        }

        int getScore() {
            return score;
        }

        void reset() {
            score = 0;
        }

        int totalHorizontalFilled() {
            int filled = 0;
            for (int i = 0; i < rows; i++) {
                int count = 0;
                for (int j = 0; j < cols; j++) {
                    if (wall[i][j] != E)
                        count++;
                }
                if (count == cols)
                    filled++;
            }
            return filled;
        }

        int totalVerticalFilled() {
            int filled = 0;
            for (int i = 0; i < rows; i++) {
                int count = 0;
                for (int j = 0; j < cols; j++) {
                    if (wall[j][i] != E)
                        count++;
                }
                if (count == cols)
                    filled++;
            }
            return filled;
        }

        int total5TilesFilled() {
            Tile tiles[] = {R, Y, B, L, U};
            int filled = 0;
            for (Tile tile : tiles) {
                int count = 0;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (wall[i][j] == tile) {
                            count++;
                        }
                    }
                }
                if (count == COLORED_TILES) {
                    filled++;
                }
            }
            return filled;
        }

        stringstream dumps() {
            stringstream out;
            out << score << " ";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    char c =  tileToChar(wall[i][j]);
                    out << c << " ";
                }
            }
            return out;
        }

        void loads(stringstream& in) {
            in >> score;
            char c;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    in >> c;
                    if (c == '.')
                        wall[i][j] = E;
                    else
                        wall[i][j] = charToTile(c);
                }
            }
        }
};

#endif