#include <iostream>
#include "howitzer.h"

using namespace std;

Howitzer::Howitzer(Position ptUpperRight) : angle(0.0) {
    // Give howitzer random X position.
    position.setPixelsX(rand() % (int)ptUpperRight.getPixelsX() + 1);

}

void Howitzer::rotate(int keyPressed) {
    if (keyPressed == 0) {
        angle += 0.5;
    }

    if (keyPressed == 1) {
        angle -= 0.5;
    }

    if (keyPressed == 3) {
        angle += (angle >= 0 ? -0.003 : 0.003);
    }

    if (keyPressed == 1) {
        angle += (angle >= 0 ? 0.003 : -0.003);
    }
}

void Howitzer::shoot() {
    timeSinceLastShot = 0;
}

Position * Howitzer::getPosition() {
    return &position;
}

double Howitzer::getAngle() {
    return angle;
}

double Howitzer::getTimeSinceLastShot() {
    return timeSinceLastShot;
}

void Howitzer::incrementTimeSinceLastShot() {
    timeSinceLastShot += 0.5;
}