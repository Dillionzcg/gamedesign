/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*使用rm.getSomeNum(min,max,k)以获得一定范围（闭区间）的k个不重复随机int，返回vector<int>
*使用a=Safecin(legal,ifblank)以获得合法输入，
 legal为合法数字向量(vector<int>)，ifblank为是否允许空输入(bool值)
*使用WaitForSeconds(second)以等待特定秒数(double)
*/
#include<iostream>
#include<random>
#include<vector>
#include<memory>
#include<string>
#include<numeric>
#include<algorithm>
#include<stdexcept>
#include<thread>   
#include<chrono>
#include<limits>
using namespace std;


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
	RandomManager& operator=(const RandomManager&) = delete;
	int getnum(int min, int max) {
		uniform_int_distribution<int> dist(min, max);
		return dist(rd);
	}
	vector<int> getSomeNum(int min, int max, int k) {
		int total = max - min + 1;
		vector<int> pool(total);
		iota(pool.begin(), pool.end(), min);
		shuffle(pool.begin(), pool.end(), rd);
		return vector<int>(pool.begin(), pool.begin() + k);
	}
};
RandomManager rm;
//以下为输入检查函数
vector<string> forcheck;
int Safecin(const vector<int>& legal, bool ifblank) {
	string chose;
	forcheck.clear();
	for (auto v : legal) {
		forcheck.push_back(to_string(v));
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
		cout << flush;
	}
}
void SafeEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
//以下为等待时间函数
void WaitForSeconds(double Time) {
	int second = (int)Time * 1000;
	this_thread::sleep_for(chrono::milliseconds(second));
}