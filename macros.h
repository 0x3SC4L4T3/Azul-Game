#ifndef MACROS_H
#define MACROS_H
#include <vector>
#include <string>
#include <fstream>

#define FACTORIES 6
#define COLORED_TILES 5
#define BROKEN_PENALTY_LEN 6
#define TOTAL_PLAYERS 2

using namespace std;

enum Tile {
    E, // empty
    R,
    Y,
    B,
    L,
    U,
    F
};




char tileToChar(Tile tile) {
    char c = 0;
    if (tile == E) c = '.';
    else if (tile == R) c = 'R';
    else if (tile == Y) c = 'Y';
    else if (tile == B) c = 'B';
    else if (tile == L) c = 'L';
    else if (tile == U) c = 'U';
    else if (tile == F) c = 'F';
    return c;
}

Tile charToTile(char c) {
    Tile tile = E;
    if (c == 'R') tile = R;
    else if (c == 'Y') tile = Y;
    else if (c == 'B') tile = B;
    else if (c == 'L') tile = L;
    else if (c == 'U') tile = U;
    else if (c == 'F') tile = F;
    else throw "color tile not found!";
    return tile;
}


vector<string> split(string s, string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> tokens;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

bool does_file_exist(string fileName)
{
    ifstream infile;
    infile.open(fileName);
    return infile.good();
}

#endif
