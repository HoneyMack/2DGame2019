#include "Mob.h"
Mob* Mob::first = nullptr;
Mob* Mob::last = nullptr;
int Mob::killedenemy = 0;
Mob::Mob()
{
	ChainMaker();
}


Mob::~Mob()
{
	ChainCutter();
}

bool Mob::HasNext() {
	if (this->next != nullptr)
		return true;
	else
		return false;
}

void Mob::AllDelete() {
	AllDelete(first);
	first = nullptr;
}

void Mob::AllDelete(Mob* mob) {
	while (mob != nullptr) {
		Mob* nextmob = mob->next;
		delete mob;
		mob = nextmob;
	}
}

void Mob::ChainMaker() 
{
	if (first == nullptr)		//もし一つもなかったらfirstに入れる
		first = this;
	else {					//ひとつ前に要素があれば
		former = last;			//自分よりいっこ前に作られたMobを保持
		former->next = this;
	}
	last = this;			//最後尾を更新
	next = nullptr;			//次をさすものはない
}
void Mob::ChainCutter() 
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