#include<GL\glew.h>

#include<Adina\IMainGame.h>

#include "GamePlayScreen1.h"

#include"ScreenIndices.h"


GamePlayScreen1::GamePlayScreen1(Adina::Window* window)
	: m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY1;
}


GamePlayScreen1::~GamePlayScreen1()
{
}


int GamePlayScreen1::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}
int GamePlayScreen1::getNextScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY2;
}
void GamePlayScreen1::build()
{

}
void GamePlayScreen1::destroy()
{

}
void GamePlayScreen1::onEntry()
{

}
void GamePlayScreen1::onExit()
{

}
void GamePlayScreen1::update(float deltaTim)
{
	checkInput();

}
void GamePlayScreen1::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
}
void GamePlayScreen1::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}