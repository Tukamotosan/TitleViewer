#include "MySurface.h"


MySurface::MySurface(void)
{
}


MySurface::~MySurface(void)
{
}

int MySurface::addPointAndColor(const ofVec3f p, const ofColor c){
	vector<ofVec3f>::iterator itr = find(points.begin(), points.end(), p);
	if(itr == points.end()){
		points.push_back(p);
		colors.push_back(c);
		return points.size() - 1;
	}
	return distance(points.begin(), itr);
}

void MySurface::addTriangle(const int i1, const int i2, const int i3){
	vector<int> t;
	t.push_back(i1); t.push_back(i2); t.push_back(i3);
	triangles.push_back(t);
}