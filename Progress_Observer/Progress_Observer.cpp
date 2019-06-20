// Progress_Observer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main(int argc, char *argv[])
{
	ParticularObserver *obs = new ParticularObserver();
	Progress *mainProgress = new Progress();

	mainProgress->Attach(obs);
	mainProgress->SetDelay(1000);
	//mainProgress->SetPermToStop(true);

	std::string path1 = "Odin_doma_3.avi";
	std::string path2 = "Film.avi";

	std::ifstream fin(path1, std::ios::in | std::ios::binary);

	std::ofstream fout(path2, std::ios::out | std::ios::binary);

	CopyFile(fin, fout, mainProgress);

	fin.close();
	fout.close();

	mainProgress->Detach(obs);
	
	if (obs)
		delete obs;
	if (mainProgress)
		delete mainProgress;

	return 0;
}

