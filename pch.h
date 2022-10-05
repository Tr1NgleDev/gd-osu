#ifndef  PCH_H
#define PCH_H

#include <gd.h>
#include <MinHook.h>
#include <cocos2d.h>

using namespace cocos2d;

#define CONSOLE

#define lerp(a, b, ratio) (a * (1.f - ratio) + b * ratio)
#define scrCenter(a, b) { a.width / 2.0f - b.width / 2.0f, a.height / 2.0f - b.height / 2.0f }
#define scrCenterA(a) { a.width / 2.0f, a.height / 2.0f }

#endif // ! PCH_H
