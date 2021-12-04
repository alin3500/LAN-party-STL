#include "Player.hpp"

Player::Player()
{
    points = 0;
}
Player::Player(string FN, string SN, int XP)
{
    firstName = FN;
    secondName = SN;
    points = XP;
}

Player::Player(const Player& sursa)
{
    firstName = sursa.getFN();
    secondName = sursa.getSN();
    points = sursa.getXP();
}

Player& Player::operator=(const Player& sursa)
{
    firstName = sursa.getFN();
    secondName = sursa.getSN();
    points = sursa.getXP();

    return (*this);
}
string Player::getFN() const
{
    return firstName;
}

string Player::getSN() const
{
    return secondName;
}

int Player::getXP() const
{
    return points;
}

void Player::setFN(string fn)
{
    firstName = fn;
}

void Player::setSN(string sn)
{
    secondName = sn;
}
void Player::addXP(int p)
{
    points += p;
}

ifstream& operator>>(ifstream& devi, Player& tinta)
{
    string fn, sn;
    int xp;
    devi >> fn >> sn >> xp;

    tinta.setFN(fn);
    tinta.setSN(sn);
    tinta.addXP(xp);

    return devi;
}

ostream& operator<<(ostream& devo, Player& sursa)
{
    devo << sursa.firstName << " " << sursa.secondName << " " << sursa.points;
    return devo;
}
