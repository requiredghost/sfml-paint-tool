#include "PaintToolManager.h"

PaintToolManager::PaintToolManager() {

	brush = new BrushTool();
	colorDialog = new ColorChooserDialog();

	canvas = new sf::Image();
	canvas->create(windowSizeX, windowSizeY, sf::Color::White);

	canvasTexture.loadFromImage(*canvas);

	canvasSprite.setTexture(canvasTexture);
	canvasSprite.setOrigin(windowSizeX / 2.0f, windowSizeY / 2.0f);
	canvasSprite.setPosition(windowSizeX / 2.0f, windowSizeY / 2.0f);
	canvasSprite.setColor(sf::Color::White);

	createPointerTextures();
	updatePointerSprite(BrushType::BRUSH);
}	


void PaintToolManager::OpenColorDialog(sf::Window* _windowRef, sf::Color* _colorRef) {
	colorDialog->Open(_windowRef,_colorRef);
}

void PaintToolManager::drawAll(sf::RenderWindow* window) {
	window->draw(canvasSprite);
	window->draw(currentPointerSprite);
}


void PaintToolManager::brushDraw(sf::Vector2i _mousePos, sf::Color* _currentColor) {
	brush->draw(canvas, _mousePos, _currentColor);
	canvasTexture.loadFromImage(*canvas);
}


void PaintToolManager::moveMousePointer(sf::Vector2i mousePos) {
	currentPointerSprite.setPosition(mousePos.x, mousePos.y);
}


void PaintToolManager::changeBrushType(BrushType type) {
	brush->changeBrushType(type);
	updatePointerSprite(type);
}

void PaintToolManager::changeBrushSize(BrushSize size) {
	brush->changeBrushSize(size);
}


void PaintToolManager::createPointerTextures() {

	currentPointerSprite.setOrigin(10, 0);

	brushTexture;
	if (!brushTexture.loadFromFile("images/paintbrush.bmp"))
	{
		// error...
	}
	brushTexture.setSmooth(true);

	spraycanTexture;
	if (!spraycanTexture.loadFromFile("images/spraycan.bmp"))
	{
		// error...
	}
	spraycanTexture.setSmooth(true);

	eraserTexture;
	if (!eraserTexture.loadFromFile("images/eraser.bmp"))
	{
		// error...
	}
	eraserTexture.setSmooth(true);
}

void PaintToolManager::updatePointerSprite(BrushType type) {
	switch (type) {
	case BrushType::BRUSH :
		currentPointerSprite.setTexture(brushTexture);
		break;
	case BrushType::ERASER :
		currentPointerSprite.setTexture(eraserTexture);
		break;
	case BrushType::SPRAYCAN :
		currentPointerSprite.setTexture(spraycanTexture);
		break;
	case BrushType::POLYGON:
		sf::Texture texture;
		currentPointerSprite.setTexture(texture);
		break;
	}
}

void PaintToolManager::updateCanvasSize(int width, int height) {
	windowSizeX = width;
	windowSizeY = height;

	sf::Image temp;

	temp = *canvas;

	canvas = new sf::Image();
	canvas->create(windowSizeX, windowSizeY, sf::Color::White);
	canvas->copy(temp, 0, 0);

	canvasTexture.loadFromImage(*canvas);
	canvasSprite.setTexture(canvasTexture);
}
