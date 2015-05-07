/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

#include "Catapult.h"
#define LOG         1
#define LOG_ADV     0

using namespace std;

//random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);
uniform_int_distribution<int> ui(1, 1000);
int nbGen = 0;

//Fonction de selection par roue biaisée
Catapult* RWS(Catapult population[])
{
    Catapult populationTrie[nbGen];
    float scoreTotal=0.f;
    float random;
    //calcul du score
    for(int i=0; i<nbGen; i++)
    {
        scoreTotal+= population[i].score;
    }

    for(int i=0; i<nbGen; i++)
    {
        Catapult A;
        Catapult B;
        //paramètres des boucles
        //uniform_int_distribution<int> ui2(1, scoreTotal-1);
        random = mt_rand()%(int)scoreTotal;
        int j = 0;

        //selection de A
        while(random > 0)
        {
            random-=population[j].score;
            j++;
        }
        A = population[j];
        populationTrie[i] = population[j];
        i++;



        //selection de B et reset dees paramètres de boucles
        j = 0;
        random = mt_rand()%(int)scoreTotal;


        while(random > 0)
        {
            random-=population[j].score;
            if(random <= 0)
            {
                B = population[j];

                //A==B on recommence la selection de B
                if(A.id==B.id)
                {
                    j = 0;
                    random = mt_rand()%(int)scoreTotal;
                }
                if(A.id!=B.id)
                {
                    populationTrie[i] = B;
                }
            }
            j++;
        }

    }
    cout << "finish RWS" <<endl;

    population = populationTrie;

    return population;
}
Catapult* crossOver(Catapult* populationTrie)
{
    cout << "Begin crossOver" << endl;
    int sizeArray = 7;

    for(int i=0; i<nbGen; i++)
    {
        for(int j=0; j< sizeArray; j++)
        {
            if(ui(mt_rand)%2)
            {
                cout << "fdffdffddf" << i << endl;
                Catapult A = populationTrie[i];
                Catapult B = populationTrie[i+1];
                float genA = A.adn[j];
                float genB = B.adn[j];
                A.adn[j] = genB;
                B.adn[j] = genA;

                populationTrie[i] = A;
                populationTrie[i+1] = B;
            }
        }
        i++;

    }

    cout << "End crossOver" << endl;

    return populationTrie;
}
///A DEBUGGER
/*void mutation(vector<Catapult*>* population, float taux)
{
    cout << "Begin Mutation" << endl;
    for(int i=0; i<population->size(); i++)
    {
        cout << "T1" << endl;
        Catapult* c = population->at(i);
        for(int j=0; j<7; j++)
        {
            int mut = ui(mt_rand)%100;
            if(mut < taux*100)
            {
                if(j==0 || j==1){
                        cout << "T2" << endl;
                    c->adn[j] = ui(mt_rand)%360;static variable
                }else{
                    cout << "T3" << endl;
                    c->adn[j] = ui(mt_rand)%1000;
                }
            }
        }
    }
    cout << "end Mutation" << endl;
}*/

int main(int argc, char *argv[])
{
    int input=1;
    while(input%2 >0)
    {
        cout << "number of catapults per generation ?" <<endl;
        cin >>input;
    }
    //nombre de catapult généré par génération
    nbGen = input;

    cout << "Mutation percentage ?" <<endl;

    cin >> input;

    int tauxMut = input/100;
    cout << tauxMut << endl;

    Catapult population[nbGen];


    //generation de la première génération de catapultes
    for(int i=0; i<nbGen; i++)
    {
        float aButee = ui(mt_rand);
        float aTraction = ui(mt_rand);
        float mBras = ui(mt_rand);
        float mPoid = ui(mt_rand);
        float mProjectile = ui(mt_rand);
        float lBase = ui(mt_rand);
        float lBras = ui(mt_rand);

        Catapult c = Catapult(aButee, aTraction, mBras, mPoid, mProjectile, lBase, lBras);
        population[i] = c;
    }


    cout << "number of generation ?" <<endl;
    cin >>input;

    for(int gen=0; gen<input; gen++)
    {
        cout << "Generation " << gen+1 << "-----------------------------------------------------" <<endl;

        Catapult* populationTrie = RWS(population);

        if(LOG_ADV)
        {
            for(int i=0; i<nbGen; i++){
                cout << "Catapute : " << i+1 << endl;
                cout << "Distance : " << populationTrie[i].portee << " metres" << endl;
                cout << "Viabilité : " << populationTrie[i].viable << endl;
                cout << "TNT : " << populationTrie[i].eTNT << endl;
                cout << "Score : " << populationTrie[i].score << endl;
                cout << "--------------------------------------" << endl;
            }
        }

        populationTrie = crossOver(populationTrie);

        for(int i=0; i<nbGen; i++)
        {
            Catapult c = population[i];
            c.calcPhysics();
            c.calcScore();
            population[i] = c;
        }
    }


    if(LOG)
    {
        cout << "Result ---------------------------------------------------------------------------------------------" << endl;
            for(int i=0; i<nbGen; i++){
                cout << "Catapute : " << i+1 << endl;
                cout << "Distance : " << population[i].portee << " metres" << endl;
                cout << "Viabilité : " << population[i].viable << endl;
                cout << "TNT : " << population[i].eTNT << endl;
                cout << "Score : " << population[i].score << endl;
                cout << "--------------------------------------" << endl;
            }
    }

    /*for(int i=0; i<nbGen; i++)
    {
        delete population[i];
    }*/
}
