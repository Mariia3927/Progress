#include "pch.h"
#include "Progress.h"


Progress::Progress() : curProgressValue(0), endProgressValue(0), cancel(false), delay(0), vecObs {}, end(false)
{

}

//Progress::Progress(int val, int maxVal, bool canc, int del) : curProgressValue(val), endProgressValue(maxVal), cancel(canc), delay(del), 
																//vecObs {}
//{
	//SyncEnd();
//}


Progress::~Progress()
{
}

bool Progress::Attach(Observer *o)
{
	if (!o) {
		std::cout << "Error! Attach func got a nullpointer." << std::endl;
		return false;
	}

	this->vecObs.push_back(o);
	return true;
}

bool Progress::Detach(Observer *o)
{
	if (!o) {
		std::cout << "Error! Detach func got a nullpointer." << std::endl;
		return false;
	}

	std::vector<Observer*>::iterator beg = vecObs.begin();

	while(beg != vecObs.end()) {
		if (*beg == o) 
			beg = vecObs.erase(beg);
		else
			beg++;
	}
	return true;
}

void Progress::Notify()
{
	for (unsigned int i = 0; i < vecObs.size(); i++)
		vecObs[i]->Update(this);
}

bool Progress::SetCurProgressValue(int val)
{
	if (val < 0) {
		std::cout << "Error! ProgressValue cannot be less than zero.";
		return false;
	}
		
	curProgressValue = val;
	SyncEnd();

	Notify();
	return true;
}

int Progress::GetCurProgressValue() const
{
	return curProgressValue;
}

bool Progress::SetEndProgressValue(int val)
{
	if (val < 0) {
		std::cout << "Error! MaxValue cannot be less than zero.";
		return false;
	}

	endProgressValue = val;
	SyncEnd();
	return true;
}

int Progress::GetEndProgressValue() const
{
	return endProgressValue;
}

bool Progress::SetDelay(int del)
{
	if (delay < 0) {
		std::cout << "Error! Delay cannot be less than zero.";
		return false;
	}

	delay = del;
	return true;
}

int Progress::GetDelay() const
{
	return delay;
}

void Progress::SetPermToStop(bool c)
{
	if (c) {
		Sleep(delay);
	}
	cancel = c;
	Notify();
}

bool Progress::GetPermToStop() const
{
	return cancel;
}

bool Progress::End() const
{
	return end;
}

void Progress::SyncEnd()
{
	if (curProgressValue >= endProgressValue && curProgressValue != 0)
		end = true;
}

bool CopyFile(std::ifstream& fin, std::ofstream& fout, Progress *p)
{
	if (!fin) {
		std::cout << "Error! We cannot open the file." << std::endl;
		return false;
	}

	if (!fout) {
		std::cout << "Error! We cannot open the file." << std::endl;
		return false;
	}

	if (!p) {
		std::cout << "Error! The Progress object is incorrect." << std::endl;
		return false;
	}

	int numOfBlocks = 0, additionalNumOfBytes = 0;
	GetFileSize(fin, numOfBlocks, additionalNumOfBytes);

	if (additionalNumOfBytes > 0)
		numOfBlocks++;

	p->SetEndProgressValue(numOfBlocks);

	int tmp = 0;
	char buf[BLOCK_SIZE] = "";
	fin.seekg(0, std::ios::beg);
	fout.seekp(0, std::ios::beg);

	while (tmp < numOfBlocks && !p->GetPermToStop()) {
		fin.seekg(tmp * BLOCK_SIZE, std::ios::beg);

		if (tmp == numOfBlocks - 1 && additionalNumOfBytes > 0) {
			fin.read(buf, additionalNumOfBytes);
			fout.write(buf, additionalNumOfBytes);
		}
		else {
			fin.read(buf, BLOCK_SIZE);
			fout.write(buf, BLOCK_SIZE);
		}
		tmp++;

		p->SetCurProgressValue(tmp);
	}

	if (p->GetPermToStop())
		fout.clear();

	return true;
}

bool GetFileSize(std::ifstream& f, int& numOfBlocks, int& additionalNumOfBytes) {

	if (!f) {
		std::cout << "Error! This file isn't opened!" << std::endl;
		return false;
	}

	f.seekg(0, std::ios::end);
	numOfBlocks = f.tellg() / BLOCK_SIZE;
	additionalNumOfBytes = f.tellg() % BLOCK_SIZE;
	f.seekg(0, std::ios::beg);

	return true;
}
