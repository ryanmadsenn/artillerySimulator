
#pragma once

#include <iostream>
#include "position.h"

using namespace std;

class Howitzer {
private:
    Position position;
    double directionRadians;

public:
    void rotate(int keyPressed);

    void shoot();
};
