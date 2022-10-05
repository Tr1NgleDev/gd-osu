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
	void beatUpdate();
	void stepUpdate();
	void stepHit();
	void beatHit();
	static OsuMenuLayer* _fastcall create();

	bool playing = false;
	float songPos = 0.f;
	int curStep;
	int curBeat;
};

