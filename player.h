#ifndef PLAYER_H
#define PLAYER_H

#include "mosaic.h"

class Player {
    string name;
    Mosaic mosaic;
    int score;
    int roundScore;


    public:
        Player() {
            name = "";
            score = 0;
            roundScore = 0;
        }

        Player(string name){
            setName(name);
            score = 0;
            roundScore = 0;
        }

        void setName(string name) {
            this->name = name;
        }

        string getName() {
            return name;
        }

        int getScore() {
            return score;
        }

        
        void setScore(int score) {
            this->score = score;
        }

        int getRoundScore() {
            return roundScore;
        }

        
        void setRoundScore(int score) {
            roundScore = score;
        }

        Mosaic& getMosaic() {
            return mosaic;
        }


        void printMosaic(ostream& out) {
            out << "Mosaic for " << getName() << ": " << endl;
            getMosaic().print(out);
            out << endl;
        }

        
        void reset() {
            mosaic.getStorage().reset();
            mosaic.getWall().reset();
            roundScore = 0;
        }

        bool hasFirstTile() {
            vector<Tile>& floorLine = mosaic.getStorage().getBroken();
            return floorLine.size() > 0 && floorLine[0] == F;
        }

        stringstream dumps() {
            stringstream out;
            out << name << " " << score << " " << roundScore << " ";
            out << mosaic.dumps().str() << " ";
            return out;
        }

        void loads(stringstream& in) {
            in >> name >> score >> roundScore;
            
            mosaic.loads(in);
        }
};

#endif