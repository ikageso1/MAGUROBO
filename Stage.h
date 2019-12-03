#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Enemy;
class Item;

// ステージ情報構造体
class Stage
{
protected:
	int		ModelHandle ;				/**< 3Dモデルハンドル */
	
public:
	/**
	* コンストラクタ　ステージの初期化
	*/
	Stage();			
	/**
	* デストラクタ　ステージの消去
	*/
	~Stage();		
	/**
	 * ステージの描画をする関数 
	 */
	void Draw();



	/**
	 * ステージのポリゴンを取得する関数 
	 */
	MV1_COLL_RESULT_POLY_DIM GetStagePoly(VECTOR pos,float r);
	MV1_COLL_RESULT_POLY_DIM CollCheckCapsule(VECTOR pos1,VECTOR pos2,float r);
	/**
	 * ステージ読み込みをする関数 
	 */
	void LoadStage(const TCHAR* filename);
	virtual Player* CreatePlayer() = 0;
	virtual void  CreateEnemies(std::vector<Enemy*> *enemies,Player *player) = 0;
	virtual void  CreateItems(std::vector<Item*> *items) = 0;
} ;
