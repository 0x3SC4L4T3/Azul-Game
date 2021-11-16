#include <time.h>
#include <stdlib.h>
#include <exception>

#include "azul.h"

#include <iostream>

using namespace std;

int seed = 1;

void gameLoop(Azul& game) {
    while (true) {
        cout << "=== Start Round ===" << endl;

        game.factoryOfferPhase(cin, cout);
        game.wallTilingPhase();
        game.printPlayerStats(cout);

        if (game.isGameOver()) {
            break;
        }

        cout << "Would you like to continue to next round? (y/n) " << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice != 'y')
            break;

        
        game.preparationPhase();
    }
    game.bonusScoringPhase();
    game.printFinalScore(cout);
    cout << endl;
}

int main(int argc, char** argv) {

    // checking command line argument
    int i;
    for(i=0; i<argc; ++i)
    {   
        string str(argv[i]);
        if (str == "-s") {
            seed = stoi(string(argv[i+1]));
            cout << "*** Seed changed to " << seed << " ***" << endl;
        }
    }

    cout << "Seed = " << seed << endl;

    TileBag tileBag(seed);

    while (true) {
        cout << "Welcome to Azul!\n" << 
            "-------------------\n" << 
            "Menu\n" << 
            "----\n" << 
            "1. New Game\n" << 
            "2. Load Game\n" << 
            "3. Credits (Show student information)\n" << 
            "4. Quit\n" << endl;
    
        cout << "> ";
        int op;
        cin >> op;
        cin.ignore();

        if (op == 1) {
            cout << "Starting New Game..." << endl;

            Azul game(tileBag);
            
            game.playersSetup(cin, cout);
            gameLoop(game);
        }
        else if (op == 2) {
            Azul game(tileBag);
            cout << "Enter the filename from which load a game" << endl;
            string filename;

            do {
                cin >> filename;
            } while(!does_file_exist(filename));

            ifstream inFile(filename);

            stringstream buffer;
            buffer << inFile.rdbuf();
            inFile.close();
            game.loads(buffer);

            cout << "Azul game successfully loaded" << endl;
            gameLoop(game);
        }
        else if (op == 3) {
            cout << "----------------------------------\n" << endl;
            
            
            cout << "Name: Saad 1\nStudent ID: 214141412\n" << endl;
            cout << "Name: Saad 2\nStudent ID: ajnsajfnasf\n" << endl;
            cout << "Name: Saad 3\nStudent ID: akknfas\n" << endl;

            cout << "----------------------------------\n" << endl;
        }
        else if (op == 4) {
            return 0;
        }
    }
}