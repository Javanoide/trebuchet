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

    this->aButee = aButee;
    this->aTraction = aTraction;
    this->mBras = mBras;
    this->mPoid = mPoid;
    this->mProjectile = mProjectile;
    this->lBase = lBase;
    this->lBras = lBras;

    this->aTraction = this->aTraction*PI/180;
    this->aButee = this->aButee*PI/180;

    this->fTraction = (this->mPoid * g) * sin(this->aTraction) - (this->mProjectile * g) * cos(this->aButee);

    this->momentBras = this->fTraction * this->lBras;

    this->inertie = (this->mBras * (this->lBras * this->lBras))/3;

    this->acceleration = this->momentBras/this->inertie;

    this->velocite = this->acceleration * this->lBras;

    this->portee = (this->velocite * this->velocite)/g * sin((2 * (90 - ((this->aButee*180)/PI)))*PI/180);

    this->eImpact = 0.5 * this->mProjectile * (this->velocite * this->velocite);

    this->eTNT = this->eImpact/4184;

    //verification resistance
    if((pow(sin(this->aButee)*this->lBras, 2) + pow(cos(this->aButee)*this->lBras-this->lBase, 2))*sin(this->aButee)*(this->mProjectile*g) <= lBase*(this->mPoid*g)){
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
        this->score+=50.f;
    }
    //50 point si elletouche la cible, entre 0 et la cible on donne en point le pourcentage de la distance parcourue appliqué à 50. 10% de la distance égale 10% de 50 points
    if(this->portee <= distance)
    {
        this->score+= (this->portee/distance)*50;
    }else
    {
        //this->score+= ((this->portee-distance)/distance)*50;
    }

    //this->score+=this->eTNT;
}
