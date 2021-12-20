#ifndef GAMEUTILITY_H

#define GAMEUTILITY_H
#ifdef __ANDROID__
#include "GLES3/gl3.h"
#include "GLES3/gl3ext.h"
#elif __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#endif
#include "iostream"
#include "string"
#include "vector"
#include "deque"
#include "chrono"
#include "algorithm"
#include "math.h"

#include "stdlib.h"

#include "stdio.h"

	


struct vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
enum shape
{
	CIRCLE = 0,
	RECTANGLE = 1,
};

vec3 Normalize(vec3& Direction);
void transScreenToGL(GLfloat screenWidth, GLfloat screenHeight,
	GLfloat inputX, GLfloat inputY, GLfloat* convertedX, GLfloat* convertedY);

void updateDeltaTime(float& deltatime, std::chrono::system_clock::time_point& lastTime);
unsigned int loadShader(const char* vertexShaderSource, const char* fragmentShaderSource);
void transGameWorldToGL(GLfloat WorldWidth, GLfloat WorldHeight, GLfloat ScreenRatio,
	GLfloat gameWorldX, GLfloat gameWorldY, GLfloat* GLposX, GLfloat* GLposY);
#endif
