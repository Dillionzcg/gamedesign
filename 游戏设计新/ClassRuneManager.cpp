#include "ClassRuneManager.h"

// 定义并初始化全局变量
shared_ptr<RuneManager> RuneNow = make_shared<RuneManager>(0);

RuneManager::RuneManager(int num) : ID(num) {}

string RuneManager::GetDescribe() {
    return RuneList[ID];
}

string RuneManager::GetDescribethroughNum(int num) {
    return RuneList[num];
}

string RuneManager::GetName() {
    return RuneName[ID];
}
int RuneManager::GetNum() {
    return ID;
}
void RuneManager::RandomChangeRune() {
    int num = rm.getnum(0, 9);
    RuneNow = make_shared<RuneManager>(num);
}

void RuneManager::ChangetoHope() {
    RuneNow = make_shared<RuneManager>(10);
}

void RuneManager::ChangetoDesperation() {
    RuneNow = make_shared<RuneManager>(11);
}

void RuneManager::ChangeRuneByNum(int num){
    RuneNow = make_shared<RuneManager>(num);
}

vector<shared_ptr<Object>> RuneDevelopment;