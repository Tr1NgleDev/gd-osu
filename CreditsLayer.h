#pragma once
#include "pch.h"

class CreditsLayer : public cocos2d::CCLayer
{
protected:
	virtual bool init() override;
	virtual void keyBackClicked();
public:
	void update(float) override;
	static CreditsLayer* create();
	//void backButton(CCObject*);

	CCSize size;
	CCEGLView* view;


	CCSprite* bg;
	CCPoint bgStartPos;

	CCSprite* tr1ngleDev;
	CCSprite* ppy;
	CCSprite* andy;
	CCSprite* hjfod;
};

