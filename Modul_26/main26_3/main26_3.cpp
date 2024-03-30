#include <iostream>
#include <string>
#include <vector>

class Monitor
{
public:
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
private:
	int width = 80;
	int height = 50;
};

class Window
{
public:
	bool setX(int inputX, Monitor& m) {
		if ((inputX + getX()) >= 0 && ((inputX + getX() + getWidth()) <= m.getWidth())) {
			x = inputX + getX();
			return true;
		}
		else {
			std::cout << "The coordinates horizontally cannot go beyond the screen area.\n\n";
			return false;
		}
	}
	bool setY(int inputY, Monitor& m) {
		if ((inputY + getY()) >= 0 && ((inputY + getY() + getHeight()) <= m.getHeight())) {
			y = inputY + getY();
			return true;
		}
		else {
			std::cout << "The coordinates vertically cannot go beyond the screen area.\n\n";
			return false;
		}
	}
	bool setWidth(int inputWidth, Monitor& m) {
		if (inputWidth >= 0 && (getX() + inputWidth <= m.getWidth())) {
			width = inputWidth;
			return true;
		}
		else {
			std::cout << "The width cannot be negative or go beyond the screen area horizontally.\n\n";
			return false;
		}
	}
	bool setHeight(int inputHeight, Monitor& m) {
		if (inputHeight >= 0 && (getY() + inputHeight <= m.getHeight())) {
			height = inputHeight;
			return true;
		}
		else {
			std::cout << "The height cannot be negative or go beyond the screen area vertically.\n\n";
			return false;
		}
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}

	void display(Monitor& m) const {
		for (int i = 0; i < m.getHeight(); i++) {
			for (int j = 0; j < m.getWidth(); j++) {
				if ((i >= getY()) && (j >= getX()) && ((i < (getY() + getHeight())) && (j < (getX() + getWidth()))))
					std::cout << "1";
				else
					std::cout << "0";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
private:
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};

int main()
{
	std::cout << "***************** Implementation of the desktop window management program *****************\n\n";

	std::string command = "";
	Monitor myMonitor;
	Window myWindow;

	while (true) {
		std::cout << "Enter the command (move, resize, display) or 'close' to exit the program: ";
		std::cin >> command;

		if (command == "move") {
			int inputX, inputY;
			bool bx, by;
			
			std::cout << "Enter the coordinates of the vector to which you want to move the window on the screen (x y): ";
			std::cin >> inputX >> inputY;
			bx = myWindow.setX(inputX, myMonitor);
			by = myWindow.setY(inputY, myMonitor);
			if(bx || by)
				std::cout << "New coordinates of the upper-left corner of the window: (" << myWindow.getX() << "," <<
					myWindow.getY() << ").\n\n";
		}
		else if (command == "resize") {
			int inputWidth, inputHeight;
			bool bw, bh;
			std::cout << "Enter the new size of the window on the screen (width height): ";
			std::cin >> inputWidth >> inputHeight;
			bw = myWindow.setWidth(inputWidth, myMonitor);
			bh = myWindow.setHeight(inputHeight, myMonitor);
			if (bw || bh)
				std::cout << "New size of the window: (" << inputWidth << "," << inputHeight << ").\n\n";			
		}
		else if (command == "display") {
			myWindow.display(myMonitor);
		}
		else if (command == "close") {
			for (int i = 0; i < 50; i++) {	//Окно монитора "закрывается"
				std::cout << std::endl;
			}
			return 0;
		}
		else {
			std::cerr << "Invalid command!\n\n";
		}
	}
}