/*
 * VisionThread.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: mtsne
 */

#include <VisionThread.h>

#include <thread>

#include "GripPipeline.h"
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

void VisionThread::Execute() {
	// Get the USB camera from CameraServer
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
	// Set the resolution
	camera.SetResolution(320, 240);
	camera.SetExposureManual(15);

	grip::GripPipeline pipeline;
	// Get a CvSink. This will capture Mats from the Camera
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();

	// Setup a CvSource. This will send images back to the Dashboard
	cs::CvSource outputStream = CameraServer::GetInstance()->
			PutVideo("Vision", 320, 240);

	// Mats are very memory expensive. Lets reuse this Mat.
	cv::Mat mat;

	while (true) {
		// Tell the CvSink to grab a frame from the camera and put it
		// in the source mat.  If there is an error notify the output.
		if (cvSink.GrabFrame(mat) == 0) {
			// Send the output the error.
			outputStream.NotifyError(cvSink.GetError());
			// skip the rest of the current iteration
			continue;
		}

		// run the GRIP pipeline
		pipeline.Process(mat);

		std::vector<std::vector<cv::Point> > &contours = *pipeline.getfindContoursOutput();
		bool foundContour = false;
		double xCenter = 0.0;
		if (contours.size() == 1)
		{
			foundContour = true;
			cv::Moments m = moments(contours[0], false);
			drawContours(mat, contours, 0, cv::Scalar(255, 0, 0), 5);
			xCenter = m.m10/m.m00;
		}

		outputStream.PutFrame(mat);

		// push x value to network table
		std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");
		table->PutBoolean("FoundContour", foundContour);
		table->PutNumber("XCenter", xCenter);
	}
}
