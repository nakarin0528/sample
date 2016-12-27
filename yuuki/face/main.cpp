#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// 対象ファイル名
	string fileName = "lena.jpg";

	// 最大幅
	int maxWidth = 200;

	// 画像読み込み
	Mat originalImage = imread(fileName, CV_LOAD_IMAGE_COLOR);

	// 大きすぎる画像は小さくする
	if (originalImage.cols > maxWidth) {
		Mat resizedImage;

		float rate = 1.0 * maxWidth / originalImage.cols;
		resize(originalImage, resizedImage, Size(), rate, rate);
		originalImage = resizedImage;
	}


	/* ********* *
	*   顔検出
	* ********* */

	// 輝度画像に変換
	Mat grayImage;
	cvtColor(originalImage, grayImage, CV_RGB2GRAY);

	// 学習済み検出器の読み込み
	string cascadeName = "haarcascade_frontalface_alt.xml";
	//string cascadeName = "C:\develop\opencv2.4.11\sources\data\haarcascades\haarcascade_frontalface_alt.xml";
	CascadeClassifier cascade;
	if (!cascade.load(cascadeName))
		return -1;

	// 顔検出を実行
	vector<Rect> faces;
	cascade.detectMultiScale(
		grayImage,   // 画像
		faces,       // 出力される矩形
		1.1,         // 縮小用のスケール
		2,           // 最小の投票数
		CV_HAAR_SCALE_IMAGE,  // フラグ
		Size(30, 30) // 最小の矩形
		);

	// 矩形を描く
	for (vector<Rect>::iterator iter = faces.begin(); iter != faces.end(); iter++) {
		rectangle(originalImage, *iter, Scalar(255, 0, 0), 1);
	}

	// 表示
	imshow("out", originalImage);
	waitKey();

	return 0;
}

