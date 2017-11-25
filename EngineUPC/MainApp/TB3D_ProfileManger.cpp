#include "TB3D_ProfileManger.h"

TB3D_ProfileManger::TB3D_ProfileManger()
{
}


TB3D_ProfileManger::~TB3D_ProfileManger()
{
}


void TB3D_ProfileManger::save(string file, string data) {
	ofstream outFile;
	outFile.open(file + ".json");
	cout << endl << data << endl;
	outFile << data;
	outFile.close();
}
const char *TB3D_ProfileManger::load(string file) {
	ifstream inFile;
	inFile.open(file + ".json");

	//Check For Error
	if (inFile.fail()) {
		cerr << "Error Opening " << file << endl;
		exit(1);
	}

	string item;
	int count = 0;
	//Read a file until you've reached the end
	string data = "";
	while (!inFile.eof()) {
		inFile >> item;
		count++;
		data = data + item;
	}
	cout << data << endl;
	inFile.close();

	int size = data.length() + 1;
	char* result = new char[size];
	strcpy_s(result, size, data.c_str());

	return result;
}
//Setup profile from referenced DOM "d"(previously loaded)
Profile TB3D_ProfileManger::SetupProfile(Document* d) {
	Profile profile(
		((Value&)(*d)["elapsedTime"]).GetDouble(),
		((Value&)(*d)["currentHp"]).GetInt(),
		((Value&)(*d)["totalHp"]).GetInt(),
		((Value&)(*d)["currentMp"]).GetInt(),
		((Value&)(*d)["totalMp"]).GetInt(),
		((Value&)(*d)["historyAdvance"]).GetInt(),
		((Value&)(*d)["mapIndex"]).GetInt(),
		((Value&)(*d)["location"]["i"]).GetInt(),
		((Value&)(*d)["location"]["j"]).GetInt(),
		((Value&)(*d)["combatStatus"]).GetBool()
	);
	return profile;
}

//Obtain data from profile and save to referenced DOM "d"
void TB3D_ProfileManger::SaveProfileToDOM(Profile profile, Document* d) {
	((Value&)(*d)["elapsedTime"]).SetDouble(profile.GetElapsedTime());
	((Value&)(*d)["currentHp"]).SetInt(profile.GetCurrenHp());
	((Value&)(*d)["totalHp"]).SetInt(profile.GetTotalHp());
	((Value&)(*d)["currentMp"]).SetInt(profile.GetCurrentMp());
	((Value&)(*d)["totalMp"]).SetInt(profile.GetTotalMp());
	((Value&)(*d)["historyAdvance"]).SetInt(profile.GetHistoryAdvance());
	((Value&)(*d)["mapIndex"]).SetInt(profile.GetMapIndex());
	((Value&)(*d)["location"]["i"]).SetInt(profile.GetLocationI());
	((Value&)(*d)["location"]["j"]).SetInt(profile.GetLocationJ());
	((Value&)(*d)["combatStatus"]).SetBool(profile.GetCombatStatus());
}