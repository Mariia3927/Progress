#pragma once

#include "pch.h"
class Observer;

class Subject {

public:
	virtual bool Attach(Observer*) = 0;
	virtual bool Detach(Observer*) = 0;
	virtual void Notify() = 0;
};