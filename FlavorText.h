#pragma once

#include <iostream>
#include <fstream>
#include  <vector>
#include <random>
#include <functional>
#include <stdlib.h> 
#include <istream>
#include <string>

using namespace std;

class FlavorText
{
public:
	FlavorText(string fileName);
	string randomLine();


private:
	ifstream* file;
	string displayedMessage;
	vector<string> messageLines;

};