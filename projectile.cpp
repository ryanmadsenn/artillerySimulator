
#include "projectile.h"


const double MASS = 46.7;
const double AREA = 0.018842;

Projectile::Projectile() {}

Position * Projectile::getPosition() {
    return &position;
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

double Projectile::getAge() {
    return age;
}

double Projectile::getPrevV() {
    return prevV;
}

double Projectile::getPrevAge() {
    return prevAge;
}

double Projectile::getPrevAltitude() {
    return prevAltitude;
}

bool Projectile::getHitGround() {
    return hitGround;
}

bool Projectile::getIsFlying() {
    return isFlying;
}

Position * Projectile::getTrail() {
    return trail;
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

void Projectile::setAge(double age) {
    this->age = age;
}

void Projectile::setPrevV(double prevV) {
    this->prevV = prevV;
}

void Projectile::setPrevAge(double prevAge) {
    this->prevAge = prevAge;
}

void Projectile::setPrevAltitude(double prevAltitude) {
    this->prevAltitude = prevAltitude;
}

void Projectile::setIsFlying(bool isFlying) {
    this->isFlying = isFlying;
}

void Projectile::setHitGround(bool hitGround) {
    this->hitGround = hitGround;
}

void Projectile::updateAge(double timeInterval) {
    age += timeInterval;
}

void Projectile::updateTrail(Position segment) {
    for (int i = 19; i > 0; i--) {
        trail[i] = trail[i - 1];
    }
    trail[0] = segment;
}

bool Projectile::getHitTarget(Position target) {
     cout << "First: " << (getPosition()->getPixelsX() >= target.getPixelsX() - 5.0) << endl;
     cout << "Second: " << (getPosition()->getPixelsX() <= target.getPixelsX() + 5.0) << endl;

    if (getPosition()->getPixelsX() >= target.getPixelsX() - 5.0 && getPosition()->getPixelsX() <= target.getPixelsX() + 5.0 &&
        getPosition()->getPixelsY() >= target.getPixelsY() - 5.0 && getPosition()->getPixelsY() <= target.getPixelsY() + 5.0) {
        return true;
    } else {
        return false; 
    }
}