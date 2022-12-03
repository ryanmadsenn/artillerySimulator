
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

    cout << "Physics tests passed" << endl;
}

void TestPhysics::setup() {
    physics.reset();
}

void TestPhysics::testLinearlyInterpolate() {
    // Test with zeros for input.
    assert(isnan(physics.linearlyInterpolate(0, 0, 0, 0, 0)));

    // Test with positive numbers for input.
    assert(physics.linearlyInterpolate(0.5, 0, 1, 0, 10) == 5);

    // Test with negative numbers for input.
    assert(physics.linearlyInterpolate(-0.5, 0, -1, 0, -10) == -5);
}

void TestPhysics::testCalculateVM() {
    // Setup.

    physics.projectile->setV(827);
    physics.setVS(340);

    // Exercise.
    physics.calculateVM();

    // Verify.
    assert(2.43234 <= physics.getVM() <= 2.43236);
}

void TestPhysics::testCalculateDX() {
    // Setup.

    physics.projectile->setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDX(0);

    // Verify.
    assert(physics.projectile->getDX() == 0);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDX(0.785398);

    // Verify.
    assert(49.99999 <= physics.projectile->getDX() <= 50.00001);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDX(1.5708);

    // Verify.
    assert(99.99999 <= physics.projectile->getDX() <= 100.00001);

}

void TestPhysics::testCalculateDY() {
    // Setup.

    physics.projectile->setV(100);

    // Test for angle 0.
    // Exercise.
    physics.calculateDY(0);

    // Verify.
    assert(physics.projectile->getDY() == 100);

    // Test for angle 0.785398 (45 degrees)
    // Exercise.
    physics.calculateDY(0.785398);

    // Verify.
    assert(49.99999 <= physics.projectile->getDY() <= 50.00001);

    // Test for angle 1.5708 (90 degrees)
    // Exercise.
    physics.calculateDY(1.5708);

    // Verify.
    assert(-0.00001 <= physics.projectile->getDY() <= 0.00001);

}

void TestPhysics::testAngleFromComponents() {
    // Setup.

    physics.projectile->setDX(100);
    physics.projectile->setDY(0);

    // Exercise and verify.
    assert(0.256050 <= physics.angleFromComponents());
    assert(physics.angleFromComponents() <= 0.256052);


    // Setup.
    physics.projectile->setDX(50);
    physics.projectile->setDY(50);

    // Exercise and verify.
    assert(0.107271 <= physics.angleFromComponents());
    assert(physics.angleFromComponents() <= 0.107273);

    // Setup.
    physics.projectile->setDX(0);
    physics.projectile->setDY(100);

    // Exercise and verify.
    assert(0.595113 <= physics.angleFromComponents());
    assert(physics.angleFromComponents() <= 0.595115);
}

void TestPhysics::testTableLookUp() {
    // Test drag table.
    // Exercise.
    physics.setCD(physics.tableLookUp(0.300, physics.DRAG_TABLE));

    // Verify.
    assert(0.1628 <= physics.getCD());
    assert(physics.getCD() <= 0.1630);

    // Test air density table.
    // Exercise.
    physics.setAD(physics.tableLookUp(0, physics.AIR_DENSITY_TABLE));

    // Verify.
    assert(1.2249 <= physics.getAD());
    assert(physics.getAD() <= 1.2251);

    // Test speed of sound table.
    // Exercise.
    physics.setVS(physics.tableLookUp(0, physics.SPEED_SOUND_TABLE));

    // Verify.
    assert(339.99999 <= physics.getVS());
    assert(physics.getVS() <= 340.00001);

    // Test gravity table.
    // Exercise.
    // Verify.
    assert(9.8069 <= physics.tableLookUp(0, physics.GRAVITY_TABLE));
    assert(physics.tableLookUp(0, physics.GRAVITY_TABLE) <= 9.8071);
}

void TestPhysics::testCalculateF() {
    // Setup.

    physics.projectile->setV(827);
    physics.setCD(0.289081);
    physics.setAD(1.2250);

    // Exercise.
    physics.calculateF();

    // Verify.
    assert(2281.72 <= physics.getF());
    assert(physics.getF() <= 2281.731);
}

void TestPhysics::testCalculateAcc() {
    // Setup.

    physics.setF(2281.73);

    // Exercise.
    physics.calculateAcc();

    // Verify.
    assert(48.8591 <= physics.getAcc());
    assert(physics.getAcc() <= 48.8594);
}

void TestPhysics::testCalculateDDX() {

    // Set components so angle from components
    // can work in calculateDDX.
    physics.projectile->setDX(827);
    physics.projectile->setDY(0);

    physics.setAcc(48.8592);

    // Exercise.
    physics.calculateDDX();

    // Verify.
    assert(-12.3741 >= physics.getDDX());
    assert(physics.getDDX() >= -12.3743);
}

void TestPhysics::testCalculateDDY() {
    // Setup.
    physics.projectile->getPosition()->setMetersY(0);
    // Set components so angle from components
    // can work in calculateDDX.
    physics.projectile->setDX(0);
    physics.projectile->setDY(827);

    physics.setAcc(48.8592);

    // Exercise.
    physics.calculateDDY();

    // Verify.
    assert(-50.2665 >= physics.getDDY());
    assert(physics.getDDY() >= -50.2667);
}

void TestPhysics::testCalculateNewPos() {
    // Setup.
    physics.projectile->getPosition()->setMetersX(0);
    physics.projectile->getPosition()->setMetersY(0);

    physics.projectile->setDX(413.5);
    physics.projectile->setDY(413.5);
    physics.setDDX(-5.23119);
    physics.setDDY(-58.3854);
    physics.setTimeInterval(1);

    // Exercise.
    physics.calculateNewPos();

    assert(410.883 <= physics.projectile->getPosition()->getMetersX());
    assert(physics.projectile->getPosition()->getMetersX() <= 410.885);
    assert(384.306 <= physics.projectile->getPosition()->getMetersY());
    assert(physics.projectile->getPosition()->getMetersY() <= 384.308);
}

void TestPhysics::testUpdateComponents() {
    // Setup.
    physics.projectile->setDX(413.5);
    physics.projectile->setDY(413.5);
    physics.setDDX(-5.23119);
    physics.setDDY(-58.3854);
    physics.setTimeInterval(1);

    // Exercise.
    physics.updateComponents();

    // Verify.
    assert(408.268 <= physics.projectile->getDX());
    assert(physics.projectile->getDX() <= 408.270);
    assert(355.114 <= physics.projectile->getDY());
    assert(physics.projectile->getDY() <= 355.116);
}

void TestPhysics::testCalculateV() {
    // Setup.
    physics.projectile->setDX(10);
    physics.projectile->setDY(10);

    // Exercise.
    physics.calculateV();

    // Verify.
    assert(14.1420 <= physics.projectile->getV());
    assert(physics.projectile->getV() <= 14.1422);
}