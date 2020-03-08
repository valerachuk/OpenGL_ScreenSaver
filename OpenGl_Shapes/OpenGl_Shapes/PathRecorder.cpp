#include "PathRecorder.h"

PathRecorder::PathRecorder() : _shape(nullptr), _isRecording(false) {}

PathRecorder& PathRecorder::getInstance()
{
	static PathRecorder inst;
	return inst;
}

void PathRecorder::startRecording(Shape* shape)
{
	if (!shape)
	{
		throw std::invalid_argument("argument cannot be null");
	}
	
	_path.clear();
	_shape = shape;
	_isRecording = true;
}

void PathRecorder::startPlaying()
{
	_isRecording = false;
}

bool PathRecorder::hasItem() const
{
	return static_cast<bool>(_shape);
}

void PathRecorder::execute()
{
	if (_isRecording && _shape)
	{
		_path.push_back(_shape->_position);
	}
	else if (!_isRecording && _shape && !_path.empty())
	{
		_shape->_position = _path.back();
		_path.pop_back();
	}
}
