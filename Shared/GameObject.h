#pragma once
#include "GameUtility.h"
enum CollisionDirection
{
	VERTICAL, HORIZONTAL
};
class GameObject
{
private:
		vec3 Scale = { 1,1,1 };
		vec3 moveDirection = { 0,0,0 };

		GLboolean isActive = false;
		GLboolean isMove = false;
		GLint Hp = 0;

public:
		vec3 Position;	
		GLfloat* vertexPosition;
		GLfloat* colorPosition;

		GLint vertexPoseSize;
		GLint colorPoseSize;

		GLint drawCount;
		GLuint vertexBuffer;
		GLuint colorBuffer;
		GLboolean isDot = false;

		GameObject();	
		GameObject(const GLfloat* vertexPos, const GLfloat* colorPos, GLint vertexSize, GLint colorSize);
		GameObject(const GLfloat* vertexPos, GLint vertexSize, GLint colorSize, GLfloat R, GLfloat G, GLfloat B);
		~GameObject();

		void setScale(GLfloat x, GLfloat y);
		vec3 getScale();

		void setPosition(GLfloat deltaX, GLfloat deltaY);
		
		void setActive(GLboolean isactive);
		GLboolean getActive();

		void setMoveActive(GLboolean ismove);
		GLboolean getMoveActive();
		
		void setHp(GLint hp);
		GLint getHp();

		GLboolean CheckCollider(GameObject& object);
		void HpDown();
		void addPosition(GLfloat x, GLfloat y);
		void physicsUpdate(GLfloat Speed, GLfloat& deltatime);
		void addForce(vec3& direction);
		void changeDirection(CollisionDirection direction);
		void setColor(GLfloat R, GLfloat G, GLfloat B);
};

