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
	void syaNextTime();
	static OsuMenuLayer* _fastcall create();

	bool playing = false;
	float songPos = 0.f;
	int curStep;
	int curBeat;

	CCSprite* bg;
	CCPoint bgStartPos;

	CCSprite* logo;
	CCSprite* logoT;
	CCPoint logoStartPos;

	CCSprite* shittyLines;
	CCSprite* ppy;
	CCSprite* tr1ngle;

	CCSprite* blackBG;

	float timer = 0;
	float timer2 = 0;
	int alphaA = 255;
	bool flashSkullEmoji;

	float flash_leftValue;
	float flash_rightValue;

	CCGLProgram* flashGradient;
	CCGLProgram* blur;

	bool closingGame;
	float closeTimer;
};

