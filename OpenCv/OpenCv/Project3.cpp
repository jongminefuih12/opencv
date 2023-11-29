//#include <opencv2/opencv.hpp>
//
//bool mosaicEnabled = false;
//bool faceSwapEnabled = false;
//
//void mosaicFaces(cv::Mat& frame, cv::CascadeClassifier& faceCascade) {
//    cv::Mat gray;
//    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));
//
//    for (const auto& face : faces) {
//        if (mosaicEnabled) {
//            cv::Mat faceROI = frame(face);
//            cv::resize(faceROI, faceROI, cv::Size(10, 10), 0, 0, cv::INTER_NEAREST);
//            cv::resize(faceROI, frame(face), face.size(), 0, 0, cv::INTER_NEAREST);
//        }
//        else {
//            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
//        }
//    }
//}
//
//void facetoswap(cv::Mat& frame, cv::CascadeClassifier& faceCascade, cv::Mat& faceToSwap) {
//    // �׷��̽����Ϸ� ��ȯ
//    cv::Mat gray;
//    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//    // �� ����
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(gray, faces, 1.3, 5);
//
//    // �� ������ �簢�� �׸��� �� ��ü �� �̹��� �ռ�
//    for (const auto& face : faces) {
//        // ��ü �� �̹����� �� ũ�⿡ �°� ����
//        cv::Mat resizedFace;
//        cv::resize(faceToSwap, resizedFace, face.size());
//
//        // ������ �� �̹����� �����ӿ� �ռ�
//        resizedFace.copyTo(frame(cv::Rect(face.x, face.y, face.width, face.height)));
//    }
//}
//
//int main() {
//    // ��ķ ����
//    cv::VideoCapture cap(0);
//
//    if (!cap.isOpened()) {
//        std::cerr << "Error opening the webcam" << std::endl;
//        return -1;
//    }
//
//    // �� ������ ���� Cascade Classifier �ʱ�ȭ
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
//        std::cerr << "Error loading face cascade file" << std::endl;
//        return -1;
//    }
//
//    // ��ü�� �� �̹��� �ҷ�����
//    cv::Mat faceToSwap = cv::imread("face.jpg");
//    if (faceToSwap.empty()) {
//        std::cerr << "Error loading face to swap image." << std::endl;
//        return -1;
//    }
//
//    // â ����
//    cv::namedWindow("Face Effects", cv::WINDOW_AUTOSIZE);
//
//    while (true) {
//        cv::Mat frame;
//        cap >> frame;
//
//        if (frame.empty()) {
//            std::cerr << "Error reading frame" << std::endl;
//            break;
//        }
//
//        // 'm' Ű�� ���� �� ������ũ Ȱ��ȭ/��Ȱ��ȭ
//        // 'f' Ű�� ���� �� Face Swap Ȱ��ȭ/��Ȱ��ȭ
//        char key = cv::waitKey(30);
//        if (key == 27) {
//            break;
//        }
//        else if (key == 'm' || key == 'M') {
//            mosaicEnabled = !mosaicEnabled;
//        }
//        else if (key == 'f' || key == 'F') {
//            faceSwapEnabled = !faceSwapEnabled;
//        }
//
//        // Face Effects Ȱ��ȭ �� �ش� �Լ� ȣ��
//        if (mosaicEnabled) {
//            mosaicFaces(frame, faceCascade);
//        }
//        if (faceSwapEnabled) {
//            facetoswap(frame, faceCascade, faceToSwap);
//        }
//
//        // ������ ���
//        cv::imshow("Face Effects", frame);
//    }
//
//    cv::destroyWindow("Face Effects");
//
//    return 0;
//}