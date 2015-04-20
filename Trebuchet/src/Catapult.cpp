#include "Catapult.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define PI 3.14159265

using namespace std;

Catapult::Catapult(float aButee, float aTraction, float mBras, float mPoid, float mProjectile, float lBase, float lBras)
{
    //Gravité
    const float g = 9.81;

    aTraction = aTraction*PI/180;
    aButee = aButee*PI/180;

    this->fTraction = (mPoid * g) * sin(aTraction) - (mProjectile * g) * cos(aButee);

    this->momentBras = this->fTraction * lBras;

    this->inertie = (mBras * (lBras * lBras))/3;

    this->acceleration = this->momentBras/this->inertie;

    this->velocite = this->acceleration * lBras;

    this->portee = (this->velocite * this->velocite)/g * sin((2 * (90 - ((aButee*180)/PI)))*PI/180);

    this->eImpact = 0.5 * mProjectile * (this->velocite * this->velocite);

    this->eTNT = this->eImpact/4184;

    //verification resistance
    if((pow(sin(aButee)*lBras, 2) + pow(cos(aButee)*lBras-lBase, 2))*sin(aButee)*(mProjectile*g) <= lBase*(mPoid*g)){
        this->viable = true;
    }else{
        this->viable = false;
    }
}

float Catapult::getPortee()
{
    return this->portee;
}
bool Catapult::isViable()
{
    return this->viable;
}
