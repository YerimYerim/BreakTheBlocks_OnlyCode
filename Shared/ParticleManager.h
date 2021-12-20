#include "Particle.h"
#include "GameUtility.h"

class ParticleManager
{
public:
	std::vector<Particle> particles;

	GLuint MaxParticle = 0;
	GLuint LastUsed = 0;
	GLuint drawCount = 36;

	GLboolean isScaling = false;
	GLboolean isGravity = false;
	GLboolean isColorChange = false;

	ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat ScaleX, GLfloat ScaleY,GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime);
	ParticleManager(GLint maxCount, GLfloat posX, GLfloat PosY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime);
	ParticleManager();
	~ParticleManager();

	void setParticlePosition(GLfloat x, GLfloat y, GLuint num);
	void setParticlesPosition(GLfloat x, GLfloat y);
	void durationTimeUpdate(GLfloat& deltaTime);
	void resetParticle(GLuint num);
	void resetParticles();
	void addLastUsedNum();
};

