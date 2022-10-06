#include "OsuMenuLayer.h"

#define circlesBPM 184.0f
#define crotchet 60.f / circlesBPM

CCSprite* bg;
CCPoint bgStartPos;

CCSprite* logo;
CCSprite* logoT;
CCPoint logoStartPos;

CCSprite* shittyLines;
CCSprite* ppy;
CCSprite* tr1ngle;

CCSize size;
CCEGLView* view;

float logoScale = 0.95f;

CCPoint oldMousePos;

CCPoint getMousePosition()
{
	return { view->m_fMouseX,view->m_fMouseY };
}
CCPoint getMousePositionC()
{
	return (getMousePosition() - view->getFrameSize() / 2.f) * 2.f;
}

void OsuMenuLayer::keyBackClicked() 
{
	//syaNextTime();
}
bool OsuMenuLayer::init() 
{
	auto shDir = CCDirector::sharedDirector();
	size = shDir->getWinSize();
	view = shDir->getOpenGLView();

	auto soundManager = gd::GameSoundManager::sharedState();
	soundManager->stopBackgroundMusic();
	
	
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
	bg->setPositionX(bg->getPositionX() - 20);
	bg->setPositionY(bg->getPositionY() - 20);
	bgStartPos = bg->getPosition();
	bg->setShaderProgram(blur);
	addChild(bg);


	ppy = CCSprite::create("osuMenu/ppy.png");
	ppy->setZOrder(100);
	ppy->setAnchorPoint({ 0, 0 });
	ppy->setScale(1.1f);

	addChild(ppy);

	tr1ngle = CCSprite::create("osuMenu/tr1ngle.png");
	tr1ngle->setZOrder(101);
	tr1ngle->setAnchorPoint({ 0, 0 });
	tr1ngle->setScale(1.1f);
	tr1ngle->setPositionX(size.width - tr1ngle->getContentSize().width - 10);

	addChild(tr1ngle);

	shittyLines = CCSprite::create("osuMenu/linesL.png");
	shittyLines->setScaleX(size.width / shittyLines->getContentSize().width);
	shittyLines->setScaleY(size.height / shittyLines->getContentSize().height);
	shittyLines->setZOrder(99);
	shittyLines->setAnchorPoint({ 0, 0 });
	shittyLines->setOpacity(125);
	addChild(shittyLines);

	logoT = CCSprite::create("osuMenu/gdlogo.png");
	logoT->setZOrder(10);
	logoT->setScale(logoScale + 0.025f);
	logoT->setOpacity(40);
	logoT->setPosition(scrCenterA(size));
	addChild(logoT);

	logo = CCSprite::create("osuMenu/gdlogo.png");
	logo->setZOrder(9);
	logo->setPosition(scrCenterA(size));
	logo->setScale(logoScale);
	logoStartPos = logo->getPosition();
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
float timer = 0;
float timer2 = 0;
int alphaA = 255;
void OsuMenuLayer::beatHit()
{
	logo->setScale(logoScale + 0.075f);
}
void OsuMenuLayer::stepHit()
{
	if (curStep % 4 == 0)
		beatHit();
}
void OsuMenuLayer::beatUpdate()
{
	curBeat = (int)floor((float)curStep / 4.f);
}
void OsuMenuLayer::stepUpdate()
{
	curStep = (int)floor(songPos / (crotchet / 4.f));
}
void OsuMenuLayer::update(float delta) 
{
	if (!playing)
		timer += delta;
	else
		timer = 0.0;

	if (timer > 0.7f) 
	{
		gd::GameSoundManager::sharedState()->playBackgroundMusic(true, "osuMenu/circles.ogg");
		
		playing = true;
	}

	if (playing)
		songPos += delta;
		
	bg->setPositionX(lerpF(bg->getPosition().x, (bgStartPos.x - getMousePositionC().x / size.width), 5.5f * delta));
	bg->setPositionY(lerpF(bg->getPosition().y, (bgStartPos.y + getMousePositionC().y / size.height), 5.5f * delta));

	logo->setPositionX(lerpF(logo->getPosition().x, (logoStartPos.x - getMousePositionC().x / size.width), 7.f * delta));
	logo->setPositionY(lerpF(logo->getPosition().y, (logoStartPos.y + getMousePositionC().y / size.height), 7.f * delta));

	logoT->setPosition(logoT->getPosition().lerp(logo->getPosition(), 6.f * delta));

	logo->setScale(lerpF(logo->getScale(), logoScale, 8.f * delta));

	int oldStep = curStep;
	stepUpdate();
	beatUpdate();
	if (oldStep != curStep && curStep > 0)
		stepHit();

	if (oldMousePos.x == getMousePositionC().x && oldMousePos.y == getMousePositionC().y)
		timer2 += delta;
	else
		timer2 = 0;

	if (timer2 > 6.f)
	{
		alphaA = (int)clampf(lerpF((float)alphaA, 0.0f, 0.001f * delta), 0, 255);
	}
	else
		alphaA = (int)clampf(lerpF((float)alphaA, 255.0f, 7.0f * delta), 0, 255);

	shittyLines->setOpacity((int)((float)alphaA / 2.0f));
	ppy->setOpacity(alphaA);
	tr1ngle->setOpacity(alphaA);

	if (CCRect(-640, -640, 640 * 2, 640 * 2).containsPoint(getMousePositionC())) // touch logo
	{
		logoScale = 1.025f;
	}
	else
		logoScale = 0.95f;
		

	oldMousePos = getMousePositionC();
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
