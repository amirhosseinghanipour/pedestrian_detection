# Pedestrian Detection using the HOG (Histograms of Oriented Gradients) Method

## Overview
This C++ code implements a pedestrian detection system using the OpenCV library. The system captures video from a camera, detects pedestrians in each frame using the Histogram of Oriented Gradients (HOG) descriptor and Support Vector Machine (SVM) classifier, and outputs the detected frames to a video file.

## Histogram of Oriented Gradients (HOG)
The HOG descriptor is a feature extraction technique used for object detection. It computes the distribution of gradient orientations in a region of interest, which is useful for detecting pedestrians. The HOG descriptor is calculated as follows:
- Divide the image into small cells.
- Compute the gradient of each pixel in each cell.
- Calculate the histogram of gradient orientations for each cell.
- Normalize the histograms to form the HOG descriptor.

## Support Vector Machine (SVM) Classifier
The SVM classifier is a machine learning algorithm used for classification. In this implementation, it is used to classify the HOG descriptors as either pedestrian or non-pedestrian. The SVM classifier works by finding the hyperplane that maximally separates the two classes.

## PedestrianDetector Class

The `PedestrianDetector` class is responsible for detecting pedestrians in a given image frame.

### Constructor

The constructor initializes the `hog` object with the default people detector, which is a pre-trained SVM classifier.

### Detect Method

The `detect` method takes a `cv::Mat` object representing the input frame, and two output vectors: `boxes` and `weights`. It detects pedestrians in the frame using the `hog` object and stores the detected bounding boxes and their corresponding weights in the output vectors.

The `detectMultiScale` method is used to detect pedestrians at multiple scales. It takes the input frame, the output vectors, and the following parameters:

- `winStride`: the stride of the sliding window.
- `padding`: the padding around the sliding window.
- `scale`: the scale factor between successive detections.
- `finalThreshold`: the final threshold for the detections.

## VideoProcessor Class

The `VideoProcessor` class is responsible for capturing video from a camera, processing each frame to detect pedestrians, and outputting the detected frames to a video file.

### Constructor

The constructor takes four parameters:

- `cameraId`: the ID of the camera to capture video from.
- `outputPath`: the path to the output video file.
- `fps`: the frame rate of the output video.
- `size`: the size of the output video frames.

It initializes the `cap` object to capture video from the specified camera, and the `out` object to write the output video file.

### Process Method

The `process` method captures video frames from the camera, resizes each frame to a fixed size, detects pedestrians using the `PedestrianDetector` class, and outputs the detected frames to the video file. It also displays the detected frames using `cv::imshow`.

### Destructor

The destructor releases the `cap` and `out` objects, closes all OpenCV windows, and waits for a key press using `cv::waitKey`.

## Main Function

The `main` function creates a `VideoProcessor` object with the specified camera ID, output file path, frame rate, and frame size, and calls its `process` method to start the pedestrian detection process.
