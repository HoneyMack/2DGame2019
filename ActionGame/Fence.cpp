#include "Fence.h"
Fence* Fence::first = nullptr;
Fence* Fence::last = nullptr;

int Fence::PicHandle = 0;

Fence::Fence(int x,int y)
{
	this->x = x;
	this->y = y;

	ChainMaker();
}

Fence::~Fence()
{
	ChainCutter();
}

void Fence::Draw() {
	if (CheckInCam(x + rect.sizeX,y) || CheckInCam(x, y)) {
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
		DrawGraph(RelativePosX(),RelativePosY(),PicHandle,TRUE);
	}
}

void Fence::AllDelete() {
	AllDelete(first);
	first = nullptr;
}

void Fence::AllDelete(Fence* mob) {
	while (mob != nullptr) {
		Fence* nextmob = mob->next;
		delete mob;
		mob = nextmob;
	}
}

void Fence::ChainMaker()
{
	if (first == nullptr)		//もし一つもなかったらfirstに入れる
		first = this;
	else {					//ひとつ前に要素があれば
		former = last;			//自分よりいっこ前に作られたFenceを保持
		former->next = this;
	}
	last = this;			//最後尾を更新
	next = nullptr;			//次をさすものはない
}
void Fence::ChainCutter()
{
	//オブジェクトの鎖を崩さないようにするための処理
	//要素がまだ別にある時
	if (last != first) {
		if (this == last) {				//this == 最後尾なら
			last = former;					//最後尾の更新
			former->next = nullptr;			//最後尾のnextをnullに
		}
		else if (this == first) {			//最前を消したら
			next->former = nullptr;			//最前になるものformerをnullに
			first = next;					//最前の更新
		}
		else {	//真ん中にあるものを消したら
			former->next = this->next;
		}
	}
	else {	//インスタンスが一つしかないときの処理
		last = first = nullptr;
	}
}

bool Fence::HasNext() {
	if (this->next != nullptr)
		return true;
	else
		return false;
}

int Fence::HitCheckReturnFace(Rect rect) {
	//個々のあたり判定
	return HitFaceRectRect(this->rect, rect);
}

int Fence::PlayerHitCheck(Rect rect) {
	//当たっているか（どこの面に）を返す処理
	int hitface = 0;

	//先頭を入手
	if (first != nullptr) {
		Fence *fence = first;

		if (fence != nullptr) {		//インスタンスを保持しているか
			while (true) {			//インスタンスをすべてチェックするまでループ
				if (fence->HitCheckReturnFace(rect) != 0) {
					//プレイヤーのあたり判定を渡して、諸々やってもらう
					hitface = hitface | fence->HitCheckReturnFace(rect);
				}
				//描画処理
				fence->Draw();

				if (fence->HasNext())	//次のインスタンスがあったら
					fence = fence->next;
				else
					break;			//無かったらループを抜ける
			}
		}
	}
	return hitface;
}