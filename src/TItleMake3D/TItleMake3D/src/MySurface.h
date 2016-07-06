#pragma once

#include <vector>
#include <algorithm>
#include "ofMain.h"

class MySurface
{
public:
	MySurface(void);
	~MySurface(void);

	int addPointAndColor(const ofVec3f p, const ofColor c);
	void addTriangle(const int i1, const int i2, const int i3);

	vector<ofVec3f> points;
	vector<ofColor> colors;
	vector<vector<int> > triangles;
};

