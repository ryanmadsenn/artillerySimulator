#include "testProjectile.h"
#include "position.h"
#include "projectile.h"
#include <iostream>
#include <cassert>

TestProjectile::TestProjectile(): projectile(), testAreaValue(0.5), testMassValue(50.0), testDXValue(150.0), testDYValue(150.0), testPositionValue(10.0, 10.0), testVValue(35.0) {}

void TestProjectile::run() {
	
	// Setup
	setup();
	
	//Excercise
	testGetDX();
	
	//Teardown -> Setup
	setup();

	//Excercise
	testGetDY();

	//Teardown -> Setup
	setup(); 

	//Exercise
	testGetV();

	//Teardown -> Setup
	setup(); 

	//Exercise
	testGetArea();

	//Teardown -> Setup
	setup(); 

	//Exercise
	testGetMass();

	//Teardown -> Setup 
	setup(); 

	//Exercise
	testGetPosition(); 

	//Teardown -> Setup
	setup(); 

	//Exercise
	testSetDX(35.0);

	//Teardown -> Setup 
	setup(); 

	//Exercise
	testSetDY(35.0);

	//Teardown -> Setup 
	setup(); 

	//Exercise
	testSetPosition(testPositionValue);
	
	//Teardown -> Setup
	setup(); 

	//Exercise
	testSetV(150.0); 

	//Teardown -> Setup 
	setup();

    cout << "Projectile tests passed" << endl;

}
void TestProjectile::setup() {
//	projectile = Projectile();
}

void TestProjectile::testGetDX() {
	//Setup
	projectile.setDX(testDXValue);
	
	// Exercise
	// Verify
	assert(projectile.getDX() == 150.0);
}

void TestProjectile::testGetDY() {
	//Setup
	projectile.setDY(testDYValue);
	
	//Exercise
	double DY = projectile.getDY();
	
	//Verify
	assert(DY == testDYValue);
	
}

void TestProjectile::testGetArea() {
	//Exercise
	double area = projectile.getArea();
	//Verify
	assert(area == 0.018842);
}

void TestProjectile::testGetMass() {
	//Exercise
	double mass = projectile.getMass(); 
	//Verify
	assert(mass == 46.7);
}

void TestProjectile::testGetV() {
	//Setup
	projectile.setV(testVValue);
	
	//Exercise
	double V = projectile.getV(); 
	
	//Verify
	assert(V == testVValue);
}

void TestProjectile::testGetPosition() {
	
	//Setup
	projectile.setPosition(testPositionValue);
	
	//Exercise
	Position * pPosition = projectile.getPosition();
	
	//Verify
	assert(*pPosition == testPositionValue);
}

void TestProjectile::testSetDX(double newDX) {
	//Exercise
	projectile.setDX(newDX); 
	
	//Verify
	double DX = projectile.getDX(); 
	assert(DX == newDX);
}

void TestProjectile::testSetDY(double newDY) {
	//Setup
	projectile.setDY(newDY);
	
	//Verify
	double DY = projectile.getDY();
	assert(DY == newDY);
}

void TestProjectile::testSetPosition(Position newPosition) {
	//Excercise
	projectile.setPosition(newPosition);
	
	//Verify
	Position * pPosition = projectile.getPosition();
	assert(*pPosition == newPosition);
}

void TestProjectile::testSetV(double V) {
	//Exercise
	projectile.setV(V);
	
	//Verify
	double v = projectile.getV();
	assert(v == V);
}