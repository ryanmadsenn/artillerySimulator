
#include <cassert>
#include "physics.h"
#include "projectile.h"

class TestPhysics {
    Physics physics;

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
