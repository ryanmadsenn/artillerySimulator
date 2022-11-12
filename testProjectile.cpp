#include "testProjectile.h"
#include "position.h"
#include "projectile.h"
#include <iostream>
#include <cassert>

testProjectile::testProjectile(): projectile(), testAreaValue(0.5), testMassValue(50.0), testDXValue(150.0), testDYValue(150.0), testPositionValue(10.0, 10.0), testVValue(35.0) {}

void testProjectile::run() {
	
	// Set
	setup();
	projectile.setDX(testDXValue);
	projectile.setDY(testDYValue);
	projectile.setPosition(testPositionValue);
	projectile.setV(testVValue);
	
	//Excercise
	double testedDX = testGetDX();
	double testedDY = testGetDY(); 
	double testedV = testGetV(); 
	double testedArea = testGetArea(); 
	double testedMass = testGetMass(); 
	Position testedPosition = testGetPosition(); 

	//Verify 
	assert(testedDX == testDXValue);
	assert(testedDY == testDYValue);
	assert(testedV = testVValue);
	assert(testedArea == testAreaValue);
	assert(testedMass == testMassValue);
	//assert(testedPosition == testPositionValue);
	
	//Teardown: None
	setup(); 

	//Exercise
	testSetDX(35.0);
	testSetDY(35.0);
	testSetPosition(testPositionValue);
	testSetV(150.0);  

	//Verify 
	assert(projectile.getDX() == 35.0);
	assert(projectile.getDY() == 35.0);
	//assert(projectile.getPosition() == testPositionValue);
	assert(projectile.getV() == 150.0); 

}
void testProjectile::setup() {
	projectile = Projectile(); 
}

double testProjectile::testGetDX() {
	double DX = projectile.getDX(); 
	return DX; 
}

double testProjectile::testGetDY() {
	double DY = projectile.getDY(); 
	return DY; 
}

double testProjectile::testGetArea() {
	double area = projectile.getArea(); 
	return area;
}

double testProjectile::testGetMass() {
	double mass = projectile.getMass(); 
	return mass; 
}

Position testProjectile::testGetPosition() {
	Position position = projectile.getPosition(); 
	return position; 
}

double testProjectile::testSetDX(double newDX) {
	projectile.setDX(newDX); 
	double DX = projectile.getDX(); 
	return DX; 
}

double testProjectile::testSetDY(double newDY) {
	projectile.setDY(newDY);
	double DY = projectile.getDY(); 
	return DY; 
}

Position testProjectile::testSetPosition(Position newPosition) {
	projectile.setPosition(newPosition);
	Position position = projectile.getPosition(); 
	return position; 
}

double testProjectile::testSetV(double V) {
	projectile.setV(V);
	double v = projectile.getV(); 
	return v; 
}