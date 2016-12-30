#include "utils/Thread.h"
#include<iostream>
#include <unistd.h>
using namespace std;
class TestThread:public android::Thread
{
	public:
	
	virtual void        		onFirstRef();
	virtual void        		onLastStrongRef(const void* id);
	virtual android::status_t   readyToRun();
	virtual bool        		threadLoop();
};
void TestThread::onFirstRef()
{
	cout<<"TestThread onFirstRef"<<endl;
}
void TestThread::onLastStrongRef(const void* id)
{
	cout<<"TestThread onLastStrongRef"<<endl;
}
android::status_t TestThread::readyToRun()
{
	cout<<"TestThread readyToRun"<<endl;
	return android::NO_ERROR;
}
bool TestThread::threadLoop()
{
	int i = 3;
	while(i--)
	{
		cout<<"TestThread threadLoop "<<i<<endl;
		sleep(2);
	}
	return false;
}
int main()
{
	android::sp<TestThread>th =new TestThread();
	//TestThread*th =new TestThread();
	th->run();
	th->join();
}