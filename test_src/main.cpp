#include <metavision/sdk/base/events/event_cd.h>
#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/driver/raw_event_file_writer.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <atomic>
#include <vector>

// グローバル画像バッファ
cv::Mat event_image;
std::mutex img_mutex;

// コールバック関数
void count_events(const Metavision::EventCD *begin, const Metavision::EventCD *end){
    std::lock_guard<std::mutex> lock(img_mutex); // マルチスレッド対策

    for (const Metavision::EventCD *ev = begin; ev != end; ++ev){
        // 極性によって色を変える
        cv::Vec3b color = ev->p ? cv::Vec3b(0, 255, 0) : cv::Vec3b(0, 0, 255); // 緑 = ON, 赤 = OFF
        if (ev->y < event_image.rows && ev->x < event_image.cols)
            event_image.at<cv::Vec3b>(ev->y, ev->x) = color;
    }
}

int main(int argc, char *argv[]){
    Metavision::Camera cam;

    if(argc >= 2){
        cam = Metavision::Camera::from_file(argv[1]);
    } else {
        cam = Metavision::Camera::from_first_available();
    }

    // カメラ解像度に合わせて OpenCV 画像を作成
    auto cd = cam.cd();
    event_image = cv::Mat::zeros(cd.height(), cd.width(), CV_8UC3);

    // コールバック登録
    cd.add_callback(count_events);

    cam.start();

    cv::namedWindow("Event View", cv::WINDOW_NORMAL);

    while(cam.is_running()){
        cv::Mat display;
        {
            std::lock_guard<std::mutex> lock(img_mutex);
            display = event_image.clone(); // スレッドセーフにコピー
        }

        // 少しぼかすとイベントが見やすくなる
        cv::GaussianBlur(display, display, cv::Size(3, 3), 0);

        cv::imshow("Event View", display);
        int key = cv::waitKey(1);
        if(key == 27) // ESCキーで終了
            break;

        // 前回のイベントを消す場合はコメントアウトを外す
        // std::lock_guard<std::mutex> lock(img_mutex);
        // event_image.setTo(cv::Scalar(0, 0, 0));
    }

    cam.stop();
    cv::destroyAllWindows();
}