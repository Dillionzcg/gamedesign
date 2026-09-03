#pragma once

#include "basis.h"

// º¯ÊıÉùÃ÷
void PrintRuneDivider(int length = 60);
void DrawBuffCard(int index, const string& icon, const string& name, const string& desc, int indent = 0);
void PrintCentered(const string& text, const string& color);
int ChooseInitialBuff();
int enterbuff();