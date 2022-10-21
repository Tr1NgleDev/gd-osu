#include "CreditsLayer.h"
#include "Mouse.h"
#include <Windows.h>


bool touchAAAA;
bool prevTouchAAAA;

void CreditsLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

bool CreditsLayer::init()
{
	
	auto shDir = CCDirector::sharedDirector();
	
	size = shDir->getWinSize();
	view = shDir->getOpenGLView();

	bg = CCSprite::create("osuMenu/credits/bg.png");
	bg->setScaleX(size.width / bg->getContentSize().width + 0.05f);
	bg->setScaleY(size.height / bg->getContentSize().height + 0.05f);
	bg->setZOrder(-10);
	bg->setAnchorPoint({ 0.5f, 0.5f });
	bg->setPositionX(size.width / 2.f);
	bg->setPositionY(size.height / 2.f);
	bgStartPos = bg->getPosition();
	addChild(bg);

	// coords from photoshop lol. (height inverted since cocos2d uses left-bottom instead of left-top)
	tr1ngleDev = CCSprite::create("osuMenu/credits/Tr1NgleDev.png");
	tr1ngleDev->setZOrder(1);
	tr1ngleDev->setPosition({ 520.f / 1920.f * size.width, 747.f / 1080.f * size.height });
	addChild(tr1ngleDev);


	ppy = CCSprite::create("osuMenu/credits/ppy.png");
	ppy->setZOrder(1);
	ppy->setPosition({ 520.f / 1920.f * size.width, 333.f / 1080.f * size.height });
	addChild(ppy);


	andy = CCSprite::create("osuMenu/credits/andy.png");
	andy->setZOrder(1);
	andy->setPosition({ 1401.f / 1920.f * size.width, 747.f / 1080.f * size.height });
	addChild(andy);


	hjfod = CCSprite::create("osuMenu/credits/HJfod.png");
	hjfod->setZOrder(1);
	hjfod->setPosition({ 1401.f / 1920.f * size.width, 333.f / 1080.f * size.height });
	addChild(hjfod);

	setKeypadEnabled(true);
	setTouchEnabled(true);
	scheduleUpdate();
	CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444); // return to gd rgba4444
	return true;
}
void CreditsLayer::update(float delta) 
{
	touchAAAA = ((GetKeyState(VK_LBUTTON) & 0x8000) != 0);

	bg->setPositionX(lerpF(bg->getPosition().x, (bgStartPos.x - Mouse::getMousePositionC(view).x / size.width / 4.f), 5.5f * delta));
	bg->setPositionY(lerpF(bg->getPosition().y, (bgStartPos.y + Mouse::getMousePositionC(view).y / size.height / 4.f), 5.5f * delta));

	if (tr1ngleDev->boundingBox().containsPoint(Mouse::getMousePositionInS(view, size))) 
	{
		tr1ngleDev->setScale(lerpF(tr1ngleDev->getScale(), 1.1f, 6.f * delta));
		if (touchAAAA && !prevTouchAAAA) // pressed
			CCApplication::sharedApplication()->openURL("https://github.com/Tr1NgleDev");
	}
	else
		tr1ngleDev->setScale(lerpF(tr1ngleDev->getScale(), 1.f, 3.f * delta));

	if (ppy->boundingBox().containsPoint(Mouse::getMousePositionInS(view, size)))
	{
		ppy->setScale(lerpF(ppy->getScale(), 1.1f, 6.f * delta));
		if (touchAAAA && !prevTouchAAAA) // pressed
			CCApplication::sharedApplication()->openURL("https://osu.ppy.sh/home");
	}
	else
		ppy->setScale(lerpF(ppy->getScale(), 1.f, 3.f * delta));

	if (andy->boundingBox().containsPoint(Mouse::getMousePositionInS(view, size)))
	{
		andy->setScale(lerpF(andy->getScale(), 1.1f, 6.f * delta));
		if (touchAAAA && !prevTouchAAAA) // pressed
			CCApplication::sharedApplication()->openURL("https://github.com/iAndyHD3");
	}
	else
		andy->setScale(lerpF(andy->getScale(), 1.f, 3.f * delta));

	if (hjfod->boundingBox().containsPoint(Mouse::getMousePositionInS(view, size)))
	{
		hjfod->setScale(lerpF(hjfod->getScale(), 1.1f, 6.f * delta));
		if (touchAAAA && !prevTouchAAAA) // pressed
			CCApplication::sharedApplication()->openURL("https://github.com/HJfod");
	}
	else
		hjfod->setScale(lerpF(hjfod->getScale(), 1.f, 3.f * delta));

	prevTouchAAAA = touchAAAA;
}
CreditsLayer* CreditsLayer::create()
{
	CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA8888);
	auto a = new CreditsLayer();
	if (a && a->init())
	{
		a->autorelease();
		return a;
	}
	CC_SAFE_DELETE(a);
	return nullptr;
}