#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"
#include "inven.h"
#include "shop.h"

//상호참조용 클래스 전방선언
class enemyManager;

enum STATE
{
	IDLE, MOVE, JUMP, DASH, FALL, ATT1, ATT2, ATT3, HIT, DEAD
};

class player : public gameNode
{
private:
	enemyManager* _em;  //절대로 동적할당 놉!!
	inven* _inven;
	shop* _shop;
	//메인게임에서 생성한 EM과 플레이어에서 생성한 EM은
	//전혀 다른 메모리 주소라서 서로 참조할 수 없다!!!
private:
	image* _player;		//플레이어 이미지
	//RECT _rcPlayer;		//플레이어 움직일 렉트
	missile* _missile;	//미사일 클래스
	bomb* _bomb;		//폭탄 클래스

	vector<tagItem> _vWeapon;
	vector<tagItem> _vAcce;
	vector<tagItem> _vShield;
	
	RECT _hit;
	RECT _rcAtt;
	RECT _rcAtt2;
	RECT _rcAtt3;

	STATE _state;
	int frameX, frameY, _count, _dashCount;
	int _dmg, _gold;
	bool _life;
	bool _dashOnL, _dashOnR;
	bool _dashLight;
	float _x, _y;
	float _probeU, _probeD, _probeL, _probeR;
	float _speed;
	float _gravity;
	bool _att2, _att3, _coolDown;
	bool _isLeft;
	bool _comeback;
	bool _magicOn;
	int magicFrameX, magicFrameY, alpha;
	RECT electric;
	RECT _camera;
	POINT _point;

	progressBar* _hpBar;	 //체력바
	progressBar2* _mpBar;
	float _maxHp, _currentHp; //최대체력, 현재체력
	float _maxMp, _currentMp; //최대체력, 현재체력

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//폭탄클래스 가져오기
	bomb* getBomb() { return _bomb; }

	//폭탄삭제
	void removeBomb(int index);

	//충돌함수(플레이어총알, 미니언충돌)
	void collision();

	//플레이어 애니메이션
	void animation();
	void camera();

	//피통깍기
	void hitDamage(float damage);

	//세이브로드
	void save();
	void load();

	//플레이어 이미지 가져오기
	image* getPlayerImg() { return _player; }
	RECT getHit() { return _hit; }
	bool getLife() { return _life; }
	int getHp() { return _currentHp; }
	void setHp(int currentHp) { _currentHp = currentHp; }
	int getMp() { return _currentMp; }
	float get_X() { return _x; }
	void set_X(float x) { _x = x; }
	float get_Y() { return _y; }
	void set_Y(float y) { _y = y; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }

	inven* getInven() { return _inven; }
	shop* getShop() { return _shop; }

	//상호참조시 적매니져 포인터를 넘겨받을 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

