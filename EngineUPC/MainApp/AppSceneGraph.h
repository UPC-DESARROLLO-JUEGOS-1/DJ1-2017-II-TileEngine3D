#pragma once

#include <FrameworkUPC\SceneGraph.h>

#include "EnumAppScenes.h"
#include "GameScene.h"
#include "Game3DScene.h"
#include "GameFontSystemScene.h"
#include "GameTile3DEngineScene.h"

class AppSceneGraph : public SceneGraph
{
public:
	AppSceneGraph() { SceneGraph::SceneGraph(); }
	~AppSceneGraph() { SceneGraph::~SceneGraph(); }

	void GoToScene(int sceneId)
	{
		if (currentScene != nullptr) {
			delete currentScene;
		}

		BaseScene* result = nullptr;

		switch (sceneId)
		{
			case EnumAppScenes::Menu:
				result = new GameScene(this);
				break;
			case EnumAppScenes::Juego:
				result = new GameTile3DEngineScene(this);
				break;
			case EnumAppScenes::Perder:
				break;
		}

		if (result != nullptr)
		{
			SceneGraph::GoToScene(sceneId);
			result->Initialize();
		}

		currentScene = result;
	}
};

