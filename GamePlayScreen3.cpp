#include<GL\glew.h>

#include<Adina\IMainGame.h>

#include "GamePlayScreen3.h"

#include"ScreenIndices.h"

GamePlayScreen3::GamePlayScreen3(Adina::Window* window)
	: m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY3;
}


GamePlayScreen3::~GamePlayScreen3()
{
}

int GamePlayScreen3::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY2;
}
int GamePlayScreen3::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}
void GamePlayScreen3::build()
{

}
void GamePlayScreen3::destroy()
{

}
void GamePlayScreen3::onEntry()
{
	initUI();

}
void GamePlayScreen3::onExit()
{

}
void GamePlayScreen3::update(float deltaTim)
{
	checkInput();
}
void GamePlayScreen3::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.2f, 0.2f, 1.0f);

	m_gui.draw();
}

void GamePlayScreen3::initUI()
{
	// Init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.9f, 0.9f, 0.1f, 0.05f), glm::vec4(0.0f), "exitButton"));
	exitButton->setText("Exit Game!");
	// Set the event to be called when we click
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlayScreen3::onExitClicked, this));


	m_gui.setMouseCursor("TaharezLook/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(0);
}
void GamePlayScreen3::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
	}
}
bool GamePlayScreen3::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Adina::ScreenState::EXIT_APPLICATION;
	return true;
}