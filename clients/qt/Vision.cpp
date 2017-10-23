#include "Vision.h"

Vision::Vision() {
    printf("Vision: Abrindo conexao com o servidor de visao\n");
    this->client.open(true);
}

Vision::~Vision() {
    this->client.close();
}

void Vision::updateFieldstate(Fieldstate *f) {
	SSL_WrapperPacket packet;
	
	printf("Vision: Recebendo pacote do servidor de visao\n");
	if (this->client.receive(packet)) {
		if (packet.has_detection()) {
			SSL_DetectionFrame detection = packet.detection();

			//printf("Camera ID=%d FRAME=%d T_CAPTURE=%.4f\n",detection.camera_id(),detection.frame_number(),detection.t_capture());

			int balls_n = detection.balls_size();
			int robots_blue_n =  detection.robots_blue_size();
			int robots_yellow_n =  detection.robots_yellow_size();
			
			for (int i = 0; i < balls_n; i++) {
				SSL_DetectionBall ball = detection.balls(i);
				f->ball.mensure_confidence = ball.confidence();
				f->ball.position.x = ball.x();
				f->ball.position.y = ball.y();
			}

			for (int i = 0; i < robots_blue_n; i++) {
				SSL_DetectionRobot robot = detection.robots_blue(i);
				f->blue[i].id = robot.robot_id();
				f->blue[i].position.x = robot.x();
				f->blue[i].position.y = robot.y();
				f->blue[i].orientation = robot.orientation();
			}
			
			for (int i = 0; i < robots_yellow_n; i++) {
				SSL_DetectionRobot robot = detection.robots_yellow(i);
				f->yellow[i].id = robot.robot_id();
				f->yellow[i].position.x = robot.x();
				f->yellow[i].position.y = robot.y();
				f->yellow[i].orientation = robot.orientation();
			}

			/*//see if packet contains geometry data:
			if (packet.has_geometry()) {
				const SSL_GeometryData & geom = packet.geometry();
				printf("-[Geometry Data]-------\n");

				const SSL_GeometryFieldSize & field = geom.field();
				printf("Field Dimensions:\n");
				printf("  -field_length=%d (mm)\n",field.field_length());
				printf("  -field_width=%d (mm)\n",field.field_width());
				printf("  -boundary_width=%d (mm)\n",field.boundary_width());
				printf("  -goal_width=%d (mm)\n",field.goal_width());
				printf("  -goal_depth=%d (mm)\n",field.goal_depth());
				printf("  -field_lines_size=%d\n",field.field_lines_size());
				printf("  -field_arcs_size=%d\n",field.field_arcs_size());

				int calib_n = geom.calib_size();
				for (int i=0; i< calib_n; i++) {
				const SSL_GeometryCameraCalibration & calib = geom.calib(i);
				printf("Camera Geometry for Camera ID %d:\n", calib.camera_id());
				printf("  -focal_length=%.2f\n",calib.focal_length());
				printf("  -principal_point_x=%.2f\n",calib.principal_point_x());
				printf("  -principal_point_y=%.2f\n",calib.principal_point_y());
				printf("  -distortion=%.2f\n",calib.distortion());
				printf("  -q0=%.2f\n",calib.q0());
				printf("  -q1=%.2f\n",calib.q1());
				printf("  -q2=%.2f\n",calib.q2());
				printf("  -q3=%.2f\n",calib.q3());
				printf("  -tx=%.2f\n",calib.tx());
				printf("  -ty=%.2f\n",calib.ty());
				printf("  -tz=%.2f\n",calib.tz());

				if (calib.has_derived_camera_world_tx() && calib.has_derived_camera_world_ty() && calib.has_derived_camera_world_tz()) {
				printf("  -derived_camera_world_tx=%.f\n",calib.derived_camera_world_tx());
				printf("  -derived_camera_world_ty=%.f\n",calib.derived_camera_world_ty());
				printf("  -derived_camera_world_tz=%.f\n",calib.derived_camera_world_tz());
				}

				}
			}*/
		}
	}
}
