
#include "testPhysics.h"


void TestPhysics::run() {
    setup();
    testLinearlyInterpolate();
    setup();
    testCalculateVM();
    setup();
    testCalculateDX();
    setup();
    testCalculateDY();
    setup();
    testAngleFromComponents();
    setup();
    testTableLookUp();
    setup();
    testCalculateF();
    setup();
    testCalculateAcc();
    setup();
    testCalculateDDX();
    setup();
    testCalculateDDY();
    setup();
    testCalculateNewPos();
    setup();
    testUpdateComponents();
    setup();
    testCalculateV();
}

void TestPhysics::setup() {
    physics.reset();
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

    physics.projectile.setV(827);
    physics.setVS(340);

    // Exercise.
    physics.calculateVM();

    // Verify.
    assert(physics.getVM() == 2.4325);
}

void TestPhysics::testCalculateDX() {
    // Setup.

    physics.projectile.setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDX(0);

    // Verify.
    assert(physics.projectile.getDX() == 0);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDX(0.785398);

    // Verify.
    assert(physics.projectile.getDX() == 50);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDX(1.5708);

    // Verify.
    assert(physics.projectile.getDX() == 100);

}

void TestPhysics::testCalculateDY() {
    // Setup.

    physics.projectile.setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDY(0);

    // Verify.
    assert(physics.projectile.getDY() == 100);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDY(0.785398);

    // Verify.
    assert(physics.projectile.getDY() == 50);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDY(1.5708);

    // Verify.
    assert(physics.projectile.getDY() == 0);

}

void TestPhysics::testAngleFromComponents() {
    // Setup.

    physics.projectile.setDX(100);
    physics.projectile.setDY(0);

    // Exercise and verify.
    assert(physics.angleFromComponents() == 0.256051);

    // Setup.
    physics.projectile.setDX(50);
    physics.projectile.setDY(50);

    // Exercise and verify.
    assert(physics.angleFromComponents() == 0.107272);

    // Setup.
    physics.projectile.setDX(0);
    physics.projectile.setDY(100);

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

    physics.projectile.setV(827);
    physics.setCD(0.289081);
    physics.setAD(1.2250);

    // Exercise.
    physics.calculateF();

    // Verify.
    assert(physics.getF() == 2281.73);
}

void TestPhysics::testCalculateAcc() {
    // Setup.

    physics.setF(2281.73);

    // Exercise.
    physics.calculateAcc();

    // Verify.
    assert(physics.getF() == 48.8592);
}

void TestPhysics::testCalculateDDX() {

    // Set components so angle from components
    // can work in calculateDDX.
    physics.projectile.setDX(827);
    physics.projectile.setDY(0);

    physics.setAcc(48.8592);

    // Exercise.
    physics.calculateDDX();

    // Verify.
    assert(physics.getDDX() == -12.3742);
}

void TestPhysics::testCalculateDDY() {
    // Setup.
    physics.projectile.getPosition().setMetersY(0);
    // Set components so angle from components
    // can work in calculateDDX.
    physics.projectile.setDX(0);
    physics.projectile.setDY(827);

    physics.setAcc(48.8592);

    // Exercise.
    physics.calculateDDX();

    // Verify.
    assert(physics.getDDX() == -50.2666);
}

void TestPhysics::testCalculateNewPos() {
    // Setup.
    physics.projectile.getPosition().setMetersX(0);
    physics.projectile.getPosition().setMetersY(0);
    physics.projectile.setDX(413.5);
    physics.projectile.setDY(413.5);
    physics.setDDX(-5.23119);
    physics.setDDY(-58.3854);
    physics.setTimeInterval(1);

    // Exercise.
    physics.calculateNewPos();

    // Verify.
    assert(physics.projectile.getPosition().getMetersX() == 410.884);
    assert(physics.projectile.getPosition().getMetersY() == 384.307);
}

void TestPhysics::testUpdateComponents() {
    // Setup.
    physics.projectile.setDX(413.5);
    physics.projectile.setDY(413.5);
    physics.setDDX(-5.23119);
    physics.setDDY(-58.3854);
    physics.setTimeInterval(1);

    // Exercise.
    physics.updateComponents();

    // Verify.
    assert(physics.getDDX() == 408.269);
    assert(physics.getDDY() == 355.115);
}

void TestPhysics::testCalculateV() {
    // Setup.
    physics.projectile.setDX(10);
    physics.projectile.setDY(10);

    // Exercise.
    physics.calculateV();

    // Verify.
    assert(physics.projectile.getV() == 14.1421);
}