#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
#include "startScene.h"
#include "inGameScene.h"
#include "fieldMap.h"
#include "cave1.h"
#include "cave2.h"
#include "cave3.h"
#include "bossMap.h"

#include "iniTestScene.h"
#include "loadingScene.h"
#include "pixelCollisionScene.h"
#include "soundTestScene.h"
//#include "maptoolScene.h"
#include "isometricTestScene.h"
#include "astarTestScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

