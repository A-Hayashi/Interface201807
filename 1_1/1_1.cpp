#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void FSPV(cv::VideoCapture cap);

int _tmain(int argc, _TCHAR* argv[])
{	
	system("del .\\output\\*.bmp");

	cv::VideoCapture cap("../video/tounan.avi");

	FSPV(cap);

	return 0;
}


void FSPV(cv::VideoCapture cap)
{
	int v_w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int v_h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int max_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CV_CAP_PROP_FPS);

	cv::Mat img;

	std::ostringstream num;
	int key;


	for (int i = 0; i < max_frame; i++) {
		num << i;
		cap >> img;

		cv::putText(img, num.str(), { 0, 50 }, cv::FONT_HERSHEY_PLAIN, 4, (255, 255, 255), 5, cv::LINE_AA);
		cv::imshow("再生動画", img);
		key = cv::waitKey(100);

		if (key == 115) {
			printf("saved at %d\n", i);
			cv::imwrite("output/image" + num.str() + ".bmp", img);

		}

		num.str("");
	}

}