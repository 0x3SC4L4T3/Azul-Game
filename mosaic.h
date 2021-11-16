/*
Name: Joel Jacob
Student ID: s3660851

Name: Ali Redha
Student ID: s3661626

Name: Julian Gencarelli
Student ID: s3661422
*/

#ifndef MOSAIC_H
#define MOSAIC_H

#include "storage.h"
#include "wall.h"


class Mosaic {
    Storage storage;
    Wall wall;

    public:

        Mosaic() {
            
        }

        void print(ostream& out) {
            for (int i = 0; i < COLORED_TILES; i++) {
                out << i+1 << ": ";
                storage.printRow(out, i);
                out << " || ";
                wall.printRow(out, i);
                out << endl;
            }
            storage.printBroken(out);
        }

        Storage& getStorage() {
            return storage;
        }

        Wall& getWall() {
            return wall;
        }

        int getScore() {
            return wall.getScore()+storage.getPenalty();
        }

        void loads(stringstream& in) {
            storage.loads(in);
            wall.loads(in);
        }

        stringstream dumps() {
            stringstream out;
            out << storage.dumps().str() << " ";
            out << wall.dumps().str() << " ";
            return out;
        }

};


#endif
