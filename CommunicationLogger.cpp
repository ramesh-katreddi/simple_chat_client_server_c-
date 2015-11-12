#include<iostream>
#include "Constants.h"
#include "CommunicationLogger.h"
using namespace std;

CommunicationLogger* CommunicationLogger::pCommLogSingleton= NULL;

CommunicationLogger::CommunicationLogger()
{
}
/*
	funciton: getInstance
	purpose: singleton for communication logger.
*/
CommunicationLogger* CommunicationLogger::GetInstance()
{
	if (pCommLogSingleton== NULL) {
		pCommLogSingleton = new CommunicationLogger();
	}
	return pCommLogSingleton;
}