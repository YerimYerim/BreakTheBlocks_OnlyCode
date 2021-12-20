#include "Particle.h"

Particle::Particle()
{
}
Particle::~Particle()
{
}
Particle::Particle(GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat ScaleX, GLfloat ScaleY ,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	Position = { posX, PosY, 0.0 };
	
	//vec3 tempColor = {  rand() % 10 * 0.1f , rand() % 10 * 0.1f , rand() % 10 * 0.1f };
	Scale = { ScaleX, ScaleY, 1};
	Velocity = { VelX,VelY,0};

	//Velocity = Normalize(tempDirection);
	Color = {R,G,B};
	Alpha = A;
	Life = lifetime;
}


void Particle::setPosition(GLfloat x, GLfloat y)
{
	Position.x = x;
	Position.y = y;
	
}

void Particle::reset()
{
	durationTime = 0;
}

GLboolean Particle::getisActive()
{
	return durationTime < Life;
}

void Particle::setPosition(vec3& pos)
{
	Position = pos;
}

void Particle::durationTimeUpdate(GLfloat& deltaTime)
{
	if (durationTime < Life)
	{
		durationTime += deltaTime;
	}
}
