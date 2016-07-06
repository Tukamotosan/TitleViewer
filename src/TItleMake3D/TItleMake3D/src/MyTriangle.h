#pragma once

#include "ofMain.h"

class MyTriangle
{
public:
	ofVec3f p1,p2,p3;
	ofColor c1,c2,c3;
	float area;
	ofColor cMean;

	MyTriangle(void);
	~MyTriangle(void);
};

