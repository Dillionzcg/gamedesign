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

//藏品类
class Object {
public:
	Object(int rarity, string camp, string type, string describe, int buffnum) :Rarity(rarity), Camp(camp), Type(type), Describe(describe), BuffNum(buffnum) {
		NeedingCoin = RarityCoin[Rarity - 1];
	}
	int GetRarity() {
		return Rarity;
	}
	int GetNeedingCoin() {
		return NeedingCoin;
	}
	string GetDescribe() {
		return Describe;
	}
	double GetBuffNum() {
		return BuffNum;
	}
	bool GetIfGotten() {
		return IfGotten;
	}
	void GainObject() {
		IfGotten = true;
	}
private:
	int Rarity;//稀有度,1/2/3
	vector<int> RarityCoin = { 2,4,6 };//稀有度对应金币数
	int NeedingCoin;//购买所需金币数
	string Describe;//藏品描述
	string Camp;//阵营，"M"为我方，"E"为敌方
	string Type;//类型
	bool IfGotten = false;//是否已获得
	double BuffNum;//加成数值
};
//藏品池
vector<shared_ptr<Object>> ObjectPool1 = {//初级藏品
	make_shared<Object>(1,"M","A","攻击力+10%",0.1),
	make_shared<Object>(1,"M","D","防御力+20%",0.2),
	make_shared<Object>(1,"M","H","生命上限+30%",0.3),
	make_shared<Object>(1,"M","HE","每点治疗能量治疗量+5",5),
	make_shared<Object>(1,"E","A","敌人攻击力-10%",-0.1),
	make_shared<Object>(1,"E","D","敌人防御力-10%",-0.1),
	make_shared<Object>(1,"E","H","敌人生命上限-10%",-0.1),
	make_shared<Object>(1,"E","CR","敌人暴击率-5%",-5),
};
vector<shared_ptr<Object>> ObjectPool2 = {//中级藏品
	make_shared<Object>(2,"M","A","攻击力+20%",0.2),
	make_shared<Object>(2,"M","D","防御力+30%",0.3),
	make_shared<Object>(2,"M","H","生命上限+40%",0.4),
	make_shared<Object>(2,"M","HE","每点治疗能量治疗量+10",10),
	make_shared<Object>(2,"E","A","敌人攻击力-15%",-0.15),
	make_shared<Object>(2,"E","D","敌人防御力-15%",-0.15),
	make_shared<Object>(2,"E","H","敌人生命上限-15%",-0.15),
	make_shared<Object>(2,"E","CR","敌人暴击率-10%",-10),

	make_shared<Object>(2,"M","IE","我方初始能量+1",1),
	make_shared<Object>(2,"M","IHE","我方初始治疗能量+1",1),
	make_shared<Object>(2,"M","MHE","我方治疗能量上限+2",2),
	make_shared<Object>(2,"M","SC","可选择技能+1",1),
};
vector<shared_ptr<Object>> ObjectPool3 = {//高级藏品
	make_shared<Object>(3,"M","A","攻击力+30%",0.3),
	make_shared<Object>(3,"M","D","防御力+40%",0.4),
	make_shared<Object>(3,"M","H","生命上限+50%",0.5),
	make_shared<Object>(3,"M","HE","每点治疗能量治疗量+15",15),
	make_shared<Object>(3,"E","A","敌人攻击力-20%",-0.2),
	make_shared<Object>(3,"E","D","敌人防御力-20%",-0.2),
	make_shared<Object>(3,"E","H","敌人生命上限-20%",-0.2),
	make_shared<Object>(3,"E","CR","敌人暴击率-15%",-15),

	make_shared<Object>(3,"M","IE","我方初始能量+2",2),
	make_shared<Object>(3,"M","IHE","我方初始治疗能量+2",2),
	make_shared<Object>(3,"M","EN","我方技能所需能量-1",-1),
	make_shared<Object>(3,"E","EN","敌方技能所需能量+2",2),
	make_shared<Object>(2,"M","SC","可选择技能+2",2),
};

vector<shared_ptr<Object>> MyObjectGroup;//我方藏品组

int TestCoins = 100;
//刷新屏幕
void Refresh() {
	cout << "\033[2J\033[H" << flush;
}
//随机数生成
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
		return vector<int>(
			pool.begin(),
			pool.begin() + k
		);
	}
};

RandomManager rm;
// 边框颜色
const string BLUE = "\033[34m";
const string PURPLE = "\033[35m";
const string GOLD = "\033[33m";
const string RESET = "\033[0m";
//输入检查函数

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
		if (ifblank) {
			cout << "(或者回车以继续)";
		}
		cout << flush;
	}
}
//安全回车
void SafeEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//等待回车
void WaitForSeconds(double Time) {
	int second = (int)Time * 1000;
	this_thread::sleep_for(
		chrono::milliseconds(second)
	);
}
//商店系统
// 商店界面的行数
int Shoprow = 40;
// 商店界面的列数
int Shopcol = 90;
// 商店地图
// Shopmap 可以理解成一张“空白画布”。

vector<vector<string>> Shopmap(
	Shoprow,
	vector<string>(Shopcol, " ")
);

//向商店地图写入居中文字
void PutShopText(int row, int col, int width, string text) {
	// 如果文字太长，截断
	if ((int)text.length() > width) {
		text = text.substr(0, width);
	}
	// 计算开始位置
	int textWidth = 0;
	for (int i = 0; i < (int)text.length();) {
		unsigned char c = text[i];
		if (c < 128) {
			textWidth += 1;
			i++;
		}
		else {
			textWidth += 2;
			i += 3;
		}
	}
	int start = col + (width - textWidth) / 2;
	// 逐个字符写入
	for (int i = 0; i < (int)text.length(); i++) {
		if (start + i >= 0 && start + i < Shopcol) {
			Shopmap[row][start + i] = string(1, text[i]);
		}
	}
}

void DrawShopItem(int startRow, int startCol, string ItemName,
	int ItemPrice, int ItemNumber, int ItemRarity) {

	// 根据稀有度选择边框颜色
	string Color;

	if (ItemRarity == 1) {
		Color = BLUE;
	}
	else if (ItemRarity == 2) {
		Color = PURPLE;
	}
	else if (ItemRarity == 3) {
		Color = GOLD;
	}

	int width = 35;
	int nameHeight = 3;
	int priceHeight = 2;

	// 上边框
	for (int j = startCol; j < startCol + width; j++) {
		Shopmap[startRow][j] = Color + "#" + RESET;
	}

	// 左右边框
	for (int i = startRow + 1; i < startRow + nameHeight; i++) {
		Shopmap[i][startCol] = Color + "#" + RESET;
		Shopmap[i][startCol + width - 1] = Color + "#" + RESET;
	}

	// 下边框
	for (int j = startCol; j < startCol + width; j++) {
		Shopmap[startRow + nameHeight - 1][j] =
			Color + "#" + RESET;
	}

	// 商品名称
	PutShopText(startRow + 1, startCol + 1, width - 2, ItemName);

	// 商品价格框
	int priceStartRow = startRow + nameHeight;

	string PriceText = "所需金币：" + to_string(ItemPrice);
	PutShopText(priceStartRow, startCol + 12, width - 2, PriceText);

	// 稀有度
	string RarityText = "稀有度：" + to_string(ItemRarity);
	PutShopText(priceStartRow, startCol - 13, width - 2, RarityText);

	// 商品编号
	string NumberText = "[" + to_string(ItemNumber) + "]";

	for (int i = 0; i < (int)NumberText.length(); i++) {
		if (startCol + 2 + i < startCol + width - 1) {
			Shopmap[startRow + 1][startCol + 2 + i] =
				string(1, NumberText[i]);
		}
	}
}
//绘制完整商店

void DrawShop() {

	//清空商店画布

	for (int i = 0; i < Shoprow; i++) {
		for (int j = 0; j < Shopcol; j++) {
			Shopmap[i][j] = " ";
		}
	}

	//绘制商店最外层边框

	//商店标题
	string ShopName = "【 符文秘境 · 商店 】";

	PutShopText(2, 1, Shopcol - 2, ShopName);

	//标题装饰线
	for (int j = 1; j < Shopcol - 1; j++) {
		Shopmap[4][j] = "=";
	}
	vector<shared_ptr<Object>> ObjectForSale;
	vector<shared_ptr<Object>> ShopItems;
	//加入4个1级藏品
	for (auto& item : ObjectPool1) {
		if (!item->GetIfGotten()) {
			ShopItems.push_back(item);
		}
	}
	vector<int> ObjectChoice;
	if ((int)ShopItems.size() < 4) {
		for (auto& item : ShopItems) {
			ObjectForSale.push_back(item);
		}
	}
	else {
		ObjectChoice = rm.getSomeNum(0, (int)ShopItems.size() - 1, 4);
		for (int i = 0; i < 4; i++) {
			ObjectForSale.push_back(ShopItems[ObjectChoice[i]]);
		}
	}

	//加入4个2级藏品
	ShopItems.clear();
	for (auto& item : ObjectPool2) {
		if (!item->GetIfGotten()) {
			ShopItems.push_back(item);
		}
	}
	ObjectChoice.clear();
	if ((int)ShopItems.size() < 4) {
		for (auto& item : ShopItems) {
			ObjectForSale.push_back(item);
		}
	}
	else {
		ObjectChoice = rm.getSomeNum(0, (int)ShopItems.size() - 1, 4);
		for (int i = 0; i < 4; i++) {
			ObjectForSale.push_back(ShopItems[ObjectChoice[i]]);
		}
	}

	//加入4个3级藏品
	ShopItems.clear();
	for (auto& item : ObjectPool3) {
		if (!item->GetIfGotten()) {
			ShopItems.push_back(item);
		}
	}
	ObjectChoice.clear();
	if ((int)ShopItems.size() < 4) {
		for (auto& item : ShopItems) {
			ObjectForSale.push_back(item);
		}
	}
	else {
		ObjectChoice = rm.getSomeNum(0, (int)ShopItems.size() - 1, 4);
		for (int i = 0; i < 4; i++) {
			ObjectForSale.push_back(ShopItems[ObjectChoice[i]]);
		}
	}
	while ((int)ObjectForSale.size() < 12) {//如果藏品不足12个，则补充
		vector<shared_ptr<Object>> ForFilling;
		for (auto& item : ObjectPool3) {//优先补充3级藏品
			if (!item->GetIfGotten()) {
				ForFilling.push_back(item);
			}
		}
		if (!ForFilling.empty()) {
			int RandomNumForFilling = rm.getnum(0, (int)ForFilling.size() - 1);
			ObjectForSale.push_back(ForFilling[RandomNumForFilling]);
		}
		else {//如果3级藏品不足，则补充2级藏品
			for (auto& item : ObjectPool2) {
				if (!item->GetIfGotten()) {
					ForFilling.push_back(item);
				}
			}
			int RandomNumForFilling = rm.getnum(0, (int)ForFilling.size() - 1);
			ObjectForSale.push_back(ForFilling[RandomNumForFilling]);
		}

	}

	//商品名称
	vector<string> ItemName;
	for (auto& item : ObjectForSale) {
		ItemName.push_back(item->GetDescribe());
	}
	//商品稀有度
	vector<int> ItemRarity;
	for (auto& item : ObjectForSale) {
		ItemRarity.push_back(item->GetRarity());
	}
	//商品价格
	vector<int> ItemPrice;
	for (auto& item : ObjectForSale) {
		ItemPrice.push_back(item->GetNeedingCoin());
	}


	//第七步：绘制12个商品

	for (int i = 0; i < 12; i++) {
		// 计算商品所在的行
		int itemRow = i / 2;
		// 计算商品所在的列
		int itemCol = i % 2;
		//
		int startRow =
			6 + itemRow * 5;
		//商品的起始列
		int startCol;
		if (itemCol == 0) { startCol = 5; }
		else { startCol = 50; }
		//绘制商品
		DrawShopItem(startRow, startCol, ItemName[i], ItemPrice[i], i + 1, ItemRarity[i]);
	}
	//显示当前金币
	string CoinText = "当前金币：" + to_string(TestCoins);
	PutShopText(37, 1, Shopcol - 2, CoinText);

	//显示操作说明
	string HelpText =
		"输入商品编号购买商品，输入0离开商店";
	PutShopText(38, 1, Shopcol - 2, HelpText);

	//刷新屏幕

	Refresh();

	//输出商店

	for (int i = 0; i < Shoprow; i++) {
		for (int j = 0; j < Shopcol; j++) {
			cout << Shopmap[i][j];
		}
		cout << endl;
	}
}

//商店测试

void ShopTest() {
	// 绘制商店
	DrawShop();
	//等待输入
	cout << endl;
	cout << "输入0退出测试：" << endl;
	vector<int> legal = { 0 };
	Safecin(legal, false);
}
