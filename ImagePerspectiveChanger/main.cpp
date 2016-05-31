
/*
 *Mat imageSource = imread("D://Qt Projects//OpenCVTransformation//book2.jpg");
    Mat imageDestination = imread("D://Qt Projects//OpenCVTransformation//book1.jpg");
 *
 * */

#include <opencv2/opencv.hpp>
#include <vector>

static int click_count = 0;

using namespace cv;
using namespace std;

struct userData{
    Mat image;
    vector <Point2f> points;
};

void mouseHandler(int event, int x, int y, int flags, void * dataPointer){
    if (event == EVENT_LBUTTONDOWN){
        userData *data = ((userData* ) dataPointer );
        circle(data->image, Point(x,y), 3, Scalar(0, 0, 255), 5, CV_AA);
        imshow("Image", data->image);
        click_count++;
        cout << "Clicked : " << click_count << " times" << endl;
        if (data->points.size() < 4){
            data->points.push_back(Point2f(x, y));
        }
    }
}

int main(int argc, char ** argv){
    Mat image_source = imread("D://Qt Projects//OpenCVTransformation//book1.jpg");
    Size size(300, 400);
    Mat image_destination = Mat::zeros(size, CV_8UC3);

    vector <Point2f> points_destination;

    points_destination.push_back(Point2f(0, 0));
    points_destination.push_back(Point2f(size.width - 1, 0));
    points_destination.push_back(Point2f(size.width - 1, size.height - 1));
    points_destination.push_back(Point2f(0, size.height - 1));

    Mat temp_image = image_source.clone();

    userData data;
    data.image = temp_image;

    cout << "Click on the four corners of the book" << endl;

    imshow("Image", temp_image);

    setMouseCallback("Image", mouseHandler, &data);

    waitKey(0);

    Mat h = findHomography(data.points, points_destination);

    warpPerspective(image_source, image_destination, h, size);

    imshow("Show image", image_destination);

    waitKey(0);
    return 0;

}

