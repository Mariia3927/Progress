#pragma once
#include "pch.h"
#include "Observer.h"


class ParticularObserver : public Observer
{
public:
	ParticularObserver();
	virtual ~ParticularObserver();

	void Update(Subject*) override;
	void Update(Progress*);

private:
	int CalcProgress(int, int);
	void ShowProgress(const Progress *);

private:
	int curState, curOutputted;
};

