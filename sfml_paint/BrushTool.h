#include <SFML/Graphics.hpp>
#include <iostream>

enum class BrushType { BRUSH = 0, SPRAYCAN, ERASER, POLYGON};
enum class BrushSize { SMALL = 0, MEDIUM, LARGE, XLARGE};


class BrushTool
{
public:
	BrushTool();
	void draw(sf::Image*, sf::Vector2i, sf::Color*);
	void changeBrushType(BrushType type);
	void changeBrushSize(BrushSize size);

private:
	void updateFilename();

	sf::Image brushImage;
	std::string filename;
	std::string typestr;
	std::string sizestr;
	int intSize;
	BrushType type;
	BrushSize size;
};

