#include "TB3D_TurnManager.h"
#include <iostream>

#include <algorithm>
#include <string>
#include <stdlib.h>
#include <functional>

using namespace std;



TB3D_TurnManager::TB3D_TurnManager() :
	entities(std::vector<entity>()),
	turns(std::vector<entity>()),
	turnsQ(std::queue<int>())	
{
	
}

void TB3D_TurnManager::Initialize(int nEntities, std::queue<int> entitiesTypes)
{
	int accum = 0;
	while (!entitiesTypes.empty()) {
		entity e = entity();
		e.alive = true;
		e.id = accum;
		switch (entitiesTypes.front())
		{
		case PLAYER:
			e.duration = 4;
			e.type = PLAYER;			
			break;

		case SCOUT:
			e.duration = 6;
			e.type = SCOUT;
			break;
		case WARRIOR:
			e.duration = 8;
			e.type = WARRIOR;
			break;
		case ARCHER:
			e.duration = 10;
			e.type = ARCHER;
			break;
		case TANK:
			e.duration = 12;
			e.type = TANK;
			break;
		default:
			e.duration = 6;
			e.type = SCOUT;
		}
		accum++;
		entitiesTypes.pop();
		entities.push_back(e);
	}
}



void TB3D_TurnManager::GenerateTurns() {
	turns = entities;

	descend desc;

	std::sort(turns.begin(), turns.end(), desc);
	printf("i\tID\tEsperaActual\tEsperaBase\n");
	for (int i = 0; i < entities.size(); i++)
	{
		printf("[ %d ]\t( %d )\t%d\t\t%d\n", i, turns[i].id, turns[i].duration, entities[turns[i].type].duration);
	}

	int turn = 0;
	int maxCombatRounds = 3;
	printf("------------------------------------\n");
	printf("[ Cantidad de rondas = %d ]\n", maxCombatRounds);
	printf("------------------------------------\n");

	while (maxCombatRounds > 0) {
		maxCombatRounds--;
		bool turnUsed = false;
		int n = entities.size();
		while (!turnUsed) {
			for (int i = 0; i < n; i++)
			{
				turns[i].duration--;
				if (turns[i].duration == 0)
					turnUsed = true;
			}

		}
		
		do {			
			//printf("i\ID\tEsperaActual\tEsperaBase\n");
			for (int i = 0; i < n; i++)
			{
				printf("[ %d ]\t( %d )\t%d\t\t%d\n", i, turns[i].id, turns[i].duration, entities[turns[i].type].duration);
			}
			printf("Turnos adicionados para IDs = ");
			for (int i = 0; i < n; i++)
			{
					printf("(%d) ", turns[i].id);
					turnsQ.push(turns[i].id);
					turns[i].duration += entities[turns[i].type].duration;
			}
			
			printf("\n\n");

		} while (!turnUsed);


	}
	/*
	printf(">>\n");
	printf("Secuencia de turnos :");
	while (!turnsQ.empty()) {
		printf(" %d", turnsQ.front());
		turnsQ.pop();
	}
	printf("\n");
	*/
}

int TB3D_TurnManager::GetNextTurn() {
	if (!turnsQ.empty()) {
		int id = turnsQ.front();
		printf(" %d ", id);
		turnsQ.pop();
		return id;
	}
	return -1;
}

