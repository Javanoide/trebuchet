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

    population = populationTrie;

    return population;
}
Catapult* crossOver(Catapult* populationTrie)
{
    int sizeArray = 7;

    for(int i=0; i<nbGen; i++)
    {
        for(int j=0; j< sizeArray; j++)
        {
            if(ui(mt_rand)%2)
            {
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

    return populationTrie;
}

Catapult* mutation(Catapult* population, float taux)
{
    for(int i=0; i<nbGen; i++)
    {
        Catapult c = population[i];
        for(int j=0; j<7; j++)
        {
            int mut = ui(mt_rand)%100;
            if(mut < taux*100)
            {
                if(j==0 || j==1){
                    c.adn[j] = ui(mt_rand)%360;
                }else{
                    c.adn[j] = ui(mt_rand)%1000;
                }
            }
        }
        population[i] = c;
    }
    return population;
}

double variance (Catapult* population)
{
    double variance;
    float sum, sumSqr;
    int n;
    for(int i=0; i<nbGen; i++)
    {
        n++;
        sum+=population[i].portee;
        sumSqr+=(population[i].portee*population[i].portee);
    }
    variance = (sumSqr-(sum*sum)/n)/(n-1);

    return variance;
}
/*  Let n = 0, Sum = 0, SumSq = 0
    For each datum x:
        n ← n + 1
        Sum ← Sum + x
        SumSq ← SumSq + x × x
    Var = (SumSq - (Sum × Sum) ⁄ n) ⁄ (n − 1)*/



int main(int argc, char *argv[])
{
    bool obj = false;
    int winner=0;
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

    Catapult population[nbGen];


    //generation de la première génération de catapultes
    for(int i=0; i<nbGen; i++)
    {
        float aButee = ui(mt_rand);
        aButee = (aButee==0) ? ui(mt_rand) : aButee;

        float aTraction = ui(mt_rand);
        aTraction = (aTraction==0) ? ui(mt_rand) : aTraction;

        float mBras = ui(mt_rand);
        mBras = (mBras==0) ? ui(mt_rand) : mBras;

        float mPoid = ui(mt_rand);
        mPoid = (mPoid==0) ? ui(mt_rand) : mPoid;

        float mProjectile = ui(mt_rand);
        mProjectile = (mProjectile==0) ? ui(mt_rand) : mProjectile;

        float lBase = ui(mt_rand);
        lBase = (lBase==0) ? ui(mt_rand) : lBase;

        float lBras = ui(mt_rand);
        lBras = (lBras==0) ? ui(mt_rand) : lBras;

        Catapult c = Catapult(aButee, aTraction, mBras, mPoid, mProjectile, lBase, lBras);
        population[i] = c;
    }


    /*cout << "number of generation ?" <<endl;
    cin >>input;

    for(int gen=0; gen<input; gen++)*/
    int gen=0;
    while(!obj)
    {
        cout << "Generation " << gen++ << "-----------------------------------------------------" <<endl;
        cout << "Variance : " << variance(population) << endl;

        Catapult* populationEnfant = RWS(population);

        if(LOG_ADV)
        {
            for(int i=0; i<nbGen; i++){
                cout << "Catapute : " << i+1 << endl;
                cout << "Distance : " << populationEnfant[i].portee << " metres" << endl;
                cout << "Viab infilité : " << populationEnfant[i].viable << endl;
                cout << "TNT : " << populationEnfant[i].eTNT << endl;
                cout << "Score : " << populationEnfant[i].score << endl;
                cout << "--------------------------------------" << endl;
            }
        }

        populationEnfant = crossOver(populationEnfant);
        populationEnfant = mutation(populationEnfant, tauxMut);

        for(int i=0; i<nbGen; i++)
        {
            Catapult c = populationEnfant[i];
            c.calcPhysics();
            c.calcScore();
            if(c.portee>=298 && c.portee<=302)
            {
                obj=true;
                winner = i;
            }
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

    cout << "Winner ---------------------------------------------------------------------------------------------" << endl;
    cout << "Distance : " << population[winner].portee << " metres" << endl;
    cout << "Viabilité : " << population[winner].viable << endl;
    cout << "TNT : " << population[winner].eTNT << endl;
    cout << "Score : " << population[winner].score << endl;
    cout << "--------------------------------------" << endl;
}
