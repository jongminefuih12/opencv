//#include <opencv2/opencv.hpp>
//
//int main() {
//    // OpenCV�� ���� �� �ν��� ���� Cascade Classifier �ʱ�ȭ
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
//        std::cerr << "Error loading face cascade." << std::endl;
//        return -1;
//    }
//
//    // ��ü�� �� �̹��� �ҷ�����
//    cv::Mat faceToSwap = cv::imread("face_to_swap.jpg");
//    if (faceToSwap.empty()) {
//        std::cerr << "Error loading face to swap image." << std::endl;
//        return -1;
//    }
//
//    // �̹��� �Ǵ� ���� ���� ����
//    cv::VideoCapture cap(0);  // ī�޶� ����Ϸ��� 0 ��� ī�޶� ��ġ ��ȣ�� ����ϼ���.
//    if (!cap.isOpened()) {
//        std::cerr << "Error opening video capture." << std::endl;
//        return -1;
//    }
//
//    cv::Mat frame;
//    while (true) {
//        // ������ �б�
//        cap >> frame;
//        if (frame.empty()) {
//            std::cerr << "Empty frame." << std::endl;
//            break;
//        }
//
//        // �׷��̽����Ϸ� ��ȯ
//        cv::Mat gray;
//        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//        // �� ����
//        std::vector<cv::Rect> faces;
//        faceCascade.detectMultiScale(gray, faces, 1.3, 5);
//
//        // �� ������ �簢�� �׸���
//        for (const auto& face : faces) {
//            // ��ü �� �̹����� �� ũ�⿡ �°� ����
//            cv::Mat resizedFace;
//            cv::resize(faceToSwap, resizedFace, face.size());
//
//            // ������ �� �̹����� �����ӿ� �ռ�
//            resizedFace.copyTo(frame(cv::Rect(face.x, face.y, face.width, face.height)));
//        }
//
//        // ��� ���
//        cv::imshow("Face Swap", frame);
//
//        // ���� ����
//        if (cv::waitKey(30) == 27) {
//            std::cout << "ESC key is pressed by the user. Stopping the video." << std::endl;
//            break;
//        }
//    }
//
//    // â �ݱ�
//    cv::destroyAllWindows();
//
//    return 0;
//}