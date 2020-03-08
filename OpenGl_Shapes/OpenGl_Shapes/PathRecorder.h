#pragma once
#include <deque>
#include "Shape.h"
#include "glm/glm.hpp"

class PathRecorder
{
private:
	PathRecorder();
	PathRecorder& operator=(const PathRecorder&) = delete;
	PathRecorder(const PathRecorder&) = delete;
	std::deque<glm::vec2> _path;
	Shape* _shape;
	bool _isRecording;
	
public:
	static PathRecorder& getInstance();
	void startRecording(Shape* shape);
	void startPlaying();
	bool hasItem() const;
	
	void execute();
	
};