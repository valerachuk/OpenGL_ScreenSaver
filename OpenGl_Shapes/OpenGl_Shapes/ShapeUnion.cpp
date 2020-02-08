#include "ShapeUnion.h"

void ShapeUnion::forEach(std::function<void(std::unique_ptr<ICanvasComponent>&)> func)
{
	const auto _ = std::for_each(children.begin(), children.end(), func);
}

void ShapeUnion::Add(std::unique_ptr<ICanvasComponent> iShapePtr)
{
	children.push_back(std::move(iShapePtr));
}

void ShapeUnion::draw()
{
	forEach([](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->draw();});
}

void ShapeUnion::translate(const glm::vec2& offset)
{
	forEach([offset](std::unique_ptr<ICanvasComponent>& iShapePtr) {iShapePtr->translate(offset); });
}

BoundingBox ShapeUnion::calcBoundingBox() const
{
	uint8_t currentField = 0;
	auto smartComparer = [&currentField](const std::unique_ptr<ICanvasComponent>& a, const std::unique_ptr<ICanvasComponent>& b) 
	{
		BoundingBox boxA = a->calcBoundingBox();
		float& fieldA = *(&boxA._top + currentField);

		BoundingBox boxB = b->calcBoundingBox();
		float& fieldB = *(&boxB._top + currentField++);

		return fieldA < fieldB;
	};

	BoundingBox bb;
	bb._top = (*(std::max_element(children.begin(), children.end(), smartComparer)))->calcBoundingBox()._top;
	bb._bottom = (*(std::min_element(children.begin(), children.end(), smartComparer)))->calcBoundingBox()._bottom;
	bb._left = (*(std::min_element(children.begin(), children.end(), smartComparer)))->calcBoundingBox()._left;
	bb._right = (*(std::max_element(children.begin(), children.end(), smartComparer)))->calcBoundingBox()._right;

	return bb;
}

void ShapeUnion::clampCanvasFit()
{
	std::function<float(float, float)> cutOver = [](float value, float max) {return value > max ? max - value : 0; };
	std::function<float(float, float)> cutUnder = [](float value, float min) {return value < min ? min - value : 0; };

	glm::vec2 clampVector = glm::vec2(0.0f);

	const BoundingBox& boundingBox = calcBoundingBox();

	clampVector.x = cutOver(boundingBox._right, 1.0f);
	clampVector.x = clampVector.x == 0 ? cutUnder(boundingBox._left, -1.0f) : clampVector.x;

	clampVector.y = cutOver(boundingBox._top, 1.0f);
	clampVector.y = clampVector.y == 0 ? cutUnder(boundingBox._bottom, -1.0f) : clampVector.y;

	translate(clampVector);
}
