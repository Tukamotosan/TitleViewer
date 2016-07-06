#include "Function.h"

vector<string> split(const string s, char delim){
	vector<string> elems;

	string item;
	for(char ch:s){
		if(ch == delim){
			if(!item.empty())
				elems.push_back(item);
			item.clear();
		}else{
			item += ch;
		}
	}
	if(!item.empty()){
		elems.push_back(item);
	}
	return elems;
}

vector<float> strToFloat(const vector<string> xs){
	vector<float> ys;
	for(int i=0; i<xs.size(); i++){
		float y;
		stringstream s;
		s << xs.at(i);
		s >> y;
		ys.push_back(y);
	}
	return ys;
}

MySurface loadCsvToSurface(const string path, const float xMin, const float xMax, const float yMin, const float yMax){
	MySurface surf;

	ifstream ifs(path.c_str());
	if(ifs.fail()){
		std::cerr << "error at load csv" << endl;
		return surf;
	}

	string str;
	getline(ifs, str);

	int cnt = 0;
	float min = 300, max = 0;
	ofColor cMin, cMax;

    ofVec3f pMin(5000, 5000, 5000), pMax(0,0,0);
    
	while(getline(ifs, str)){
		vector<string> xs = split(str, ',');
		if(xs.size() < 15){continue;}
		vector<float> ts = strToFloat(xs);
		MyTriangle t;
		ofVec3f p1, p2, p3;
		ofColor c1, c2, c3;

		p1.x = ts.at(0); p1.y = ts.at(1);
		c1.r = ts.at(2); c1.g = ts.at(3); c1.b = ts.at(4);
		p1.z = 0.0;

		p2.x = ts.at(5); p2.y = ts.at(6);
		c2.r = ts.at(7); c2.g = ts.at(8); c2.b = ts.at(9);
		p2.z = 0.0;

		p3.x = ts.at(10); p3.y = ts.at(11);
		c3.r = ts.at(12); c3.g = ts.at(13); c3.b = ts.at(14);
		p3.z = 0.0;
        
        if(p1.y < pMin.y){pMin.y = p1.y;}
        if(p2.y < pMin.y){pMin.y = p2.y;}
        if(p3.y < pMin.y){pMin.y = p3.y;}
        
        if(p1.y > pMax.y){pMax.y = p1.y;}
        if(p2.y > pMax.y){pMax.y = p2.y;}
        if(p3.y > pMax.y){pMax.y = p3.y;}

		int i1 = surf.addPointAndColor(p1, c1);
		int i2 = surf.addPointAndColor(p2, c2);
		int i3 = surf.addPointAndColor(p3, c3);
		surf.addTriangle(i1,i2,i3);

		if(c1.r < cMin.r){cMin.r = c1.r;}
		if(c1.g < cMin.g){cMin.g = c1.g;}
		if(c1.b < cMin.b){cMin.b = c1.b;}

		if(c1.r > cMax.r){cMax.r = c1.r;}
		if(c1.g > cMax.g){cMax.g = c1.g;}
		if(c1.b > cMax.b){cMax.b = c1.b;}
	}
    
    float yCenter = (pMax.y + pMin.y)/2.0;

	for(int i=0; i<surf.points.size(); i++){
		surf.colors.at(i).r = ofMap(surf.colors.at(i).r, cMin.r, cMax.r,  84, 211);
        surf.colors.at(i).g = ofMap(surf.colors.at(i).g, cMin.g, cMax.g,  21, 53);
		surf.colors.at(i).b = ofMap(surf.colors.at(i).b, cMin.b, cMax.b,  44, 111);
        
        //surf.colors.at(i).r = sigMap(surf.colors.at(i).r, cMin.r, cMax.r, 84, 211);
        //surf.colors.at(i).g = sigMap(surf.colors.at(i).g, cMin.g, cMax.g, 21, 53);
        //surf.colors.at(i).b = sigMap(surf.colors.at(i).b, cMin.b, cMax.b, 44, 111);
		surf.colors.at(i).a = 255;
        
        float ydash = surf.points.at(i).y - yCenter;
        surf.points.at(i).y = -ydash + yCenter;
        
	}

	return surf;
}

vector<MyTriangle> loadCsv(const string path, const float xMin, const float xMax, 
											  const float yMin, const float yMax){
	vector<MyTriangle> ys;

	ifstream ifs(path.c_str());
	if(ifs.fail()){
		std::cerr << "error at load csv" << endl;
		return ys;
	}

	string str;
	getline(ifs, str);

	int cnt = 0;
	float min = 300, max = 0;
	while(getline(ifs, str)){
		vector<string> xs = split(str, ',');
		if(xs.size() < 15){continue;}
		vector<float> ts = strToFloat(xs);
		MyTriangle t;
		ofVec3f p1, p2, p3;
		ofColor c1, c2, c3;

		p1.x = ts.at(0); p1.y = ts.at(1);
		c1.r = ts.at(2); c1.g = ts.at(3); c1.b = ts.at(4);
		p1.z = ofMap(c1.getSaturation(), 0, 255, -100, 100);

		p2.x = ts.at(5); p2.y = ts.at(6);
		c2.r = ts.at(7); c2.g = ts.at(8); c2.b = ts.at(9);
		p2.z = ofMap(c2.getSaturation(), 0, 255, -100, 100);

		p3.x = ts.at(10); p3.y = ts.at(11);
		c3.r = ts.at(12); c3.g = ts.at(13); c3.b = ts.at(14);
		p3.z = ofMap(c3.getSaturation(), 0, 255, -100, 100);

		t.p1 = p1; t.p2 = p2; t.p3 = p3;
		t.c1 = c1; t.c2 = c2; t.c3 = c3;
		ys.push_back(t);
	}

	return ys;
}

float sigMap(const float x, const float xMin, const float xMax, const float yMin, const float yMax){
    float xDash = ofMap(x, xMin, xMax, -6.0, 6.0);
    float y = 1.0/(1.0+exp(-xDash));
    return ofMap(y, 0.0, 1.0, yMin, yMax);
}







