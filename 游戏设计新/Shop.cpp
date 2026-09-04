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
int Safecin_Shop(const vector<int>& legal, bool ifblank) {
	string chose;
	forcheck.clear();
	for (auto v : legal) forcheck.push_back(to_string(v));
	while (true) {
		getline(cin, chose);
		if (ifblank && chose.empty()) return -1;
		for (auto& item : forcheck) {
			if (item == chose) return stoi(chose);
		}
		cout << "请在";
		for (auto& item : forcheck) cout << item << ",";
		cout << "中选择一个数字:";
		if (ifblank) cout << "（或者回车以退出商店）";
		cout << flush;
	}
}
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
	else if (ItemRarity == 0) {
		Color = HUI;
	}

	int width = 40;
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

void DrawingShop(vector<int> BoughtNum,vector<string> ItemName,vector<int> ItemPrice,vector<int> ItemRarity) {
	for (int i = 0; i < Shoprow; i++) {
		for (int j = 0; j < Shopcol; j++) {
			Shopmap[i][j] = " ";
		}
	}
	string ShopName = RED_WINE + "【 符文秘境 · 商店 】";
	PutShopText(2, 1, Shopcol - 2, ShopName);
	for (int j = 1; j < Shopcol - 1; j++) {
		Shopmap[4][j] = "=";
	}
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
		if (itemCol == 0) { startCol = 3; }
		else { startCol = 48; }
		//绘制商品
		if (find(BoughtNum.begin(), BoughtNum.end(), i) == BoughtNum.end()) {
			DrawShopItem(startRow, startCol, ItemName[i], ItemPrice[i], i + 1, ItemRarity[i]);
		}
		else {
			DrawShopItem(startRow, startCol, ItemName[i], ItemPrice[i], i + 1, 0);
		}

	}
	//显示当前金币
	string CoinText =YELLOW+ "当前金币：" + to_string(mycharacter.GetCoins());
	PutShopText(37, 1, Shopcol - 2, CoinText);

	//显示操作说明
	string HelpText =RED_WINE+
		"输入商品编号购买商品，回车以离开商店，输入0以查看当前状态";
	PutShopText(38, 1, Shopcol - 8, HelpText);

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
void ShopStart() {
	bool IfRefreshShop = true;
	//清空商店画布

	for (int i = 0; i < Shoprow; i++) {
		for (int j = 0; j < Shopcol; j++) {
			Shopmap[i][j] = " ";
		}
	}

	//绘制商店最外层边框

	//商店标题
	string ShopName = RED_WINE+"【 符文秘境 · 商店 】";

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
	while ((int)ObjectForSale.size() < 12) { // 如果藏品不足12个，则补充
		vector<shared_ptr<Object>> ForFilling;

		// 优先补充3级藏品
		for (auto& item : ObjectPool3) {
			// 条件1：未被获得过
			// 条件2：当前不在 ObjectForSale 售卖列表中（防止重复）
			if (!item->GetIfGotten() && find(ObjectForSale.begin(), ObjectForSale.end(), item) == ObjectForSale.end()) {
				ForFilling.push_back(item);
			}
		}

		if (!ForFilling.empty()) {
			int RandomNumForFilling = rm.getnum(0, (int)ForFilling.size() - 1);
			ObjectForSale.push_back(ForFilling[RandomNumForFilling]);
		}
		else {
			// 如果3级藏品不足或全都在商店里了，则尝试补充2级藏品
			for (auto& item : ObjectPool2) {
				if (!item->GetIfGotten() && find(ObjectForSale.begin(), ObjectForSale.end(), item) == ObjectForSale.end()) {
					ForFilling.push_back(item);
				}
			}

			if (!ForFilling.empty()) {
				int RandomNumForFilling = rm.getnum(0, (int)ForFilling.size() - 1);
				ObjectForSale.push_back(ForFilling[RandomNumForFilling]);
			}
			else {
				while ((int)ObjectForSale.size() < 12) {
					make_shared<Object>(3, "M", "HE", "Wunder：每点治疗能量治疗量+15", 15);
				}
			}
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

	vector<int> BoughtNum;
	vector<int> LegalShopChoice = {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	//第七步：绘制12个商品
	while (1) {
		if (IfRefreshShop) {
			DrawingShop(BoughtNum, ItemName, ItemPrice, ItemRarity);
		}
		int BuyingChoice=Safecin_Shop(LegalShopChoice, true)-1;
		if (BuyingChoice == -2) {
			IfRefreshShop = true;
			break;
		}
		else if (BuyingChoice == -1) {
			PrintMyCharacterStatus();
			IfRefreshShop = true;
			continue;
		}
		else {
			if (ObjectForSale[BuyingChoice]->GetIfGotten()) {
				cout <<YELLOW<< "已购买该藏品！请重新选择。" << endl;
				cout << HUI << "按回车继续..." << endl;
				IfRefreshShop = true;
				SafeEnter();
			}
			else if (mycharacter.GetCoins() >= ItemPrice[BuyingChoice]) {
				mycharacter.UsingCoins(ItemPrice[BuyingChoice]);
				MyObjectGroup.push_back(ObjectForSale[BuyingChoice]);
				ObjectForSale[BuyingChoice]->GainObject();
				BoughtNum.push_back(BuyingChoice);
				DrawingShop(BoughtNum, ItemName, ItemPrice, ItemRarity);
				cout << YELLOW << "已消耗 "<<ItemPrice[BuyingChoice]<<" 枚金币购买 " << ItemRarity[BuyingChoice] << "级 藏品" << endl;
				cout << GREEN_BRIGHT << ItemName[BuyingChoice] << endl;
				cout <<WHITE<< "请继续输入以购买商品...(或回车以离开商店，输入0以查看当前状态)" << endl;
				IfRefreshShop = false;
			}
			else {
				cout << YELLOW << "金币不足！请重新选择。" << endl;
				cout << HUI << "按回车继续..." << endl;
				IfRefreshShop = true;
				SafeEnter();
			}
		}
	}
}

