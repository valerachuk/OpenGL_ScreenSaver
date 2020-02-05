#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Buffer.h"
#include "IDrawable.h"

class Figure: public IDrawable {
private:
	const int DEFORM_FACTOR = 2;

	glm::vec2 _scale;
	glm::vec2 _position;
	glm::vec4 _color;
	bool _isHillighted;
	bool _isDeformed;
	std::shared_ptr<Buffer> _buffer;
	
	void clampPos();
	glm::mat4 calcModelMatrix();

	const glm::vec2& getScale() const;
	const glm::vec2& getPos() const;
	const glm::vec4& getColor() const;

public:
	void setScale(const glm::vec2&);
	void setPos(const glm::vec2&);
	void setColor(const glm::vec4&);

	bool getHilighted() const;
	void setHilighed(bool);

	bool getDeformed() const;
	void setDeformed(bool);

	const Buffer& getBuffer() const;
	void translate(const glm::vec2&);
	bool isOtherCollision(const Figure&);
	void Draw(GLRenderSystem&) override;

	Figure(std::shared_ptr<Buffer>);

};