#include "OsuMenuLayer.h"
CCSprite* bg;
CCPoint bgStartPos;
CCSprite* logo;
void OsuMenuLayer::keyBackClicked() 
{
	//syaNextTime();
}
bool OsuMenuLayer::init() 
{

	auto shDir = CCDirector::sharedDirector();
	auto size = shDir->getWinSize();

	auto soundManager = gd::GameSoundManager::sharedState();

	CCGLProgram* blur = new CCGLProgram();
	blur->initWithVertexShaderFilename("osuMenu/vertex.vsh", "osuMenu/blur.fsh");
	blur->addAttribute("a_position", 0);
	blur->addAttribute("a_color", 1u);
	blur->addAttribute("a_texCoord", 2u);
	blur->link();
	blur->updateUniforms();
	blur->setUniformLocationWith1f(blur->getUniformLocationForName("blurRadius"), 0.5f);
	
	
	bg = CCSprite::create("game_bg_20_001-uhd.png");
	
	bg->setScaleX(size.width / bg->getContentSize().width + 0.2f);
	bg->setScaleY(size.height / bg->getContentSize().height + 0.2f);
	bg->setZOrder(-10);
	bg->setAnchorPoint({ 0, 0 });
	bgStartPos = bg->getPosition();
	bg->setShaderProgram(blur);
	addChild(bg);


	CCSprite* ppy = CCSprite::create("osuMenu/ppy.png");
	ppy->setZOrder(100);
	ppy->setAnchorPoint({ 0, 0 });
	ppy->setScale(1.1f);

	addChild(ppy);

	CCSprite* tr1ngle = CCSprite::create("osuMenu/tr1ngle.png");
	tr1ngle->setZOrder(101);
	tr1ngle->setAnchorPoint({ 0, 0 });
	tr1ngle->setScale(1.1f);
	tr1ngle->setPositionX(size.width - tr1ngle->getContentSize().width - 10);

	addChild(tr1ngle);

	CCSprite* shittyLines = CCSprite::create("osuMenu/linesL.png");
	shittyLines->setScaleX(size.width / shittyLines->getContentSize().width);
	shittyLines->setScaleY(size.height / shittyLines->getContentSize().height);
	shittyLines->setZOrder(99);
	shittyLines->setAnchorPoint({ 0, 0 });
	shittyLines->setOpacity(125);
	addChild(shittyLines);

	CCSprite* logoT = CCSprite::create("osuMenu/gdlogo.png");
	logoT->setZOrder(10);
	logoT->setScale(0.975f);
	logoT->setOpacity(40);
	logoT->setPosition(scrCenterA(size));
	addChild(logoT);

	logo = CCSprite::create("osuMenu/gdlogo.png");
	logo->setZOrder(9);
	logo->setPosition(scrCenterA(size));
	logo->setScale(0.95f);
	addChild(logo);

	CCSprite* blackBG = CCSprite::create("square.png");
	auto bgSz = blackBG->getContentSize();
	blackBG->setScaleX(size.width / bgSz.width);
	blackBG->setScaleY(size.height / bgSz.height);
	blackBG->setZOrder(50);
	blackBG->setAnchorPoint({ 0, 0 });
	blackBG->setColor({ 0, 0, 0 });
	addChild(blackBG);


	if (!openedBefore) 
	{
		soundManager->stopBackgroundMusic();
		soundManager->playSound("osuMenu/welcome.ogg");
		CCSprite* welcome = CCSprite::create("osuMenu/welcome_text.png");
		welcome->setZOrder(51);
		welcome->setOpacity(0);
		welcome->setAnchorPoint({ 0, 0 });
		welcome->setPosition(scrCenter(size, welcome->getContentSize()));
		welcome->setScaleY(0.0f);

		addChild(welcome);

		welcome->runAction(CCSequence::create(
			CCDelayTime::create(.0),
			CCSpawn::create(
				CCEaseExponentialOut::create(
					CCScaleTo::create(2, 1)
				),
				CCEaseExponentialOut::create(
					CCFadeTo::create(2, 255)
				),
				nullptr
			),
			nullptr
		));
		blackBG->runAction(CCSequence::create(
			CCDelayTime::create(2.),
			CCSpawn::create(
				CCEaseInOut::create(
					CCFadeTo::create(.5, 0), 4.
				),
				nullptr
			),
			nullptr
		));
		welcome->runAction(CCSequence::create(
			CCDelayTime::create(2.1),
			CCSpawn::create(
				CCEaseInOut::create(
					CCFadeTo::create(.5, 0), 4.
				),
				nullptr
			),
			nullptr
		));
	}
	
	setKeypadEnabled(true);
	setTouchEnabled(true);

	scheduleUpdate();

	openedBefore = true;

	return true;
}
void OsuMenuLayer::update(float delta) 
{
}
OsuMenuLayer* OsuMenuLayer::create() 
{
	auto a = new OsuMenuLayer();
	if (a && a->init()) 
	{
		a->autorelease();
		return a;
	}
	CC_SAFE_DELETE(a);
	return nullptr;
}
