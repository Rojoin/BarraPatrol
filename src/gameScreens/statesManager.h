#pragma once
#include "GameStates.h"
#include "menu.h"

class StatesManager
{
private:
	bool isProgramRunning;
	GameStates gameState;
	void logicProgram();
	void drawProgram();
	void loadAudios();
	void loadTextures();
	void loadResources();
	void unLoadAudio();
	void unLoadTextures();
	void unLoadResources();

public:
	StatesManager();
	~StatesManager();
	void initProgram();
	void exitProgram();
};

