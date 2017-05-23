///*
// * Capture_BPM.cpp
// *
// *  Created on: Apr 24, 2017
// *      Author: alavery
// */
//
//#include "Test_Hounslow.cpp"
//#include <cstdio>
//#include <ctime>
//#include <vector>
//#include <utility>
//
//
//
//
//
//bool saw_beat(VideoCapture &capture, Mat &cameraFeed, Mat &HSV, Mat &threshold)
//{
//	//store image to matrix
//	capture.read(cameraFeed);
//	//convert frame from BGR to HSV colorspace
//	cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
//	//filter HSV image between values and store filtered image to
//	//threshold matrix
//	inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
//	//perform morphological operations on thresholded image to eliminate noise
//	//and emphasize the filtered object(s)
//	morphOps(threshold);
//	//pass in thresholded frame to our object tracking function
//	//this function will return the x and y coordinates of the
//	//filtered object
//	trackFilteredObject(x,y,threshold,cameraFeed);
//
//	//show frames
//	imshow(windowName2,threshold);
//	//imshow(windowName,cameraFeed);
//	//imshow(windowName1,HSV);
//
//
//	//delay 30ms so that screen can refresh.
//	//image will not appear without this waitKey() command
//	waitKey(30);
//}
//
//
//std::pair<double, double> capture_beat_data(int num_of_beats)
//{
//	bool trackObjects = true;
//	bool useMorphOps = true;
//	//Matrix to store each frame of the webcam feed
//	Mat cameraFeed;
//	//matrix storage for HSV image
//	Mat HSV;
//	//matrix storage for binary threshold image
//	Mat threshold;
//	//x and y values for the location of the object
//	int x=0, y=0;
//	//create slider bars for HSV filtering
//	createTrackbars();
//	//video capture object to acquire webcam feed
//	VideoCapture capture;
//	//open capture object at location zero (default location for webcam)
//	capture.open(0);
//	//set height and width of capture frame
//	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
//	//start an infinite loop where webcam feed is copied to cameraFeed matrix
//	//all of our operations will be performed within this loop
//	std::clock_t timer = std::clock();
//	double duration;
//	int beats = 0;
//	int captured_y = 0;
//	float start;
//	while(1){
//
//		if(captured_y < 280 && y > 285)
//		{
//			std::cout << "Beat ---> " << captured_y << " to " << y << std::endl;
//			beats++;
//			if(beats == 1) start = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
//			if(beats == 11)
//			{
//				duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//				std::cout << "Duration: " << duration << std::endl;
//				std::cout << "BPM: " << 60 / (duration / 10) << std::endl;
//				break;
//			}
//
//		}
//		captured_y = y;
//
//		//store image to matrix
//		capture.read(cameraFeed);
//		//convert frame from BGR to HSV colorspace
//		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
//		//filter HSV image between values and store filtered image to
//		//threshold matrix
//		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
//		//perform morphological operations on thresholded image to eliminate noise
//		//and emphasize the filtered object(s)
//		if(useMorphOps)
//		morphOps(threshold);
//		//pass in thresholded frame to our object tracking function
//		//this function will return the x and y coordinates of the
//		//filtered object
//		if(trackObjects)
//			trackFilteredObject(x,y,threshold,cameraFeed);
//
//		//show frames
//		imshow(windowName2,threshold);
//		//imshow(windowName,cameraFeed);
//		//imshow(windowName1,HSV);
//
//
//		//delay 30ms so that screen can refresh.
//		//image will not appear without this waitKey() command
//		waitKey(30);
//	}
//}
//
//
//
