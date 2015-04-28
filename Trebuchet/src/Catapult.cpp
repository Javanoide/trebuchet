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

    adn[0] = aButee*PI/180; //converti en radian
    adn[1] = aTraction*PI/180;
    adn[2] = mBras;
    adn[3] = mPoid;
    adn[4] = mProjectile;
    adn[5] = lBase;
    adn[6] = lBras;

    aButee = adn[0]; //on rebalance la valeur en radian
    aTraction = adn[1];

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

    this->calcScore();
}

float Catapult::calcScore()
{
    int distance = 300;
    //si la catapulte est viable 50 points
    if(this->viable)
    {
        this->score+=10.f;
    }
    //50 point si elletouche la cible, entre 0 et la cible on donne en point le pourcentage de la distance parcourue appliqué à 50. 10% de la distance égale 10% de 50 points
    if(this->portee <= distance)
    {
        //this->score+= (this->portee/distance)*50;
        this->score+=this->portee;
    }else
    {
        /*if(this->portee>0)
            this->score-= ((this->portee-distance)/distance)*50;

        if(this->portee<0)
            this->score+= ((this->portee-distance)/distance)*50;*/
    }

    this->score+=(this->eTNT/10000000);
}
