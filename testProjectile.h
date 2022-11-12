#pragma once

#include <iostream>
#include "position.h"
#include "projectile.h"
#include <cassert>
using namespace std; 

class testProjectile {
public:
	Projectile projectile; 
	
	testProjectile(); 
	void run(); 
	void setup();
	void testGetDX(); 
	void testGetDY(); 
	void testGetV(); 
	void testGetMass(); 
	void testGetArea();
	void testGetPosition(); 
	
	//Test setters
	void testSetPosition(Position position);
	void testSetDX(double newDX);
	void testSetDY(double newDY);
	void testSetV(double newV);

private:
	double testDXValue; 
	double testDYValue; 
	double testVValue; 
	double testMassValue; 
	double testAreaValue; 
	Position testPositionValue; 

};