#pragma once
#include "Shape.h"
#include "Utils.h"

class ScreenSaverShape : public Shape
{
private:

	bool _toDelete;
	ScreenSaverShape* _target;
public:
	explicit ScreenSaverShape(std::shared_ptr<Buffer> buffer);
	explicit ScreenSaverShape();

	bool getDeleteState();
	void setDeleteState(bool state);

	ScreenSaverShape* getTarget();
	void setTarget(ScreenSaverShape* target);
};
