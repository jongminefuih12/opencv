//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <map>
//
//void ontrackbarmove(int position, void* userdata);
//void restoreoriginalface(int selected_face_id, int max_face_id, int mosaic_level, cv::mat& frame, const std::map<int, cv::rect>& tracked_faces, const cv::mat& original_roi);
//
//int main() {
//    cv::videocapture capture(0);
//
//    if (!capture.isopened()) {
//        std::cerr << "error: could not open a camera." << std::endl;
//        return 1;
//    }
//
//    cv::cascadeclassifier face_cascade;
//    face_cascade.load("haarcascade_frontalface_default.xml");
//
//    if (face_cascade.empty()) {
//        std::cerr << "error: could not load haar cascade classifier." << std::endl;
//        return 1;
//    }
//
//    cv::mat frame;
//    cv::namedwindow("face detection", cv::window_autosize);
//
//    std::map<int, cv::rect> tracked_faces;  // 감지된 얼굴을 저장하는 맵
//    cv::mat original_roi;  // 처음 감지된 얼굴에 대한 roi
//
//    int unique_face_id = 0;  // 고유한 얼굴 id
//    int selected_face_id = 0;  // 선택된 얼굴 id
//    int mosaic_level = 5;  // 모자이크 레벨
//
//    // 트랙바 생성
//    cv::createtrackbar("select face id", "face detection", &selected_face_id, unique_face_id - 1, ontrackbarmove, &tracked_faces);
//    cv::createtrackbar("mosaic level", "face detection", &mosaic_level, 10, ontrackbarmove, &tracked_faces);
//
//    while (true) {
//        capture.read(frame);
//
//        if (frame.empty()) {
//            std::cerr << "error: could not read frame." << std::endl;
//            break;
//        }
//
//        cv::mat gray;
//        cv::cvtcolor(frame, gray, cv::color_bgr2gray);
//
//        std::vector<cv::rect> faces;
//        face_cascade.detectmultiscale(gray, faces, 1.3, 5);
//
//        for (const cv::rect& face : faces) {
//            bool found_existing_face = false;
//            int existing_face_id = -1;
//
//            // 각 얼굴에 대해 이전에 추적된 얼굴과 비교
//            for (const auto& pair : tracked_faces) {
//                const int face_id = pair.first;
//                const cv::rect& tracked_face = pair.second;
//
//                // 새로운 얼굴과 기존 얼굴의 중심 좌표 비교
//                cv::point new_face_center(face.x + face.width / 2, face.y + face.height / 2);
//                cv::point tracked_face_center(tracked_face.x + tracked_face.width / 2, tracked_face.y + tracked_face.height / 2);
//
//                int distance = cv::norm(new_face_center - tracked_face_center);
//
//                // 중심 좌표 간의 거리가 어떤 임계값 이하인 경우 같은 얼굴로 처리
//                if (distance < 50) {
//                    found_existing_face = true;
//                    existing_face_id = face_id;
//                    break;
//                }
//            }
//
//            if (found_existing_face) {
//                // 기존 얼굴을 업데이트
//                tracked_faces[existing_face_id] = face;
//            }
//            else {
//                // 처음 감지된 얼굴에 대한 roi 저장
//                if (tracked_faces.empty()) {
//                    original_roi = frame(face).clone();
//                }
//
//                // 새로운 얼굴을 식별할 고유한 id를 할당
//                tracked_faces[unique_face_id] = face;
//                unique_face_id++;
//            }
//        }
//
//        // 선택된 얼굴에 대해 모자이크 제외하고 다시 그리기
//        restoreoriginalface(selected_face_id, unique_face_id, mosaic_level, frame, tracked_faces, original_roi);
//
//        for (const auto& pair : tracked_faces) {
//            const int face_id = pair.first;
//            const cv::rect& tracked_face = pair.second;
//
//            cv::rectangle(frame, tracked_face, cv::scalar(0, 255, 0), 2);
//            cv::puttext(frame, "face " + std::to_string(face_id), cv::point(tracked_face.x, tracked_face.y - 10),
//                cv::font_hershey_simplex, 0.5, cv::scalar(0, 255, 0), 2);
//        }
//
//        cv::imshow("face detection", frame);
//
//        if (cv::waitkey(30) == 'q') {
//            break;
//        }
//    }
//
//    capture.release();
//    cv::destroyallwindows();
//
//    return 0;
//}
//
//// 트랙바 이벤트 핸들러
//void ontrackbarmove(int position, void* userdata) {
//    std::map<int, cv::rect>* tracked_faces = static_cast<std::map<int, cv::rect>*>(userdata);
//
//    if (tracked_faces) {
//        // 아무 작업 없이 두어도 됩니다.
//        // 사용자 데이터의 변화를 반영하도록 하는 용도입니다.
//    }
//}
//
//// 선택된 얼굴에 대해 모자이크를 제외하고, 다시 원래의 얼굴로 복원
//void restoreoriginalface(int selected_face_id, int max_face_id, int mosaic_level, cv::mat& frame, const std::map<int, cv::rect>& tracked_faces, const cv::mat& original_roi) {
//    for (const auto& pair : tracked_faces) {
//        const int face_id = pair.first;
//        const cv::rect& tracked_face = pair.second;
//
//        if (face_id == selected_face_id) {
//            // 선택된 얼굴에 대해 모자이크 제외하고 다시 그리기
//            cv::mat roi = frame(tracked_face);
//            original_roi.copyto(roi);
//            cv::puttext(frame, "selected face id: " + std::to_string(selected_face_id) +
//                " mosaic level: " + std::to_string(mosaic_level),
//                cv::point(10, 20), cv::font_hershey_simplex, 0.5, cv::scalar(0, 255, 0), 2);
//        }
//        else {
//            // 선택되지 않은 얼굴에 대해 모자이크
//            cv::mat roi = frame(tracked_face);
//            cv::mat blurred_roi;
//            cv::gaussianblur(roi, blurred_roi, cv::size(55, 55), 0);
//            cv::addweighted(roi, 1.0 - static_cast<double>(mosaic_level) / 10, blurred_roi, static_cast<double>(mosaic_level) / 10, 0, roi);
//        }
//    }
//}