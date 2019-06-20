#pragma once
#include "pch.h"
#include "Subject.h"

const int BLOCK_SIZE = 4096;
const int MAX_PERC = 100;


class Progress : public Subject
{
public:
	Progress();
	//Progress(int, int, bool, int);
	virtual ~Progress();

	bool Attach(Observer*) override;
	bool Detach(Observer*) override;
	void Notify() override;

	bool SetCurProgressValue(int);
	int GetCurProgressValue() const;
	bool SetEndProgressValue(int);
	int GetEndProgressValue() const;
	bool SetDelay(int);
	int GetDelay() const;
	void SetPermToStop(bool);
	bool GetPermToStop() const;
	bool End() const;

private:
	void SyncEnd();

private:
	int curProgressValue, endProgressValue; 
	bool cancel;
	int delay; 
	bool end;

	std::vector<Observer*> vecObs;
};


bool GetFileSize(std::ifstream&, int&, int&);
bool CopyFile(std::ifstream&, std::ofstream&, Progress*);

