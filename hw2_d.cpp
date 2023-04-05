#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat image = imread("C:/my_images/Fig0310(b)(washed_out_pollen_image).tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cout << "Failed to load image" << std::endl;
        return -1;
    }

    // Apply Otsu thresholding
    double thresh = threshold(image, image, 0, 255, THRESH_BINARY | THRESH_OTSU);
    std::cout << "Otsu threshold: " << thresh << std::endl;

    // Show the binary image
    imshow("Binary image", image);
    waitKey(0);

    return 0;
}