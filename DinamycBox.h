#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <Adina/Vertex.h>
#include <Adina/SpriteBatch.h>
#include <Adina/GLTexture.h>

class DinamycBox
{
	glm::vec4 m_uvRect;
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimensions;
	Adina::ColorRGBA8 m_color;
	Adina::GLTexture m_texture;
public:
	DinamycBox();
	~DinamycBox();

	void init(
		b2World* world,
		const glm::vec2& position,
		const glm::vec2& dimensions,
		Adina::GLTexture texture,
		Adina::ColorRGBA8 color,
		bool fixedRotation,
		glm::vec4& uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	void draw(Adina::SpriteBatch& spriteBatch);

	b2Body* getBody() const { return m_body; }
	b2Fixture* getFixture() const { return m_fixture; }
	const glm::vec2& getDimensions() const { return m_dimensions; }
	const Adina::ColorRGBA8& getColor() const { return m_color; }
};

