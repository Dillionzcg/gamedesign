#pragma once

#include "basis.h"
#include"MainProcess.h"


void DrawBlock(int blocktype, int line);
void PrintMaphelp();
void UpdateMap(int floor, int step);
void DrawMap(int floor, int step);
void ResetLastBarLength();
void PrintBalttleGround(int* myData, int* enemyData, int round, int turn);
void PrintEventGround(int Type);
void PrintMyCharacterStatus();
void ChangeShopToBattle(int floor);

extern vector<vector<string>> Themap;
extern vector<int> Maptype;
extern vector<int> Map1;
extern vector<int> Map2;
extern vector<int> Map3;
extern int Battlerow;
extern int Battlecol;
extern bool IfBattleIsOver;
extern vector<vector<string>> Battlemap;
extern int MyLastHpBarLength;
extern int EnemyLastHpBarLength;
extern int MyLastEnergyBarLength;
extern int EnemyLastEnergyBarLength;
extern int MyLasthealBarLength;
extern int MydataWhenBattle[9];
extern int EnemydataWhenBattle[7];
