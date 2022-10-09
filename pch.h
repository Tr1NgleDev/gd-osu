#ifndef  PCH_H
#define PCH_H

#include <gd.h>
#include <MinHook.h>
#include <cocos2d.h>

using namespace cocos2d;

#define DEBUG

#define lerpF(a, b, ratio) (a * (1.f - ratio) + b * ratio)
#define lerpColor3(start, target, ratio) { (unsigned char)(int)clampf(lerpF((float)start.r, (float)target.r, ratio), 0, 255), (unsigned char)(int)clampf(lerpF((float)start.g, (float)target.g, ratio), 0, 255), (unsigned char)(int)clampf(lerpF((float)start.b, (float)target.b, ratio), 0.0f, 255.0f) }
#define scrCenter(a, b) { a.width / 2.0f - b.width / 2.0f, a.height / 2.0f - b.height / 2.0f }
#define scrCenterA(a) { a.width / 2.0f, a.height / 2.0f }
#ifdef DEBUG
#define debugCOUT(a) std::cout << a << "\n";
#else
#define debugCOUT(a)
#endif
#endif // ! PCH_H
