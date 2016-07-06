#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "ofMain.h"
#include "MyTriangle.h"
#include "MySurface.h"

using namespace std;

vector<string> split(const string s, char delim);
vector<float> strToFloat(const vector<string> xs);
vector<MyTriangle> loadCsv(const string path, const float xMin, const float xMax, const float yMin, const float yMax);
MySurface loadCsvToSurface(const string path, const float xMin, const float xMax, const float yMin, const float yMax);
float sigMap(const float x, const float xMin, const float xMax, const float yMin, const float yMax);
