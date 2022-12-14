#pragma once
#include <d3d11.h>
#include <list>
#include <unordered_map>

#include "AUIScreen.h"
#include "Texture.h"
#include "DebugWindow.h"


typedef std::string String;
typedef std::list<AUIScreen*> UIList;
typedef std::unordered_map<String, AUIScreen*> UITable;

class CreditsScreen;
class MenuToolBar;
class GameView;
class PerspectiveView;
class TopdownView;
class ColorPicker;
class InspectorWindow;
class SceneEditor;

class UINames
{
public:
	const String MENU_TOOL_BAR = "MENU_TOOL_BAR";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLOR_PICKER = "COLOR_PICKER";

	const String GAME_VIEW = "GAME_VIEW";
	const String PERSPECTIVE_VIEW = "PERSPECTIVE_VIEW";
	const String TOPDOWN_VIEW = "TOPDOWN_VIEW";
	const String WIREFRAME_VIEW = "WIREFRAME_VIEW";

	const String SCENE_EDITOR = "SCENE_EDITOR";
	const String INSPECTOR_WINDOW = "INSPECTOR_WINDOW";
	const String OBJECT_SPAWN_PANEL = "OBJECT_SPAWN_PANEL";
	
	const String PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const String ACTIONS_SCREEN = "ACTIONS_SCREEN";

	const String DEBUG_WINDOW = "DEBUG_WINDOW";
};


class UISystem
{
public:
	UISystem();
	~UISystem();

	static void initialize();
	static UISystem* getInstance();
	static void destroy();

	void updateNewFrame();
	void update();
	void initImGUI(HWND hwnd);
	void UpdateDebugWindow(const std::string str);
	static const int WINDOW_HEIGHT = 900;
	static const int WINDOW_WIDTH = 1440;

private:
	static UISystem* sharedInstance;

	UINames uiNames;
	UIList uiList;
	UITable uiTable;

	bool show_demo_window = true;

private:
	friend class CreditsScreen;
	friend class MenuToolBar;
	friend class ColorPicker;
	friend class GameView;
	friend class PerspectiveView;
	friend class TopdownView;
	friend class WireframeView;
	friend class InspectorWindow;
	friend class SceneEditor;
	friend class DebugWindow;
};

