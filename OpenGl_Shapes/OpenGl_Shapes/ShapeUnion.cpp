#include "ShapeUnion.h"

void ShapeUnion::forEach(std::function<void(std::unique_ptr<ICanvasComponent>&)> func)
{
	const auto _ = std::for_each(_children.begin(), _children.end(), func);
}

void ShapeUnion::add(std::unique_ptr<ICanvasComponent>& iShapePtr)
{
	_children.push_back(std::move(iShapePtr));
}

ISelectable* ShapeUnion::getById(int id)
{
	if (_id == id)
		return this;

	for (auto& i : _children)
	{
		ISelectable* selectable = i->getById(id);
		if (selectable)
			return selectable;
	}

	return nullptr;
}

void ShapeUnion::draw()
{
	forEach([](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->draw();});
}

void ShapeUnion::setColor(const glm::vec4& color)
{
	forEach([&color](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setColor(color);});
}

void ShapeUnion::setPos(const glm::vec2& pos)
{
	forEach([&pos](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setPos(pos); });
}

void ShapeUnion::setTrail(bool state)
{
	forEach([&state](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setTrail(state);});
}

void ShapeUnion::setDeformed(bool state)
{
	forEach([&state](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setDeformed(state);});
}

void ShapeUnion::setScale(const glm::vec2& scale)
{
	forEach([&scale](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setScale(scale);});
}

void ShapeUnion::setHidden(bool state)
{
	forEach([&state](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->setHidden(state); });
}

void ShapeUnion::translate(const glm::vec2& offset)
{
	forEach([offset](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->translate(offset); });
}

BoundingBox ShapeUnion::calcBoundingBox() const
{
	int currentField = 0;
	auto smartComparer = [&currentField](const std::unique_ptr<ICanvasComponent>& a, const std::unique_ptr<ICanvasComponent>& b) 
	{
		BoundingBox boxA = a->calcBoundingBox();
		const float fieldA = *(&boxA._top + currentField);

		BoundingBox boxB = b->calcBoundingBox();
		const float fieldB = *(&boxB._top + currentField);

		return fieldA < fieldB;
	};

	BoundingBox bb;
	bb._top = (*(std::max_element(_children.begin(), _children.end(), smartComparer)))->calcBoundingBox()._top;
	
	currentField++;
	bb._bottom = (*(std::min_element(_children.begin(), _children.end(), smartComparer)))->calcBoundingBox()._bottom;
	
	currentField++;
	bb._left = (*(std::min_element(_children.begin(), _children.end(), smartComparer)))->calcBoundingBox()._left;
	
	currentField++;
	bb._right = (*(std::max_element(_children.begin(), _children.end(), smartComparer)))->calcBoundingBox()._right;

	return bb;
}

void ShapeUnion::clampCanvasFit()
{
	const std::function<float(float, float)> cutOver = [](float value, float max) {return value > max ? max - value : 0; };
	const std::function<float(float, float)> cutUnder = [](float value, float min) {return value < min ? min - value : 0; };

	glm::vec2 clampVector = glm::vec2(0.0f);

	const BoundingBox& boundingBox = calcBoundingBox();

	clampVector.x = cutOver(boundingBox._right, 1.0f);
	clampVector.x = clampVector.x == 0 ? cutUnder(boundingBox._left, -1.0f) : clampVector.x;

	clampVector.y = cutOver(boundingBox._top, 1.0f);
	clampVector.y = clampVector.y == 0 ? cutUnder(boundingBox._bottom, -1.0f) : clampVector.y;

	translate(clampVector);
}

void ShapeUnion::print(std::ostream& stream, std::string indent) const
{
	stream << indent << _id << ") Type:Union" << std::endl;
	std::for_each(_children.begin(), _children.end(), [&](const std::unique_ptr<ICanvasComponent>& item) {
		item->print(stream, indent + "\t");
	});
}
