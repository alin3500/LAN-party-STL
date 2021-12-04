#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <cmath>
#include <iomanip>
using namespace std;

class Player
{
private:
    string firstName;
    string secondName;
    int points;

public:
    Player();
    Player(string, string, int);
    Player(const Player&);
    Player& operator=(const Player&);

    string getFN() const;
    string getSN() const;
    int getXP() const;
        
    void setFN(string);
    void setSN(string);
    void addXP(int);

    friend ifstream& operator>>(ifstream&, Player&);
    friend ostream& operator<<(ostream&, Player&);
};

#endif
