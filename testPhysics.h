
#include <cassert>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "physics.h"
#include "projectile.h"

class TestPhysics {
private:
    Physics physics;

public:
    void run();
    void setup();
    void testInitialCalculations();
    void testUpdateProjectile();
    void testLinearlyInterpolate();
    void testCalculateVM();
    void testCalculateDX();
    void testCalculateDY();
    void testAngleFromComponents();
    void testTableLookUp();
    void testCalculateF();
    void testCalculateAcc();
    void testCalculateDDX();
    void testCalculateDDY();
    void testCalculateNewPos();
    void testUpdateComponents();
    void testCalculateV();

};
