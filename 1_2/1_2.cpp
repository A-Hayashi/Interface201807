#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void ALVP(cv::Mat img1, cv::Mat img2);
void AL(cv::Mat img, cv::Mat img2, cv::Mat img3, int i);

int _tmain(int argc, _TCHAR* argv[])
{
	cv::Mat img1 = cv::imread("input/input1.bmp");
	cv::Mat img2 = cv::imread("input/input2.bmp");

	ALVP(img1, img2);

	return 0;

}

void AL(cv::Mat img, cv::Mat img2, cv::Mat img3, int i)
{
	int x, y;

	int B[3], G[3], R[3];

	for (y = 0; y < img.rows; y++) {
		for (x = 0; x < img.cols; x++) {
			B[0] = img.at<cv::Vec3b>(y, x)[0];
			G[0] = img.at<cv::Vec3b>(y, x)[1];
			R[0] = img.at<cv::Vec3b>(y, x)[2];

			B[1] = img2.at<cv::Vec3b>(y, x)[0];
			G[1] = img2.at<cv::Vec3b>(y, x)[1];
			R[1] = img2.at<cv::Vec3b>(y, x)[2];

			if (i % 2 == 0)
			{
				B[2] = B[0];
				G[2] = G[0];
				R[2] = R[0];
			}
			else {
				B[2] = B[1];
				G[2] = G[1];
				R[2] = R[1];
			}

			B[2] = std::max(std::min(B[2], 255), 0);
			G[2] = std::max(std::min(G[2], 255), 0);
			R[2] = std::max(std::min(R[2], 255), 0);
			img3.at<cv::Vec3b>(y, x)[0] = B[2];
			img3.at<cv::Vec3b>(y, x)[1] = G[2];
			img3.at<cv::Vec3b>(y, x)[2] = R[2];
		}
	}

}

void ALVP(cv::Mat img1, cv::Mat img2)
{
	int v_w = img1.cols;
	int v_h = img1.rows;

	int fps = 4;
	int max_frame = fps * 5;

	cv::Mat img3 = img1.clone();
	cv::VideoWriter writer("output/output.avi", CV_FOURCC_DEFAULT, fps, cv::Size(v_w, v_h), true);

	for (int i = 0; i < max_frame; i++) {
		AL(img1, img2, img3, i);
		writer << img3;

		cv::imshow("経過", img3);
		cv::waitKey(1);
	}

}