/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Catapult.h"
#define LOG         1
#define LOG_ADV     0

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
        scoreTotal+= population[i]->score;
    }

    for(int i=0; i<(population.size()/2); i++)
    {
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
            j+=population[n]->score;
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
            j+=population[n]->score;
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
    for(int i=0; i<couples.size(); i++)
    {
        vector<Catapult*> couple = couples[i];
        //on tire au hasard 0 ou 1 si 1, on inverse le géne, si 0 on garde
        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->aButee;
            float g1 = couple[1]->aButee;

            couple[0]->aButee = g1;
            couple[1]->aButee = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->aTraction;
            float g1 = couple[1]->aTraction;

            couple[0]->aTraction = g1;
            couple[1]->aTraction = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->mBras;
            float g1 = couple[1]->mBras;

            couple[0]->mBras = g1;
            couple[1]->mBras = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->mPoid;
            float g1 = couple[1]->mPoid;

            couple[0]->mPoid = g1;
            couple[1]->mPoid = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->mProjectile;
            float g1 = couple[1]->mProjectile;

            couple[0]->mProjectile = g1;
            couple[1]->mProjectile = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->lBase;
            float g1 = couple[1]->lBase;

            couple[0]->lBase = g1;
            couple[1]->lBase = g0;
        }

        srand(rand());
        if(rand()%2)
        {
            float g0 = couple[0]->lBras;
            float g1 = couple[1]->lBras;

            couple[0]->lBras = g1;
            couple[1]->lBras = g0;
        }

        couples[i] = couple;
    }
    return couples;
}

int main(int argc, char *argv[])
{
    int input=1;
    while(input%2 >0)
    {
        cout << "number of generation ?" <<endl;
        cin >>input;
    }

    const int nbGen = input;
    vector<Catapult*> population;

    for(int gen=0; gen<nbGen; gen++)
    {
        cout << "Generation " << gen << "-----------------------------------------------------" <<endl;

        //generation de la première génération de catapultes
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

        if(LOG_ADV)
        {
            for(int i=0; i<nbGen; i++){
                cout << "Catapute : " << i+1 << endl;
                cout << "Distance : " << population[i]->portee << " metres" << endl;
                cout << "Viabilité : " << population[i]->viable << endl;
                cout << "TNT : " << population[i]->eTNT << endl;
                cout << "Score : " << population[i]->score << endl;
                cout << "--------------------------------------" << endl;
            }
        }

        vector<vector<Catapult*>> couples = RWS(population);
        couples = mutation(couples, 0);
        vector<Catapult*> newPopulation;

        for(int i=0; i<couples.size(); i++)
        {
            vector<Catapult*> couple = couples[i];

            for(int j=0; j<couple.size(); j++)
            {
                newPopulation.push_back(couple[j]);
            }
        }

        population = newPopulation;
    }


    if(LOG)
    {
        cout << "Result ---------------------------------------------------------------------------------------------" << endl;
        for(int i=0; i<population.size(); i++){
            cout << "Catapute : " << i+1 << endl;
            cout << "Distance : " << population[i]->portee << " metres" << endl;
            cout << "Viabilité : " << population[i]->viable << endl;
            cout << "TNT : " << population[i]->eTNT << endl;
            cout << "Score : " << population[i]->score << endl;
            cout << "--------------------------------------" << endl;
        }
    }
}
