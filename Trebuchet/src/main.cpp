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

#include "Catapult.h"
#define LOG         1
#define LOG_ADV     0

using namespace std;

random_device rd;
mt19937 mt_rand(rd());

//Fonction de selection par roue biaisée
vector<vector<Catapult*>> RWS(vector<Catapult*> population)
{
    //Tableau de couples
    vector<vector<Catapult*>> couples;
    float scoreTotal=0.f;
    float random;
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
        random = mt_rand()%(int)scoreTotal;
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
        random = mt_rand()%(int)scoreTotal;

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
                    random = mt_rand()%(int)scoreTotal+1;
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
vector<vector<Catapult*>> crossOver(vector<vector<Catapult*>> couples)
{
    int sizeArray = 7;
    int nbChangeUsed = 0;
    for(int i=0; i<couples.size(); i++)
    {
        vector<Catapult*> couple = couples[i];
        //on tire au hasard 0 ou 1 si 1, on inverse le géne, si 0 on garde
        for(int j=0; j< sizeArray; j++)
        {
            if(mt_rand()%2)
            {
                swap(couple[0]->adn[j], couple[1]->adn[j]);
            }
        }

    }
    return couples;
}

vector<Catapult*> mutation(vector<Catapult*> population, float taux)
{
    for(int i=0; i<population.size(); i++)
    {
        for(int j=0; j<7; j++)
        {
            int mut = mt_rand()%100;
            if(mut <= taux*100)
            {
                cout << "CHANGE" << endl;
                population[i]->adn[j] = mt_rand();
            }
        }
    }

    return population;
}

int main(int argc, char *argv[])
{
    int input=1;
    while(input%2 >0)
    {
        cout << "number of catapults per generation ?" <<endl;
        cin >>input;
    }
    //nombre de catapult généré par génération
    const int nbGen = input;

    float tauxMut=0.f;
    cout << "Mutation ratio ? (%)" << endl;
    cin >> tauxMut;
    tauxMut/=100;

    vector<Catapult*> population;


    //generation de la première génération de catapultes
    for(int i=0; i<nbGen; i++)
    {
        float aButee = mt_rand();
        float aTraction = mt_rand();
        float mBras = mt_rand();
        float mPoid = mt_rand();
        float mProjectile = mt_rand();
        float lBase = mt_rand();
        float lBras = mt_rand();

        Catapult* c = new Catapult(aButee, aTraction, mBras, mPoid, mProjectile, lBase, lBras);
        population.push_back(c);
    }

    cout << "number of generation ?" <<endl;
    cin >>input;

    for(int gen=0; gen<input; gen++)
    {
        cout << "Generation " << gen+1 << "-----------------------------------------------------" <<endl;

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
        couples = crossOver(couples);
        //on efface les paretns du tableau population
        population.clear();
        //on met les enfants dans le tableau population
        for(int i=0; i<couples.size(); i++)
        {
            vector<Catapult*> couple = couples[i];

            for(int j=0; j<couple.size(); j++)
            {
                population.push_back(couple[j]);
            }
        }

        //on melange
        srand(rand());
        std::shuffle(population.begin(), population.end(), default_random_engine(rand()));

        population = mutation(population, tauxMut);
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
