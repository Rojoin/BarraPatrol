#pragma once
#include "menu.h"

class statesManager
{
private:
	bool isProgramRunning;

public:
	statesManager();
	~statesManager();
	void initProgram();
	void logicProgram();
	void drawProgram();
	void loadAudios();
	void loadTextures();
	void loadResources();
	void unLoadAudio();
	void unLoadTextures();
	void unLoadResources();
};

