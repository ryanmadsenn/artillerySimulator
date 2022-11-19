//
// Created by Ryan Madsen on 11/12/22.
//
#include "physics.h"

void Physics::initialCalculations(double aRadians) {
    projectile.setV(827); // Set projectile velocity to 827 m/s
    vs = tableLookUp(projectile.getPosition()->getMetersY(),
    SPEED_SOUND_TABLE); // Look up speed of sound.
    calculateVM(); // Calculate velocity mach.
    calculateDX(aRadians); // Calculate horizontal component.
    calculateDY(aRadians); // Calculate vertical component.
}

void Physics::updateProjectile() {
    cd = tableLookUp(vm, DRAG_TABLE); // Calculate coefficient of drag.
    ad = tableLookUp(projectile.getPosition()->getMetersY(),
                     AIR_DENSITY_TABLE); // Calculate air density.
    calculateF(); // Calculate force on shell.
    calculateAcc(); // Calculate acceleration.
    calculateDDX(); // Calculate horizontal component of acceleration.
    calculateDDY(); // Calculate vertical component of acceleration.
    calculateNewPos(); // Calculate new position.
    updateComponents(); // Calculate new horizontal and vertical components.
    calculateV(); // Calculate new total velocity.
    vs = tableLookUp(projectile.getPosition()->getMetersY(),
                     SPEED_SOUND_TABLE); // Re-calculate speed of sound.
    calculateVM(); // Re-calculate velocity mach.
}


double Physics::linearlyInterpolate(double value, double v0, double v1, double c0, double c1) {
    return c0 + (value - v0) * (c1 - c0) / (v1 - v0);
}


double Physics::tableLookUp(double value, map<double, double> table) {
    pair<double, double> prev;

    for (auto const& [key, val] : table) {
        if(key > value) {
            return linearlyInterpolate(value, prev.first, key, prev.second, val);
        }

        prev.first = key;
        prev.second = val;
    }
}


void Physics::calculateVM() {
    vm = projectile.getV() / vs;
}

double Physics::calculateDX(double aRadians) {
    projectile.setDX(sin(aRadians) * projectile.getV());
}

double Physics::calculateDY(double aRadians) {
    projectile.setDY(cos(aRadians) * projectile.getV());
}

double Physics::angleFromComponents() {
    return fmod((atan2(projectile.getDX(), projectile.getDY()) + M_PI), M_2_PI);
}

void Physics::calculateF() {
    f = (.5 * cd) * ad * pow(projectile.getV(), 2) * projectile.getArea();
}

void Physics::calculateAcc() {
    acc = f / projectile.getMass();
}

void Physics::calculateDDX() {
    ddx = -sin(angleFromComponents()) * acc;
}

void Physics::calculateDDY() {
    ddy = -tableLookUp(projectile.getPosition()->getMetersY(), GRAVITY_TABLE)
            - cos(angleFromComponents()) * acc;
}

void Physics::calculateNewPos() {
    projectile.getPosition()->setMetersX((
            projectile.getPosition()->getMetersX() +
            projectile.getDX() * timeInterval +
            0.5 * ddx * pow(timeInterval, 2)));

    projectile.getPosition()->setMetersY((
            projectile.getPosition()->getMetersY() +
            projectile.getDY() * timeInterval +
            0.5 * ddy * pow(timeInterval, 2)));
}


void Physics::updateComponents() {
    projectile.setDX(projectile.getDX() + ddx * timeInterval);
    projectile.setDY(projectile.getDY() + ddy * timeInterval);
}

void Physics::calculateV() {
    projectile.setV(sqrt(pow(projectile.getDX(), 2) +
                        pow(projectile.getDY(), 2)));
}

void Physics::reset() {
    vs = 0; // Velocity of sound.
    vm = 0; // Velocity mach.
    timeInterval = 0;
    cd = 0; // Coefficient of drag.
    ad = 0; // Air density.
    f = 0; // Force on shell.
    acc = 0; // Acceleration.
    ddx = 0; // Horizontal component of acceleration.
    ddy = 0; // Vertical component of acceleration.
}


// Getters.
double Physics::getVS() {
    return vs;
}
double Physics::getVM() {
    return vm;
}
double Physics::getTimeInterval() {
    return timeInterval;
}
double Physics::getCD() {
    return cd;
}
double Physics::getAD() {
    return ad;
}
double Physics::getF() {
    return f;
}
double Physics::getAcc() {
    return acc;
}
double Physics::getDDX() {
    return ddx;
}
double Physics::getDDY() {
    return ddy;
}

// Setters.
void Physics::setVS(double vs) {
    this->vs = vs;
}
void Physics::setVM(double vm) {
    this->vm = vm;
}
void Physics::setTimeInterval(double timeInterval) {
    this->timeInterval = timeInterval;
}
void Physics::setCD(double cd) {
    this->cd = cd;
}
void Physics::setAD(double ad) {
    this->ad = ad;
}
void Physics::setF(double f) {
    this->f = f;
}
void Physics::setAcc(double acc) {
    this->acc = acc;
}
void Physics::setDDX(double ddx) {
    this->ddx = ddx;
}
void Physics::setDDY(double ddy) {
    this->ddy = ddy;
}










