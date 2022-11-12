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
	double testGetDX(); 
	double testGetDY(); 
	double testGetV(); 
	double testGetMass(); 
	double testGetArea();
	Position testGetPosition(); 
	
	//Test setters
	Position testSetPosition(Position position);
	double testSetDX(double newDX);
	double testSetDY(double newDY);
	double testSetV(double newV);

private:
	double testDXValue; 
	double testDYValue; 
	double testVValue; 
	double testMassValue; 
	double testAreaValue; 
	Position testPositionValue; 

};