#pragma once

#include<Adina\IMainGame.h>

#include"GamePlayScreen1.h"
#include"GamePlayScreen2.h"
#include"GamePlayScreen3.h"

class App: public Adina::IMainGame
{
	std::unique_ptr<GamePlayScreen1> m_gamePlayScreen1 = nullptr;
	std::unique_ptr<GamePlayScreen2> m_gamePlayScreen2 = nullptr;
	std::unique_ptr<GamePlayScreen3> m_gamePlayScreen3 = nullptr;
public:
	App();
	~App();

	// Called on initialization
	virtual void onInit() override;
	// For adding all screens
	virtual void addScreens() override;
	// Called when exiting
	virtual void onExit() override;
};

