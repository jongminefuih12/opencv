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
//    // 그레이스케일로 변환
//    cv::Mat gray;
//    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//    // 얼굴 감지
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(gray, faces, 1.3, 5);
//
//    // 얼굴 주위에 사각형 그리기 및 대체 얼굴 이미지 합성
//    for (const auto& face : faces) {
//        // 대체 얼굴 이미지를 얼굴 크기에 맞게 조절
//        cv::Mat resizedFace;
//        cv::resize(faceToSwap, resizedFace, face.size());
//
//        // 조절된 얼굴 이미지를 프레임에 합성
//        resizedFace.copyTo(frame(cv::Rect(face.x, face.y, face.width, face.height)));
//    }
//}
//
//int main() {
//    // 웹캠 열기
//    cv::VideoCapture cap(0);
//
//    if (!cap.isOpened()) {
//        std::cerr << "Error opening the webcam" << std::endl;
//        return -1;
//    }
//
//    // 얼굴 감지를 위한 Cascade Classifier 초기화
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
//        std::cerr << "Error loading face cascade file" << std::endl;
//        return -1;
//    }
//
//    // 대체할 얼굴 이미지 불러오기
//    cv::Mat faceToSwap = cv::imread("face.jpg");
//    if (faceToSwap.empty()) {
//        std::cerr << "Error loading face to swap image." << std::endl;
//        return -1;
//    }
//
//    // 창 생성
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
//        // 'm' 키를 누를 때 모자이크 활성화/비활성화
//        // 'f' 키를 누를 때 Face Swap 활성화/비활성화
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
//        // Face Effects 활성화 시 해당 함수 호출
//        if (mosaicEnabled) {
//            mosaicFaces(frame, faceCascade);
//        }
//        if (faceSwapEnabled) {
//            facetoswap(frame, faceCascade, faceToSwap);
//        }
//
//        // 프레임 출력
//        cv::imshow("Face Effects", frame);
//    }
//
//    cv::destroyWindow("Face Effects");
//
//    return 0;
//}