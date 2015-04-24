#ifndef CATAPULT_H
#define CATAPULT_H


class Catapult
{
    public:
        Catapult(float aButee, float aTraction, float mBras, float mPoid, float mProjectile, float lBase, float lBras);

        /*float getFTraction();
        float getMomentBras();
        float getInertie();
        float getAcceleration();
        float getVelocite();
        float getEImpact();*/
        float getETNT();
        float getPortee();
        float getScore();
        bool isViable();
        void setCouple();

    private:

        float calcScore();

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
