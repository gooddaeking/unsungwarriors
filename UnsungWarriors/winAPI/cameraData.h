#pragma once
#include "singletonBase.h"
class cameraData : public singletonBase <cameraData>
{
private:
	image* _image;
	int _hp;
	int _width, _height;
	float _x, _y;

	

public:
	HRESULT init();
	void release();

	image* getImage() { return _image; }
	void setImage(image* image) { _image = image; }
	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }
	float get_X() { return _x; }
	void set_X(float x) { _x = x; }
	float get_Y() { return _y; }
	void set_Y(float y) { _y = y; }
	int getWidth() { return _width; }
	void setWidth(int width) { _width = width; }
	int getHeight() { return _height; }
	void setHeight(int height) { _height = height; }

	cameraData() {}
	~cameraData() {}
};

