#pragma once
#include <vector>
#include "define.h"
#include "Rect.h"

using namespace std;

class Map
{
private:
	int numX, numY;
public:
	static int PicHandle[];						//画像保持
	vector<vector<int> > m_map;					//描画するマップの情報

	Map();										//コンストラクタ
	Map(int lenX);								//コンストラクタ
	~Map();										//デストラクタ

	void setNum(int x, int y);					//変数numX = x,numY = yにセット (配列あふれを防ぐための保険)
	void setArray();							//配列の長さをnumX,numYにセット
	void resetMap();							//マップの要素を0で初期化
	void setFrame();							//プレイヤーがあふれないように外枠を作る

	int getNumX();								//numXを返す
	int getNumY();								//numYを返す

	int PosInfo(int x,int y);	//x,y座標のブロックのナンバーを返す
	void Draw(Rect *Camera);
};

//マップでの要素番号に直す
int ReturnMapIndex(double x);