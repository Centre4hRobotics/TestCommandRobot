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
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

void VisionThread::Execute() {
	// Get the USB camera from CameraServer
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
	// Set the resolution
	camera.SetResolution(640, 480);
	camera.SetExposureManual(1);
	grip::GripPipeline pipeline;
	// Get a CvSink. This will capture Mats from the Camera
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	// Setup a CvSource. This will send images back to the Dashboard
	cs::CvSource outputStream = CameraServer::GetInstance()->
			PutVideo("Rectangle", 640, 480);

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
		// Put a rectangle on the image
		//rectangle(mat, cv::Point(180, 110), cv::Point(460, 370),
		//		cv::Scalar(255, 255, 255), 5);
		// Give the output stream a new image to display

		pipeline.Process(mat);

		outputStream.PutFrame(*pipeline.gethslThresholdOutput());
	}
}
