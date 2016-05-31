#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using std::cout;
using std::endl;


using namespace cv;


int main(void){


    cv::VideoCapture camera;
    camera.open(0);
    if (!camera.isOpened()){
        std::cout << "Can't open video cam" << std::endl;
        return -1;

    }

    //Get the height and width of frame of video
    double width = camera.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = camera.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Frame size: " << width << " x " << height << endl;

    cv::namedWindow("Video Camera", CV_WINDOW_AUTOSIZE);

    while(true){
        cv::Mat frame;
        bool success =  camera.read(frame);
        if (!success){
            cout << "Can't read frame" << endl;
            break;
        }

        Mat des;
        //Flips the image to mirror form
        flip(frame, des, 1);

        cv::imshow("My Video", des);

        if (waitKey(30) == 27) {
            cout << "Esc key pressed... exiting" << endl;
            break;
        }
    }
    return 0;
}
