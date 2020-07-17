#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init()
{
	return S_OK;
}

void playerData::release()
{
}

void playerData::setSerial(int index)
{
	_serial.push_back(index);
}
