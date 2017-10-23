#ifndef VISION_H
#define VISION_H

#include <cstdio>

#include "../Classes/Geometrics.h"
#include "../Classes/Fieldstate.h"

#include "robocup_ssl_client.h"
#include "protobuf/messages_robocup_ssl_detection.pb.h"
#include "protobuf/messages_robocup_ssl_geometry.pb.h"
#include "protobuf/messages_robocup_ssl_wrapper.pb.h"

class Vision {
	public:
	Vision();
	~Vision();
	
    void updateFieldstate(Fieldstate *f);
	
	private:
	RoboCupSSLClient client;
};

#endif
