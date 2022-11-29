#pragma once
#include "GameStates.h"

namespace GAME
{

	class StatesManager
	{
	private:
		GameStates gameState;
		bool isProgramRunning;
		void logicProgram();
		void drawProgram();
		void loadAudios();
		void loadTextures();
		void loadResources();
		void unLoadAudio();
		void unLoadTextures();
		void unLoadResources();
		void initProgram();
		void exitProgram();
	public:
		StatesManager();
		~StatesManager();
		void runProgram();

	};

}
