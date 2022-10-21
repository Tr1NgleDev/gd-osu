#pragma once
#include "pch.h"

class RewardsPage : public gd::FLAlertLayer
{
public:
	static RewardsPage* create() {
		return reinterpret_cast<RewardsPage * (__fastcall*)()>(
			gd::base + 0x217850
			)();
	}
};