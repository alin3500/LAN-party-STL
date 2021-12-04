#include "meci.hpp"
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>

int main(int argc, char** argv)
{
    vector<string> v8;
    list<echipa> echipe, top8;

    ifstream cer(argv[1], ios::in);
    //Creeaza un vector in care sunt stocate datele din cerinte.in
    int *buf = new int[5];

    for(int i = 0; i < 5; i++)
        cer >> buf[i];

    int nrEchipe;

    //Cerinta 1
    if(buf[0] == 1)
    {
        list<echipa>::iterator it;
        ofstream fout(argv[3], ios::out);
        ifstream fin(argv[2], ios::in);
        echipa aux;

        fin >> nrEchipe;
        fin >> aux;
        echipe.push_back(aux);

        for(int i = 1; i < nrEchipe; i++)
        {
            fin >> aux;
            echipe.push_front(aux);
        }

        for(it = echipe.begin(); it != echipe.end(); ++it)
            fout << (*it).getNume() << endl;

        fin.close();
        fout.close();
    }

    //Cerinta 2
    if(buf[1] == 1)
    {   
        list<echipa>::iterator it;
        ofstream fout2(argv[3], ios::out);

        vector<float> scorAux;
        vector<float>::iterator itScor;
        int p2_Max = 1;

        //Cauta puterea maxima a lui 2 <= cu numarul de echipe
        while(echipe.size() >= p2_Max * 2)
            p2_Max *= 2;

        //Creeaza un vector cu punctajele fiecarei echipe
        for(it = echipe.begin(); it != echipe.end(); ++it)
            scorAux.push_back((*it).getScor());

        //Sorteaza vectorul cu punctaje, pentru a putea fi eliminate, ulterior, 
        //echipele cu cele mai mici punctaje
        sort(scorAux.begin(), scorAux.end());

        itScor = scorAux.begin();
        int size = echipe.size();

        //Cauta echipele in ordine crescatoare a punctajelor si le elimina
        for(int i = 0; i < size - p2_Max; i++)
        {
            for(it = echipe.begin(); it != echipe.end(); ++it)
            {
                if((*it).getScor() == (*itScor))
                {
                    it = echipe.erase(it);
                    it = echipe.end();
                    it--;
                }
            }
            //Odata gasita o echipa, o elimina si trece la urmator punctaj de cautat, conform enuntului 2
            itScor++;
        }

        for(it = echipe.begin(); it != echipe.end(); ++it)
            fout2 << (*it).getNume() << endl;

        nrEchipe = p2_Max;

        fout2.close();
    }


    //Cerinta 3
    if(buf[2] == 1)
    {
        ofstream fout3(argv[3], ios::app);

        list<echipa>::iterator it;
        stack<echipa> Winners, Losers;
        queue<meci> Coada;

        int runda = 1;
        while(nrEchipe > 1)
        {
            
            while(!Coada.empty())
                Coada.pop();
            while(!Winners.empty())
                Winners.pop();
            while(!Losers.empty())
                Losers.pop();

            it = echipe.begin();
            
            for(int i = 0; i < nrEchipe / 2; i++)
            {   
                //Adaugare meciuri in coada
                echipa ec1(*it);
                it++;
                echipa ec2(*it);
                meci meciAux(ec1, ec2);
                Coada.push(meciAux);

                //Impartirea echipelor in stivele de castigatori, respectiv pierzatori
                Winners.push(meciAux.getWinner());
                Losers.push(meciAux.getLoser());

                it++;
            }

            //Goleste lista de echipe;
            echipe.clear();


            while(!Losers.empty())
                Losers.pop();
            
            stack<echipa> winAux = Winners;

            while(!winAux.empty())
            {
                //Adauga castigatorii pentru a forma noua lista de echipe
                echipe.push_back(winAux.top());

                if(nrEchipe == 16)
                    top8.push_back(winAux.top());

                winAux.pop();
            }
        
            //Scrie meciurile

            fout3 << endl << "--- ROUND NO:" << runda << endl;
            for(int i = 0; i < nrEchipe / 2; i++)
            {
                Coada.front().printMeci(fout3);
                Coada.pop();
            }

            //Scrie castigatorii
            fout3 << endl << "WINNERS OF ROUND NO:" << runda;
            for(int i = 0; i < nrEchipe / 2; i++)
            {
                fout3 << endl << Winners.top().getNume();
                for(int j = 0; j < 34 - Winners.top().getNume().length() ; j++)
                    fout3 << " ";
                
                fout3 << "-  " << fixed << setprecision(2) << Winners.top().getScor();
                
                Winners.pop();
            }

            fout3 << endl;

            runda++;
            nrEchipe /= 2;
        }
        fout3.close();
        
    }

//Cerinta 4
    if(buf[3] == 1)
    {
        multimap<float, string> BST;
        multimap<float, string>::reverse_iterator itmap, itmap2;

        ofstream fout4(argv[3], ios::app);
        list<echipa>::iterator it;

        //Parcurge primele 8 echipe si le introduce in map
        for(it = top8.begin(); it != top8.end(); ++it)
            BST.insert(pair<float, string>((*it).getScor(), (*it).getNume()));

        fout4 << endl << "TOP 8 TEAMS:";

        for(itmap = BST.rbegin(); itmap != BST.rend(); ++itmap)
        {
            map<string, float> mapAux;
            map<string, float>::reverse_iterator itmapAux;
            int n = 0;

            //Cauta cate echipe cu acelasi scor urmeaza, si le introduce in <mapAux> pentru a fi sortate dupa nume
            for(itmap2 = itmap; itmap2 != BST.rend(); ++itmap2)
                if((*itmap).first == (*itmap2).first)
                {
                    n++;
                    mapAux.insert(pair<string, float>((*itmap2).second, (*itmap2).first));
                }

            //Scrie echipele in fisier, iar in cazul in care acestea au acelasi punctaj,
            //le scrie in ordine alfabetica descrescatoare
            for(itmapAux = mapAux.rbegin(); itmapAux != mapAux.rend(); ++itmapAux)
            {
                fout4 << endl << (*itmapAux).first;

                for(int j = 0; j < 34 - (*itmapAux).first.length() ; j++)
                    fout4 << " ";
                    
                fout4 << "-  " << fixed << setprecision(2) << (*itmapAux).second;

                //Se introduc numele echipelor in ordinea corecta in vectorul <v8>
                v8.push_back((*itmapAux).first);
            }
        
            for(int i = 0; i < n-1; i++)
                itmap++;
        }
        fout4.close();
    }
    
    if(buf[4] == 1)
    {
        ofstream fout5(argv[3], ios::app);

        multimap<float, string> AVL;
        vector<string>::iterator itv = v8.begin();
        list<echipa>::iterator it;

        //Parcurge primele 8 echipe si le introduce in map
        for(it = top8.begin(); it != top8.end(); ++it)
            AVL.insert(pair<float, string>((*it).getScor(), (*it).getNume()));

        fout5 << endl << endl << "THE LEVEL 2 TEAMS ARE:";

        //Sunt scrise numele din vectorul cu ordinea corecta
        for(int i = 0; i < 8; i++)
        {
            if(i % 2 == 0)
                fout5 << endl << *itv;

            ++itv;
        }

    }
    delete [] buf;

    return 0;
}
