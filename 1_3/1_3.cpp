#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void CH(cv::Mat img);
void GVP(cv::VideoCapture cap);

int _tmain(int argc, _TCHAR* argv[])
{
	cv::VideoCapture cap("../video/himawari.avi");

	GVP(cap);

	return 0;
}


void GVP(cv::VideoCapture cap)
{
	int v_w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int v_h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int max_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CV_CAP_PROP_FPS);

	cv::VideoWriter writer("output/output.avi", CV_FOURCC_DEFAULT, fps, cv::Size(v_w, v_h), true);
	cv::Mat img;

	printf("max_frame:%04d\n", max_frame);

	for (int i = 0; i < max_frame; i++)
	{
		printf("frame:%04d\n", i);
		cap >> img;
		cv::imshow("color", img);

		CH(img);
		cv::imshow("gray", img);		
		cv::waitKey(1);

		writer << img;
	}
}

void CH(cv::Mat img)
{
	int x, y;

	int B, G, R, P;
	for (y = 0; y < img.rows; y++) {
		for (x = 0; x < img.cols; x++) {
			//printf("\tx:%04d y:%04d\n", x, y);
			B = img.at<cv::Vec3b>(y, x)[0];
			G = img.at<cv::Vec3b>(y, x)[1];
			R = img.at<cv::Vec3b>(y, x)[2];

			P = int(0.298912*double(B) + 0.586611*double(G + 0.114478*double(R)));

			img.at<cv::Vec3b>(y, x)[0] = P;
			img.at<cv::Vec3b>(y, x)[1] = P;
			img.at<cv::Vec3b>(y, x)[2] = P;

		}
	}

}