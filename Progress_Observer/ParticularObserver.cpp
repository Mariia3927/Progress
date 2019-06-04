#include "pch.h"
#include "ParticularObserver.h"


ParticularObserver::ParticularObserver() : curState(0), curOutputted(0)
{

}


ParticularObserver::~ParticularObserver()
{
}

void ParticularObserver::Update(Subject *s) 
{
	if (dynamic_cast<Progress*>(s))
		Update((Progress*)s);
}

void ParticularObserver::Update(Progress *p) {
	curState = CalcProgress(p->GetCurProgressValue(), p->GetEndProgressValue());

	ShowProgress(p);
}

int ParticularObserver::CalcProgress(int curProgrVal, int endProgrVal)
{
	if (curProgrVal < 0 || endProgrVal < 0) {
		std::cout << "Error! the progress values cannot be less than zero!" << std::endl;
		return 0;
	}

	int res = 0;
	if(endProgrVal != 0)
		res = curProgrVal * MAX_PERC / endProgrVal;

	return res;
}

void ParticularObserver::ShowProgress(const Progress *p)
{
	int dif = curState - curOutputted;
	if (dif > 0) {
		for (int i = 0; i < dif; i++)
			std::cout << "I";
	}
	curOutputted = curState;

	if (p->GetPermToStop())
		std::cout << "Operation cancelled!" << std::endl;

	if (p->End())
		std::cout << "\nEnd!" << std::endl;
}
