//#include "ALooper.h"
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/AString.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ADebug.h>
#include <iostream>
using namespace std;

// static
android::status_t PostAndAwaitResponse(
        const android::sp<android::AMessage> &msg, android::sp<android::AMessage> *response) {
			
    android::status_t err = msg->postAndAwaitResponse(response);

    if (err != android::OK) {
        return err;
    }

    if (!(*response)->findInt32("err", &err)) {
        err = android::OK;
    }

    return err;
}

class SimplePlayer:public android::AHandler
{
public:
	 SimplePlayer();
	android::status_t setDataSource(const char *path);
    android::status_t prepare();
    android::status_t start();
    android::status_t stop();
    android::status_t reset();
protected:
    virtual ~SimplePlayer();
    virtual void onMessageReceived(const android::sp<android::AMessage> &msg);
	android::status_t onPrepare();
    android::status_t onStart();
    android::status_t onStop();
    android::status_t onReset();
	enum {
		kWhatSetDataSource,
		kWhatSetSurface,
		kWhatPrepare,
		kWhatStart,
		kWhatStop,
		kWhatReset,
		kWhatDoMoreStuff,
	};
};
SimplePlayer::SimplePlayer(){
}
SimplePlayer::~SimplePlayer() {
}
android::status_t SimplePlayer::setDataSource(const char *path) {
    android::sp<android::AMessage> msg = new android::AMessage(kWhatSetDataSource, id());
    msg->setString("path", path);
    android::sp<android::AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}
android::status_t SimplePlayer::prepare() {
    android::sp<android::AMessage> msg = new android::AMessage(kWhatPrepare, id());
    android::sp<android::AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

android::status_t SimplePlayer::start() {
    android::sp<android::AMessage> msg = new android::AMessage(kWhatStart, id());
    android::sp<android::AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

android::status_t SimplePlayer::stop() {
    android::sp<android::AMessage> msg = new android::AMessage(kWhatStop, id());
    android::sp<android::AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

android::status_t SimplePlayer::reset() {
    android::sp<android::AMessage> msg = new android::AMessage(kWhatReset, id());
    android::sp<android::AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

android::status_t SimplePlayer::onPrepare(){
	cout<<__FUNCTION__<<endl;
	android::status_t err = android::OK;
	return err;
}
android::status_t SimplePlayer::onStart(){
	cout<<__FUNCTION__<<endl;
	android::status_t err = android::OK;
	return err;
}
android::status_t SimplePlayer::onStop(){
	cout<<__FUNCTION__<<endl;
	android::status_t err = android::OK;
	return err;
}
android::status_t SimplePlayer::onReset(){
	cout<<__FUNCTION__<<endl;
	android::status_t err = android::OK;
	return err;
}
void SimplePlayer::onMessageReceived(const android::sp<android::AMessage> &msg) {
	switch (msg->what()) {
        case kWhatSetDataSource:
		case kWhatPrepare:
			onPrepare();
		case kWhatStart:
			onStart();
		case kWhatStop:
			onStop();
		case kWhatReset:
			onReset();
			android::status_t err;
			uint32_t replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));
            android::sp<android::AMessage> response = new android::AMessage;
            response->setInt32("err", err);
            response->postReply(replyID);
	}
}
int main(int argc, const char * argv[])
{
	android::sp<SimplePlayer> player = new SimplePlayer;
	android::sp<android::ALooper> looper = new android::ALooper();
	looper->start();
	looper->registerHandler(player);
	player->prepare();
	player->start();
	player->stop();
	player->reset();
	return 0;
}