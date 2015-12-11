#include<GL\glew.h>

#include<Adina\IMainGame.h>

#include <Adina/ResourceManager.h>

#include"ScreenIndices.h"

#include <random>

#include "Light.h"

#include "GamePlayScreen1.h"

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
	b2Vec2 gravity(0.0f, -25.0);
	m_world = std::make_unique<b2World>(gravity);

	m_debugRenderer.init();

	// Make the ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -20.0f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
	// Make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Load the texture
	m_texture = Adina::ResourceManager::getTexture("Assets/bricks_top.png");

	addStaticBoxes();
	addDinamycBoxes();

	// Initialize spritebatch
	m_spriteBatch.init();

	// Shader init
	// Compile our texture
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
	// Compile our light shader
	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightProgram.addAttribute("vertexPosition");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");
	m_lightProgram.linkShaders();

	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScaleFactor(32.0f);

	// Init player
	m_player.init(m_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), Adina::ColorRGBA8(255, 255, 255, 255));

	initUI();
}
void GamePlayScreen1::onExit()
{
	m_debugRenderer.dispose();
}
void GamePlayScreen1::update(float deltaTim)
{
	m_camera.setPosition(m_player.getPosition());
	m_camera.update();
	checkInput();
	m_player.update(m_game->inputManager);
	// Update the physics simulation
	m_world->Step(1.0f / 60.0f, 6, 2);
}
void GamePlayScreen1::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	// Upload texture uniform
	m_textureProgram.setUniform1i("mySampler", 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	m_textureProgram.setUniformMatrix4fv("P", m_camera.getCameraMatrix());

	m_spriteBatch.begin();

	// Draw all the boxes
	for (auto& b : m_StaticBoxes) {
		b.draw(m_spriteBatch);
	}
	for (auto& b : m_DinamBoxes) {
		b.draw(m_spriteBatch);
	}
	m_player.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	// Debug rendering
	if (m_renderDebug) {
		glm::vec4 destRect;
		for (auto& b : m_StaticBoxes) {
			destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.0f;
			destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.0f;
			destRect.z = b.getDimensions().x;
			destRect.w = b.getDimensions().y;
			m_debugRenderer.drawBox(destRect, Adina::ColorRGBA8(255, 255, 255, 255), b.getBody()->GetAngle());
		}
		for (auto& b : m_DinamBoxes) {
			destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.0f;
			destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.0f;
			destRect.z = b.getDimensions().x;
			destRect.w = b.getDimensions().y;
			m_debugRenderer.drawBox(destRect, Adina::ColorRGBA8(255, 255, 255, 255), b.getBody()->GetAngle());
		}
		m_player.drawDebug(m_debugRenderer);
		// Render player
		m_debugRenderer.end();
		m_debugRenderer.render(projectionMatrix, 2.0f);
	}

	// Render some test lights
	// TODO: Don't hardcode this!
	Light playerLight;
	playerLight.color = Adina::ColorRGBA8(255, 255, 255, 128);
	playerLight.position = m_player.getPosition();
	playerLight.size = 30.0f;

	Light mouseLight;
	mouseLight.color = Adina::ColorRGBA8(255, 0, 255, 150);
	mouseLight.position = m_camera.convertScreenToWorld(m_game->inputManager.getMouseCoords());
	mouseLight.size = 45.0f;

	m_lightProgram.use();
	m_textureProgram.setUniformMatrix4fv("P", projectionMatrix);

	// Additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_spriteBatch.begin();

	playerLight.draw(m_spriteBatch);
	mouseLight.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_lightProgram.unuse();

	// Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_gui.draw();
}

void GamePlayScreen1::initUI() {
	// Init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.9f, 0.9f, 0.1f, 0.05f), glm::vec4(0.0f), "exitButton"));
	exitButton->setText("Exit Game!");
	// Set the event to be called when we click
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlayScreen1::onExitClicked, this));


	CEGUI::PushButton* newGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.9f, 0.8f, 0.1f, 0.05f), glm::vec4(0.0f), "newGameButton"));
	newGameButton->setText("new game");
	// Set the event to be called when we click
	newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlayScreen1::onNextGameClicked, this));


	m_gui.setMouseCursor("TaharezLook/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(0);
}
void GamePlayScreen1::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
	}
}

bool GamePlayScreen1::onNextGameClicked(const CEGUI::EventArgs& e) {
	m_currentState = Adina::ScreenState::CHANGE_NEXT;
	return true;
}
bool GamePlayScreen1::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Adina::ScreenState::EXIT_APPLICATION;
	return true;
}
void GamePlayScreen1::addStaticBoxes()
{
	// Make a bunch of boxes
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0, 25.0f);
	std::uniform_real_distribution<float> size(0.5, 2.5f);
	std::uniform_int_distribution<int> color(50, 255);

	Adina::ColorRGBA8 randColor = Adina::ColorRGBA8(color(randGenerator), color(randGenerator), color(randGenerator), 255);

	unsigned int i = 0;
	StaticBox newBox[10];

	glm::vec2 posBox = glm::vec2(-10, -10);
	glm::vec2 dimBox = glm::vec2(4, 2);
	newBox[i].init(m_world.get(), posBox, dimBox, m_texture, randColor, false);
	m_StaticBoxes.push_back(newBox[i++]);

	posBox = glm::vec2(-5, -5);
	dimBox = glm::vec2(4, 2);
	newBox[i].init(m_world.get(), posBox, dimBox, m_texture, randColor, false);
	m_StaticBoxes.push_back(newBox[i++]);

	posBox = glm::vec2(0, 0);
	dimBox = glm::vec2(4, 2);
	newBox[i].init(m_world.get(), posBox, dimBox, m_texture, randColor, false);
	m_StaticBoxes.push_back(newBox[i++]);

	posBox = glm::vec2(5, 5);
	dimBox = glm::vec2(4, 2);
	newBox[i].init(m_world.get(), posBox, dimBox, m_texture, randColor, false);
	m_StaticBoxes.push_back(newBox[i++]);

	posBox = glm::vec2(10, 5);
	dimBox = glm::vec2(4, 2);
	newBox[i].init(m_world.get(), posBox, dimBox, m_texture, randColor, false);
	m_StaticBoxes.push_back(newBox[i++]);

}

void GamePlayScreen1::addDinamycBoxes()
{

	// Make a bunch of boxes
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0, 25.0f);
	std::uniform_real_distribution<float> size(0.5, 2.5f);
	std::uniform_int_distribution<int> color(50, 255);
	const int NUM_BOXES = 10;

	for (int i = 0; i < NUM_BOXES; i++) {
		Adina::ColorRGBA8 randColor;
		randColor.r = color(randGenerator);
		randColor.g = color(randGenerator);
		randColor.b = color(randGenerator);
		randColor.a = 255;
		DinamycBox newBox;
		newBox.init(
			m_world.get(),
			glm::vec2(xPos(randGenerator), yPos(randGenerator)),
			glm::vec2(size(randGenerator), size(randGenerator)),
			m_texture,
			randColor,
			false,
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		m_DinamBoxes.push_back(newBox);
	}
}