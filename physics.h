
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

    // Getters.
    double getVS();
    double getVM();
    double getTimeInterval();
    double getCD();
    double getAD();
    double getF();
    double getAcc();
    double getDDX();
    double getDDY();

    // Setters.
    void setVS(double vs);
    void setVM(double vm);
    void setTimeInterval(double timeInterval);
    void setCD(double cd);
    void setAD(double ad);
    void setF(double f);
    void setAcc(double acc);
    void setDDX(double ddx);
    void setDDY(double ddy);

    // Tables.
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

    const map<double, double> SPEED_SOUND_TABLE = {
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




};