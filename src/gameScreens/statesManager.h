#pragma once
#include "menu.h"

class statesManager
{
private:
	bool isProgramRunning;
	void logicProgram();
	void drawProgram();
	void loadAudios();
	void loadTextures();
	void loadResources();
	void unLoadAudio();
	void unLoadTextures();
	void unLoadResources();

public:
	statesManager();
	~statesManager();
	void initProgram();
	void exitProgram();
};

