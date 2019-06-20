#pragma once
#include "pch.h"

class Observer {
public:
	virtual void Update(Subject*) = 0;
};