/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Catapult.h"
#define LOG 1

using namespace std;

//Fonction de selection par roue biaisée
vector<vector<Catapult*>> RWS(vector<Catapult*> population)
{
    //Tableau de couples
    vector<vector<Catapult*>> couples;
    float scoreTotal=0.f;
    float random = rand();
    //calcul du score
    for(int i=0; i<population.size(); i++)
    {
        scoreTotal+= population[i]->getScore();
    }

    for(int i=0; i<(population.size()/2); i++)
    {
        cout << "couple : " << i << endl;
        vector<Catapult*> couple;
        Catapult* A;
        Catapult* B;
        //paramètres des boucles
        srand(random);
        random = rand()%(int)scoreTotal;
        float j = 0;
        int n=0;
        bool finish = false;

        //selection de A
        while(j<scoreTotal && !finish)
        {
            j+=population[n]->getScore();
            if(j>random)
            {
                A = population[n];
                couple.push_back(A);
                finish=true;
            }
            n++;
        }

        //selection de B et reset dees paramètres de boucles
        finish = false;
        j = 0;
        n=0;
        srand(random);
        random = rand()%(int)scoreTotal;

        while(j<scoreTotal && !finish)
        {
            j+=population[n]->getScore();
            if(j>random)
            {
                B = population[n];

                //A==B on recommence la selection de B
                if(A==B)
                {
                    j = 0;
                    n = -1;
                    random = rand()%(int)scoreTotal+1;
                }
                if(A!=B)
                {
                    cout << "not equals" << endl;
                    couple.push_back(B);
                    finish=true;
                }
            }

            n++;
        }

        couples.push_back(couple);
    }
    cout << "finish" << endl;
    return couples;
}

//fonction de mutation
vector<vector<Catapult*>> mutation(vector<vector<Catapult*>> couples, int tauxMutation)
{
    return null;
}

int main(int argc, char *argv[])
{
    const int nbGen = 10;
    vector<Catapult*> population;

    //generation des catapultes
    for(int i=0; i<nbGen; i++)
    {
        float aButee = rand()%360 + 1;
        float aTraction = rand()%360 + 1;
        float mBras = rand();
        float mPoid = rand();
        float mProjectile = rand();
        float lBase = rand();
        float lBras = rand();

        Catapult* c = new Catapult(aButee, aTraction, mBras, mPoid, mProjectile, lBase, lBras);
        population.push_back(c);
    }

    if(LOG){
        for(int i=0; i<nbGen; i++){
            cout << "Catapute : " << i+1 << endl;
            cout << "Distance : " << population[i]->getPortee() << " metres" << endl;
            cout << "Viabilité : " << population[i]->isViable() << endl;
            cout << "TNT : " << population[i]->getETNT() << endl;
            cout << "Score : " << population[i]->getScore() << endl;
            cout << "--------------------------------------" << endl;
        }
    }

    vector<vector<Catapult*>> couples = RWS(population);

    for(int i=0; i<couples.size(); i++)
    {
        cout << "----------Couple " << i << endl;
        vector<Catapult*> couple = couples[i];

        for(int j=0; j<couple.size(); j++)
        {
            cout << couple[j]->getScore() << endl;
        }
    }

    //cout << rand()%2 << endl;
}
