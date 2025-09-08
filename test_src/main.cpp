#include <metavision/sdk/base/events/event_cd.h>
#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/driver/raw_event_file_writer.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <atomic>
#include <memory>

int main() {
    using namespace Metavision;

    try {
        Camera cam = Camera::from_first_available();
        std::atomic<bool> recording(false);
        std::unique_ptr<RawEventFileWriter> writer;

        cam.cd().add_callback([&](const EventCD *begin, const EventCD *end) {
            if (recording && writer) {
                writer->add_events(begin, end);
            }
        });

        cam.start();

        std::cout << "Press 's' to start/stop recording, 'q' to quit.\n";

        while (true) {
            int key = cv::waitKey(1);
            if (key == 's') {
                if (!recording) {
                    std::cout << "Start recording...\n";
                    writer = std::make_unique<RawEventFileWriter>("output.raw", cam.geometry());
                    recording = true;
                } else {
                    std::cout << "Stop recording.\n";
                    recording = false;
                    writer.reset();
                }
            } else if (key == 'q') {
                std::cout << "Exit.\n";
                break;
            }
        }

        cam.stop();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}