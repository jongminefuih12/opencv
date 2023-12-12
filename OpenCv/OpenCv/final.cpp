#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool mosaicEnabled = false;
bool grayscaleEnabled = false;

bool drawFaceRectangles(Mat& frame, const vector<Rect>& faces) {
    if (faces.empty()) {
        return false;
    }

    for (const auto& face : faces) {
        rectangle(frame, face, Scalar(0, 255, 0), 2);
    }

    return true;
}

void drawNoFaceDetected(Mat& frame) {
    putText(frame, "NO FACE DETECTED", Point(170, 270), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 3);
}

void grayscale(Mat& frame, CascadeClassifier& faceCascade) {
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    vector<Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

    if (!drawFaceRectangles(frame, faces)) {
        drawNoFaceDetected(frame);
        return;
    }

    for (const auto& face : faces) {
        Mat faceROI = frame(face);
        cvtColor(faceROI, faceROI, COLOR_BGR2GRAY);
        cvtColor(faceROI, frame(face), COLOR_GRAY2BGR);
    }
}

void mosaic(Mat& frame, CascadeClassifier& faceCascade) {
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    vector<Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

    /*if (!drawFaceRectangles(frame, faces)) {
        drawNoFaceDetected(frame); 실행했을 때 화면이 깨져서 주석처리 했습니다.
        return;
    }*/

    for (const auto& face : faces) {
        if (mosaicEnabled) {
            Mat faceROI = frame(face);
            resize(faceROI, faceROI, Size(10, 10), 0, 0, INTER_NEAREST);
            resize(faceROI, frame(face), face.size(), 0, 0, INTER_NEAREST);
        }
        else {
            rectangle(frame, face, Scalar(0, 255, 0), 2);
        }
    }
}

int main() {
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cerr << "Error opening the webcam" << endl;
        return -1;
    }

    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error loading face cascade file" << endl;
        return -1;
    }

    if (faceCascade.empty()) {
        cerr << "Error loading face cascade" << endl;
        return -1;
    }

    namedWindow("Face Effects", WINDOW_AUTOSIZE);

    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cerr << "Error reading frame" << endl;
            break;
        }

        char key = waitKey(30);
        if (key == 27) {
            break;
        }
        else if (key == 'm' || key == 'M') {
            mosaicEnabled = !mosaicEnabled;
            grayscaleEnabled = false;
        }
        else if (key == 'g' || key == 'G') {
            grayscaleEnabled = !grayscaleEnabled;
            mosaicEnabled = false;
        }

        if (!grayscaleEnabled && !mosaicEnabled) {
            Mat gray;
            cvtColor(frame, gray, COLOR_BGR2GRAY);

            vector<Rect> faces;
            faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

            if (!drawFaceRectangles(frame, faces)) {
                drawNoFaceDetected(frame);
            }
        }
        else if (grayscaleEnabled) {
            grayscale(frame, faceCascade);
        }
        else if (mosaicEnabled) {
            mosaic(frame, faceCascade);
        }

        imshow("Face Effects", frame);
    }

    destroyWindow("Face Effects");

    return 0;
}