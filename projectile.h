
#include <iostream>
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
    Position * getTrail();

    // Setters.
    void setPosition(Position position);
    void setDX(double dx);
    void setDY(double dy);
    void setV(double v);
    void setIsFlying(bool isFlying);

    // Other methods.
    void updateAge(double timeInterval);
    void updateTrail(Position segment);

};
