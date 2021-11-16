#ifndef AZUL
#define AZUL

#include "macros.h"
#include "factory.h"
#include "tilebag.h"
#include "wall.h"
#include "storage.h"
#include "mosaic.h"
#include "player.h"
#include "List.h"
class Azul {
    List *players;
    Factory factories[FACTORIES];
    TileBag tileBag1;
    TileBag& tileBagRef = tileBag1;
    int turn;

    public:

        Azul() {
            turn = 0;
            preparationPhase();
        }
        
        Azul(TileBag& tileBag) {
            players = new List;
            Player *a, *b;
            a = new Player;
            b = new Player;
            players->insert(a);
            players->insert(b);
            turn = 0;
            preparationPhase();
            tileBagRef = tileBag;
        }

        void playersSetup(istream& in, ostream& out) {
            
            // input user names
            string name;
            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                out << "Enter a name for player " << i+1 << endl;
                getline(in, name);
                (*(players->get(i))).setName(name);
            }
        }

        
        void preparationPhase() {
            // reset factores and player round scores
            for (int i = 1; i < FACTORIES; i++) {
                factories[i].getTiles().clear();
                tileBagRef.fillFactory(factories[i]);
            }
            factories[0].getTiles().clear();
            factories[0].addTile(F);

            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                (*(players->get(i))).reset();
            }
        }

        bool areFactoriesEmpty() {
            // check if all factories are empty, if yes then return true
            for (int i = 0; i < FACTORIES; i++) {
                if (factories[i].getTiles().size() > 0)
                    return false;
            }
            return true;
        }

        bool noMovesLeft() {
            // check if player is able to move tiles into storage row, if there is no move left, return true.
            for (int i = 0; i < FACTORIES; i++) {
                for (Tile tile : factories[i].getTiles()) {
                    for (int i = 0; i < COLORED_TILES; i++) {
                        if ((*(players->get(turn))).getMosaic().getStorage().insertable(i, tile) && !(*(players->get(turn))).getMosaic().getWall().rowContains(i, tile))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        void factoryOfferPhase(istream& in, ostream& out) {
            // players start taking tiles from factory into their storage
            int factory;
            char color;
            int storagerow;
            Tile tile;

            while (!areFactoriesEmpty() && !noMovesLeft()) {
                // print factories
                out << "Factories:" << endl;
                for (int i = 0; i < FACTORIES; i++) {
                    factories[i].print(out);
                    out << endl;
                }

                
                // print mosaic
                (*(players->get(turn))).printMosaic(out);

                // taking input
                out << "TURN FOR PLAYER: " << (*(players->get(turn))).getName() << endl;
                int tilesCount = 0;
                string line;
                do  {
                    try {
                        out << "> ";
                        getline(in, line);
                        vector<string> tokens = split(line, " ");
                        if (tokens[0] == "save") {
                            if (tokens.size() == 2) {
                                string filename = tokens[1];
                                ofstream outfile(filename);
                                outfile << dumps().str() << endl;
                                outfile.close();
                                out << "saved as gameData.txt!" << endl;
                            }
                            else
                                out << "Syntax: save <filename>" << endl;
                            continue;
                        }
                        else if (tokens[0] == "exit") {
                            out << "Exiting.." << endl;
                            exit(0);
                        }
// add hellp code here
                        else if (tokens[0] == "help") {
                            out << "To take your turn enter 'ROLE NUMBER 'LETTER' 'NUMBER ROLE'" << endl;
                            out << "EXAMPLE 4 B 1" << endl;
                            out << "                " << endl;
                            out << "AVAILABLE COMMANDS" << endl;
                            out << "save (filename)" << endl;
                            out << "exit" << endl;
                            continue;
                        }
                        else if (tokens.size() != 3) {
                            out << "Invalid input!" << endl;
                            continue;
                        }
                        factory = stoi(tokens[0]);
                        color = tokens[1][0];
                        storagerow = stoi(tokens[2]);

                        storagerow -= 1;
                        tile = charToTile(color);
                    } catch (char const* e) {
                        out << e << endl;
                        continue;
                    }
                    catch (exception& e) {
                        // out << e.what() << endl;
                        out << "[Error] Invalid input! Please try again." << endl;
                        continue;
                    }

                    if (!factories[factory].containsTile(tile)) {
                        out << "[Error] No such element in factory!" << endl;
                    }
                    if (!(*(players->get(turn))).getMosaic().getStorage().insertable(storagerow, tile)) {
                        out << "[Error] Tile not insertable in storage row!" << endl;
                    }
                    if ((*(players->get(turn))).getMosaic().getWall().rowContains(storagerow, tile)) {
                        out << "[Error] Wall row already contains the tile of same color." << endl;
                    }                    

                }
                while (factory < 0 || factory > FACTORIES || !factories[factory].containsTile(tile) || !(*(players->get(turn))).getMosaic().getStorage().insertable(storagerow, tile) || (*(players->get(turn))).getMosaic().getWall().rowContains(storagerow, tile));
                

                // take tile from factory. returns frequncy of color taken and all remaining tiles that were not taken.
                // the remaining tiles will be placed inside 0 factory.
                pair<int, vector<Tile>> ret = factories[factory].takeTile(tile);
                tilesCount = ret.first;
                

                if (factory == 0) { // if tiles are being taken from center factory (0)
                    // if factory contains F tile, put that tile into broken or floor line
                    if (factories[factory].containsTile(F))
                        (*(players->get(turn))).getMosaic().getStorage().storeFirstTile();
                }
                // clear factory after tiles are taken.
                factories[factory].getTiles().clear();
                // put tiles that were not chosen into 0 factory
                for (int i = 0; i < ret.second.size(); i++) {
                    factories[0].getTiles().push_back(ret.second[i]);
                }


                // insert tile into mosaic storage
                (*(players->get(turn))).getMosaic().getStorage().insert(storagerow, tile, tilesCount);

                L1:

                out << "Turn successful." << endl;


                // switch trun
                turn = (turn+1)%2;

            }

            out << "Round Ended." << endl;

            // give first turn to that person who has "First" tile
            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                if ((*(players->get(i))).hasFirstTile())
                    turn = i;
            }
            
        }

        void printPlayerStats(ostream& out) {
            // print score
            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                (*(players->get(i))).printMosaic(out);
                out << (*(players->get(i))).getName() <<  "'s round score = " << (*(players->get(i))).getRoundScore() << endl;
                out << (*(players->get(i))).getName() <<  "'s total score = " << (*(players->get(i))).getScore() << endl;
            }
        }

        void bonusScoringPhase() {
            // give bonus score
            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                Wall& wall = (*(players->get(i))).getMosaic().getWall();
                int horizontalFilled = wall.totalHorizontalFilled();
                int verticalFilled = wall.totalVerticalFilled();
                int count5Tiles = wall.total5TilesFilled();

                (*(players->get(i))).setScore((*(players->get(i))).getScore()+horizontalFilled*2+verticalFilled*7+count5Tiles*20);
            }
        }
        
        bool isGameOver() {
            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                if ((*(players->get(i))).getMosaic().getWall().isAnyRowFilled())
                    return true;
            }
            return false;
        }

        void printFinalScore(ostream& out) {
            
            out << "-------------" << endl;

            int maxi = 0;
            int maxScore = 0;
            int maxScoreCount = 0;

            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                out << (*(players->get(i))).getName() << "'s score: " << (*(players->get(i))).getScore() << endl;
                if ((*(players->get(i))).getScore() > maxScore) {
                    maxScore = (*(players->get(i))).getScore();
                    maxi = i;
                    maxScoreCount = 1;
                }
                else if ((*(players->get(i))).getScore() == maxScore) {
                    maxScoreCount++;
                }
            }

            if (maxScoreCount == TOTAL_PLAYERS) {
                out << "Draw" << endl;
            } else {
                out << "Winner is " << (*(players->get(maxi))).getName() << endl;
            }

            out << "-------------" << endl;

            return;
        }

        void wallTilingPhase() {
            // inserting tiles from storage row into wall rows and updating the score

            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                int oldTotalScore = (*(players->get(i))).getMosaic().getScore();
                Storage& storage = (*(players->get(i))).getMosaic().getStorage();
                Wall& wall = (*(players->get(i))).getMosaic().getWall();
                for (int j = 0; j < COLORED_TILES; j++) {
                    if (storage.isFull(j)) {
                        Tile tile = storage.getTile(j);
                        storage.emptyLine(j);
                        wall.insert(j, tile);
                    }
                }
                (*(players->get(i))).setRoundScore((*(players->get(i))).getMosaic().getScore());
                (*(players->get(i))).setScore((*(players->get(i))).getScore()+(*(players->get(i))).getRoundScore());
            }
        }

        stringstream dumps() {
            // save data

            stringstream outs;
            
            outs << turn << " ";

            for (int i = 0; i < FACTORIES; i++) {
                outs << factories[i].dumps().str() << " ";
            }

            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                outs << (*(players->get(i))).dumps().str() << " ";
            }
            return outs;
        }

        void loads(stringstream& in) {
            // load data
            in >> turn;

            for (int i = 0; i < FACTORIES; i++) {
                factories[i].loads(in);
            }
            

            for (int i = 0; i < TOTAL_PLAYERS; i++) {
                (*(players->get(i))).loads(in);
            }

        }



};

#endif
