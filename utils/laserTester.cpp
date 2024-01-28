#include "recieve.h"
#include "localization.h"
#include "laserScaler.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <tuple>
#include <iostream>

// Function to create an image from 2D points
cv::Mat createImageFromPoints(const std::vector<std::tuple<float, float, int>> &points, int width, int height)
{
    // Find the min and max values of x and y
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for (const auto &point : points)
    {
        float x, y;
        std::tie(x, y, std::ignore) = point; // Ignore the angle
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }

    // Calculate scale factors to fit points within the image dimensions
    float scaleX = width / (maxX - minX);
    float scaleY = height / (maxY - minY);

    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC1);

    for (const auto &point : points)
    {
        float x, y;
        std::tie(x, y, std::ignore) = point;

        // Scale and translate points
        int imgX = static_cast<int>((x - minX) * scaleX);
        int imgY = static_cast<int>((y - minY) * scaleY);

        // Invert Y axis to align with the traditional coordinate system
        imgY = height - imgY - 1;

        if (imgX >= 0 && imgX < width && imgY >= 0 && imgY < height)
        {
            image.at<uchar>(imgY, imgX) = 255; // Set pixel to white
        }
    }

    // Display the points image for visualization
    cv::namedWindow("Points Visualization", cv::WINDOW_NORMAL);
    cv::imshow("Points Visualization", image);
    cv::waitKey(0); // Wait for a key press to close the window

    return image;
}

bool findIntersection(const cv::Vec4i &a, const cv::Vec4i &b, cv::Point2f &intersection) {
    // Line AB represented as a1x + b1y = c1
    double a1 = b[1] - a[1];
    double b1 = a[0] - b[0];
    double c1 = a1 * a[0] + b1 * a[1];  // Using point A (a[0], a[1])

    // Line CD represented as a2x + b2y = c2
    double a2 = b[3] - a[3];
    double b2 = a[2] - b[2];
    double c2 = a2 * a[2] + b2 * a[3];  // Using point C (a[2], a[3])

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        // The lines are parallel. No intersection.
        return false;
    } else {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        intersection = cv::Point2f(x, y);
        return true; // Intersection found
    }
}


void detectCorners(const std::vector<std::tuple<float, float, int>> &points)
{
    int width = 1000;  // Image width
    int height = 1000; // Image height

    // Calculate min and max values for x and y from points
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for (const auto &point : points)
    {
        float x, y;
        std::tie(x, y, std::ignore) = point; // Ignore the angle
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }

    // Scale factors
    float scaleX = width / (maxX - minX);
    float scaleY = height / (maxY - minY);

    cv::Mat pointCloudImage = createImageFromPoints(points, width, height);

    // Hough Transform parameters
    double rho = 0.5;
    double theta = CV_PI / 180;
    int threshold = 8;
    double minLineLength = 0.5 * scaleX;
    double maxLineGap = 1.5 * scaleX;

    // Detect lines using Hough Transform
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(pointCloudImage, lines, rho, theta, threshold, minLineLength, maxLineGap);

    std::cout << "Number of lines detected: " << lines.size() << std::endl;

    // Iterate over each line to find its midpoint
    for (const auto &line : lines) {
        int x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];
        cv::Point midpoint((x1 + x2) / 2, (y1 + y2) / 2);

        // Convert midpoint back to real-world coordinates
        float realX = midpoint.x / scaleX + minX;
        float realY = (height - midpoint.y - 1) / scaleY + minY;

        std::cout << "Line Midpoint (in meters): (" << realX << ", " << realY << ")" << std::endl;

        // Optional: Draw the line and its midpoint for visualization
        cv::line(pointCloudImage, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255), 1);
        cv::circle(pointCloudImage, midpoint, 5, cv::Scalar(0, 255, 0), -1);
    }

    // Create an image for line visualization
    cv::Mat lineImage = cv::Mat::zeros(height, width, CV_8UC1);

    // Draw detected lines on the line visualization image
    for (const auto &line : lines) {
        cv::line(lineImage, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(255), 1);
    }

    // Display the line visualization image
    cv::namedWindow("Detected Lines", cv::WINDOW_NORMAL);
    cv::imshow("Detected Lines", lineImage);
    cv::waitKey(0);
}

int main()
{
    Recv laserRecv;
    LaserDataExtractor laserDataExtractor;

    std::string laserData = laserRecv.recvScan();
    std::vector<float> ranges = laserDataExtractor.extractRanges(laserData);
    localization localizer(ranges);
    std::vector<std::tuple<float, float, int>> cartesianTouple = localizer.convertToCartesian(ranges);
    localizer.pyPlot(cartesianTouple);
    detectCorners(cartesianTouple);
}