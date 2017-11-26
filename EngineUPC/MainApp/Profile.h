#pragma once

class Profile
{
public:
	Profile();
	~Profile();

	Profile(double elapsedTime,
		int currentHp, int totalHp,
		int currentMp, int totalMp,
		int historyAdvance,
		int mapIndex,
		int locationI, int locationJ,
		bool combatStatus);

	double GetElapsedTime();
	int GetCurrenHp();
	int GetTotalHp();
	int GetCurrentMp();
	int GetTotalMp();
	int GetHistoryAdvance();
	int GetMapIndex();
	int GetLocationI();
	int GetLocationJ();
	bool GetCombatStatus();

	void SetElapsedTime		(double time);
	void SetCurrenHp		(int hp);
	void SetTotalHp			(int hp);
	void SetCurrentMp		(int mp);
	void SetTotalMp			(int mp);
	void SetHistoryAdvance	(int iteration);
	void SetMapIndex		(int index);
	void SetLocationI		(int i);
	void SetLocationJ		(int j);
	void SetCombatStatus	(bool inCombat);
private:
	double elapsedTime;
	int currentHp, totalHp,
		currentMp, totalMp,
		historyAdvance,
		mapIndex,
		locationI, locationJ;
	bool combatStatus;

};

