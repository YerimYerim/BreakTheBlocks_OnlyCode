#include "Renderer.h"
#define PI 3.14

Renderer::Renderer(GLfloat width, GLfloat height)
{ 
    GLuint VertexArrayID;
    screenRatio = width / height;
    shader = loadShader(objectVertexShader, objectfragmentShader);
    particleShader = loadShader(particleVertexShader, particleFragmentShader);
    makeCirCle();
    screenWidth = width;
    screenHeight = height;
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
    
    glGenFramebuffers(0, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);
        
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, width, height);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
Renderer::~Renderer()
{
}
void Renderer::setupObjectRenderer( GameObject& gameObject, shape Shape )
{ 
    GLuint ColorSize;
    GLuint VertexSize;
    switch (Shape)
    {
    case CIRCLE:
        ColorSize = sizeof(circleColor);
        VertexSize = sizeof(circleVertexBuffer);
        gameObject = GameObject(circleVertexBuffer, circleColor, VertexSize, ColorSize);
        gameObject.drawCount = 36;
        break;
    case RECTANGLE:
       ColorSize = sizeof(rectangleVertexBuffer);
       VertexSize = sizeof(rectangleColorBuffer);
       gameObject = GameObject(rectangleVertexBuffer, VertexSize, ColorSize , 0.0f, 0.5f, 0.0f);
       gameObject.drawCount = 6;
       break;
    default:
       break;
    }

    //glGenBuffers(1, &gameObject.vertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, gameObject.vertexPoseSize * sizeof(GLint), gameObject.vertexPosition, GL_STATIC_DRAW);
    //glGenBuffers(1, &gameObject.colorBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    //glBufferData(GL_ARRAY_BUFFER, gameObject.colorPoseSize * sizeof(GLint), gameObject.colorPosition, GL_STATIC_DRAW);

}
void Renderer::updateRenderer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void Renderer::makeCirCle()
{
    //circle 만들어주기
    GLfloat xPos[12];
    GLfloat yPos[12];

    for (int i = 0; i < 12; ++i)
    {
        xPos[i] = cos(PI / 180 * 30 * (i));
        yPos[i] = sin(PI / 180 * 30 * (i));
    }
    int posNum = 0;
    for (int i = 0; i < 12* 3 * 3; i += 9)
    {
        circleVertexBuffer[i] = xPos[posNum];
        circleVertexBuffer[i + 1] = yPos[posNum];
        circleVertexBuffer[i + 2] = 0;
     
        if (i == 11 * 3 * 3 )
        {
            circleVertexBuffer[i + 3] = xPos[0];
            circleVertexBuffer[i + 4] = yPos[0];
            circleVertexBuffer[i + 5] = 0;
        }
        else
        {
            circleVertexBuffer[i + 3] = xPos[posNum + 1];
            circleVertexBuffer[i + 4] = yPos[posNum + 1];
            circleVertexBuffer[i + 5] = 0;

        }

        circleVertexBuffer[i + 6] = 0;
        circleVertexBuffer[i + 7] = 0;
        circleVertexBuffer[i + 8] = 0;

        ++posNum;
    }

    for (int i = 0; i < 12 * 3 * 3; i+=3)
    {
        circleColor[i] = 0.51f;
        circleColor[i+1] = 0.65f;
        circleColor[i+2] = 1.0f;
    }
   

}
void Renderer::drawGameObject(GameObject& gameObject)
{ 
    glUseProgram(shader);
    
    GLuint attribPosLoc = glGetAttribLocation(shader, "aPos");
    glGenBuffers(1, &gameObject.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.vertexPoseSize * sizeof(GLint), gameObject.vertexPosition, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribPosLoc);
    glVertexAttribPointer(attribPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint attribColorLoc = glGetAttribLocation(shader, "aColor");
    glGenBuffers(1, &gameObject.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.colorPoseSize * sizeof(GLint), gameObject.colorPosition, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribColorLoc);
    glVertexAttribPointer(attribColorLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint uniformRatio = glGetUniformLocation(shader, "aRatio");
    glUniform1f(uniformRatio, screenRatio);

    if (gameObject.colorPosition != NULL)
    {
        GLfloat glX;
        GLfloat glY;
        transGameWorldToGL(300.0f,300.0f, screenRatio, gameObject.Position.x, gameObject.Position.y, &glX, &glY);

        GLuint uniformTransform = glGetUniformLocation(shader, "aTransX");
        glUniform1f(uniformTransform, glX);

        GLuint uniformTransformY = glGetUniformLocation(shader, "aTransY");
        glUniform1f(uniformTransformY, glY);

        GLuint uniformSizeX = glGetUniformLocation(shader, "aSizeX");
        glUniform1f(uniformSizeX, gameObject.getScale().x / 300.0f);
        
        GLuint uniformSizeY = glGetUniformLocation(shader, "aSizeY");
        glUniform1f(uniformSizeY, gameObject.getScale().y / 300.0f);    

        GLuint uniformScreen = glGetUniformLocation(shader, "u_resolution");
        glUniform2f(uniformScreen, screenWidth, screenHeight);

        GLuint uinformisDot = glGetUniformLocation(shader, "u_isDot");
        glUniform1i(uinformisDot, gameObject.isDot);
    }
    glDrawArrays(GL_TRIANGLES, 0, gameObject.drawCount);
    glDeleteBuffers(1, &gameObject.colorBuffer);
    glDeleteBuffers(1, &gameObject.vertexBuffer);
    glDisableVertexAttribArray(0);
}
void Renderer::drawParticle(Particle& particle, GLboolean isGravity, GLboolean isScaling, GLboolean isAlphaChange)
{
    glUseProgram(particleShader);

    GLuint attribPosLoc = glGetAttribLocation(particleShader, "aPos");
    glGenBuffers(1, &particle.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertexBuffer) * sizeof(GLint), &rectangleVertexBuffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribPosLoc);
    glVertexAttribPointer(attribPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));


    GLuint uniformColor = glGetUniformLocation(particleShader, "v_Color");
    glUniform4f(uniformColor, particle.Color.x  , particle.Color.y, particle.Color.z, particle.Alpha);

    GLuint uniformScale = glGetUniformLocation(particleShader, "scale");
    glUniform3f(uniformScale, particle.Scale.x, particle.Scale.y, particle.Scale.z);

    GLuint uniformDir = glGetUniformLocation(particleShader, "direction");
    glUniform3f(uniformDir, particle.Velocity.x, particle.Velocity.y, particle.Velocity.z);

    GLuint uniformRatio = glGetUniformLocation(particleShader, "aRatio");
    glUniform1f(uniformRatio, screenRatio);

    GLfloat glX;
    GLfloat glY;

    transGameWorldToGL(300.0f, 300.0f, screenRatio, particle.Position.x, particle.Position.y, &glX, &glY);
    GLuint uniformTrans = glGetUniformLocation(particleShader, "transform");
    glUniform3f(uniformTrans, glX, glY, particle.Position.z);

   // float scalePerTime = pow(0.99f, particle.durationTime);
    
    GLuint uniformTimeScale = glGetUniformLocation(particleShader, "durationTime");
    
    glUniform1f(uniformTimeScale, particle.durationTime);

    GLuint uniformLifeTime = glGetUniformLocation(particleShader, "lifeTime");
    glUniform1f(uniformLifeTime, particle.Life);

    GLuint uniformIsGravity = glGetUniformLocation(particleShader, "isGravity");
    glUniform1i(uniformIsGravity, isGravity);
    
    GLuint uniformIsScaling = glGetUniformLocation(particleShader, "isScaling");
    glUniform1i(uniformIsScaling, isScaling);

    GLuint uniformisAlphachange = glGetUniformLocation(particleShader, "isAlphaChange");
    glUniform1i(uniformisAlphachange, isAlphaChange);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDeleteBuffers(1, &particle.vertexBuffer);
    glDisableVertexAttribArray(0);
}
