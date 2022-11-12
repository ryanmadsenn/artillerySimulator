
#pragma once

#include <iostream>
#include "position.h"

using namespace std;

class Howitzer {
private:
    Position position;
    double angle;
    double timeSinceLastShot;

public:
    Howitzer(Position ptUpperRight);

    void rotate(int keyPressed);

    void shoot();

    Position * getPosition();

    double getAngle();

    double getTimeSinceLastShot();

    void incrementTimeSinceLastShot();
};
