
#include <iostream>
#include "position.h"

#pragma once

using namespace std;

class Projectile {
private:
    Position position;
    double dx;
    double dy;
    double v;

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

    // Setters.
    void setPosition(Position position);
    void setDX(double dx);
    void setDY(double dy);
    void setV(double v);



};
