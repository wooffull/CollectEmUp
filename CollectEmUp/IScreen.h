#pragma once

#include "GameObject.h"
#include "MouseEvent.h"

class IScreen :
	public GameObject
{
public:
	virtual void onMouseMove( MouseEvent e ) = 0;
	virtual void onMouseDown( MouseEvent e ) = 0;
	virtual void onMouseUp( MouseEvent e ) = 0;
};