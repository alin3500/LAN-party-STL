#include "meci.hpp"

meci::meci()
{
    e1 = echipa();
    e2 = echipa();
    urmator = NULL;
}

meci::meci(const meci& sursa)
{
    e1 = sursa.e1;
    e2 = sursa.e2;
    urmator = sursa.urmator;
}
meci::meci(echipa& ec1, echipa& ec2)
{
    e1 = ec1;
    e2 = ec2;
    urmator = NULL;
}

void meci::printMeci(ostream& devo)
{
    devo << e1.getNume();
    for(int i = 0; i < (33 - e1.getNume().length()); i++)
        devo << " ";
    
    devo << "-";
    
    for(int i = 0; i < (33 - e2.getNume().length()); i++)
        devo << " ";

    devo << e2.getNume() << endl;
}

echipa& meci::getWinner()
{
    if(e2.getScor() >= e1.getScor())
    {
        e2.addScor(1);
        return e2;
    }
    else
    {
        e1.addScor(1);
        return e1;
    }
}

echipa& meci::getLoser()
{
    if(e2.getScor() < e1.getScor())
        return e2;
    
    else
        return e1;
  
}