#include "SceneManager.h"


SceneManager::SceneManager(GLuint width, GLuint height):screenWidth(width),screenHeight(height),
GameWorldWidth(300.0f) , GameWorldHeight(300.0f)
{
	renderer = new Renderer(screenWidth, screenHeight);
	inputManager = new InputManager(screenWidth, screenHeight);

	#pragma region setBlocks
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{		
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			renderer->setupObjectRenderer(Blocks[i][j], RECTANGLE);
			
			setBlockPos(i, j, i, j); 
			Blocks[i][j].setMoveActive(false);
			Blocks[i][j].setActive(false);
			Blocks[i][j].setColor(1.0f, 0.0f, 0.0f);

			BlockparticleManagers[i][j] = ParticleManager(30, Blocks[i][j].Position.x, Blocks[i][j].Position.y, 
				Blocks[i][j].getScale().y * 0.5f, Blocks[i][j].getScale().y * 0.5f, 1, 0, 0, 0.8f, 100.0f);
			BlockparticleManagers[i][j].isColorChange = true;
			BlockparticleManagers[i][j].isScaling = true;
			BlockparticleManagers[i][j].isGravity = true;
		}
		BlockLineArr.push_back(i);
	}
	#pragma endregion	
	#pragma region setWall
	//SET WALL
	for (int i = 0; i < MAXWALLCOUNT; ++i)	//SET WALL
	{
		renderer->setupObjectRenderer(Walls[i], RECTANGLE);
		Walls[i].setActive(true);
		Walls[i].setMoveActive(false);
	}
	Walls[BOTTOM].setPosition(0, -150.0f);
	Walls[BOTTOM].setScale(300.0f, 5.0f);

	Walls[TOP].setPosition(0, 150.0f);
	Walls[TOP].setScale(300.0f, 5.0f);

	Walls[LEFT].setPosition(-150.0f, 0);
	Walls[LEFT].setScale(5.0f, 300.0f);

	Walls[RIGHT].setPosition(150.0f, 0);
	Walls[RIGHT].setScale(5.0f, 300.0f);
	#pragma endregion
	#pragma region setBalls
	for (int i = 0; i < MAXBALLCOUNT; ++i)
	{
		renderer->setupObjectRenderer(Balls[i], CIRCLE);
		Balls[i].setScale(10.0f, 10.0f);
		Balls[i].setPosition(0, -150.0f + Balls[0].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
		Balls[i].setActive(false);
		Balls[i].setMoveActive(false);

		ParticleManager BallParticles(30, 0, 0, 0, 0, 7, 7, 0.51f, 0.65f, 1.0f, 0.5f, 10.0f);
		BallParticles.isColorChange = true;
		BallParticles.isScaling = true;
		BallParticles.isGravity = false;
		BallParticles.setParticlesPosition(-600, -11);
		BallparticleManagers.push_back(BallParticles);
	}
	Balls[0].setActive(true);
	
	for (int i = 0; i < 10; ++i)
	{	
		renderer->setupObjectRenderer(BallsGuideLine[i], CIRCLE);

		BallsGuideLine[i].setScale(5.0f, 5.0f);
		BallsGuideLine[i].setPosition(0, -150.0f + Balls[0].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
		BallsGuideLine[i].setActive(false);
		BallsGuideLine[i].setMoveActive(false);
	}
	#pragma endregion

	FuncSetballactive = std::bind(&SceneManager::setBallActiveTrue, this);
	FuncSetBallParticleActive = std::bind(&SceneManager::setBallParticle, this);
	initBlockLine();
} 

SceneManager::~SceneManager()
{
	delete renderer;
	delete inputManager;
}

void SceneManager::updateScene()
{
	updateDeltaTime(deltaTime, lastTime);
	renderer->updateRenderer();
	
	#pragma region BlockUpdate
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i) 
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			if (Blocks[BlockLineArr[i]][j].getActive() == true)
			{
				renderer->drawGameObject(Blocks[BlockLineArr[i]][j]);
			}
			else if (BlockparticleManagers[i][j].particles[0].getisActive() == true)
			{
				BlockparticleManagers[i][j].durationTimeUpdate(deltaTime);
				for (int t = 0; t < BlockparticleManagers[i][j].MaxParticle; ++t)
				{
					renderer->drawParticle(BlockparticleManagers[i][j].particles[t], BlockparticleManagers[i][j].isGravity,
						BlockparticleManagers[i][j].isScaling, BlockparticleManagers[i][j].isColorChange);
				}
			}
		}
	}
	#pragma endregion

	for (int i = 0; i < 10; ++i)
	{
		if (BallsGuideLine[i].getActive() == true)
		{
			renderer->drawGameObject(BallsGuideLine[i]);
		}
		else
		{
			break;
		}
	}
	#pragma region BallUpdate
	for (int i = 0; i < roundCount; ++i)
	{
		BallparticleManagers[i].durationTimeUpdate(deltaTime);
		for (int j = 0; j < BallparticleManagers[i].MaxParticle; ++j)
		{
			if (BallparticleManagers[i].particles[j].getisActive() == true)
			{
				renderer->drawParticle(BallparticleManagers[i].particles[j], BallparticleManagers[i].isGravity,
					BallparticleManagers[i].isScaling, BallparticleManagers[i].isColorChange);
			}
		}
		if (Balls[i].getActive() == true) 
		{
			renderer->drawGameObject(Balls[i]);
		   	Balls[i].physicsUpdate(15.0f, deltaTime);
		}
	}
	#pragma endregion

	#pragma region WallUpdate
	for (int i = 0; i < MAXWALLCOUNT; ++i)
	{
		renderer->drawGameObject(Walls[i]);
	}
	#pragma endregion
	switch (stageState)
	{
	case WAIT:
	case SHOOT:
	{
		checkCollision();
		if (nowBallShootingCount < roundCount)
		{
			Timer(deltaTime, BallShootdurationTime, 1, FuncSetballactive);
		}
	}break;
	case END:
	{
		nowBallShootingCount = 1; 
	}break;
	default:
		break;
	}
	Timer(deltaTime, BallParticledurationTime, 0.5f, FuncSetBallParticleActive);
}

void SceneManager::setBallParticle()
{
	for (int i = 0; i < roundCount; ++i)
	{
		BallparticleManagers[i].resetParticle(BallparticleManagers[i].LastUsed);
		BallparticleManagers[i].setParticlePosition(Balls[i].Position.x, Balls[i].Position.y, BallparticleManagers[i].LastUsed);
		BallparticleManagers[i].addLastUsedNum();
	}
}

void SceneManager::setBallActiveTrue()
{
	Balls[nowBallShootingCount].setActive(true);
	++nowBallShootingCount;
}

void SceneManager::input(GLboolean isTouched, GLfloat x, GLfloat y)
{
	#ifdef __ANDROID__
	if (stageState == END)
	{
		if (isTouched == false) // ��ġ off
		{
			for (int i = 0; i < roundCount; ++i)
			{
				if (inputManager->inputTouchOff(Balls[i]) == true && i == 0)
				{
					stageState = SHOOT;
				}
			}
			inputManager->inputBoolReset();

			for (int i = 0; i < 10; ++i)
			{
				BallsGuideLine[i].setActive(false);
			}
		}
		else if (isTouched == true)// ù ��ġ
		{
			inputManager->inputTouchOn(x, y);
			for (int i = 0; i < 10; ++i)
			{
				if(BallsGuideLine[i].getActive() == false)
					BallsGuideLine[i].setActive(true);
				BallsGuideLine[i].setPosition(Balls[0].Position.x + inputManager->direction.x * i * 10, Balls[0].Position.y + inputManager->direction.y * 10 * i);
			}
		}

	}
	#elif __APPLE__

	#endif
}

void SceneManager::initBlockLine()
{
	for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
	{
		//1. �� ���� �ִ� ��� �������ְ�
		if (rand() % 10 < GenBlockProbability)
		{
			GLint HP = std::min(MAXBALLCOUNT, (int)roundCount);
			Blocks[BlockLineArr.front()][j].setHp(HP);
			Blocks[BlockLineArr.front()][j].setColor(1.0f, 0.0f, 0.0f);
			Blocks[BlockLineArr.front()][j].setActive(true);
		}
		//2. ������ ĭ�� active �Ǿ��ִ��� Ȯ���Ѵ�.-->over���� �ƴ��� ����
		if (isGameOver == false && Blocks[BlockLineArr.back()][j].getActive())
		{
			isGameOver = true;
			for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
			{
				for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
				{
					if (Blocks[i][j].getActive())
					{
						Blocks[i][j].setActive(false);
						for (int t = 0; t < BlockparticleManagers[i][j].MaxParticle; ++t)
						{
							BlockparticleManagers[i][j].resetParticle(t);
						}
					}
				}
			} 
			resetGame();
		}
	}

	BlockLineArr.push_front(BlockLineArr.back());
	BlockLineArr.pop_back();

	//3. ���ĭ�� ����!
	for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
	{
		for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
		{
			setBlockPos(BlockLineArr.at(i), j, i, j);
		}
	}

}

void SceneManager::resetGame()
{
	for (int i = 0; i < roundCount; ++i)
	{
		Balls[i].setActive(false);
		BallparticleManagers[i].setParticlesPosition(-600, -11);
	}
	Balls[0].setActive(true);
	roundCount = 1;
	isGameOver = false;
}

void SceneManager::setBlockPos(GLuint nowCol, GLuint nowRow, GLfloat afterCol, GLfloat afterRow)
{
	GLfloat blockwidth = (GLfloat)(GameWorldWidth / MAXBLOCKROWCOUNT);
	GLfloat blockheight = (GLfloat)(GameWorldHeight / MAXBLOCKCOLCOUNT);

	Blocks[nowCol][nowRow].setScale(blockwidth, blockheight);
	Blocks[nowCol][nowRow].setPosition(-150.0f + blockwidth * (0.501f+ afterRow), 150.0f - blockheight *(0.501f + afterCol));
	Blocks[nowCol][nowRow].setScale(blockwidth * 0.95f, blockheight * 0.95f);
}

void SceneManager::checkCollision()
{
	int moveFalseCount = 0;
	for (int ballcnt = 0; ballcnt < roundCount; ++ballcnt)
	{
		if (Balls[ballcnt].getMoveActive() == true)
		{
			#pragma region BlockCheckCollider
			for (int i = 0; i < MAXBLOCKCOLCOUNT; ++i)
			{
				for (int j = 0; j < MAXBLOCKROWCOUNT; ++j)
				{
					if (Blocks[BlockLineArr[i]][j].getActive() == true && Blocks[BlockLineArr[i]][j].CheckCollider(Balls[ballcnt]))
					{
						int HP = Blocks[BlockLineArr[i]][j].getHp();
						if (HP < 1)
						{
							BlockparticleManagers[i][j].resetParticles();							
						}
						else
						{
							Blocks[BlockLineArr[i]][j].setColor(1.0f, 1.0f - (GLfloat)HP / (GLfloat)roundCount * 0.9f, 1.0f - (GLfloat)HP / (GLfloat)roundCount * 0.9f);
						}
					}
				}
			}
			#pragma endregion

			#pragma region WallCheckCollider
			for (int i = 0; i < MAXWALLCOUNT; ++i)
			{
				if (Walls[i].CheckCollider(Balls[ballcnt]))
				{
					if (i == BOTTOM)
					{
						Balls[ballcnt].setPosition(Balls[ballcnt].Position.x, -150.0f + Balls[ballcnt].getScale().y * 0.5f + Walls[BOTTOM].getScale().y * 0.5f);
						Balls[ballcnt].setMoveActive(false);
						Balls[ballcnt].setActive(false);
	
						if (firtFallBallNum == -1)//ù���� �ٴڰ� �浹�� WAIT �� ���� �� ����
						{
							firtFallBallNum = ballcnt;
							Balls[ballcnt].setActive(true);
							stageState = WAIT; 
						}
						else
						{
							Balls[ballcnt].setPosition(Balls[firtFallBallNum].Position.x , Balls[firtFallBallNum].Position.y);
						}
					}
				}
			}
			#pragma endregion
		}
		if (Balls[ballcnt].getMoveActive() == false)
		{
			moveFalseCount++;
		}
		if (moveFalseCount  == roundCount) // ���� ��� ��������
		{
			stageState = END;
			roundCount += 1;
			//ó�� �������� �Ⱥ��̰� ���� ù��°�� ���̵���
			Balls[firtFallBallNum].setActive(false);
			Balls[0].setActive(true);
			//������ ��ġ �ٲ��ֱ�
			if (ballcnt < MAXBALLCOUNT)
			{
				Balls[ballcnt + 1].setPosition(Balls[firtFallBallNum].Position.x, Balls[firtFallBallNum].Position.y);
			}
			initBlockLine();
			firtFallBallNum = -1;
			moveFalseCount = 0;
		}
	}

}

void SceneManager::Timer(float& deltatime, GLfloat& durationSec, int endSecond,const std::function<void()>& Function)
{
	if (durationSec > endSecond)
	{
		Function();
		durationSec = 0;
	}
	else
	{
		durationSec += deltatime;
	}
}

std::string SceneManager::getRoundCount() {
	return std::to_string(roundCount);
}
