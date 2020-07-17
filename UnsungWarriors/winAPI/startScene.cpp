#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 400, 400, 100);
	
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("필드화면");
		}
	}

}

void startScene::render()
{
	IMAGEMANAGER->render("bgLoadingScene", getMemDC());
	IMAGEMANAGER->render("start", getMemDC(), _rc.left, _rc.top);
}
