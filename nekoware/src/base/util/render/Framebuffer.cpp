#include "Framebuffer.h"


void Framebuffer::createBindFramebuffer(int width, int height)
{
	if (!isFramebufferEnabled())
	{
		this->framebufferWidth = width;
		this->framebufferHeight = height;
	}
	else
	{
		glEnable(GL_DEPTH_TEST);

		if (this->framebufferObject >= 0)
		{
			this->deleteFramebuffer();
		}

		this->createFramebuffer(width, height);
		this->checkFramebufferComplete();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void Framebuffer::deleteFramebuffer()
{
	if (isFramebufferEnabled())
	{
		this->unbindFramebufferTexture();
		this->unbindFramebuffer();

		if (this->depthBuffer > -1)
		{
			glDeleteRenderbuffers(1, &this->depthBuffer);
			this->depthBuffer = -1;
		}

		if (this->framebufferTexture > -1)
		{
			glDeleteTextures(1, &this->framebufferTexture);
			this->framebufferTexture = -1;
		}

		if (this->framebufferObject > -1)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &this->framebufferObject);
			this->framebufferObject = -1;
		}
	}
}

void Framebuffer::createFramebuffer(int width, int height)
{
	this->framebufferWidth = width;
	this->framebufferHeight = height;
	this->framebufferTextureWidth = width;
	this->framebufferTextureHeight = height;

	if (!isFramebufferEnabled())
	{
		this->framebufferClear();
	}
	else
	{
		glGenFramebuffers(1, &this->framebufferObject);
		glGenTextures(1, &this->framebufferTexture);

		if (this->useDepth)
		{
			glGenRenderbuffers(1, &this->depthBuffer);
		}

		this->setFramebufferFilter(GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, this->framebufferTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->framebufferTextureWidth, this->framebufferTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebufferObject);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->framebufferTexture, 0);

		if (this->useDepth)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, this->depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->framebufferTextureWidth, this->framebufferTextureHeight);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthBuffer);
		}

		this->framebufferClear();
		this->unbindFramebufferTexture();
	}
}

void Framebuffer::setFramebufferFilter(GLenum filter)
{
	if (isFramebufferEnabled())
	{
		this->framebufferFilter = filter;
		glBindTexture(GL_TEXTURE_2D, this->framebufferTexture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLfloat>(filter));
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLfloat>(filter));
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 10496.0F);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 10496.0F);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Framebuffer::checkFramebufferComplete()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
		{
			throw std::runtime_error("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
		}
		else if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
		{
			throw std::runtime_error("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
		}
		else if (status == GL_FRAMEBUFFER_UNSUPPORTED)
		{
			throw std::runtime_error("GL_FRAMEBUFFER_UNSUPPORTED");
		}
		else
		{
			throw std::runtime_error("Unknown framebuffer error");
		}
	}
}

void Framebuffer::bindFramebuffer()
{
	if (isFramebufferEnabled())
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebufferObject);
		glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
	}
}

void Framebuffer::unbindFramebuffer()
{
	if (isFramebufferEnabled())
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
	}
}

void Framebuffer::bindFramebufferTexture()
{
	if (isFramebufferEnabled())
	{
		glBindTexture(GL_TEXTURE_2D, this->framebufferTexture);
	}
}

void Framebuffer::unbindFramebufferTexture()
{
	if (isFramebufferEnabled())
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Framebuffer::framebufferClear()
{
	if (isFramebufferEnabled())
	{
		glClearColor(this->framebufferColor[0], this->framebufferColor[1], this->framebufferColor[2], this->framebufferColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

bool Framebuffer::isFramebufferEnabled()
{
	GLint framebufferEnabled = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebufferEnabled);
	return framebufferEnabled != 0;
}
