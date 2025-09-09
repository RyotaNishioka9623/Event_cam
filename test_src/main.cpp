#include <metavision/sdk/base/events/event_cd.h>
#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/driver/raw_event_file_writer.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <atomic>

void count_events(const Metavision::EventCD *begin, const Metavision::EventCD *end){
    int counter = 0;

    //コールバック処理
    for (const Metavision::EventCD *ev = begin; ev != end; ++ev)
    {
        ++counter;

        std::cout << "Event received: coordinates(" << ev->x <<", "<< ev->y << "), t: " << ev->t << ", polarity:" << ev->p << std::endl;
    }

    std::cout << "There were " << counter << " events in this callback" << std::endl;
}

int main(int argc, char *argv[]){
    Metavision::Camera cam;

    if(argc >= 2)
    {
        cam = Metavision::Camera::from_file(argv[1]);
    }
    else
    {
        cam = Metavision::Camera::from_first_available();
    }

    cam.cd().add_callback(count_events);

    cam.start();

    while(cam.is_running()){}

    cam.stop();
}