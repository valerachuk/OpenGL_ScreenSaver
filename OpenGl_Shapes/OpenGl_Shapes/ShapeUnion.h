#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include "Interfaces.h"
#include "BoundingBox.h"

class ShapeUnion : public ICanvasComponent {
private:
	std::vector<std::unique_ptr<ICanvasComponent>> children;
	void forEach(std::function<void(std::unique_ptr<ICanvasComponent>&)>);
public:
	void Add(std::unique_ptr<ICanvasComponent>);

	void draw() override;
	void translate(const glm::vec2&) override;
	BoundingBox calcBoundingBox() const override;
	void clampCanvasFit() override;
};