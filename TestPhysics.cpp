
#include "testPhysics.h"


void TestPhysics::setup() {
    physics = Physics();
}

void TestPhysics::testLinearlyInterpolate() {
    // Test with zeros for input.
    assert(physics.linearlyInterpolate(0, 0, 0, 0, 0) == 0);

    // Test with positive numbers for input.
    assert(physics.linearlyInterpolate(0.5, 0, 1, 0, 10) == 5);

    // Test with negative numbers for input.
    assert(physics.linearlyInterpolate(-0.5, 0, -1, 0, -10) == -5);
}

void TestPhysics::testCalculateVM() {
    // Instantiate projectile.
    Projectile projectile;
    // Set velocity to 827 m/s.
    projectile.setV(827);



}