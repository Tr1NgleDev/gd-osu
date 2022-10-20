/*

	im not using CCMenu-s because its shit
	so im just making it "hard-coded" way

	also code is so shitty but i dont really care because it works.
	L
*/

#include "OsuMenuLayer.h"
#include "CreditsLayer.h"
#include "Mouse.h"

#define circlesBPM 184.0f
#define crotchet 60.f / circlesBPM

float songPos = 0.f;
int curStep;
int curBeat;

CCPoint oldMousePos;



bool touchAAA;
bool prevTouchAAA;

bool AABBCircleL(CCPoint c, float radius, CCPoint rp, CCPoint rs) 
{
	float tmpX = c.x;
	float tmpY = c.y;

	if (c.x < rp.x)         tmpX = rp.x;
	else if (c.x > rp.x + rs.x) tmpX = rp.x + rs.x;
	if (c.y < rp.y)         tmpY = rp.y;
	else if (c.y > rp.y + rs.y) tmpY = rp.y + rs.y;

	float dX = c.x - tmpX;
	float dY = c.y - tmpY;
	float d = sqrt((dX * dX) + (dY * dY));

	return d <= radius;
}

void OsuMenuLayer::syaNextTime() 
{
	inMainMenu = false;
	inPlayMenu = false;
	logoPos = logoStartPos;
	closingGame = true;
}
void OsuMenuLayer::keyBackClicked() 
{
	syaNextTime();
}
void OsuMenuLayer::createMainMenuButtons() 
{
	playBtnN = CCSprite::create("osuMenu/buttons/menu-button-play.png");
	playBtnO = CCSprite::create("osuMenu/buttons/menu-button-play-over.png");
	playBtnN->setAnchorPoint({ 0.f, 0.5f });
	playBtnO->setAnchorPoint({ 0.f, 0.5f });
	addChild(playBtnN);
	addChild(playBtnO);

	iconsBtnN = CCSprite::create("osuMenu/buttons/menu-button-icons.png");
	iconsBtnO = CCSprite::create("osuMenu/buttons/menu-button-icons-over.png");
	iconsBtnN->setAnchorPoint({ 0.f, 0.5f });
	iconsBtnO->setAnchorPoint({ 0.f, 0.5f });
	addChild(iconsBtnN);
	addChild(iconsBtnO);

	creditsBtnN = CCSprite::create("osuMenu/buttons/menu-button-credits.png");
	creditsBtnO = CCSprite::create("osuMenu/buttons/menu-button-credits-over.png");
	creditsBtnN->setAnchorPoint({ 0.f, 0.5f });
	creditsBtnO->setAnchorPoint({ 0.f, 0.5f });
	addChild(creditsBtnN);
	addChild(creditsBtnO);

	optionsBtnN = CCSprite::create("osuMenu/buttons/menu-button-options.png");
	optionsBtnO = CCSprite::create("osuMenu/buttons/menu-button-options-over.png");
	optionsBtnN->setAnchorPoint({ 0.f, 0.5f });
	optionsBtnO->setAnchorPoint({ 0.f, 0.5f });
	addChild(optionsBtnN);
	addChild(optionsBtnO);

	exitBtnN = CCSprite::create("osuMenu/buttons/menu-button-exit.png");
	exitBtnO = CCSprite::create("osuMenu/buttons/menu-button-exit-over.png");
	exitBtnN->setAnchorPoint({ 0.f, 0.5f });
	exitBtnO->setAnchorPoint({ 0.f, 0.5f });
	addChild(exitBtnN);
	addChild(exitBtnO);

	playBtnN->setOpacity(0);
	iconsBtnN->setOpacity(0);
	creditsBtnN->setOpacity(0);
	optionsBtnN->setOpacity(0);
	exitBtnN->setOpacity(0);

	playBtnO->setOpacity(0);
	iconsBtnO->setOpacity(0);
	creditsBtnO->setOpacity(0);
	optionsBtnO->setOpacity(0);
	exitBtnO->setOpacity(0);

	playBtnN->setPosition({ size.width / 2.75f - 30, size.height / 2 + playBtnN->getContentSize().height * 2.f });
	iconsBtnN->setPosition({ size.width / 2.75f - 15, size.height / 2 + iconsBtnN->getContentSize().height });
	creditsBtnN->setPosition({ size.width / 2.75f - 7.5f, size.height / 2 });
	optionsBtnN->setPosition({ size.width / 2.75f - 15, size.height / 2 - optionsBtnN->getContentSize().height });
	exitBtnN->setPosition({ size.width / 2.75f - 30, size.height / 2 - exitBtnN->getContentSize().height * 2.f });
}
bool OsuMenuLayer::init() 
{
	auto shDir = CCDirector::sharedDirector();
	size = shDir->getWinSize();
	view = shDir->getOpenGLView();

	auto soundManager = gd::GameSoundManager::sharedState();

	
	if (!gd::FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying() && openedBefore)
	{
		soundManager->stopBackgroundMusic();
		soundManager->playBackgroundMusic(true, "menuLoop.mp3");
		playing = true;
	}
	if(!openedBefore)
		soundManager->stopBackgroundMusic();
	if (gd::FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		playing = true;
	blur = new CCGLProgram();
	blur->initWithVertexShaderFilename("osuMenu/shaders/vertex.vsh", "osuMenu/shaders/blur.fsh");
	blur->addAttribute("a_position", 0);
	blur->addAttribute("a_color", 1u);
	blur->addAttribute("a_texCoord", 2u);
	blur->link();
	blur->updateUniforms();
	blur->setUniformLocationWith1f(blur->getUniformLocationForName("blurRadius"), 0.25f);
	CCShaderCache::sharedShaderCache()->addProgram(blur, "blur_sh");

	flashGradient = new CCGLProgram();
	flashGradient->initWithVertexShaderFilename("osuMenu/shaders/vertex.vsh", "osuMenu/shaders/flash.fsh");
	flashGradient->addAttribute("a_position", 0);
	flashGradient->addAttribute("a_color", 1u);
	flashGradient->addAttribute("a_texCoord", 2u);
	flashGradient->link();
	flashGradient->updateUniforms();
	CCShaderCache::sharedShaderCache()->addProgram(flashGradient, "flashGradient_sh");

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

	CCSprite* flash = CCSprite::create("square.png");
	flash->setScaleX(size.width / flash->getContentSize().width);
	flash->setScaleY(size.height / flash->getContentSize().height);
	flash->setZOrder(20);
	flash->setAnchorPoint({ 0, 0 });
	flash->setShaderProgram(flashGradient);
	addChild(flash);


	ppy = CCSprite::create("osuMenu/ppy.png");
	ppy->setZOrder(100);
	ppy->setAnchorPoint({ 0, 0 });
	ppy->setScale(1.1f);

	addChild(ppy);

	tr1ngle = CCSprite::create("osuMenu/tr1ngle.png");
	tr1ngle->setZOrder(101);
	tr1ngle->setAnchorPoint({ 1, 0 });
	tr1ngle->setScale(1.1f);
	tr1ngle->setPositionX(size.width);

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
	logoPos = logo->getPosition();
	logoStartPos = logoPos;
	addChild(logo);

	blackBG = CCSprite::create("square.png");
	auto bgSz = blackBG->getContentSize();
	blackBG->setScaleX(size.width / bgSz.width);
	blackBG->setScaleY(size.height / bgSz.height);
	blackBG->setZOrder(50);
	blackBG->setAnchorPoint({ 0, 0 });
	blackBG->setColor({ 0, 0, 0 });
	addChild(blackBG);

	if (openedBefore)
		blackBG->setOpacity(0);

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

	createMainMenuButtons();
	//createPlayMenuButtons();
	
	setKeypadEnabled(true);
	setTouchEnabled(true);

	scheduleUpdate();

	openedBefore = true;
	CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444); // return to gd rgba4444
	return true;
}

void OsuMenuLayer::beatHit()
{
	logo->setScale(logoScale + 0.075f);

	if (curBeat == 40 - 3)
	{
		flash_leftValue = 0.5f;
		flash_rightValue = 0.5f;
	}
	if (curBeat >= 44 - 3 && curBeat != 75 - 3 && curBeat != 76 - 3)
	{
		flashSkullEmoji = !flashSkullEmoji;
		if (flashSkullEmoji)
			flash_leftValue = 0.7f;
		else
			flash_rightValue = 0.7f;
	}
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
bool playingSeeyaNextTime;

void OsuMenuLayer::update(float delta) 
{
	playBtnO->setPosition(playBtnN->getPosition());
	iconsBtnO->setPosition(iconsBtnN->getPosition());
	creditsBtnO->setPosition(creditsBtnN->getPosition());
	optionsBtnO->setPosition(optionsBtnN->getPosition());
	exitBtnO->setPosition(exitBtnN->getPosition());

	if (inMainMenu && !inPlayMenu) 
	{
		playBtnO->setOpacity(255 - playBtnN->getOpacity());
		iconsBtnO->setOpacity(255 - iconsBtnN->getOpacity());
		creditsBtnO->setOpacity(255 - creditsBtnN->getOpacity());
		optionsBtnO->setOpacity(255 - optionsBtnN->getOpacity());
		exitBtnO->setOpacity(255 - exitBtnN->getOpacity());
	}

	touchAAA = ((GetKeyState(VK_LBUTTON) & 0x8000) != 0);
	if (blackBG->getOpacity() >= 200)
		touchAAA = false;
	flashGradient->use();
	if (!playing)
		timer += delta;
	else
		timer = 0.0;
	if(!gd::FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	if (timer > 0.7f) 
	{
		gd::GameSoundManager::sharedState()->playBackgroundMusic(true, "menuLoop.mp3");
		
		playing = true;
	}

	if (playing)
		songPos += delta;
		
	bg->setPositionX(lerpF(bg->getPosition().x, (bgStartPos.x -  Mouse::getMousePositionC(view).x / size.width), 5.5f * delta));
	bg->setPositionY(lerpF(bg->getPosition().y, (bgStartPos.y +  Mouse::getMousePositionC(view).y / size.height), 5.5f * delta));

	logo->setPositionX(lerpF(logo->getPosition().x, (logoPos.x -  Mouse::getMousePositionC(view).x / size.width), 15.f * delta));
	logo->setPositionY(lerpF(logo->getPosition().y, (logoPos.y +  Mouse::getMousePositionC(view).y / size.height), 15.f * delta));
	logoT->setPosition(logoT->getPosition().lerp(logo->getPosition(), 6.f * delta));

	logo->setScale(lerpF(logo->getScale(), logoScale, 8.f * delta));

	flash_leftValue = lerpF(flash_leftValue, 0.0f, 2.f * delta);
	flash_rightValue = lerpF(flash_rightValue, 0.0f, 2.f * delta);

	int oldStep = curStep;
	stepUpdate();
	beatUpdate();
	if (oldStep != curStep && curStep > 0)
		stepHit();

	if (oldMousePos.x ==  Mouse::getMousePositionC(view).x && oldMousePos.y ==  Mouse::getMousePositionC(view).y)
		timer2 += delta;
	else
		timer2 = 0;

	if (timer2 > 6.f)
	{
		if(logoPos.x == logoStartPos.x && logoPos.y == logoStartPos.y)
			alphaA = (int)clampf(lerpF((float)alphaA, 0.0f, 0.001f * delta), 0, 255);
		else
		{
			timer2 = 0.f;
			logoPos = logoStartPos;
			inMainMenu = false;
			inPlayMenu = false;
		}
	}
	else
		alphaA = (int)clampf(lerpF((float)alphaA, 255.0f, 7.0f * delta), 0, 255);

	shittyLines->setOpacity((int)((float)alphaA / 2.0f));
	ppy->setOpacity(alphaA);
	tr1ngle->setOpacity(alphaA);
	if (ppy->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
	{
		ccColor3B targetColor = { 255, 255, 100 };
		ppy->setColor(lerpColor3(ppy->getColor(), targetColor, 6.0f * delta));
		if (touchAAA && !prevTouchAAA)
			CCApplication::sharedApplication()->openURL("https://osu.ppy.sh/home");

		ppy->setScale(lerpF(ppy->getScale(), 1.15f, 6.0f * delta));
	}
	else 
	{
		ccColor3B targetColor = { 255, 255, 255 };
		ppy->setColor(lerpColor3(ppy->getColor(), targetColor, 8.0f * delta));
		ppy->setScale(lerpF(ppy->getScale(), 1.1f, 8.0f * delta));
	}

	if (tr1ngle->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
	{
		ccColor3B targetColor = { 255, 255, 100 };
		tr1ngle->setColor(lerpColor3(tr1ngle->getColor(), targetColor, 7.0f * delta));
		if (touchAAA && !prevTouchAAA)
			CCApplication::sharedApplication()->openURL("https://github.com/Tr1NgleDev");
		tr1ngle->setScale(lerpF(tr1ngle->getScale(), 1.15f, 6.0f * delta));
	}
	else
	{
		ccColor3B targetColor = { 255, 255, 255 };
		tr1ngle->setColor(lerpColor3(tr1ngle->getColor(), targetColor, 7.0f * delta));
		tr1ngle->setScale(lerpF(tr1ngle->getScale(), 1.1f, 8.0f * delta));
	}
	if (!closingGame) 
	{
		if (AABBCircleL(logoPos, logo->getContentSize().width / 2.f * 0.9f,  Mouse::getMousePositionInS(view, size), {1, 1})) // touch logo
		{
			logoScale = 1.025f;
			if (touchAAA && !prevTouchAAA) 
			{
				if (!inMainMenu && !inPlayMenu) 
				{
					inMainMenu = true;
					touchAAA = true;
					prevTouchAAA = true;
				}
				else
				{
					if (inMainMenu && !inPlayMenu) 
					{
						inPlayMenu = true;
						touchAAA = true;
						prevTouchAAA = true;
					}
						
					else
						if (inMainMenu && inPlayMenu) 
						{
							debugCOUT("open robtop levels");
							auto scene = CCScene::create();
							auto laye = gd::LevelSelectLayer::create(0);
							scene->addChild(laye);
							CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
						}
							
				}
				debugCOUT(inMainMenu << " | " << inPlayMenu);
			}	
		}
		else
			logoScale = 0.95f;
	}	
	if (inMainMenu)
		logoPos = logoStartPos - CCPoint{ logo->getContentSize().width / 3.f, 0 };
	else
		logoPos = logoStartPos;
	if (inMainMenu && !inPlayMenu) 
	{
		bool touchingLogoL = AABBCircleL(logoPos, logo->getContentSize().width / 2.f * 0.9f,  Mouse::getMousePositionInS(view, size), { 1, 1 });
		
		if(!playBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
			playBtnN->setOpacity((int)clampf(lerpF((float)playBtnN->getOpacity(), 255.0f, 10.f * delta), 0, 255));
		else if (!touchingLogoL && playBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size))) 
		{
			playBtnN->setOpacity((int)clampf(lerpF((float)playBtnN->getOpacity(), 0.0f, 15.f * delta), 0, 255));
			if (touchAAA && !prevTouchAAA) // pressed
			{
				// do action L
				inPlayMenu = true;
			}
		}
			
		
		if (!iconsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
			iconsBtnN->setOpacity((int)clampf(lerpF((float)iconsBtnN->getOpacity(), 255.0f, 10.f * delta), 0, 255));
		else if (!touchingLogoL && iconsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size))) 
		{
			iconsBtnN->setOpacity((int)clampf(lerpF((float)iconsBtnN->getOpacity(), 0.0f, 15.f * delta), 0, 255));
			if (touchAAA && !prevTouchAAA) // pressed
			{
				// do action L
				auto scene = CCScene::create();
				auto laye = gd::GJGarageLayer::create();
				scene->addChild(laye);
				CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
			}
		}
			
		
		if (!creditsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
			creditsBtnN->setOpacity((int)clampf(lerpF((float)creditsBtnN->getOpacity(), 255.0f, 10.f * delta), 0, 255));
		else if (!touchingLogoL && creditsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size))) 
		{
			creditsBtnN->setOpacity((int)clampf(lerpF((float)creditsBtnN->getOpacity(), 0.0f, 15.f * delta), 0, 255));
			if (touchAAA && !prevTouchAAA) // pressed
			{
				// do action L
				auto scene = CCScene::create();
				auto laye = CreditsLayer::create();
				scene->addChild(laye);
				CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
			}
		}
			
		
		if (!optionsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
			optionsBtnN->setOpacity((int)clampf(lerpF((float)optionsBtnN->getOpacity(), 255.0f, 10.f * delta), 0, 255));
		else if (!touchingLogoL && optionsBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size))) 
		{
			optionsBtnN->setOpacity((int)clampf(lerpF((float)optionsBtnN->getOpacity(), 0.0f, 15.f * delta), 0, 255));
			if (touchAAA && !prevTouchAAA) // pressed
			{
				// do action L
				
			}
		}
			
		
		if (!exitBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size)))
			exitBtnN->setOpacity((int)clampf(lerpF((float)exitBtnN->getOpacity(), 255.0f, 10.f * delta), 0, 255));
		else if (!touchingLogoL && exitBtnN->boundingBox().containsPoint( Mouse::getMousePositionInS(view, size))) 
		{
			exitBtnN->setOpacity((int)clampf(lerpF((float)exitBtnN->getOpacity(), 0.0f, 15.f * delta), 0, 255));
			if (touchAAA && !prevTouchAAA) // pressed
			{
				// do action L
				syaNextTime();
			}
		}
			
	}
	else
	{
		playBtnN->setOpacity((int)clampf(lerpF((float)playBtnN->getOpacity(), 0.0f, 8.f * delta), 0, 255));
		iconsBtnN->setOpacity((int)clampf(lerpF((float)iconsBtnN->getOpacity(), 0.0f, 8.f * delta), 0, 255));
		creditsBtnN->setOpacity((int)clampf(lerpF((float)creditsBtnN->getOpacity(), 0.0f, 8.f * delta), 0, 255));
		optionsBtnN->setOpacity((int)clampf(lerpF((float)optionsBtnN->getOpacity(), 0.0f, 8.f * delta), 0, 255));
		exitBtnN->setOpacity((int)clampf(lerpF((float)exitBtnN->getOpacity(), 0.0f, 8.f * delta), 0, 255));

		playBtnO->setOpacity(playBtnN->getOpacity());
		iconsBtnO->setOpacity(iconsBtnN->getOpacity());
		creditsBtnO->setOpacity(creditsBtnN->getOpacity());
		optionsBtnO->setOpacity(optionsBtnN->getOpacity());
		exitBtnO->setOpacity(exitBtnN->getOpacity());
	}

	oldMousePos =  Mouse::getMousePositionC(view);

	flashGradient->setUniformLocationWith1f(flashGradient->getUniformLocationForName("leftValue"), flash_leftValue);
	flashGradient->setUniformLocationWith1f(flashGradient->getUniformLocationForName("rightValue"), flash_rightValue);


	if (closingGame) 
	{
		if (!playingSeeyaNextTime) 
		{
			gd::GameSoundManager::playSound("osuMenu/seeya.ogg");
			playingSeeyaNextTime = true;
			blackBG->stopAllActions();
			blackBG->runAction(CCSequence::create(
				CCSpawn::create(
					CCEaseInOut::create(
						CCFadeTo::create(3, 255), 4.
					),
					nullptr
				),
				nullptr
			));
		}
			
		closeTimer += delta;
		
		logoScale = lerpF(logoScale, 0.2f, delta / 4.f);
		logoT->setScale(lerpF(logoT->getScale(), 0.3f, delta / 4.f));

		logo->setRotation(lerpF(logo->getRotation(), 10.f, delta / 4.f));
		logoT->setRotation(lerpF(logoT->getRotation(), 10.f, delta / 4.f));
		

		if (closeTimer > 3.1f) 
			exit(0);
	}

	prevTouchAAA = touchAAA;
}
OsuMenuLayer* OsuMenuLayer::create() 
{
	CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA8888);
	auto a = new OsuMenuLayer();
	if (a && a->init()) 
	{
		a->autorelease();
		return a;
	}
	CC_SAFE_DELETE(a);
	return nullptr;
}
