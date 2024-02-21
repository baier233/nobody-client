#pragma once
#include <Windows.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#define GLEW_STATIC
#include <GLES3/gl3.h>
#include <iostream>
#pragma comment(lib,"glew32s.lib")
class Framebuffer
{
public:
	int framebufferTextureWidth;
	int framebufferTextureHeight;
	int framebufferWidth;
	int framebufferHeight;
	bool useDepth;
	GLuint framebufferObject;
	GLuint framebufferTexture;
	GLuint depthBuffer;
	float framebufferColor[4];
	GLenum framebufferFilter;
	Framebuffer(int width, int height, bool useDepth)
	{
		this->useDepth = useDepth;
		this->framebufferObject = -1;
		this->framebufferTexture = -1;
		this->depthBuffer = -1;
		this->framebufferColor[0] = 1.0f;
		this->framebufferColor[1] = 1.0f;
		this->framebufferColor[2] = 1.0f;
		this->framebufferColor[3] = 0.0f;
		this->createBindFramebuffer(width, height);
	}
	void createBindFramebuffer(int width, int height);
	void deleteFramebuffer();
	void createFramebuffer(int width, int height);
	void setFramebufferFilter(GLenum filter);
	void checkFramebufferComplete();
	void bindFramebuffer();
	void unbindFramebuffer();
	void bindFramebufferTexture();
	void unbindFramebufferTexture();
	void framebufferClear();
	bool isFramebufferEnabled();
private:

};
