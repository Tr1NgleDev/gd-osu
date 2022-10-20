#pragma once
#include "pch.h"

class Mouse
{
public:
	static CCPoint getMousePosition(CCEGLView* view)
	{
		return { view->m_fMouseX,view->m_fMouseY };
	}
	static CCPoint getMousePositionC(CCEGLView* view)
	{
		return (getMousePosition(view) - view->getFrameSize() / 2.f) * 2.f;
	}
	static CCPoint getMousePositionF(CCEGLView* view)
	{
		return { getMousePosition(view).x / view->getFrameSize().width, getMousePosition(view).y / view->getFrameSize().height };
	}
	static CCPoint getMousePositionCF(CCEGLView* view)
	{
		return { getMousePositionC(view).x / view->getFrameSize().width, getMousePositionC(view).y / view->getFrameSize().height };
	}
	static CCPoint getMousePositionInS(CCEGLView* view, CCSize size)
	{
		return { getMousePositionF(view).x * size.width, (1.f - getMousePositionF(view).y) * size.height };
	}
};

