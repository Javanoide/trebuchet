#include "Catapult.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define PI  3.14159265
#define G   9.81

using namespace std;

int Catapult::genId = 0;

Catapult::Catapult(){
}

Catapult::Catapult(float aButee, float aTraction, float mBras, float mPoid, float mProjectile, float lBase, float lBras)
{
    this->adn[0] = aButee*PI/180; //converti en radian
    this->adn[1] = aTraction*PI/180;
    this->adn[2] = mBras;
    this->adn[3] = mPoid;
    this->adn[4] = mProjectile;
    this->adn[5] = lBase;
    this->adn[6] = lBras;

    this->calcPhysics();
    this->calcScore();

    this->id = genId;
    genId++;
}

void Catapult::calcPhysics()
{
    int aButee = adn[0]; //on rebalance la valeur en radian
    int aTraction = adn[1];
    int mBras = adn[2];
    int mPoid = adn[3];
    int mProjectile = adn[4];
    int lBase = adn[5];
    int lBras = adn[6];


    this->fTraction = (mPoid * G) * sin(aTraction) - (mProjectile * G) * cos(aButee);

    this->momentBras = this->fTraction * lBras;

    this->inertie = (mBras * (lBras * lBras))/3;

    this->acceleration = this->momentBras/this->inertie;

    this->velocite = this->acceleration * lBras;

    this->portee = (this->velocite * this->velocite)/G * sin((2 * (90 - ((aButee*180)/PI)))*PI/180);
    if(this->portee>10000 || this->portee==NAN){
        this->portee = 10000;
    }

    this->eImpact = 0.5 * mProjectile * (this->velocite * this->velocite);

    this->eTNT = this->eImpact/4184;

    //verification resistance
    if((pow(sin(aButee)*lBras, 2) + pow(cos(aButee)*lBras-lBase, 2))*sin(aButee)*(mProjectile*G) <= lBase*(mPoid*G)){
        this->viable = true;
    }else{
        this->viable = false;
    }
}


void Catapult::calcScore()
{
    this->score = 0;
    int distance = 300;

    this->score+= (this->eTNT);

    if(this->viable){
        this->score*=2;
    }else{
        this->score/=2;
    }

    if(this->portee>=299 && this->portee<=301 && this->viable){
        this->score*=8;
    }else{
        this->score/=8;
    }
}
