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

	// Start driver assist camera
	cs::UsbCamera driverCamera = CameraServer::GetInstance()->StartAutomaticCapture(1);

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

		std::vector<std::vector<cv::Point> > contours = *pipeline.getfindContoursOutput();
		bool foundContour = false;
		double xCenter = 0.0;
		if (contours.size() == 1)
		{
			foundContour = true;
			cv::Moments m = moments(contours[0], false);
			drawContours(mat, contours, 0, cv::Scalar(255, 0, 0), 5);
			xCenter = m.m10/m.m00;
		}
		else if (contours.size() == 2)
		{
			// found two contours
			foundContour = true;
			cv::Moments m0 = moments(contours[0], false);
			cv::Moments m1 = moments(contours[1], false);
			drawContours(mat, contours, 0, cv::Scalar(255, 0, 0), 5);
			drawContours(mat, contours, 1, cv::Scalar(255, 0, 0), 5);

			xCenter = ((m0.m10/m0.m00)+(m1.m10/m1.m00))*0.5;
		}
		else if (contours.size() > 2)
		{
			double yMin0 = 0;
			double yMin1 = 0;

			unsigned i0, i1;
			for(unsigned i=0; i<contours.size(); ++i)
			{
				cv::Moments m = moments(contours[i], false);

				if (m.m00 > 25.0) {
					double y = m.m01/m.m00;

					if (y > yMin0) {
						yMin0 = y;
						i0 = i;
					}
					else if(y > yMin1) {
						yMin1 = y;
						i1 = i;
					}
				}
			}

			cv::Moments m0 = moments(contours[i0], false);
			cv::Moments m1 = moments(contours[i1], false);

			drawContours(mat, contours, i0, cv::Scalar(255, 0, 0), 5);
			drawContours(mat, contours, i1, cv::Scalar(255, 0, 0), 5);

			xCenter = ((m0.m10/m0.m00)+(m1.m10/m1.m00))*0.5;
			foundContour = true;
		}
		else
		{
			foundContour = false;
		}




		outputStream.PutFrame(mat);

		// push x value to network table
		std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");
		table->PutBoolean("FoundContour", foundContour);
		table->PutNumber("XCenter", xCenter);
	}
}
