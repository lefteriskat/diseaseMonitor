//main.cpp
#include <iostream>
#include "DiseaseMonitor.h"
#include "TopkArrayList.h"
#include "TopkMaxHeap.h"

using namespace std;

int main(int argc,char* argv[]) {

	DiseaseMonitor* diseaseMonitor = new DiseaseMonitor();

	if( !diseaseMonitor || !diseaseMonitor->readArguments(argc, argv))
	{
		delete diseaseMonitor;
		return -1;
	}

	diseaseMonitor->readPatientRecordsFile();
	diseaseMonitor->globalDiseaseStats(NULL, NULL);

	diseaseMonitor->readUserInput();

	delete diseaseMonitor;
	return 0;
}