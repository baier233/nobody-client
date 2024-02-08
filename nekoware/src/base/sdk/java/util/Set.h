#pragma once

#include "Collection.h"

class Set : public Collection
{
public:
	using Collection::Collection;
	jobjectArray toArray();
};

