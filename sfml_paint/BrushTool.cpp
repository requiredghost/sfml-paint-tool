#include "BrushTool.h"

BrushTool::BrushTool() {
	if (!brushImage.loadFromFile("images/brush_small.bmp")) {
		std::cout << "image failed to load" << std::endl;
	}

	typestr = "brush";
	sizestr = "small";
	intSize = brushImage.getSize().x;
}

void BrushTool::draw(sf::Image* canvas, sf::Vector2i mousePos, sf::Color* currentPenColor) {
	sf::Color drawColor = *currentPenColor;
	if (type == BrushType::ERASER) {
		drawColor = sf::Color::White;
	}

	int sizeX = canvas->getSize().x;
	int sizeY = canvas->getSize().y;

	for (int i = (-intSize/2); i < intSize/2; i++) {
		for (int j = (-intSize / 2); j < intSize /2; j++) {
			if (( (mousePos.x +i) <= 0 || (mousePos.x + i) >= sizeX || (mousePos.y + j) <= 0 || (mousePos.y + j) >= sizeY) == false) {
				if (brushImage.getPixel(i+ intSize /2, j+ intSize /2).r == 0) {
					canvas->setPixel(mousePos.x+i, mousePos.y+j, drawColor);
				}
			}
		}

	}
}


void BrushTool::changeBrushType(BrushType brushtype) {
	type = brushtype;

	switch (brushtype) {
	case BrushType::BRUSH :
		typestr = "brush";
		break;
	case BrushType::SPRAYCAN :
		typestr = "spraycan";
		break;
	case BrushType::ERASER :
		typestr = "eraser";
		break;

	default :
		std::cout << "invalid brush type" << std::endl;
		break;
	}

	updateFilename();

	if (!brushImage.loadFromFile("images/" + filename)) {
		std::cout << "image failed to load" << std::endl;
	}
	intSize = brushImage.getSize().x;
}

void BrushTool::changeBrushSize(BrushSize brushsize) {
	size = brushsize;

	switch (brushsize) {
	case BrushSize::SMALL :
		sizestr = "small";
		break;
	case BrushSize::MEDIUM :
		sizestr = "medium";
		break;
	case BrushSize::LARGE :
		sizestr = "large";
		break;
	case BrushSize::XLARGE:
		sizestr = "xlarge";
		break;
	default:
		std::cout << "invalid brush size" << std::endl;
		break;
	}

	updateFilename();

	if (!brushImage.loadFromFile("images/" + filename)) {
		std::cout << "image failed to load" << std::endl;
	}
	intSize = brushImage.getSize().x;
}

void BrushTool::updateFilename() {
	filename = typestr + "_" + sizestr + ".bmp";
}

