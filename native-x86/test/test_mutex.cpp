#include "utils/Mutex.h"
int main(int argc, const char * argv[])
{
	android::Mutex mutex;
	mutex.lock();
	mutex.unlock();
	android::AutoMutex l(mutex);
	return 0;
}