// #############################################################################
// # File test_ev.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file test_ev.cpp
 * @brief Test pour l'ouverture du port serie d'Arduino
 *
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h>  // UNIX standard function definitions
#include <iostream>
#include <cstring>

cv::Mat capturedFrame;
bool imageCaptured = false;
bool programShouldFinish = false; // Flag to indicate the program should finish
int time_id = 0;

// Constants for movement steps and initial positions
const int STEP_SIZE = 5;
int posX = 120; // Initial X position
int posY = 120; // Initial Y position

// Function that configures the serial port
int open_serial(const char *device)
{
    int fd = open(device, O_RDWR | O_NOCTTY | O_SYNC); // Open the device at the path, e.g., /dev/ttyACM0

    if (fd < 0)
    {
        std::cerr << "Error opening " << device << ": " << strerror(errno) << std::endl;
        return -1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0)
    {
        std::cerr << "Error from tcgetattr: " << strerror(errno) << std::endl;
        return -1;
    }

    cfsetospeed(&tty, B9600); // 9600 baud
    cfsetispeed(&tty, B9600); // 9600 baud

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK; // disable break processing
    tty.c_lflag = 0;        // no signaling chars, no echo,
                            // no canonical processing
    tty.c_oflag = 0;        // no remapping, no delays
    tty.c_cc[VMIN] = 0;     // read doesn't block
    tty.c_cc[VTIME] = 5;    // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
                                       // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        std::cerr << "Error from tcsetattr: " << strerror(errno) << std::endl;
        return -1;
    }
    return fd;
}

/** Sends the coordinates to the serial Port */
void send_coordinates(int x, int y)
{
    static int fd = open_serial("/dev/ttyACM0"); // Adjust as needed for your system
    if (fd < 0)
        return;

    char buffer[50];
    int n = snprintf(buffer, sizeof(buffer), "%d %d\n", x, y);
    int w = write(fd, buffer, n);
    if (w != n)
    {
        std::cerr << "Error writing to serial port: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Coordinates X = " << x << ", Y = " << y << " sent." << std::endl;
    }
}

/**
 * @brief Handles mouse events in the "Decision" window
 *
 * @param event
 * @param x
 * @param y
 * @param userdata
 */
void on_decision_mouse(int event, int x, int y, int, void *)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::ofstream decisionFile("tmp3209803-ext34V3");

        if (x >= 50 && x <= 150 && y >= 25 && y <= 75) // "Keep" button
        {
            // Checking if "images" directory exists
            std::string folder = "images";
#if defined(_WIN32)
            _mkdir(folder.c_str());
#else
            mkdir(folder.c_str(), 0777);
#endif

            // Save the image in the "images" folder
            std::string filename = folder + "/codec-V1.jpeg";
            if (cv::imwrite(filename, capturedFrame))
            {
                std::cout << "Image captured and saved as '" << filename << "'" << std::endl;
                decisionFile << "1";
            }
            else
            {
                std::cerr << "Error: Could not save the image" << std::endl;
                decisionFile << "0";
            }
        }
        else if (x >= 160 && x <= 260 && y >= 25 && y <= 75) // "Discard" button
        {
            std::cout << "Image discarded" << std::endl;
            decisionFile << "0";
        }

        decisionFile.close();
        cv::destroyWindow("Captured Image");
        cv::destroyWindow("Decision");
        imageCaptured = false; // Reset the flag to capture new images

        programShouldFinish = true; // Set the flag to finish the program
    }
}

/**
 * @brief Captures the image if mouse is on the designated area
 *
 * @param event
 * @param x
 * @param y
 * @param userdata
 */
void on_mouse(int event, int x, int y, int, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN && !imageCaptured)
    {
        if (x >= 10 && x <= 110 && y >= 10 && y <= 60)
        {
            cv::Mat *frame = static_cast<cv::Mat *>(userdata);
            cv::Size targetSize(640, 480); // 480p resolution

            // Remove the button area from the frame
            cv::Mat frameWithoutButton = frame->clone();
            cv::rectangle(frameWithoutButton, cv::Point(10, 10), cv::Point(110, 60), cv::Scalar(0, 0, 0), cv::FILLED);

            // Calculate aspect ratio
            double aspectRatio = static_cast<double>(frameWithoutButton.cols) / frameWithoutButton.rows;
            int targetWidth, targetHeight;

            if (frameWithoutButton.cols > frameWithoutButton.rows)
            {
                targetHeight = targetSize.height;
                targetWidth = static_cast<int>(targetSize.height * aspectRatio);
            }
            else
            {
                targetWidth = targetSize.width;
                targetHeight = static_cast<int>(targetSize.width / aspectRatio);
            }

            // Resize the frame
            cv::Mat resizedFrame;
            cv::resize(frameWithoutButton, resizedFrame, cv::Size(targetWidth, targetHeight));

            // Crop to center
            int xOffset = (targetWidth - targetSize.width) / 2;
            int yOffset = (targetHeight - targetSize.height) / 2;
            cv::Rect cropRegion(xOffset, yOffset, targetSize.width, targetSize.height);
            capturedFrame = resizedFrame(cropRegion);

            // Display the captured image to the user
            cv::imshow("Captured Image", capturedFrame);

            // Create buttons for user decision
            cv::namedWindow("Decision");
            cv::Mat decisionMat(100, 300, CV_8UC3, cv::Scalar(255, 255, 255));
            cv::rectangle(decisionMat, cv::Point(50, 25), cv::Point(150, 75), cv::Scalar(0, 255, 0), cv::FILLED);
            cv::putText(decisionMat, "Keep", cv::Point(70, 55), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
            cv::rectangle(decisionMat, cv::Point(160, 25), cv::Point(260, 75), cv::Scalar(0, 0, 255), cv::FILLED);
            cv::putText(decisionMat, "Discard", cv::Point(170, 55), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
            cv::imshow("Decision", decisionMat);

            cv::setMouseCallback("Decision", on_decision_mouse);

            imageCaptured = true; // Set the flag to prevent multiple captures
        }
    }
}

int main()
{
    // Open the default camera (usually the first one detected by the system)
    cv::VideoCapture cap(4);

    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open video capture" << std::endl;
        return -9;
    }

    // Set camera resolution to a higher value if supported by the camera
    // Does not work for all computers
    // Disable the following two lines for cameras with lower resolution than that
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // Create a window to display the video feed
    cv::namedWindow("Video Feed");

    cv::Mat frame;
    cv::setMouseCallback("Video Feed", on_mouse, &frame);

    while (true)
    {
        if (cap.read(frame))
        {
            // Draw the button on the frame
            cv::rectangle(frame, cv::Point(10, 10), cv::Point(110, 60), cv::Scalar(0, 255, 0), cv::FILLED);
            cv::putText(frame, "Capture", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);

            // Display the frame
            cv::imshow("Video Feed", frame);

            int key = cv::waitKey(30); // Waits for a key event for a "delay" (30 milliseconds)
            if (key == 'q' || key == 27)
            { // 'q' or ESC to quit
                break;
            }
            else if (key == 'a')
            {                                           // Left arrow key
                posX = std::min(640, posX + STEP_SIZE); // Assuming 640 as max width
                if (posX > 180)
                {
                    posX = 180;
                }
            }
            else if (key == 'd')
            { // Right arrow key
                posX = std::max(0, posX - STEP_SIZE);
            }
            else if (key == 'w')
            { // Up arrow key
                posY = std::max(0, posY - STEP_SIZE);
            }
            else if (key == 's')
            {                                           // Down arrow key
                posY = std::min(480, posY + STEP_SIZE); // Assuming 480 as max height
                if (posY > 130)
                {
                    posY = 130;
                }
            }

            // Send updated coordinates to Arduino

            send_coordinates(posX, posY);

            // std::cerr << "HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << std::endl;
        }
        else
        {
            std::cerr << "Error: Could not read frame from video capture" << std::endl;
        }

        // // Break the loop if the user presses the 'q' key or if the program should finish
        // if (cv::waitKey(30) == 'q' || programShouldFinish)
        // {
        //     break;
        // }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
