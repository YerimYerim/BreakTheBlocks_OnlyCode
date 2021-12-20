#pragma once
#include "Renderer.h"
#include "InputManager.h"
#include "ParticleManager.h"
#include <deque>
#define MAXBALLCOUNT 200
#define MAXWALLCOUNT 4
#define MAXBLOCKCOLCOUNT 9
#define MAXBLOCKROWCOUNT 6

enum StageState
{
	WAIT = 0,
	SHOOT = 1,
	END = 2,
};
enum Wall
{
	BOTTOM,TOP,LEFT,RIGHT
};
class SceneManager
{
	private:
		Renderer* renderer;
		InputManager* inputManager;

		GameObject Balls[200]; // �ִ� ���� 200���� ���� 
		GameObject Blocks[MAXBLOCKCOLCOUNT][MAXBLOCKROWCOUNT];// ���� 5�� ���� 3*5�� �ִ� --> 75���� ���
		GameObject Walls[4];
		GameObject BallsGuideLine[10];
		StageState stageState = END;
		GLboolean isGameOver = false;
		
		GLuint roundCount = 1;
		const GLuint screenWidth;
		const GLuint screenHeight;		
		
		const GLfloat GameWorldWidth;
		const GLfloat GameWorldHeight;
		std::deque<GLuint> BlockLineArr;
		std::vector<ParticleManager> BallparticleManagers;

		GLuint GenBlockProbability = 6;

		std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();
		GLfloat deltaTime;
		GLfloat BallShootdurationTime = 0;
		GLfloat BallParticledurationTime = 0;
		GLint nowBallShootingCount = 0;
		int firtFallBallNum = -1;
		std::function<void()> FuncSetballactive;
		std::function<void()> FuncSetBallParticleActive;

		ParticleManager BlockparticleManagers[MAXBLOCKCOLCOUNT][MAXBLOCKROWCOUNT];
	public:
		SceneManager(GLuint width, GLuint height);
		~SceneManager();

		void updateScene();
		void setBallParticle();
		void setBallActiveTrue();
		void input(GLboolean isTouched, GLfloat x, GLfloat y);
		void initBlockLine();
		void resetGame();
		void setBlockPos(GLuint nowCol, GLuint nowRow, GLfloat afterCol, GLfloat afterRow);
		void checkCollision();
		void Timer(float& deltatime, GLfloat& durationSec, int endSecond, const std::function<void()>& renderFunc);
		std::string getRoundCount();
};

