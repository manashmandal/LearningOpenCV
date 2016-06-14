
#define image_link "C://Users//Manash//AndroidStudioProjects//TestApplication//app//src//main//res//drawable//a.jpg"


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;

int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void*);
void Dilation(int, void*);

int main(void){
    src=  imread(image_link);

    namedWindow("Erosion Demo", CV_WINDOW_NORMAL);
    namedWindow("Dilation Demo", CV_WINDOW_NORMAL);
    cv::moveWindow("Dilation Demo", src.cols, 0);

    createTrackbar("Element\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo", &erosion_elem, max_elem, Erosion);

    createTrackbar("Kernel Size:\n 2n + 1", "Erosion Demo", &erosion_size, max_kernel_size, Erosion);

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo", &dilation_elem, max_elem, Dilation);

    createTrackbar("Kernel Size: \n 2n + 1", "Dilation Demo", &dilation_size, max_kernel_size, Dilation);

    Erosion(0, 0);
    Dilation(0, 0);

    waitKey(0);
}

void Erosion(int, void *){
    int erosion_type;

    switch(erosion_elem){
        case 0:
            erosion_type = MORPH_RECT;
            break;
        case 1:
            erosion_type = MORPH_CROSS;
            break;
        case 2:
            erosion_type = MORPH_ELLIPSE;
        break;
        default:
            erosion_type = MORPH_RECT;
            break;
    }

    Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

    erode(src, erosion_dst, element);
    imshow("Erosion Demo", erosion_dst);
}

void Dilation(int, void *){
    int dilation_type;

    switch(dilation_elem){
        case 0:
            dilation_type = MORPH_RECT;
            break;
        case 1:
            dilation_type = MORPH_CROSS;
            break;
        case 2:
            dilation_type = MORPH_ELLIPSE;
        break;
        default:
            dilation_type = MORPH_RECT;
            break;
    }

    Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));

    dilate(src, dilation_dst, element);
    imshow("Dilation Demo", dilation_dst);
}
