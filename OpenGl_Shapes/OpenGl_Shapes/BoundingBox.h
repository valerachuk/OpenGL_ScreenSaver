#pragma once

struct BoundingBox {
	float _top, _bottom, _left, _right;

	BoundingBox(const float top, const float bottom, const float left, const float right) : 
		_top(top), 
		_bottom(bottom), 
		_left(left), 
		_right(right) {}

	BoundingBox() :
		_top(0.0f),
		_bottom(0.0f),
		_left(0.0f),
		_right(0.0f) {}
};