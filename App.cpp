#include <Adina/ScreenList.h>

#include "App.h"


App::App()
{
}


App::~App()
{
}


void App::onInit() {

}

void App::addScreens() {
	// this have to be in a specific order

	m_gamePlayScreen1 = std::make_unique<GamePlayScreen1>(&m_window);
	m_gamePlayScreen2 = std::make_unique<GamePlayScreen2>(&m_window);
	m_gamePlayScreen3 = std::make_unique<GamePlayScreen3>(&m_window);

	m_screenList->addScreen(m_gamePlayScreen1.get());
	m_screenList->addScreen(m_gamePlayScreen2.get());
	m_screenList->addScreen(m_gamePlayScreen3.get());

	m_screenList->setScreen(m_gamePlayScreen1->getScreenIndex());
}

void App::onExit() {

}
