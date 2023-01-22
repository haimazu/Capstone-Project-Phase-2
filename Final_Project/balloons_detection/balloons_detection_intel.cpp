#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

#include <ipp.h>

const int rows = 14175;
std::vector<cv::Mat> outputs;
cv::Mat blob;

const std::vector<cv::Scalar> colors = { cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0) };

const float INPUT_WIDTH = 480.0;
const float INPUT_HEIGHT = 480.0;
const float SCORE_THRESHOLD = 0.58; //To filter low probability class scores
const float NMS_THRESHOLD = 0.45; //To remove overlapping bounding boxes
const float CONFIDENCE_THRESHOLD = 0.50; //Filters low probability detections

struct Detection
{
    int class_id;
    float confidence;
    cv::Rect box;
};

void load_net(cv::dnn::Net& net, bool is_cuda)
{
    auto result = cv::dnn::readNet("config_files/ballon_yolov5n_389e_480.onnx");
    if (is_cuda)
    {
        std::cout << "Attempty to use CUDA\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    }
    else
    {
        std::cout << "Running on CPU\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    net = result;
}

cv::Mat format_yolov5(const cv::Mat& source) {
    int col = source.cols;
    int row = source.rows;
    int _max = MAX(col, row);
    cv::Mat result = cv::Mat::zeros(_max, _max, CV_8UC3);
    source.copyTo(result(cv::Rect(0, 0, col, row)));
    return result;
}

void detect(cv::Mat& image, cv::dnn::Net& net, std::vector<Detection>& output)
{
    auto input_image = format_yolov5(image);

    // Create a blob from the image using OpenCV's dnn module - resize the input image
    cv::dnn::blobFromImage(input_image, blob, 1.0 / 255.0, cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false);
    net.setInput(blob);
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    // Get the output data from the model and calculate the scaling factors
    float* data = (float*)outputs[0].data;
    float x_factor = input_image.cols / INPUT_WIDTH;
    float y_factor = input_image.rows / INPUT_HEIGHT;

    // Create containers for class_ids, confidences and boxes
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (Ipp32s i = 0; i < rows; ++i) {
        Ipp32f confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD) {
            cv::Point class_id;
            confidences.push_back(confidence);
            class_ids.push_back(class_id.x);
            Ipp32f x = data[0];
            Ipp32f y = data[1];
            Ipp32f w = data[2];
            Ipp32f h = data[3];
            // Use IPP function to scale x, y, w, and h values
            float x_scaled = 0.0f, y_scaled = 0.0f, w_scaled = 0.0f, h_scaled = 0.0f;
            Ipp32f  left_temp = (x - 0.5 * w);
            Ipp32f  top_temp = (y - 0.5 * h);
            Ipp32f  width_temp = 0.0f;
            Ipp32f  height_temp = 0.0f;
            ippsMulC_32f(&left_temp, x_factor, &x_scaled, 1);
            ippsMulC_32f(&top_temp, y_factor, &y_scaled, 1);
            Ipp32f  width = (w * x_factor);
            Ipp32f  height = (h * y_factor);

            // Use IPP function to round left, top, width, and height values to nearest integer
            ippsFloor_32f(&x_scaled, &left_temp, 1);
            ippsFloor_32f(&y_scaled, &top_temp, 1);
            ippsFloor_32f(&width, &width_temp, 1);
            ippsFloor_32f(&height, &height_temp, 1);
            boxes.push_back(cv::Rect(left_temp, top_temp, width_temp, height_temp));
        }
        data += 7;
    }

    // Use OpenCV's dnn module to perform non-maximum suppression
    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);
    // Process the results of the non-maximum suppression
    for (int i = 0; i < nms_result.size(); i++) {
        int idx = nms_result[i];
        Detection result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }

    // Draw a dot at the center coordinates
    for (int i = 0; i < output.size(); i++) {
        int center_x = output[i].box.x + output[i].box.width / 2;
        int center_y = output[i].box.y + output[i].box.height / 2;
        cv::circle(image, cv::Point(center_x, center_y), 3, cv::Scalar(0, 0, 0), -1);
        std::cout << "The coordinates were sent to the laser " << "(" << center_x <<
            ", " << center_y << ")" << std::endl;
    }
}

int main(int argc, char** argv)
{
    cv::VideoCapture cap(2);

    // check if we succeeded
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the camera." << std::endl;
        return -1;
    }

    bool is_cuda = false;

    cv::dnn::Net net;
    load_net(net, is_cuda);

    auto start = std::chrono::high_resolution_clock::now();
    int frame_count = 0;
    cv::Mat frame;
    double fps = 0;

    cv::namedWindow("Drone Camera", cv::WINDOW_NORMAL);
    cv::resizeWindow("Drone Camera", 600, 400);

    while (true)
    {
        cap >> frame; // get a new frame from camera
        if (frame.empty()) break;

        std::vector<Detection> output;
        detect(frame, net, output);

        int detections = output.size();
        frame_count++;

        for (int i = 0; i < detections; ++i)
        {
            auto detection = output[i];
            auto box = detection.box;
            auto classId = detection.class_id;
            const auto color = colors[classId % colors.size()];
            cv::rectangle(frame, box, color, 2);
            cv::rectangle(frame, cv::Point(box.x, box.y - 20), cv::Point(box.x + box.width, box.y), color, cv::FILLED);
            int label1 = int(output[i].confidence * 100);
            std::string percentage = std::to_string(label1);
            percentage = ": " + percentage + "%";
            cv::putText(frame, "balloon" + percentage, cv::Point(box.x, box.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
        }

        if (frame_count >= 24) {
            auto end = std::chrono::high_resolution_clock::now();
            fps = frame_count * 1000.0 / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            frame_count = 0;
            start = std::chrono::high_resolution_clock::now();
        }

        if (fps > 0) {
            std::ostringstream fps_label;
            fps_label << std::fixed << std::setprecision(2);
            fps_label << "FPS: " << fps;
            std::string fps_label_str = fps_label.str();

            cv::putText(frame, fps_label_str.c_str(), cv::Point(10, 25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Drone Camera", frame);

        if(cv::waitKey(30) >= 0) break;
    }

    // On exit, release the video capture
    cap.release();

    return 0;
}
