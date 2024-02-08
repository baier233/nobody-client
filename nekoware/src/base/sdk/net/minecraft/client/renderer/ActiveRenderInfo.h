#pragma once

#include "../../../../Object.h"
#include "../../../../../util/math/geometry.h"


class CActiveRenderInfo
{
public:
	static Matrix ProjectionMatrix();
	static Matrix ModelViewMatrix();
	static int Get_VIEWPORT();
};

