#ifndef MECI_HPP_INCLUDED
#define MECI_HPP_INCLUDED

#include "echipa.hpp"

class meci
{
public:
    echipa e1;
    echipa e2;
    meci* urmator;

    meci();
    meci(const meci&);
    meci(echipa&, echipa&);

    void printMeci(ostream&);
    echipa& getWinner();
    echipa& getLoser();

};
#endif