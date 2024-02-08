
#pragma once
#include "../AbstractEvent.h"
#include <gl/GL.h>
class EventChams : public Event<EventChams> {
public:
    EventChams(GLenum target, GLenum pname, GLint param) : target(target), pname(pname), param(param) {}

    GLenum getTarget() const { return this->target; }
    GLenum getPname() const { return this->pname; }
    GLint getParam() const { return this->param; }

private:
    GLenum target;
    GLenum pname;
    GLint param;
};

