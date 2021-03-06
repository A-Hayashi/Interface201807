#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void RPVP(cv::VideoCapture cap);

int _tmain(int argc, _TCHAR* argv[])
{
	cv::VideoCapture cap("../video/tounan.avi");

	RPVP(cap);

	return 0;

}

void RPVP(cv::VideoCapture cap)
{
	int v_w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int v_h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int max_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CV_CAP_PROP_FPS);

	int x, y, i;

	cv::Mat img;
	cv::Mat CB(v_h, v_w, CV_8UC(max_frame), cv::Scalar(0));
	cv::Mat CG(v_h, v_w, CV_8UC(max_frame), cv::Scalar(0));
	cv::Mat CR(v_h, v_w, CV_8UC(max_frame), cv::Scalar(0));
	
	cv::VideoWriter writer("output/output.avi", CV_FOURCC_DEFAULT, fps, cv::Size(v_w, v_h));
	for (i = 0; i < max_frame; i++) {
		cap >> img;
		for (y = 0; y < img.rows; y++) {
			for (x = 0; x < img.cols; x++) {
				CB.at<uchar>(y, x*max_frame + i) = img.at<cv::Vec3b>(y, x)[0];
				CG.at<uchar>(y, x*max_frame + i) = img.at<cv::Vec3b>(y, x)[1];
				CR.at<uchar>(y, x*max_frame + i) = img.at<cv::Vec3b>(y, x)[2];

			}
		}
	}

	for (i = 0; i < max_frame; i++) {
		for (y = 0; y < img.rows; y++) {
			for (x = 0; x < img.cols; x++) {
				img.at<cv::Vec3b>(y, x)[0] = CB.at<uchar>(y, x*max_frame + (max_frame - 1 - i));
				img.at<cv::Vec3b>(y, x)[1] = CG.at<uchar>(y, x*max_frame + (max_frame - 1 - i));
				img.at<cv::Vec3b>(y, x)[2] = CR.at<uchar>(y, x*max_frame + (max_frame - 1 - i));

			}
		}
		writer << img;
	}


}