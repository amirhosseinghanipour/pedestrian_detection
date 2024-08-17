#include <opencv4/opencv2/opencv.hpp>

class PedestrianDetector {
private:
    cv::HOGDescriptor hog;

public:
    PedestrianDetector() {
        hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    }

    void detect(const cv::Mat& frame, std::vector<cv::Rect>& boxes, std::vector<double>& weights) {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);

        hog.detectMultiScale(gray, boxes, weights);
    }
};

class VideoProcessor {
private:
    cv::VideoCapture cap;
    cv::VideoWriter out;

public:
    VideoProcessor(int cameraId, const std::string& outputPath, double fps, cv::Size size)
        : cap(cameraId), out(outputPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size) {}

    void process() {
        while (true) {
            cv::Mat frame;
            cap >> frame;

            if (frame.empty()) {
                break;
            }

            cv::resize(frame, frame, cv::Size(640, 480));

            PedestrianDetector detector;
            std::vector<cv::Rect> boxes;
            std::vector<double> weights;
            detector.detect(frame, boxes, weights);

            for (const auto& box : boxes) {
                cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);
            }

            out << frame;
            cv::imshow("frame", frame);

            if ((cv::waitKey(1) & 0xFF) == 'q') {
                break;
            }
        }
    }

    ~VideoProcessor() {
        cap.release();
        out.release();
        cv::destroyAllWindows();
        cv::waitKey(1);
    }
};

int main() {
    VideoProcessor processor(0, "output.avi", 15.0, cv::Size(640, 480));
    processor.process();

    return 0;
}
