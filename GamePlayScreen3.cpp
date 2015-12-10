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
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

}
void GamePlayScreen3::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}