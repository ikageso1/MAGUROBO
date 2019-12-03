#pragma once
#include <vector>

class Input;
class Menu{
protected:
	int Model;
	float Angle;

	//メニュー画面の背景
	int menuGraph;
	//座標(デフォルトは0)
	int x,y;
	// 媒介変数(べじぇ)
	int t;
	//間の大きさ
	int height;
	//カーソル
	int cursor;
	//文字色
	int color;
	//選択時の文字色
	int selectedColor;
	//効果音
	int sound;
	int dicideSound;
	//BGMのファイル名
	char *bgm;
	//メニュー画面のリスト
	std::vector<char*> menuList;
	//選択フラグ値
	int retFlag;
public:
	//デフォルトコンストラクタ(文字色はデフォルトで白）
	Menu();
	//引数付きコンストラクタ
	//第一引数：文字色
	Menu(int color);
	//引数付きコンストラクタ
	//第一引数：文字色、第二引数：背景画像
	Menu(int color,char* source);
	//選択時の色を設定(デフォルトは赤)
	void setSelectedColor(int color);
	//メニューリストに文字列を追加
	void addMenuList(char* str);
	//座標の設定
	void setPoint(int x,int y);
	//文字列間の大きさの設定(デフォルトは20)
	void setHeight(int h);
	//カーソル移動時の効果音の登録
	void setSound(char *file);
	//メニュー画面のBGMの登録
	void setBGM(char *file);
	//表示
	virtual void show();
	//メニュー画面処理を関数内ループ付きでスタート
	//Enterが押された場合はtureを返す。押されていない場合はfalse
	//ESCキーなどが押された場合は-1を返す
	bool start(Input *input);
	//選択された選択肢の順番の値を返す（1から始まる番号)
	int getSelectChoice();
	// ベジェ曲線
	void Bezier(double x1,double y1,double x2,double y2,double x3,double y3,int t,int *ansX,int *ansY);

	void Rotate();
	void ChengeSelectStageMenu();
};