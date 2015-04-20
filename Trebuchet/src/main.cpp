/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Catapult.h"
#define LOG 1

using namespace std;

int main(int argc, char *argv[])
{
    int i = 100;

    while(i>0){

        float aButee = rand()%360 + 1;
        float aTraction = rand()%360 + 1;
        float mBras = rand();
        float mPoid = rand();
        float mProjectile = rand();
        float lBase = rand();
        float lBras = rand();

        Catapult* c = new Catapult(aButee, aTraction, mBras, mPoid, mProjectile, lBase, lBras);
        if(LOG){
            cout << "Distance : " << c->getPortee() << " metres" << endl;
            cout << "Viabilité : " << c->isViable() << endl;
            cout << "--------------------------------------" << endl;
        }

        i--;
    }
}
