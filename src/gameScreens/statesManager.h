#pragma once
#include "GameStates.h"


class StatesManager
{
private:
	GameStates gameState;
	bool isProgramRunning;
	int mousePosX;
	int mousePosY;
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
	void runProgram();
	void initProgram();
	void exitProgram();
};

