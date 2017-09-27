#include "fieldstate.h"

void Fieldstate::fieldUpdate(std::vector<Robot> *robotVector){

    SSL_DetectionFrame robotInfo;

    std::fstream input("../../CMakeFiles/grsim.dir/messages_robocup_ssl_detection.pb.cc.o", std::fstream::in | std::fstream::binary);

    if (!robotInfo.ParseFromIstream(&input)) {
        return;
    }

    for(int i = 0;i<robotInfo.robots_yellow_size();i++){
        SSL_DetectionRobot yellow = robotInfo.robots_yellow(i);

        Robot *robot = new Robot();

        robot->id = yellow.robot_id();
        robot->orientation = yellow.orientation();
        robot->x = yellow.x();
        robot->y = yellow.y();

        robotVector->insert(i,robot);
    }

    for(int i = 0;i<robotInfo.robots_blue_size();i++){
        SSL_DetectionRobot blue = robotInfo.robots_blue(i);

        Robot *robot = new Robot();

        robot->id = blue.robot_id();
        robot->orientation = blue.orientation();
        robot->x = blue.x();
        robot->y = blue.y();

        robotVector->insert(i+6,robot);
    }
}
