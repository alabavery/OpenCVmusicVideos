/*
 * Main.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: alavery
 */

//#include <iostream>
//#include <vector>
#include "Test_Hounslow.cpp"
#include <highgui.h>
#include <cv.h>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;


struct Hounslow_Variables {
	int H_MIN ;
	int H_MAX ;
	int S_MIN ;
	int S_MAX ;
	int V_MIN ;
	int V_MAX ;
	//default capture width and height
	int FRAME_WIDTH ;
	int FRAME_HEIGHT ;
	//max number of objects to be detected in frame
	int MAX_NUM_OBJECTS ;
	//minimum and maximum object area
	int MIN_OBJECT_AREA ;
	int MAX_OBJECT_AREA ;
	//names that will appear at the top of each window
	string windowName ;
	string windowName1 ;
	string windowName2 ;
	string windowName3 ;
	string trackbarWindowName;
};


Hounslow_Variables prepare_to_Hounslow(VideoCapture &cap)
{
	Hounslow_Variables hv;
	//initial min and max HSV filter values.
	//these will be changed using trackbars
	hv.H_MIN = 20;
	hv.H_MAX = 49;
	hv.S_MIN = 104;
	hv.S_MAX = 256;
	hv.V_MIN = 160;
	hv.V_MAX = 256;
	//default capture width and height
	hv.FRAME_WIDTH = 640;
	hv.FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	hv.MAX_NUM_OBJECTS=50;
	//minimum and maximum object area
	hv.MIN_OBJECT_AREA = 20*20;
	hv.MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
	//names that will appear at the top of each window
	hv.windowName = "Original Image";
	hv.windowName1 = "HSV Image";
	hv.windowName2 = "Thresholded Image";
	hv.windowName3 = "After Morphological Operations";
	hv.trackbarWindowName = "Trackbars";
	createTrackbars();

	//set height and width of capture frame
	cap.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

	return hv;
}


VideoWriter create_video_writer(Mat &cameraFeed, string write_file_name)
{
	bool isColor = (cameraFeed.type() == CV_8UC3);
	//--- INITIALIZE VIDEOWRITER
	VideoWriter writer;
	int codec = CV_FOURCC('M', 'P', '4', 'V');  // select desired codec (must be available at runtime)
	double fps = 14.5319;                          // framerate of the created video stream
	writer.open(write_file_name, codec, fps, cameraFeed.size(), isColor);

	return writer;
}


float find_object_y(Mat &cameraFeed, Mat &HSV, Mat &threshold, Hounslow_Variables &hv, int &x, int &y)
{
	//convert frame from BGR to HSV colorspace
	cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
	//filter HSV image between values and store filtered image to
	//threshold matrix
	inRange(HSV,Scalar(hv.H_MIN,hv.S_MIN,hv.V_MIN),Scalar(hv.H_MAX,hv.S_MAX,hv.V_MAX),threshold);
	//perform morphological operations on thresholded image to eliminate noise
	//and emphasize the filtered object(s)
	morphOps(threshold);
	//pass in thresholded frame to our object tracking function
	//this function will return the x and y coordinates of the
	//filtered object
	trackFilteredObject(x,y,threshold,cameraFeed);

	return y;
}


bool saw_beat(int y, int previous_y)
{
	return y > 200 && previous_y < 190;
}



string WRITE_FILE_NAME = "./live.mp4";
string READ_FILE_NAME = "MovingBall2.mp4";



int main(int argc, char* argv[]) {

	VideoCapture cap(READ_FILE_NAME);
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	Hounslow_Variables hv = prepare_to_Hounslow(cap);

	Mat cameraFeed;
	cap >> cameraFeed;
	// check if we succeeded
	if (cameraFeed.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		return -1;
	}

	VideoWriter writer = create_video_writer(cameraFeed, WRITE_FILE_NAME);
	if (!writer.isOpened())
	{
		cerr << "Could not open the output video file for write\n";
		return -1;
	}

	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	//x and y values for the location of the object
	int x=0, y=0, previous_y=1000;
	int frames_since_previous_beat = 1000;

	int frames_since_first_beat = 0;
	bool beats_have_started = false;
	int beats = 0;
	cout << "Enter 's' to stop program." << endl;
	while(1)
	{
//		if(beats_have_started) frames_since_first_beat++;
		// copy next frame to cameraFeed and check if we succeeded
		if (!cap.read(cameraFeed))
		{
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		y = find_object_y(cameraFeed, HSV, threshold, hv, x, y);
		if(saw_beat(y, previous_y))
		{
			if(frames_since_previous_beat < 3) putText(cameraFeed,"Beat",Point(20,100),1,1,Scalar(0,255,0),2);
			previous_y = y;
			frames_since_previous_beat = 0;
//			beats++;
//			if(!beats_have_started) beats_have_started = true;
		}
		frames_since_previous_beat++;

		// encode the frame into the videofile stream
		writer.write(cameraFeed);

		// wait for a key with timeout long enough to show images
//		imshow("Live", cameraFeed);
		if (waitKey(5) >= 0)
			break;
		//if(beats > 4) break;
	}
//	float bpm = 1.0 / ((((float)frames_since_first_beat / 15.0) / 60.0) / 4.0);
//	cout << endl << bpm << endl;
	return 0;
}
//

