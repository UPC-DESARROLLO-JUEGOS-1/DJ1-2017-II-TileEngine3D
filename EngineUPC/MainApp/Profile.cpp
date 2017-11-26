#include "Profile.h"
#include <iostream>

Profile::Profile():
	elapsedTime(0.0f),
	currentHp(50), totalHp(50),
	currentMp(50), totalMp(50),
	historyAdvance(0),
	mapIndex(0),
	locationI(0), locationJ(0),
	combatStatus(false)
{
}

Profile::Profile(double elapsedTime,
	int currentHp, int totalHp,
	int currentMp, int totalMp,
	int historyAdvance,
	int mapIndex,
	int locationI, int locationJ,
	bool combatStatus)
{
	SetElapsedTime(elapsedTime);
	SetCurrenHp(currentHp);
	SetTotalHp(totalHp);
	SetCurrentMp(currentMp);
	SetTotalMp(totalMp);
	SetHistoryAdvance(historyAdvance);
	SetMapIndex(mapIndex);
	SetLocationI(locationI);
	SetLocationJ(locationJ);
	SetCombatStatus(combatStatus);
}

double Profile::GetElapsedTime()	{ return elapsedTime; }
int Profile::GetCurrenHp()			{ return currentHp; }
int Profile::GetTotalHp()			{ return totalHp; }
int Profile::GetCurrentMp()			{ return currentMp;}
int Profile::GetTotalMp()			{ return totalMp; }
int Profile::GetHistoryAdvance()	{ return historyAdvance; }
int Profile::GetMapIndex()			{ return mapIndex; }
int Profile::GetLocationI()			{ return locationI; }
int Profile::GetLocationJ()			{ return locationJ; }
bool Profile::GetCombatStatus()		{ return combatStatus; }

void Profile::SetElapsedTime	(double time)		{ elapsedTime = time; }
void Profile::SetCurrenHp		(int hp)			{ currentHp = hp; }
void Profile::SetTotalHp		(int hp)			{ totalHp = hp; }
void Profile::SetCurrentMp		(int mp)			{ currentMp = mp; }
void Profile::SetTotalMp		(int mp)			{ totalMp = mp; }
void Profile::SetHistoryAdvance	(int iteration)		{ historyAdvance = iteration; }
void Profile::SetMapIndex		(int index)			{ mapIndex = index; }
void Profile::SetLocationI		(int i)				{ locationI = i; }
void Profile::SetLocationJ		(int j)				{ locationJ = j; }
void Profile::SetCombatStatus	(bool combatStatus)	{ this->combatStatus = combatStatus; }

Profile::~Profile()
{
}
