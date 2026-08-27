#include<iostream>
#include<random>
#include<vector>
#include<memory>
#include<string>
using namespace std;
//符文文本
string Rune[11] = {
	//通常(0~8)
	"死仇：我方和敌方的攻击力+30%。",
	"虚弱：我方和敌方的攻击力-30%。",
	"脆弱：我方和敌方的防御力-50%。",
	"亢奋：我方和敌方技能条所需能量-1",
	"迷雾：该层的商店不再展示商品详细信息，但该层商店的售价-50%。",
	"金融：该层的商店售价+50%，但战斗后掉落藏品+1。",
	"萧条：该层的商店售价-50%，但战斗后不再掉落藏品。",
	"狂暴：敌方攻击力+30%，但每次移动后额外获得一枚金币。",
	"教堂：在该层战斗死亡时可复活（仅限一次）,但该层战斗时防御力-30%。",
	//特殊(9~10)
	"希望：在该层每次移动后金币+2，攻击力+30%。",
	"绝望：所有敌人攻击力+20%，我方攻击力-20%。"
};
/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*使用a=Safecin(legal,length,ifblank)以获得合法输入，
*legal为合法数字数组(int数组)，length为数组长度(int)，ifblank为是否允许空输入(bool值)
*/
void Refresh() {
	cout << "\033[2J\033[H" << flush;
}
//以下为随机数生成器
class RandomManager {
private:
	mt19937 rd;
public:
	RandomManager() :rd(random_device{}()) {}
	RandomManager(const RandomManager&) = delete;
	RandomManager operator=(const RandomManager&) = delete;
	int getnum(int min, int max) {
		uniform_int_distribution<int> dist(min, max);
		return dist(rd);
	}
};
RandomManager rm;
//以下为输入检查函数
vector<string> forcheck;
int Safecin(int legal[], int length, bool ifblank) {
	string chose;
	forcheck.clear();
	for (int i = 0; i < length; i++) {
		forcheck.push_back(to_string(legal[i]));
	}
	while (1) {
		getline(cin, chose);
		if (ifblank) {
			if (chose.empty()) {
				return -1;
			}
		}
		for (auto& item : forcheck) {
			if (item == chose) {
				return stoi(chose);
			}
		}
		cout << "请在";
		for (auto& item : forcheck) {
			cout << item << ",";
		}
		cout << "中选择一个数字:";
		if (ifblank) cout << "(或者回车以继续)";
	}
}
//以下为主要运行程序

vector<vector<string>> Themap(8, vector<string>(100, " "));
void DrawBlock(int blocktype, int line) {
	if (blocktype != 5 && blocktype != 0) {//blocktype为5为双节点，blocktype为0为已经过节点
		for (int j = line; j < line + 5;j++) {
			Themap[2][j] = "#";
			Themap[4][j] = "#";
			Themap[3][line] = "#";
			Themap[3][line + 4] = "#";
		}
		switch (blocktype) {
		case 1:
			Themap[3][line + 2] = "*";//普通战斗
			break;
		case 2:
			Themap[3][line + 2] = "?";//非战斗节点
			break;
		case 3:
			Themap[3][line + 2] = "$";//商店节点
			break;
		case 4:
			Themap[3][line + 2] = "B";//boss节点
			break;
		}
	}
	else if (blocktype == 0) {
		for (int j = line; j < line + 5; j++) {
			Themap[2][j] = "#";
			Themap[3][j] = "#";
			Themap[4][j] = "#";
		}
	}
	else {//双节点
		for (int i = 1;i < 4;i++) {
			Themap[3][line - i] = " ";
		}
		for (int i = 1;i <= 5;i++) {
			if (i != 3) {
				Themap[i][line - 3] = "|";
				Themap[i][line + 6] = "|";
			}
		}
		Themap[1][line - 2] = "-";
		Themap[5][line - 2] = "-";
		Themap[1][line - 1] = ">";
		Themap[5][line - 1] = ">";
		Themap[1][line + 5] = "-";
		Themap[5][line + 5] = "-";
		Themap[3][line + 7] = "-";
		Themap[3][line + 8] = ">";
		for (int i = 0;i < 7;i++) {
			if (i != 3) {
				Themap[i][line] = "#";
				Themap[i][line + 4] = "#";
			}
		}
		for (int i = 1;i <= 3;i++) {
			Themap[0][line + i] = "#";
			Themap[2][line + i] = "#";
			Themap[4][line + i] = "#";
			Themap[6][line + i] = "#";
		}
		Themap[1][line + 2] = "*";
		Themap[5][line + 2] = "?";
	}
	if (blocktype != 5 && blocktype != 4) {//boss节点不需要箭头,此处为单节点的箭头设置
		Themap[3][line + 5] = "-";
		Themap[3][line + 6] = "-";
		Themap[3][line + 7] = "-";
		Themap[3][line + 8] = ">";
	}
}
void PrintMaphelp() {
	cout << "地图说明：" << endl;
	cout << " * :战斗节点" << endl;
	cout << " ? :未知事件节点" << endl;
	cout << " $ :商店节点" << endl;
	cout << " B :Boss节点" << endl;
	cout << " ^ :当前位置" << endl;
}
vector<int> Maptype;
int Map1[5] = { 1,2,5,3,4 };
int Map2[6] = { 2,1,1,5,3,4 };
int Map3[7] = { 2,2,1,1,5,3,4 };
void DrawMap(int floor, int step) {
	Refresh();
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 100;j++) {
			Themap[i][j] = " ";
		}
	}
	Maptype.clear();
	switch (floor) {
	case 1:
		for (int i = 0; i < 5; i++) {
			Maptype.push_back(Map1[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++) {
			Maptype.push_back(Map2[i]);
		}
		break;
	case 3:
		for (int i = 0; i < 7; i++) {
			Maptype.push_back(Map3[i]);
		}
		break;
	}
	for (int n = 0;n < step;n++) {
		Maptype[n] = 0;
	}
	for (int n = 0; n < Maptype.size(); n++) {
		DrawBlock(Maptype[n], n * 9);
	}
	if (Maptype[step] != 5) {
		Themap[5][step * 9 + 2] = "^";

	}
	else {
		Themap[7][step * 9 + 2] = "^";
	}
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 100;j++) {
			cout << Themap[i][j];
		}
		cout << endl;
	}
	cout << "目前在第" << floor << "层"<<endl;
	cout << endl;
	PrintMaphelp();
	cout << endl;
}
void SupplementDigitNumber(string &num) {
	while (num.length() < 3) {
		num = "0" + num;
	}
}
int Battlerow = 20;
int Battlecol = 90;
vector<vector<string>> Battlemap(Battlerow, vector<string>(Battlecol, " "));
void PrintBalttleGround(int *myData, int *enemyData,int round) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";	
		}
	}
	string myhp = to_string(myData[0]);
	string myHP = to_string(myData[1]);
	string enemyhp = to_string(enemyData[0]);
	string enemyHP = to_string(enemyData[1]);
	SupplementDigitNumber(myhp);
	SupplementDigitNumber(myHP);
	SupplementDigitNumber(enemyhp);
	SupplementDigitNumber(enemyHP);
	double MyHpPercent = (double)myData[0] / myData[1];
	double EnemyHpPercent = (double)enemyData[0] / enemyData[1];
	double MyEnergyPercent = (double)myData[2] / myData[3];
	int MyEnergyBarLength = (int)(MyEnergyPercent * 19);
	double Myhealpercent = (double)myData[4] / myData[5];
	int MyhealBarLength = (int)(Myhealpercent * 19);
	double EnemyEnergyPercent = (double)enemyData[2] / enemyData[3];
	int EnemyEnergyBarLength = (int)(EnemyEnergyPercent * 19);
	int MyHpBarLength = (int)(MyHpPercent * 28);
	int EnemyHpBarLength = (int)(EnemyHpPercent * 28);
	Refresh();
	for (int i = 0; i < Battlerow; i++) {
		Battlemap[i][0] = "#";
		Battlemap[i][Battlecol - 1] = "#";
	}
	for (int j = 0; j < Battlecol; j++) {
		Battlemap[0][j] = "#";
		Battlemap[Battlerow - 1][j] = "#";
	}
	Battlemap[1][40] = "M";
	Battlemap[1][41] = "y";
	Battlemap[1][42] = "C";
	Battlemap[1][43] = "h";
	Battlemap[1][44] = "a";
	Battlemap[1][45] = "r";
	Battlemap[1][46] = "a";
	Battlemap[1][47] = "c";
	Battlemap[1][48] = "t";
	Battlemap[1][49] = "e";
	Battlemap[1][50] = "r";
	Battlemap[18][43] = "E";
	Battlemap[18][44] = "n";
	Battlemap[18][45] = "e";
	Battlemap[18][46] = "m";
	Battlemap[18][47] = "y";
	//以下为我方血量条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for(int j=32;j<=59;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for(int j=32;j<32+MyHpBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	Battlemap[5][40] = "H";
	Battlemap[5][41] = "P";
	Battlemap[5][42] = ":";
	Battlemap[5][43] = myhp[0];
	Battlemap[5][44] = myhp[1];
	Battlemap[5][45] = myhp[2];
	Battlemap[5][46] = "/";
	Battlemap[5][47] = myHP[0];
	Battlemap[5][48] = myHP[1];
	Battlemap[5][49] = myHP[2];
	//以下为我方能量条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6;j <= 24;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	Battlemap[5][11] = "E";
	Battlemap[5][12] = "n";
	Battlemap[5][13] = "e";
	Battlemap[5][14] = "r";
	Battlemap[5][15] = "g";
	Battlemap[5][16] = "y";
	Battlemap[5][17] = ":";
	Battlemap[5][18] = to_string(myData[2]);
	Battlemap[5][19] = "/";
	Battlemap[5][20] = to_string(myData[3]);
	for (int j = 6;j < 6 + MyEnergyBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	//以下为我方治疗条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][66] = "#";
		Battlemap[i][86] = "#";
	}
	for (int j = 67;j <= 85;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	Battlemap[5][73] = "H";
	Battlemap[5][74] = "e";
	Battlemap[5][75] = "a";
	Battlemap[5][76] = "l";
	Battlemap[5][77] = ":";
	Battlemap[5][78] = to_string(myData[4]);
	Battlemap[5][79] = "/";
	Battlemap[5][80] = to_string(myData[5]);
	for (int j = 67;j < 67 + MyhealBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	//以下为敌方血量条位置
	for (int i = 15;i <= 17;i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for(int j=32;j<=59;j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	for (int j = 32;j < 32 + EnemyHpBarLength;j++) {
		Battlemap[16][j] = "|";
	}
	Battlemap[14][40] = "H";
	Battlemap[14][41] = "P";
	Battlemap[14][42] = ":";
	Battlemap[14][43] = enemyhp[0];
	Battlemap[14][44] = enemyhp[1];
	Battlemap[14][45] = enemyhp[2];
	Battlemap[14][46] = "/";
	Battlemap[14][47] = enemyHP[0];
	Battlemap[14][48] = enemyHP[1];
	Battlemap[14][49] = enemyHP[2];
	//以下为敌方能量条位置
	for (int i = 15;i <= 17;i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6;j <= 24;j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	Battlemap[14][11] = "E";
	Battlemap[14][12] = "n";
	Battlemap[14][13] = "e";
	Battlemap[14][14] = "r";
	Battlemap[14][15] = "g";
	Battlemap[14][16] = "y";
	Battlemap[14][17] = ":";
	Battlemap[14][18] = to_string(enemyData[2]);
	Battlemap[14][19] = "/";
	Battlemap[14][20] = to_string(enemyData[3]);
	for (int j = 6;j < 6 + EnemyEnergyBarLength;j++) {
		Battlemap[16][j] = "|";
	}
	Battlemap[16][73] = "R";
	Battlemap[16][74] = "o";
	Battlemap[16][75] = "u";
	Battlemap[16][76] = "n";
	Battlemap[16][77] = "d";
	Battlemap[16][78] = to_string(round);
	for(int i=7;i<=11;i++) {
		Battlemap[i][i+32] = "*";
	}
	for(int i=7;i<=10;i++) {
		Battlemap[i][54-i] = "*";
	}
	//打印地图
	for(int i = 0; i < Battlerow; i++) {
		for(int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j]<<flush;
		}
		cout << endl;
	}
}
void PrintEventGround() {
	Refresh();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";
		}
	}
	for (int i = 0; i < Battlerow; i++) {
		Battlemap[i][0] = "#";
		Battlemap[i][Battlecol - 1] = "#";
	}
	for (int j = 0; j < Battlecol; j++) {
		Battlemap[0][j] = "#";
		Battlemap[Battlerow - 1][j] = "#";
	}
	//打印地图
	for (int i = 0; i < Battlerow; i++) {
		for (int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j];
		}
		cout << endl;
	}
}
int MydataWhenBattle[6] = { 120, 300, 2, 3, 1, 3 };
//血量，血量上限，能量，能量上限，治疗条，治疗条上限
int EnemydataWhenBattle[4] = { 50, 100, 2, 5 };
//血量，血量上限，能量，能量上限
int main() {
	int floor = 1;
	int	step = 0;
	int Rune = -1;
	while (1) {
		DrawMap(floor, step);
		switch (Maptype[step]) {
		case 1://普通战斗
			cout << "进入战斗节点，按回车继续..." << endl;
			cin.ignore();
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, 1);
			break;
		case 4://boss战斗
			cout << "进入Boss战斗节点，按回车继续..." << endl;
			cin.ignore();
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, 1);
			break;
		case 2://非战斗节点
			cout << "进入未知事件节点，按回车继续..." << endl;
			cin.ignore();
			PrintEventGround();
			break;
		case 3://商店节点
			cout << "进入商店节点，按回车继续..." << endl;
			cin.ignore();
			PrintEventGround();
			break;
		case 5://双节点
			cout << "进入双节点，请选择节点。输入1以选择战斗节点，输入2以选择未知事件节点..." << endl;
			while (1) {
				int choice=0;
				int legal[2] = { 1,2 };
				choice=Safecin(legal, 2, false);
				if (choice == 1) {
					PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, 1);
					break;
				}
				else if (choice == 2) {
					PrintEventGround();
					break;
				}
			}
			break;
		}
		cin.ignore();
		step++;
		if (step >= Maptype.size() && floor < 3) {
			step = 0;
			floor++;
		}
		if (step >= Maptype.size() && floor == 3) {
			break;
		}
	}
	return 0;
}