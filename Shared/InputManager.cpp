#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::InputManager(GLint ScreenWidth, GLint ScreeHeight)
{
	screenWidth = ScreenWidth;
	screenHeight = ScreeHeight;
	inputBoolReset();
}

InputManager::~InputManager()
{
}

void InputManager::setScreenSize(GLint ScreenWidth, GLint ScreeHeight)
{
	screenWidth = ScreenWidth;
	screenHeight = ScreeHeight;
	inputBoolReset();
}

void InputManager::inputTouchOn(GLfloat inputX, GLfloat inputY)
{
	GLfloat convertedX = 0;
	GLfloat convertedY = 0;


	transScreenToGL(screenWidth, screenHeight, inputX, inputY, &convertedX, &convertedY);
	nowPosition.x = convertedX;
	nowPosition.y = convertedY;

	// ù ��ġ
	if (isTouched == false) 
	{
		isTouched = true;
		startTouchPosition.x = convertedX;
		startTouchPosition.y = convertedY;
	}
	// ��ġ ���� �Ʒ��� ������ �������� 
	else if (isTouched == true && isShootReady == false) 
	{
		if (nowPosition.y < startTouchPosition.y)
		{
			isShootReady = true;
		}
	}
	// ��ġ ���� �Ʒ��� ���� �߻� �غ� �� ������ �����ϴ� ����
	else if (isTouched == true && isShootReady == true) 
	{
		direction.x = startTouchPosition.x - nowPosition.x;
		direction.y = startTouchPosition.y - nowPosition.y;

		direction = Normalize(direction);
	}
}
GLboolean InputManager::inputTouchOff(GameObject& gameobject)
{
	if (isShootReady == true)
	{
		// �߻�!
		gameobject.addForce(direction);
		gameobject.setMoveActive(true);
		return true;
	}
	else if (isShootReady == false)
	{
	}
	return false;
}

void InputManager::inputBoolReset()
{
	isTouched = false;
	isShootReady = false;
	direction = { 0,0,0 };
}

