
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
    // Setup.
    Projectile projectile;
    projectile.setV(827);
    physics.setVS(340);

    // Exercise.
    physics.calculateVM();

    // Verify.
    assert(physics.getVM() == 2.4325);
}

void TestPhysics::testCalculateDX() {
    // Setup.
    Projectile projectile;
    projectile.setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDX(0);

    // Verify.
    assert(projectile.getDX() == 0);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDX(0.785398);

    // Verify.
    assert(projectile.getDX() == 50);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDX(1.5708);

    // Verify.
    assert(projectile.getDX() == 100);

}

void TestPhysics::testCalculateDY() {
    // Setup.
    Projectile projectile;
    projectile.setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDY(0);

    // Verify.
    assert(projectile.getDY() == 100);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDY(0.785398);

    // Verify.
    assert(projectile.getDY() == 50);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDY(1.5708);

    // Verify.
    assert(projectile.getDY() == 0);

}

void TestPhysics::testAngleFromComponents() {
    // Setup.
    Projectile projectile;
    projectile.setDX(100);
    projectile.setDY(0);

    // Exercise and verify.
    assert(physics.angleFromComponents() == 0.256051);

    // Setup.
    projectile.setDX(50);
    projectile.setDY(50);

    // Exercise and verify.
    assert(physics.angleFromComponents() == 0.107272);

    // Setup.
    projectile.setDX(0);
    projectile.setDY(100);

    // Exercise and verify.
    assert(physics.angleFromComponents() == 0.595114);
}

void TestPhysics::testTableLookUp() {
    // Test drag table.
    // Exercise.
    physics.setCD(physics.tableLookUp(0.300, physics.DRAG_TABLE));

    // Verify.
    assert(physics.getCD() == 0.1629);

    // Test air density table.
    // Exercise.
    physics.setAD(physics.tableLookUp(0, physics.AIR_DENSITY_TABLE));

    // Verify.
    assert(physics.getCD() == 1.2250);

    // Test speed of sound table.
    // Exercise.
    physics.setAD(physics.tableLookUp(0, physics.SPEED_SOUND_TABLE));

    // Verify.
    assert(physics.getCD() == 340);

    // Test gravity table.
    // Exercise.
    physics.setAD(physics.tableLookUp(0, physics.GRAVITY_TABLE));

    // Verify.
    assert(physics.getCD() == 9.807);
}

void TestPhysics::testCalculateF() {
    // Setup.
    Projectile projectile;
    projectile.setV(827);
    physics.setCD(0.289081);
    physics.setAD(1.2250);

    // Exercise.
    physics.calculateF();

    // Verify.
    assert(physics.getF() == 2281.73);
}

void TestPhysics::testCalculateAcc() {
    // Setup.
    Projectile projectile;
    physics.setF(2281.73);

    // Exercise.
    physics.calculateAcc();

    // Verify.
    assert(physics.getF() == 48.8592);
}
