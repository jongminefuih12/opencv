//#include <opencv2/opencv.hpp>
//
//int main() {
//    // OpenCV를 통한 얼굴 인식을 위한 Cascade Classifier 초기화
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
//        std::cerr << "Error loading face cascade." << std::endl;
//        return -1;
//    }
//
//    // 대체할 얼굴 이미지 불러오기
//    cv::Mat faceToSwap = cv::imread("face_to_swap.jpg");
//    if (faceToSwap.empty()) {
//        std::cerr << "Error loading face to swap image." << std::endl;
//        return -1;
//    }
//
//    // 이미지 또는 비디오 파일 열기
//    cv::VideoCapture cap(0);  // 카메라를 사용하려면 0 대신 카메라 장치 번호를 사용하세요.
//    if (!cap.isOpened()) {
//        std::cerr << "Error opening video capture." << std::endl;
//        return -1;
//    }
//
//    cv::Mat frame;
//    while (true) {
//        // 프레임 읽기
//        cap >> frame;
//        if (frame.empty()) {
//            std::cerr << "Empty frame." << std::endl;
//            break;
//        }
//
//        // 그레이스케일로 변환
//        cv::Mat gray;
//        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//        // 얼굴 감지
//        std::vector<cv::Rect> faces;
//        faceCascade.detectMultiScale(gray, faces, 1.3, 5);
//
//        // 얼굴 주위에 사각형 그리기
//        for (const auto& face : faces) {
//            // 대체 얼굴 이미지를 얼굴 크기에 맞게 조절
//            cv::Mat resizedFace;
//            cv::resize(faceToSwap, resizedFace, face.size());
//
//            // 조절된 얼굴 이미지를 프레임에 합성
//            resizedFace.copyTo(frame(cv::Rect(face.x, face.y, face.width, face.height)));
//        }
//
//        // 결과 출력
//        cv::imshow("Face Swap", frame);
//
//        // 종료 조건
//        if (cv::waitKey(30) == 27) {
//            std::cout << "ESC key is pressed by the user. Stopping the video." << std::endl;
//            break;
//        }
//    }
//
//    // 창 닫기
//    cv::destroyAllWindows();
//
//    return 0;
//}