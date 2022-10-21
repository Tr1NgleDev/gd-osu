#pragma once
#include "pch.h"

class OsuMenuLayer : public cocos2d::CCLayer
{
protected:
	virtual bool init() override;
	virtual void keyBackClicked();
public:
	void createMainMenuButtons();
	void createPlayMenuButtons();
	static bool openedBefore;
	void update(float) override;
	void beatUpdate();
	void stepUpdate();
	void stepHit();
	void beatHit();
	void syaNextTime();
	static OsuMenuLayer* _fastcall create();

	CCSize size;
	CCEGLView* view;

	bool playing = false;

	CCSprite* bg;
	CCPoint bgStartPos;

	CCSprite* logo;
	CCSprite* logoT;
	CCPoint logoStartPos;
	float logoScale = 0.95f;
	CCPoint logoPos;

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

	bool inMainMenu;
	bool inPlayMenu;

	CCSprite* rewardsBtn;

	CCSprite* accBtn;
	CCLabelBMFont* username;
	CCLabelBMFont* info;

	// main menu buttons
	CCSprite* playBtnN;
	CCSprite* playBtnO;

	CCSprite* iconsBtnN;
	CCSprite* iconsBtnO;

	CCSprite* creditsBtnN;
	CCSprite* creditsBtnO;

	CCSprite* optionsBtnN;
	CCSprite* optionsBtnO;
	
	CCSprite* exitBtnN;
	CCSprite* exitBtnO;

	// play menu buttons
	CCSprite* levelsBtnN;
	CCSprite* levelsBtnO;

	CCSprite* onlineBtnN;
	CCSprite* onlineBtnO;

	CCSprite* backBtnN;
	CCSprite* backBtnO;
	
};

