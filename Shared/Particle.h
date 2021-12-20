#ifndef PARTICLE_H
#define PARTICLE_H
#include "GameUtility.h"

class Particle
{
public:
    vec3 Position;
    vec3 Velocity;
    vec3 Scale = {1, 1 ,1};
    vec3 Color;
    GLfloat Alpha;
    GLfloat Life;
    GLfloat durationTime = 100000.0f;
    GLuint vertexBuffer;


    Particle(GLfloat posX, GLfloat PosY, GLfloat VelX, GLfloat VelY, GLfloat ScaleX, GLfloat ScaleY, GLfloat R, GLfloat G, GLfloat B, GLfloat A, GLfloat lifetime);
    Particle();
    ~Particle();

    void durationTimeUpdate(GLfloat& deltaTime);
    void setPosition(GLfloat x, GLfloat y);
    void setPosition(vec3& pos);
    void reset();
    GLboolean getisActive();
};

#endif
