#pragma once

#include <vector>
#include <queue>

enum enityType {
	PLAYER = 0,
	SCOUT = 1,
	WARRIOR = 2,
	ARCHER = 3,
	TANK = 4
};

typedef struct entity {
	int id;
	int type;
	int duration;
	bool alive;
}entity;


struct descend {
	bool operator()(const entity& a, const entity& b) {
		return a.duration > b.duration;
	}
};

//struct ascend {
//	bool operator()(const entity& a, const entity& b) {
//		return a.duration < b.duration;
//	}
//}asc;


class TB3D_TurnManager
{
public:
	TB3D_TurnManager();
	~TB3D_TurnManager() {}
	
	void Initialize(int nEntities, std::queue<int> entitiesTypes);
	void GenerateTurns();
	int GetNextTurn();

	std::vector<entity> entities;
	std::vector<entity> turns;
	std::queue<int> turnsQ;
	


};

