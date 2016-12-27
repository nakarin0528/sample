#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// �Ώۃt�@�C����
	string fileName = "lena.jpg";

	// �ő啝
	int maxWidth = 200;

	// �摜�ǂݍ���
	Mat originalImage = imread(fileName, CV_LOAD_IMAGE_COLOR);

	// �傫������摜�͏���������
	if (originalImage.cols > maxWidth) {
		Mat resizedImage;

		float rate = 1.0 * maxWidth / originalImage.cols;
		resize(originalImage, resizedImage, Size(), rate, rate);
		originalImage = resizedImage;
	}


	/* ********* *
	*   �猟�o
	* ********* */

	// �P�x�摜�ɕϊ�
	Mat grayImage;
	cvtColor(originalImage, grayImage, CV_RGB2GRAY);

	// �w�K�ς݌��o��̓ǂݍ���
	string cascadeName = "haarcascade_frontalface_alt.xml";
	//string cascadeName = "C:\develop\opencv2.4.11\sources\data\haarcascades\haarcascade_frontalface_alt.xml";
	CascadeClassifier cascade;
	if (!cascade.load(cascadeName))
		return -1;

	// �猟�o�����s
	vector<Rect> faces;
	cascade.detectMultiScale(
		grayImage,   // �摜
		faces,       // �o�͂�����`
		1.1,         // �k���p�̃X�P�[��
		2,           // �ŏ��̓��[��
		CV_HAAR_SCALE_IMAGE,  // �t���O
		Size(30, 30) // �ŏ��̋�`
		);

	// ��`��`��
	for (vector<Rect>::iterator iter = faces.begin(); iter != faces.end(); iter++) {
		rectangle(originalImage, *iter, Scalar(255, 0, 0), 1);
	}

	// �\��
	imshow("out", originalImage);
	waitKey();

	return 0;
}

