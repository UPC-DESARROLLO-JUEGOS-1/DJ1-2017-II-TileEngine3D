#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Profile.h"

using namespace std;
using namespace rapidjson;

class TB3D_ProfileManger
{
public:
	TB3D_ProfileManger();
	~TB3D_ProfileManger();
	void save(string file, string data);
	const char *load(string file);
	Profile SetupProfile(Document* d);
	void SaveProfileToDOM(Profile profile, Document* d);
};

