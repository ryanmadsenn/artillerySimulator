//
// Created by Ryan Madsen on 11/12/22.
//
#include "physics.h"

const map<double, double> DRAG_TABLE = {
        {0.300, 0.1629},
        {0.500, 0.1659},
        {0.700, 0.2031},
        {0.890, 0.2597},
        {0.920, 0.3010},
        {0.960, 0.3287},
        {0.980, 0.4002},
        {1.000, 0.4258},
        {1.020, 0.4335},
        {1.060, 0.4483},
        {1.240, 0.4064},
        {1.530, 0.3663},
        {1.990, 0.2897},
        {2.870, 0.2297},
        {2.890, 0.2306},
        {5.000, 0.2656}
};

const map<double, double> AIR_DENSITY_TABLE = {
        {0, 1.2250000},
        {1000, 1.1120000},
        {2000, 1.0070000},
        {3000, 0.9093000},
        {4000, 0.8194000},
        {5000, 0.7364000},
        {6000, 0.6601000},
        {7000, 0.5900000},
        {8000, 0.5258000},
        {9000, 0.4671000},
        {10000, 0.4135000},
        {15000, 0.1948000},
        {20000, 0.0889100},
        {25000, 0.0400800},
        {30000, 0.0184100},
        {40000, 0.0039960},
        {50000, 0.0010270},
        {60000, 0.0003097},
        {70000, 0.0000828},
        {80000, 0.0000185}
};

const map<double, double> SPEED_SOUND_TABLE =  {
        {0, 340},
        {1000, 336},
        {2000, 332},
        {3000, 328},
        {4000, 324},
        {5000, 320},
        {6000, 316},
        {7000, 312},
        {8000, 308},
        {9000, 303},
        {10000, 299},
        {15000, 295},
        {20000, 295},
        {25000, 295},
        {30000, 305},
        {40000, 324}
};

const map<double, double> GRAVITY_TABLE = {
        {0, 9.807},
        {1000, 9.804},
        {2000, 9.801},
        {3000, 9.797},
        {4000, 9.794},
        {5000, 9.791},
        {6000, 9.788},
        {7000, 9.785},
        {8000, 9.782},
        {9000, 9.779},
        {10000, 9.776},
        {15000, 9.761},
        {20000, 9.745},
        {25000, 9.730}
};

void Physics::initialCalculations(double aRadians) {
    projectile.setV(827); // Set projectile velocity to 827 m/s
    vs = tableLookUp(projectile.getPosition().getMetersY(),
    SPEED_SOUND_TABLE); // Look up speed of sound.
    calculateVM(); // Calculate velocity mach.
    calculateDX(aRadians); // Calculate horizontal component.
    calculateDY(aRadians); // Calculate vertical component.
}

void Physics::updateProjectile() {
    cd = tableLookUp(vm, DRAG_TABLE); // Calculate coefficient of drag.
    ad = tableLookUp(projectile.getPosition().getMetersY(),
                     AIR_DENSITY_TABLE); // Calculate air density.
    calculateF(); // Calculate force on shell.
    calculateAcc(); // Calculate acceleration.
    calculateDDX(); // Calculate horizontal component of acceleration.
    calculateDDY(); // Calculate vertical component of acceleration.
    calculateNewPos(); // Calculate new position.
    updateComponents(); // Calculate new horizontal and vertical components.
    calculateV(); // Calculate new total velocity.
    vs = tableLookUp(projectile.getPosition().getMetersY(),
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
    return fmod((atan2(projectile.getDY(), projectile.getDY()) + M_PI), M_2_PI);
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
    ddy = -tableLookUp(projectile.getPosition().getMetersY(), GRAVITY_TABLE) \
            - cos(angleFromComponents()) * acc;
}

void Physics::calculateNewPos() {
    projectile.getPosition().setMetersX((
            projectile.getPosition().getMetersX() +
            projectile.getDX() * timeInterval +
            0.5 * ddx * pow(timeInterval, 2)));

    projectile.getPosition().setMetersY((
            projectile.getPosition().getMetersY() +
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








