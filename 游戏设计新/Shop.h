#pragma once

#include "basis.h"
#include"MainProcess.h"


using namespace std;

// 边框颜色声明
extern const string BLUE_S;
extern const string PURPLE_S;
extern const string GOLD_S;
extern const string RESET_S;

// 商店系统相关全局变量声明
extern int Shoprow;
extern int Shopcol;
extern vector<vector<string>> Shopmap;

// 函数声明
void ShopStart();
