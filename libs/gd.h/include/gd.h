#ifndef __GD_H__
#define __GD_H__

#include <cocos2d.h>
#include <cocos-ext.h>

#include "gdMacros.h"

namespace gd {
	inline auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

	inline bool init() {
		static_assert(sizeof(std::string) == 24,
			"\n[GD.H] std::string is not 24 bytes\n" \
			"[GD.H] Any classes containing member strings or using strings in functions will break!\n" \
			"[GD.H] this is caused by building in Debug mode, to fix switch to Release\n");
		return base;
	}
}
#define FMOD_TIMEUNIT_MS 0x00000001
#define FMOD_TIMEUNIT_PCM 0x00000002
#define FMOD_TIMEUNIT_PCMBYTES 0x00000004
#define FMOD_TIMEUNIT_RAWBYTES 0x00000008
#define FMOD_TIMEUNIT_PCMFRACTION 0x00000010
#define FMOD_TIMEUNIT_MODORDER 0x00000100
#define FMOD_TIMEUNIT_MODROW 0x00000200
#define FMOD_TIMEUNIT_MODPATTERN 0x00000400
enum FMOD_RESULT {
	FMOD_OK,
	FMOD_ERR_BADCOMMAND,
	FMOD_ERR_CHANNEL_ALLOC,
	FMOD_ERR_CHANNEL_STOLEN,
	FMOD_ERR_DMA,
	FMOD_ERR_DSP_CONNECTION,
	FMOD_ERR_DSP_DONTPROCESS,
	FMOD_ERR_DSP_FORMAT,
	FMOD_ERR_DSP_INUSE,
	FMOD_ERR_DSP_NOTFOUND,
	FMOD_ERR_DSP_RESERVED,
	FMOD_ERR_DSP_SILENCE,
	FMOD_ERR_DSP_TYPE,
	FMOD_ERR_FILE_BAD,
	FMOD_ERR_FILE_COULDNOTSEEK,
	FMOD_ERR_FILE_DISKEJECTED,
	FMOD_ERR_FILE_EOF,
	FMOD_ERR_FILE_ENDOFDATA,
	FMOD_ERR_FILE_NOTFOUND,
	FMOD_ERR_FORMAT,
	FMOD_ERR_HEADER_MISMATCH,
	FMOD_ERR_HTTP,
	FMOD_ERR_HTTP_ACCESS,
	FMOD_ERR_HTTP_PROXY_AUTH,
	FMOD_ERR_HTTP_SERVER_ERROR,
	FMOD_ERR_HTTP_TIMEOUT,
	FMOD_ERR_INITIALIZATION,
	FMOD_ERR_INITIALIZED,
	FMOD_ERR_INTERNAL,
	FMOD_ERR_INVALID_FLOAT,
	FMOD_ERR_INVALID_HANDLE,
	FMOD_ERR_INVALID_PARAM,
	FMOD_ERR_INVALID_POSITION,
	FMOD_ERR_INVALID_SPEAKER,
	FMOD_ERR_INVALID_SYNCPOINT,
	FMOD_ERR_INVALID_THREAD,
	FMOD_ERR_INVALID_VECTOR,
	FMOD_ERR_MAXAUDIBLE,
	FMOD_ERR_MEMORY,
	FMOD_ERR_MEMORY_CANTPOINT,
	FMOD_ERR_NEEDS3D,
	FMOD_ERR_NEEDSHARDWARE,
	FMOD_ERR_NET_CONNECT,
	FMOD_ERR_NET_SOCKET_ERROR,
	FMOD_ERR_NET_URL,
	FMOD_ERR_NET_WOULD_BLOCK,
	FMOD_ERR_NOTREADY,
	FMOD_ERR_OUTPUT_ALLOCATED,
	FMOD_ERR_OUTPUT_CREATEBUFFER,
	FMOD_ERR_OUTPUT_DRIVERCALL,
	FMOD_ERR_OUTPUT_FORMAT,
	FMOD_ERR_OUTPUT_INIT,
	FMOD_ERR_OUTPUT_NODRIVERS,
	FMOD_ERR_PLUGIN,
	FMOD_ERR_PLUGIN_MISSING,
	FMOD_ERR_PLUGIN_RESOURCE,
	FMOD_ERR_PLUGIN_VERSION,
	FMOD_ERR_RECORD,
	FMOD_ERR_REVERB_CHANNELGROUP,
	FMOD_ERR_REVERB_INSTANCE,
	FMOD_ERR_SUBSOUNDS,
	FMOD_ERR_SUBSOUND_ALLOCATED,
	FMOD_ERR_SUBSOUND_CANTMOVE,
	FMOD_ERR_TAGNOTFOUND,
	FMOD_ERR_TOOMANYCHANNELS,
	FMOD_ERR_TRUNCATED,
	FMOD_ERR_UNIMPLEMENTED,
	FMOD_ERR_UNINITIALIZED,
	FMOD_ERR_UNSUPPORTED,
	FMOD_ERR_VERSION,
	FMOD_ERR_EVENT_ALREADY_LOADED,
	FMOD_ERR_EVENT_LIVEUPDATE_BUSY,
	FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH,
	FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT,
	FMOD_ERR_EVENT_NOTFOUND,
	FMOD_ERR_STUDIO_UNINITIALIZED,
	FMOD_ERR_STUDIO_NOT_LOADED,
	FMOD_ERR_INVALID_STRING,
	FMOD_ERR_ALREADY_LOCKED,
	FMOD_ERR_NOT_LOCKED,
	FMOD_ERR_RECORD_DISCONNECTED,
	FMOD_ERR_TOOMANYSAMPLES
};
namespace FMOD 
{
	class System;
	class Sound;
	class Channel 
	{
	public:
		FMOD_RESULT getPosition(unsigned int* result, int timeUnit)
		{
			const auto addr = GetProcAddress(GetModuleHandleA("fmod.dll"), "?getPosition@Channel@FMOD@@QAG?AW4FMOD_RESULT@@PAII@Z");
			return reinterpret_cast<FMOD_RESULT(__thiscall*)(FMOD::Channel*, unsigned int*, int)>(
				addr
				)(this, result, timeUnit);
		}
	};
	class ChannelControl{};
	class DSP;
}



#include "GDProtocols.h"

#include "delegates/delegates.h"

#include "actions/CCCircleWave.h"

#include "achievement_nodes/AchievementBar.h"
#include "achievement_nodes/AchievementNotifier.h"

#include "menu_nodes/CCMenuItemSpriteExtra.h"
#include "menu_nodes/CCMenuItemToggler.h"
#include "menu_nodes/Slider.h"
#include "menu_nodes/InfoAlertButton.h"

#include "manager_nodes/GManager.h"
#include "manager_nodes/GameManager.h"
#include "manager_nodes/GameStatsManager.h"
#include "manager_nodes/GameSoundManager.h"
#include "manager_nodes/GameLevelManager.h"
#include "manager_nodes/AchievementManager.h"
#include "manager_nodes/GJUserScore.h"
#include "manager_nodes/GJAccountManager.h"
#include "manager_nodes/GJEffectManager.h"
#include "manager_nodes/MusicDownloadManager.h"
#include "manager_nodes/ObjectToolbox.h"
#include "manager_nodes/LocalLevelManager.h"

#include "scroll_nodes/CCContentLayer.h"
#include "scroll_nodes/CCIndexPath.h"
#include "scroll_nodes/CCScrollLayerExt.h"
#include "scroll_nodes/TableView.h"
#include "scroll_nodes/BoomListView.h"
#include "scroll_nodes/CustomListView.h"
#include "scroll_nodes/ScrollingLayer.h"

#include "layers_scenes_transitions_nodes/CCNodeContainer.h"
#include "layers_scenes_transitions_nodes/OBB2D.h"
#include "layers_scenes_transitions_nodes/FLAlertLayer.h"
#include "layers_scenes_transitions_nodes/GJDropDownLayer.h"
#include "layers_scenes_transitions_nodes/GJListLayer.h"
#include "layers_scenes_transitions_nodes/LoadingLayer.h"
#include "layers_scenes_transitions_nodes/MenuLayer.h"
#include "layers_scenes_transitions_nodes/TextAlertPopup.h"
#include "layers_scenes_transitions_nodes/LoadingCircle.h"
#include "layers_scenes_transitions_nodes/CCBlockLayer.h"
#include "layers_scenes_transitions_nodes/PauseLayer.h"
#include "layers_scenes_transitions_nodes/GJBaseGameLayer.h"
#include "layers_scenes_transitions_nodes/PlayLayer.h"
#include "layers_scenes_transitions_nodes/LevelEditorLayer.h"
#include "layers_scenes_transitions_nodes/EditorUI.h"
#include "layers_scenes_transitions_nodes/NumberInputLayer.h"
#include "layers_scenes_transitions_nodes/SetIDPopup.h"
#include "layers_scenes_transitions_nodes/CustomSongWidget.h"
#include "layers_scenes_transitions_nodes/CustomSongLayer.h"
#include "layers_scenes_transitions_nodes/SongInfoLayer.h"
#include "layers_scenes_transitions_nodes/GJSpecialColorSelect.h"
#include "layers_scenes_transitions_nodes/HSVWidgetPopup.h"
#include "layers_scenes_transitions_nodes/GJScaleControl.h"
#include "layers_scenes_transitions_nodes/GJRotationControl.h"
#include "layers_scenes_transitions_nodes/SetGroupIDLayer.h"
#include "layers_scenes_transitions_nodes/ProfilePage.h"
#include "layers_scenes_transitions_nodes/LevelInfoLayer.h"
#include "layers_scenes_transitions_nodes/LevelBrowserLayer.h"
#include "layers_scenes_transitions_nodes/CustomizeObjectLayer.h"
#include "layers_scenes_transitions_nodes/ListButtonBar.h"
#include "layers_scenes_transitions_nodes/DialogLayer.h"
#include "layers_scenes_transitions_nodes/GaragePage.h"
#include "layers_scenes_transitions_nodes/GJGarageLayer.h"
#include "layers_scenes_transitions_nodes/CreateGuidelinesLayer.h"
#include "layers_scenes_transitions_nodes/VideoOptionsLayer.h"
#include "layers_scenes_transitions_nodes/SetupPulsePopup.h"
#include "layers_scenes_transitions_nodes/ColorSelectPopup.h"
#include "layers_scenes_transitions_nodes/MoreOptionsLayer.h"
#include "layers_scenes_transitions_nodes/KeybindingsLayer.h"
#include "layers_scenes_transitions_nodes/DrawGridLayer.h"
#include "layers_scenes_transitions_nodes/CreatorLayer.h"
#include "layers_scenes_transitions_nodes/LevelSearchLayer.h"
#include "layers_scenes_transitions_nodes/LevelSelectLayer.h"
#include "layers_scenes_transitions_nodes/OptionsLayer.h"
#include "layers_scenes_transitions_nodes/DailyLevelPage.h"
#include "layers_scenes_transitions_nodes/ChallengesPage.h"
#include "layers_scenes_transitions_nodes/GauntletSelectLayer.h"
#include "layers_scenes_transitions_nodes/LeaderboardsLayer.h"
#include "layers_scenes_transitions_nodes/InfoLayer.h"

#include "audio_nodes/FMODAudioEngine.h"
#include "audio_nodes/FMODSound.h"

#include "level_nodes/GJGameLevel.h"
#include "level_nodes/GJSearchObject.h"
#include "level_nodes/LevelSettingsObject.h"
#include "level_nodes/SongInfoObject.h"
#include "level_nodes/ColorAction.h"
#include "level_nodes/GJMapPack.h"

#include "sprite_nodes/CCSpritePlus.h"
#include "sprite_nodes/ColorActionSprite.h"
#include "sprite_nodes/ButtonSprite.h"
#include "sprite_nodes/GameObject.h"
#include "sprite_nodes/EffectGameObject.h"
#include "sprite_nodes/CCAnimatedSprite.h"
#include "sprite_nodes/AnimatedShopKeeper.h"
#include "sprite_nodes/PlayerObject.h"
#include "sprite_nodes/TextArea.h"
#include "sprite_nodes/GJItemIcon.h"
#include "sprite_nodes/GJRobotSprite.h"
#include "sprite_nodes/GJSpiderSprite.h"
#include "sprite_nodes/GJSpriteColor.h"
#include "sprite_nodes/SimplePlayer.h"
#include "sprite_nodes/HardStreak.h"
#include "sprite_nodes/ColorChannelSprite.h"
#include "sprite_nodes/TeleportPortalObject.h"

#include "trigger_popups/SetupPickupTriggerPopup.h"

#include "cell_nodes/GJComment.h"

#include "text_input_nodes/CCTextInputNode.h"

#include "other_nodes/CheckpointObject.h"
#include "other_nodes/PlayerCheckpoint.h"
#include "other_nodes/PointNode.h"
#include "other_nodes/UndoObject.h"
#include "other_nodes/DialogObject.h"


#include "GameToolbox.h"

#endif
