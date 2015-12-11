#include<GL\glew.h>

#include<Adina\IMainGame.h>

#include <Adina/ResourceManager.h>

#include"ScreenIndices.h"

#include <random>

#include "Light.h"

#include "GamePlayScreen2.h"



GamePlayScreen2::GamePlayScreen2(Adina::Window* window)
	: m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY2;
}


GamePlayScreen2::~GamePlayScreen2()
{
}

int GamePlayScreen2::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY1;
}
int GamePlayScreen2::getNextScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY3;
}
void GamePlayScreen2::build()
{

}
void GamePlayScreen2::destroy()
{

}
void GamePlayScreen2::onEntry()
{
	initUI();
	m_debugRenderer.init();
}
void GamePlayScreen2::onExit()
{

}
void GamePlayScreen2::update(float deltaTim)
{
	checkInput();

}
void GamePlayScreen2::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_gui.draw();
}

void GamePlayScreen2::initUI()
{
	// Init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");


	CEGUI::PushButton* newGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.9f, 0.8f, 0.1f, 0.05f), glm::vec4(0.0f), "newGameButton"));
	newGameButton->setText("new game");
	// Set the event to be called when we click
	newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlayScreen2::onNextGameClicked, this));


	m_gui.setMouseCursor("TaharezLook/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(0);
}
void GamePlayScreen2::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
	}
}

bool GamePlayScreen2::onNextGameClicked(const CEGUI::EventArgs& e) {
	m_currentState = Adina::ScreenState::CHANGE_NEXT;
	return true;
}
void GamePlayScreen2::addStaticBoxes()
{

}
void GamePlayScreen2::addDinamycBoxes()
{

}