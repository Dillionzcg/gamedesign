#pragma once
#include"basis.h"
#include"StartBuff.h"
#include"FirstEnter.h"
#include"Map.h"
#include"ClassObject.h"
#include"ClassRuneManager.h"
#include"ClassMycharacter_Enemy.h"
#include"Shop.h"
#include"ClassSkill_RoundBuff.h"
#include"UnknownEvent.h"
#include"ClassEnemyNum.h"



extern shared_ptr<SkillManage> MySkill;
extern shared_ptr<SkillManage> EnemySkill;
extern bool EnemyIfDizzy;
extern bool IfBattleIsOver;
extern vector<int> Maptype;


// º¯ÊýÉùÃ÷
void AddRoundBuff(string type, double buffnum, int round);
void UpdateData(shared_ptr<Enemy> enemy);
int UseSkill(shared_ptr<SkillManage> skill);
void MyAttack(shared_ptr<Enemy> enemy, int round, bool ifskill);
void MyDefend(shared_ptr<Enemy> enemy, int round, bool ifskill);
int RoundStart(int round, shared_ptr<Enemy> enemy);
void PostWarSettleMent(bool IfBoss);
bool BattleStart(int floor, bool isBoss, bool IfHard);
void PrintMyCharacterStatus();
int MapChoose(int floor, int step, int type);
void MainProgress();

