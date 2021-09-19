#pragma once

class GMouse {
public:
	static int x;
	static int y;

	static bool leftPressed;
	static bool rightPressed;

	static void mousePressed();
	static void mouseReleased();
	static void mouseMoved();
};
