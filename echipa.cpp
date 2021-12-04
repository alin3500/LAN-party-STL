#include "echipa.hpp"

echipa::echipa()
{
    nume = " ";
    nrPlayeri = 0;
    playeri = NULL;
    scor = 0.0;
    urmator = NULL;
}


echipa::~echipa()
{
    delete [] playeri;
}

echipa::echipa(const echipa& sursa)
{
    nume = sursa.nume;
    nrPlayeri = sursa.nrPlayeri;
    playeri = new Player[nrPlayeri];
    for(int i = 0; i < nrPlayeri; i++)
        playeri[i] = sursa.playeri[i];
    
    scor = sursa.scor;
    urmator = sursa.urmator;
}

echipa& echipa::operator=(const echipa& sursa)
{
    nume = sursa.getNume();
    nrPlayeri = (sursa.getNR());

    if(playeri != NULL)
        delete [] playeri;
        
    playeri = new Player[nrPlayeri];
    for(int i = 0; i < nrPlayeri; i++)
        playeri[i] = sursa.getPlayer(i);

    scor = sursa.getScor();
    urmator = sursa.urmator;

    return *this;
}

float echipa::getScor() const
{
    return scor;
}

string echipa::getNume() const
{
    return nume;
}

void echipa::setScor(float s)
{
    scor = s;
}
void echipa::addScor(float s)
{
    scor += s;
    for(int i = 0; i < nrPlayeri; i++)
        playeri[i].addXP(s);
}
 int echipa::getNR() const
 {
     return nrPlayeri;
 }
void echipa::printEchipa(ostream& devo) const
{
    devo << endl << nume;
    for(int i = 0; i < 34 - nume.length(); i++)
        devo << " ";
    devo << "-  " << fixed << setprecision(2) << scor;
}

Player& echipa::getPlayer(int i) const
{
    return playeri[i];
}
ifstream& operator >>(ifstream& devi, echipa& tinta)
{
    char* buf = new char[100];
    devi >> tinta.nrPlayeri;
    devi.getline(buf,256, '\n');
    
    //Sterge eventualele spatii de la sfarsitul numelui
    if(buf[strlen(buf)-1] == ' ')
        buf[strlen(buf)-1] = '\0';

    float scorAux = 0.0;

    tinta.nume = &buf[1];

    if(tinta.playeri != NULL)
        delete [] tinta.playeri;
    tinta.playeri = new Player[tinta.nrPlayeri];
    for(int i = 0; i < tinta.nrPlayeri; i++)
        devi >> tinta.playeri[i];

    
    for(int i = 0; i < tinta.nrPlayeri; i++)
        scorAux += tinta.playeri[i].getXP();

    scorAux /= tinta.getNR();

    tinta.setScor(scorAux);

    delete [] buf;

    return devi;
}

ostream& operator<<(ostream& devo, echipa& sursa)
{
    devo << sursa.nume << " ";
    devo << sursa.nrPlayeri << " ";

    for(int i = 0; i < sursa.nrPlayeri; i++)
        devo << endl << sursa.playeri[i];
    
    return devo;

}