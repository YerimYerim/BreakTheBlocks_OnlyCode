#pragma once
#include "GameObject.h"

class InputManager
{

private:
	GLboolean isTouched = false;
	GLboolean isShootReady = false;

	vec3 startTouchPosition = { -1, -1, 0 };
	vec3 readyTouchPosition = { -1, -1, 0 };
public:
	GLint screenWidth;
	GLint screenHeight;
	vec3 direction = { 0,0,0 };

	vec3 nowPosition = { -1, -1, 0 };
	InputManager();
	InputManager(GLint ScreenWidth, GLint ScreeHeight);
	~InputManager();
	void setScreenSize(GLint ScreenWidth, GLint ScreeHeight);
	void inputTouchOn(GLfloat inputX, GLfloat inputY);
	GLboolean inputTouchOff(GameObject& gameobject);
	void inputBoolReset();
};