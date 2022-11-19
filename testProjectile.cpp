#include "testProjectile.h"
#include "position.h"
#include "projectile.h"
#include <iostream>
#include <cassert>

testProjectile::testProjectile(): projectile(), testAreaValue(0.5), testMassValue(50.0), testDXValue(150.0), testDYValue(150.0), testPositionValue(10.0, 10.0), testVValue(35.0) {}

void testProjectile::run() {
	
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

}
void testProjectile::setup() {
	projectile = Projectile(); 
}

void testProjectile::testGetDX() {
	//Setup
	projectile.setDX(testDXValue);
	
	//Exercise
	double DX = projectile.getDX();
	
	//Verify
	assert(projectile.getDX() == 35.0); 
}

void testProjectile::testGetDY() {
	//Setup
	projectile.setDY(testDYValue);
	
	//Exercise
	double DY = projectile.getDY();
	
	//Verify
	assert(DY == testDYValue);
	
}

void testProjectile::testGetArea() {
	//Exercise
	double area = projectile.getArea();
	//Verify
	assert(area == 0.018842);
}

void testProjectile::testGetMass() {
	//Exercise
	double mass = projectile.getMass(); 
	//Verify
	assert(mass == 46.7);
}

void testProjectile::testGetV() {
	//Setup
	projectile.setV(testVValue);
	
	//Exercise
	double V = projectile.getV(); 
	
	//Verify
	assert(V == testVValue);
}

void testProjectile::testGetPosition() {
	
	//Setup
	projectile.setPosition(testPositionValue);
	
	//Exercise
	Position position = projectile.getPosition(); 
	
	//Verify
	assert(position == testPositionValue);
}

void testProjectile::testSetDX(double newDX) {
	//Exercise
	projectile.setDX(newDX); 
	
	//Verify
	double DX = projectile.getDX(); 
	assert(DX == newDX);
}

void testProjectile::testSetDY(double newDY) {
	//Setup
	projectile.setDY(newDY);
	
	//Verify
	double DY = projectile.getDY();
	assert(DY == newDY);
}

void testProjectile::testSetPosition(Position newPosition) {
	//Excercise
	projectile.setPosition(newPosition);
	
	//Verify
	Position position = projectile.getPosition();
	assert(position == newPosition);
}

void testProjectile::testSetV(double V) {
	//Exercise
	projectile.setV(V);
	
	//Verify
	double v = projectile.getV();
	assert(v == V);
}