#pragma once
#include "pch.h"
class OsuMenuLayer : public cocos2d::CCLayer
{
protected:
	virtual bool init() override;
	virtual void keyBackClicked();
public:
	static bool openedBefore;
	void update(float) override;
	static OsuMenuLayer* _fastcall create();
};

