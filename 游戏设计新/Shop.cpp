#include"Shop.h"
using namespace std;

// 边框颜色
const string BLUE_S = "\033[38;5;39m";
const string PURPLE_S = "\033[35m";
const string GOLD_S = "\033[33m";
const string RESET_S = "\033[0m";

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
		Color = BLUE_S;
	}
	else if (ItemRarity == 2) {
		Color = PURPLE_S;
	}
	else if (ItemRarity == 3) {
		Color = GOLD_S;
	}

	int width = 35;
	int nameHeight = 3;
	int priceHeight = 2;

	// 上边框
	for (int j = startCol; j < startCol + width; j++) {
		Shopmap[startRow][j] = Color + "#" + RESET_S;
	}

	// 左右边框
	for (int i = startRow + 1; i < startRow + nameHeight; i++) {
		Shopmap[i][startCol] = Color + "#" + RESET_S;
		Shopmap[i][startCol + width - 1] = Color + "#" + RESET_S;
	}

	// 下边框
	for (int j = startCol; j < startCol + width; j++) {
		Shopmap[startRow + nameHeight - 1][j] =
			Color + "#" + RESET_S;
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
	int TestCoin = 10;
	//显示当前金币
	string CoinText = "当前金币：" + to_string(TestCoin);
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
