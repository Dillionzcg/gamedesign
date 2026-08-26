#include<iostream>
#include<random>
#include<vector>
#include<memory>
#include<string>
using namespace std;
/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*/
void Refresh() {
	cout << "\033[2J\033[H" << flush;
}
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
}

int main() {
	int floor = 1;
	int	step = 0;
	while (1) {
		DrawMap(floor, step);
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