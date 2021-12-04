#ifndef ECHIPA_HPP_INCLUDED
#define ECHIPA_HPP_INCLUDED

#include "Player.hpp"

class echipa
{
private:
    string nume;
    int nrPlayeri;
    Player* playeri;
    float scor;

public:
    echipa *urmator;
    echipa();
    ~echipa();
    echipa(const echipa&);
    echipa& operator=(const echipa&);

    float getScor() const;
    string getNume() const;

    Player& getPlayer(int) const;
    void setScor(float);
    void addScor(float);
    int getNR() const;
    void printEchipa(ostream&) const;

    friend ifstream& operator>>(ifstream&, echipa&);
    friend ostream& operator<<(ostream&, echipa&);
};

#endif