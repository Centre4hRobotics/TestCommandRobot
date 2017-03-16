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

static const double DEGREES_PER_PIXEL = 0.0795; // math says .0795

void VisionThread::Execute() {

	// start vision camera manually, not through CameraServer since we never feed raw image to DS
	cs::UsbCamera visionCamera("USBCamera0", 0);
	// Set the resolution
	visionCamera.SetExposureManual(25);
	visionCamera.SetResolution(640, 480);
	visionCamera.SetBrightness(51.0);
	visionCamera.SetWhiteBalanceManual(4500);
	visionCamera.SetFPS(20);

	// create the camera sink
	cs::CvSink cvSink("opencv_USBCamera0");
	cvSink.SetSource(visionCamera);

	// Start driver assist camera
	cs::UsbCamera driverCamera = CameraServer::GetInstance()->StartAutomaticCapture(1);
	driverCamera.SetResolution(320,240);
	driverCamera.SetFPS(10);

	grip::GripPipeline pipeline;

	// Setup a CvSource. This will send images back to the Dashboard
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Vision", 640, 480);

	// Mats are very memory expensive. Lets reuse this Mat.
	cv::Mat mat;

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

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

		line(mat, cv::Point(320,0), cv::Point(320,480), cv::Scalar(0, 255, 0));

		std::vector<std::vector<cv::Point> > contours = *pipeline.getfilterContoursOutput();
		for(unsigned i = 0; i<contours.size(); ++i)
			drawContours(mat, contours, i, cv::Scalar(255, 0, 0), 5);

		bool foundContour = false;
		double xCenter = 0.0;
		if (contours.size() == 1)
		{
			foundContour = true;
			cv::Moments m = moments(contours[0], false);
			xCenter = m.m10/m.m00;
		}
		else if (contours.size() == 2)
		{
			// found two contours
			foundContour = true;
			cv::Moments m0 = moments(contours[0], false);
			cv::Moments m1 = moments(contours[1], false);

			xCenter = ((m0.m10/m0.m00)+(m1.m10/m1.m00))*0.5;
			double yCenter = ((m0.m01/m0.m00)+(m1.m01/m1.m00))*0.5;

			circle(mat, cv::Point(xCenter, yCenter), 5, cv::Scalar(0, 0, 255), 5);
		}
		else if (contours.size() > 2)
		{
			foundContour = false;
			double aMax0 = 0;
			double aMax1 = 0;

			unsigned i0=0, i1=0;
			for(unsigned i=0; i<contours.size(); ++i)
			{
				cv::Moments m = moments(contours[i], false);
				double area = m.m00;

				if (area > aMax0) {
					if (area > aMax1)
					{
						aMax1 = aMax0;
						aMax0 = area;
						i1 = i0;
						i0 = i;

					}
					else
					{
						aMax0 = area;
						i0 = i;
					}
				}
				else if(area > aMax1) {
					aMax1 = area;
					i1 = i;
				}
				//std::cout << "Area: " << area << " aMax0: " << aMax0 << " aMax1: " << aMax1 << " i0: " << i0 << " i1: " << i1 << std::endl;
			}

			cv::Moments m0 = moments(contours[i0], false);
			cv::Moments m1 = moments(contours[i1], false);


			xCenter = ((m0.m10/m0.m00)+(m1.m10/m1.m00))*0.5;
			double yCenter = ((m0.m01/m0.m00)+(m1.m01/m1.m00))*0.5;
			circle(mat, cv::Point(xCenter, yCenter), 5, cv::Scalar(0, 0, 255), 5);

			foundContour = true;

		}
		else
		{
			foundContour = false;
		}

		// display annotated vision image
		outputStream.PutFrame(mat);

		// push x value to network table

		double angleOffset = (xCenter-320)*DEGREES_PER_PIXEL;
		std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");
		table->PutBoolean("FoundContour", foundContour);
		table->PutNumber("XCenter", angleOffset);
		table->PutBoolean("NewFrame", true);
	}
}
