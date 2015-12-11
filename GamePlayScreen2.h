#pragma once

#include "StaticBox.h"
#include "DinamycBox.h"
#include "Player.h"
#include <Adina/IGameScreen.h>
#include <Box2D/Box2D.h>
#include <Adina/SpriteBatch.h>
#include <Adina/GLSLProgram.h>
#include <Adina/Camera2D.h>
#include <Adina/GLTexture.h>
#include <Adina/Window.h>
#include <Adina/DebugRenderer.h>
#include <vector>

#include <Adina/GUI.h>

class GamePlayScreen2 : public Adina::IGameScreen
{
	Adina::SpriteBatch m_spriteBatch;
	Adina::GLSLProgram m_textureProgram;
	Adina::GLSLProgram m_lightProgram;
	Adina::Camera2D m_camera;
	Adina::GLTexture m_texture;
	Adina::Window* m_window;
	Adina::DebugRenderer m_debugRenderer;
	Adina::GUI m_gui;

	bool m_renderDebug = false;

	Player m_player;
	std::vector<StaticBox> m_StaticBoxes;
	std::vector<DinamycBox> m_DinamBoxes;
	std::unique_ptr<b2World> m_world;
public:
	GamePlayScreen2(Adina::Window* window);
	~GamePlayScreen2();

	virtual int getPreviousScreenIndex() const override;

	virtual int getNextScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTim) override;

	virtual void draw() override;
private:
	void checkInput();
	void initUI();

	bool onNextGameClicked(const CEGUI::EventArgs& e);

	void addStaticBoxes();
	void addDinamycBoxes();
};

