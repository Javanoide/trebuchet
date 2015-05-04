#include "Catapult.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define PI  3.14159265
#define G   9.81

using namespace std;

Catapult::Catapult(float aButee, float aTraction, float mBras, float mPoid, float mProjectile, float lBase, float lBras)
{
    //Gravité
    const float g = 9.81;

    this->adn[0] = aButee*PI/180; //converti en radian
    this->adn[1] = aTraction*PI/180;
    this->adn[2] = mBras;
    this->adn[3] = mPoid;
    this->adn[4] = mProjectile;
    this->adn[5] = lBase;
    this->adn[6] = lBras;

    this->calcPhysics();
    this->calcScore();
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

    this->eImpact = 0.5 * mProjectile * (this->velocite * this->velocite);

    this->eTNT = this->eImpact/4184;

    //verification resistance
    if((pow(sin(aButee)*lBras, 2) + pow(cos(aButee)*lBras-lBase, 2))*sin(aButee)*(mProjectile*G) <= lBase*(mPoid*G)){
        this->viable = true;
    }else{
        this->viable = false;
    }
}

float Catapult::calcScore()
{
    this->score = 0;
    int distance = 300;
    //si la catapulte est viable 50 points
    if(this->viable)
    {
        this->score+=10.f;
    }
    //50 point si elletouche la cible, entre 0 et la cible on donne en point le pourcentage de la distance parcourue appliqué à 50. 10% de la distance égale 10% de 50 points
    if(this->portee <= distance && this->portee < 0)
    {
        //this->score+= (this->portee/distance)*50;
        this->score+=this->portee;
    }else
    {
        this->portee=0;
        /*if(this->portee>0)
            this->score-= ((this->portee-distance)/distance)*50;

        if(this->portee<0)
            this->score+= ((this->portee-distance)/distance)*50;*/
    }

    //this->score+=(this->eTNT/10000000);
    //pas de scores inférieur àà 0
    if(this->score < 0)
    {
        this->score = 0;
    }
}
