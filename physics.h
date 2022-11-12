
#include <map>
#include "projectile.h"

using namespace std;

class Physics {
private:
    double vs; // Velocity of sound.
    double vm; // Velocity mach.
    double timeInterval;
    double cd; // Coefficient of drag.
    double ad; // Air density.
    double f; // Force on shell.
    double acc; // Acceleration.
    double ddx; // Horizontal component of acceleration.
    double ddy; // Vertical component of acceleration.
    Projectile projectile;

public:
    void initialCalculations(double aRadians); // Makes initial calculations when howitzer shoots.
    void updateProjectile(); // Calls all methods necessary to update projectile.
    double linearlyInterpolate(double value, double v0, double v1, double c0, double c1); // Perform linear interpolation.
    void calculateVM(); // Calculate velocity in mach.
    double calculateDX(double aRadians); // Calculate horizontal component.
    double calculateDY(double aRadians); // Calculate vertical component.
    double angleFromComponents();
    double tableLookUp(double value, map<double, double> table);
    void calculateF(); // Calculate force on shell.
    void calculateAcc();
    void calculateDDX(); // Calculate horizontal component of acceleration.
    void calculateDDY(); // Calculate vertical component of acceleration.
    void calculateNewPos(); // Calculate new position.
    void updateComponents(); // Calculate new horizontal and vertical component.
    void calculateV(); // Calculate total velocity.
};