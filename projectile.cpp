
#include "projectile.h"


const double MASS = 46.7;
const double AREA = 0.018842;

Position Projectile::getPosition() {
    return position;
}

double Projectile::getDX() {
    return dx;
}

double Projectile::getDY() {
    return dy;
}

double Projectile::getV() {
    return v;
}

double Projectile::getMass() {
    return MASS;
}

double Projectile::getArea() {
    return AREA;
}

void Projectile::setPosition(Position position) {
    this->position = position;
}

void Projectile::setDX(double dx) {
    this->dx = dx;
}

void Projectile::setDY(double dy) {
    this->dy = dy;
}

void Projectile::setV(double v) {
    this->v = v;
}
