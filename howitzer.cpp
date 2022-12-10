#define _USE_MATH_DEFINES
#include <iostream>
#include "howitzer.h"
#include <cmath>

using namespace std;

Howitzer::Howitzer(Position ptUpperRight) : angle(0.0) {
    // Give howitzer random X position.
    position.setPixelsX(rand() % (int)ptUpperRight.getPixelsX() + 1);

}

void Howitzer::rotate(double amount) {
    angle += amount;
}

void Howitzer::shoot() {
    timeSinceLastShot = 0;
}

Position * Howitzer::getPosition() {
    return &position;
}

double Howitzer::getAngleDegrees() {
    return angle * 180 / M_PI;
}

double Howitzer::getAngleRadians() {
    return angle;
}

double Howitzer::getTimeSinceLastShot() {
    return timeSinceLastShot;
}

void Howitzer::incrementTimeSinceLastShot() {
    timeSinceLastShot += 0.5;
}

void Howitzer::resetTimeSinceLastShot() {
    timeSinceLastShot = 0;
}
