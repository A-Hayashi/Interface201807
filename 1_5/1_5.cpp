#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void HVP(cv::VideoCapture cap, int s);



int _tmain(int argc, _TCHAR* argv[])
{
	cv::VideoCapture cap("../video/tounan.avi");

	HVP(cap, 2);

	return 0;
}

void HVP(cv::VideoCapture cap, int s)
{
	int v_w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int v_h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int max_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CV_CAP_PROP_FPS);

	cv::Mat Image;

	cv::VideoWriter writer("output/output.avi", CV_FOURCC_DEFAULT, fps, cv::Size(v_w, v_h), true);

	for (int i = 0; i < max_frame; i++) {
		cap >> Image;
		if (i%s == 0) {
			writer << Image;
		}
	}
}