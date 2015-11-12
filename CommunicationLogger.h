#include<iostream>

/*
This must be a singleton instance to log the communication between client and server.
This needs to be singleton as if multiple objects try to access same file it gets corrupted.

In writing to file we need to use mutex mechanism or queuing requests(inefficient) or google glog.

TODO-- Due to non sufficient time could not write it.
*/
class CommunicationLogger {

public:
   static CommunicationLogger* GetInstance();
private:
   CommunicationLogger();
   static CommunicationLogger* pCommLogSingleton;		// singleton instance
};