
#include <iostream>
#include <vector>
#include "position.h"

#pragma once

using namespace std;

class Projectile {
private:
    Position position;
    double dx;
    double dy;
    double v = 0;
    double age = 0;
    bool isFlying = false;
    bool hitGround = false;
    double prevV;
    double prevAge;
    double prevAltitude;
    Position trail[20]; 

public:
    // Constructor
    Projectile();

    // Getters.
    Position * getPosition();
    double getDX();
    double getDY();
    double getV();
    double getMass();
    double getArea();
    double getAge();
    bool getIsFlying();
    double getPrevV();
    double getPrevAge();
    double getPrevAltitude();
    bool getHitGround();
    Position * getTrail();

    // Setters.
    void setPosition(Position position);
    void setDX(double dx);
    void setDY(double dy);
    void setV(double v);
    void setAge(double age);
    void setPrevV(double prevV);
    void setPrevAge(double prevAge);
    void setPrevAltitude(double prevAltitude);
    void setHitGround(bool hitGround);
    void setIsFlying(bool isFlying);
    void resetTrail();

    // Other methods.
    void updateAge(double timeInterval);
    void updateTrail(Position segment);
    bool getHitTarget(Position target);
    void resetTrail();

};
