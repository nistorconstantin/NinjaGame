#include<GL\glew.h>

#include<Adina\IMainGame.h>

#include "GamePlayScreen2.h"

#include"ScreenIndices.h"


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
}
void GamePlayScreen2::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}