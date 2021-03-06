#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

void TSLVP(cv::VideoCapture cap);

int _tmain(int argc, _TCHAR* argv[])
{
	cv::VideoCapture cap("../video/himawari.avi");
	TSLVP(cap);

	return 0;
}

void TSL(cv::Mat img, cv::Mat img1, cv::Mat img2, cv::Mat img3)
{
	int x, y;

	int B[8], G[8], R[8];

	for (y = 1; y < img.rows - 1; y++) {
		for (x = 1; x < img.cols - 1; x++) {
			B[5] = img.at<cv::Vec3b>(y, x)[0];
			G[5] = img.at<cv::Vec3b>(y, x)[1];
			R[5] = img.at<cv::Vec3b>(y, x)[2];

			B[0] = img1.at<cv::Vec3b>(y, x)[0];
			G[0] = img1.at<cv::Vec3b>(y, x)[1];
			R[0] = img1.at<cv::Vec3b>(y, x)[2];


			B[1] = img1.at<cv::Vec3b>(y - 1, x)[0];
			G[1] = img1.at<cv::Vec3b>(y - 1, x)[1];
			R[1] = img1.at<cv::Vec3b>(y - 1, x)[2];


			B[2] = img1.at<cv::Vec3b>(y, x - 1)[0];
			G[2] = img1.at<cv::Vec3b>(y, x - 1)[1];
			R[2] = img1.at<cv::Vec3b>(y, x - 1)[2];


			B[3] = img1.at<cv::Vec3b>(y + 1, x)[0];
			G[3] = img1.at<cv::Vec3b>(y + 1, x)[1];
			R[3] = img1.at<cv::Vec3b>(y + 1, x)[2];


			B[4] = img1.at<cv::Vec3b>(y, x + 1)[0];
			G[4] = img1.at<cv::Vec3b>(y, x + 1)[1];
			R[4] = img1.at<cv::Vec3b>(y, x + 1)[2];

			B[6] = img2.at<cv::Vec3b>(y, x)[0];
			G[6] = img2.at<cv::Vec3b>(y, x)[1];
			R[6] = img2.at<cv::Vec3b>(y, x)[2];


			B[7] = B[1] + B[2] + B[3] + B[4] + B[5] + B[6] - 6 * B[0];
			G[7] = G[1] + G[2] + G[3] + G[4] + G[5] + G[6] - 6 * G[0];
			R[7] = R[1] + R[2] + R[3] + R[4] + R[5] + R[6] - 6 * R[0];

			B[7] += 127;
			G[7] += 127;
			R[7] += 127;

			std::max(std::min(B[7], 255), 0);
			std::max(std::min(G[7], 255), 0);
			std::max(std::min(R[7], 255), 0);

			img3.at<cv::Vec3b>(y, x)[0] = B[7];
			img3.at<cv::Vec3b>(y, x)[1] = G[7];
			img3.at<cv::Vec3b>(y, x)[2] = R[7];
		}
	}

}


void TSLVP(cv::VideoCapture cap)
{
	int v_w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int v_h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int max_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CV_CAP_PROP_FPS);

	cv::Mat Image[4];

	cv::VideoWriter writer("output/output.avi", CV_FOURCC_DEFAULT, fps, cv::Size(v_w, v_h), true);

	printf("max:%d\n\n", max_frame - 3);

	for (int i = 0; i < max_frame - 3; i++) {
		cap >> Image[2];
		printf("i:%d\n", i);
		Image[3] = Image[2].clone();

		if (i == 1) {
			Image[0] = Image[2].clone();
		}
		if (i == 0) {
			Image[1] = Image[2].clone();
			Image[0] = Image[2].clone();
		}

		TSL(Image[2], Image[1], Image[0], Image[3]);

		writer << Image[3];

		if (i < max_frame - 3) {
			Image[0] = Image[1].clone();
			Image[1] = Image[2].clone();
		}
	}
}