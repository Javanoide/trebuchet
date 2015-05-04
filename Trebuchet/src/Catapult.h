#ifndef CATAPULT_H
#define CATAPULT_H


class Catapult
{
    public:
        Catapult(float aButee, float aTraction, float mBras, float mPoid, float mProjectile, float lBase, float lBras);

        bool isViable();
        float calcScore();
        void calcPhysics();

        //Genetique
        float adn[7];

        //fonction physique calculée
        float fTraction;
        float momentBras;
        float inertie;
        float acceleration;
        float velocite;
        float eImpact;
        float eTNT;
        float portee;
        float score;
        bool viable;

};

#endif // CATAPULT_H
