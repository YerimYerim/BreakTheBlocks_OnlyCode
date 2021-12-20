#include "ParticleManager.h"

ParticleManager::~ParticleManager()
{
}

void ParticleManager::addLastUsedNum()
{
	if (LastUsed < MaxParticle - 1)
	{
		++LastUsed;
	}
	else
	{
		LastUsed = 0;
	}
}

void ParticleManager::setParticlePosition( GLfloat x, GLfloat y, GLuint num)
{
	particles[num].setPosition(x, y);
}

void ParticleManager::setParticlesPosition(GLfloat x, GLfloat y)
{
	for(int i = 0; i< MaxParticle; ++i)
		particles[i].setPosition(x, y);
}

void ParticleManager::durationTimeUpdate(GLfloat& deltaTime)
{
	for (int i = 0; i < MaxParticle; ++i)
	{
		particles[i].durationTimeUpdate(deltaTime);
	}
}

ParticleManager::ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		Particle Particle = { posX, PosY, VelX, VelY,  ScaleX , ScaleY ,R, G, B, A, lifetime };
		particles.push_back(Particle);
	}
}
ParticleManager::ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime)
{
	MaxParticle = maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		vec3 tempVel = { rand() % 10 * 0.1f - 0.5f, rand() % 10 * 0.1f - 0.5f , 0};
		tempVel = Normalize(tempVel);
		Particle particle(posX, PosY, tempVel.x * 0.7f, tempVel.y * 0.5f,ScaleX ,ScaleY ,R, G, B, A, lifetime);
		particles.push_back(particle);
	}
}
ParticleManager::ParticleManager()
{
}

void ParticleManager::resetParticle(GLuint num)
{
	particles[num].reset();
}

void ParticleManager::resetParticles()
{
	for (int i = 0; i < MaxParticle; ++i)
	{
		particles[i].reset();
	}
}
