#include "PaintToolManager.h"

int windowXSize = 1024;
int windowYSize = 720;

sf::Color currentPenColor;

PaintToolManager* PaintToolManager::instance = 0;
PaintToolManager* ptm = PaintToolManager::getInstance();

HINSTANCE g_hInstance;

sf::RenderWindow window;

std::vector<sf::Shape*> shapes;

int circRadius = 0;
int rectWidth = 0;
int rectHeight = 0;

enum class PaintMode {BRUSH, CIRCLE, RECTANGLE};

PaintMode mode = PaintMode::BRUSH;




LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message) 
	{
	case WM_COMMAND: 
	{
		int wmId = LOWORD(WParam); 
		switch (wmId)
		{
		case ID_MAIN_EXIT: 
			PostQuitMessage(0);
			break;
		case ID_EDIT_COLORCHOOSER:
			ptm->OpenColorDialog(&window, &currentPenColor);
		
		case ID_BRUSHTYPES_STANDARDBRUSH:
			ptm->changeBrushType(BrushType::BRUSH);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHTYPES_SPRAYCAN:
			ptm->changeBrushType(BrushType::SPRAYCAN);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHTYPES_ERASER:
			ptm->changeBrushType(BrushType::ERASER);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_SMALL:
			ptm->changeBrushSize(BrushSize::SMALL);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_MEDIUM:
			ptm->changeBrushSize(BrushSize::MEDIUM);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_LARGE:
			ptm->changeBrushSize(BrushSize::LARGE);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_EXTRALARGE:
			ptm->changeBrushSize(BrushSize::XLARGE);
			mode = PaintMode::BRUSH;
			break;

		case ID_CIRCLE_SMALL:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 10;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_MEDIUM:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 20;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_LARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 40;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_EXTRALARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 65;
			mode = PaintMode::CIRCLE;
			break;
		case ID_RECTANGLE_SMALL:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 20;
			rectHeight = 10;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_MEDIUM:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 30;
			rectHeight = 10;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_LARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 40;
			rectHeight = 20;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_EXTRALARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 60;
			rectHeight = 30;
			mode = PaintMode::RECTANGLE;
			break;


		default: 
			return DefWindowProc(Handle, Message, WParam, LParam); 
		}
	}
	break; 

	
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(Handle, Message, WParam, LParam); 
}






int main() {
	WNDCLASS WindowClass; 
	WindowClass.style = 0; 
	WindowClass.lpfnWndProc = &OnEvent;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = g_hInstance;
	WindowClass.hIcon = NULL; 
	WindowClass.hCursor = 0; 

	WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);

	WindowClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WindowClass.lpszClassName = L"Paint Tool - GD1P03";

	RegisterClass(&WindowClass);

	HWND Window = CreateWindow(WindowClass.lpszClassName, L"Paint Tool - GD1P03", WS_OVERLAPPEDWINDOW  | WS_VISIBLE | WS_THICKFRAME, 0, 0, windowXSize, windowYSize, NULL, NULL, g_hInstance, NULL);

	sf::RenderWindow window(Window); 


	MSG Message;
				

	Message.message = ~WM_QUIT; 



	sf::Vector2i currentMousePos;
	sf::Event event;

	while (Message.message != WM_QUIT)
	{
		ptm->moveMousePointer(sf::Mouse::getPosition(window));

		currentMousePos.x = sf::Mouse::getPosition(window).x;
		currentMousePos.y = sf::Mouse::getPosition(window).y;
	
		event = *new sf::Event();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				ptm->updateCanvasSize(event.size.width, event.size.height);
			}

			if (mode == PaintMode::BRUSH) {
				//mouse pointer paint
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					ptm->brushDraw(currentMousePos, &currentPenColor);
				}
			}
			else if (mode == PaintMode::CIRCLE) {
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
					
						sf::CircleShape* circ = new sf::CircleShape();
						circ->setRadius(circRadius);
						circ->setOrigin(circ->getLocalBounds().width / 2, circ->getLocalBounds().height / 2);
						circ->setPosition(currentMousePos.x, currentMousePos.y);
						circ->setFillColor(currentPenColor);

						shapes.push_back(circ);
					
				}
			}
			else if (mode == PaintMode::RECTANGLE) {
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
					sf::RectangleShape* rect = new sf::RectangleShape();
					rect->setSize(sf::Vector2f(rectWidth, rectHeight));
					rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
					rect->setPosition(currentMousePos.x, currentMousePos.y);
					rect->setFillColor(currentPenColor);

					shapes.push_back(rect);

				}
			}
			

		}

		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{

			window.clear();
			ptm->drawAll(&window);
			for (int i = 0; i < shapes.size(); i++) {
				window.draw(*shapes[i]);
			};
			window.display();


		}




	}


}