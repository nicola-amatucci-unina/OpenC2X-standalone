#include <utility/CommunicationSender.h>

CommunicationSender::CommunicationSender(string ownerModule, string portOut) {
	mOwnerModule = ownerModule;

	mContext = new zmq::context_t(1);
	mPublisher = new zmq::socket_t(*mContext, ZMQ_PUB);
	mPublisher->bind(("tcp://*:" + portOut).c_str());

	mLogger = new LoggingUtility(mOwnerModule);
}

CommunicationSender::~CommunicationSender() {
	mContext->close();
	mPublisher->close();
	delete mContext;
	delete mPublisher;
	delete mLogger;
}

void CommunicationSender::send(string envelope, string message) {
	s_sendmore(*mPublisher, envelope);
	s_send(*mPublisher, message);

	mLogger->logDebug(envelope + " sent");
}

void CommunicationSender::sendToHw(string message) {
	s_send(*mPublisher, message);

	mLogger->logDebug("sent to HW");
}

void CommunicationSender::sendGpsData(string envelope, string message) {
	s_sendmore(*mPublisher, envelope);
	s_send(*mPublisher, message);
}
