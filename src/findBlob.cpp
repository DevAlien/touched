#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvblob.h>

#include "findBlob.h"

using namespace cvb;
using namespace std;

int DetectBlobsShowVideo(int captureWidth, int captureHeight) {
    /// Variables /////////////////////////////////////////////////////////
    CvCapture *capture;
    CvSize imgSize;

    IplImage *image, *frame, *segmentated, *labelImg;
    CvPoint pt1, pt2, pt3, pt4, pt5, pt6;
    CvScalar red, green, blue;
    int picWidth, picHeight, thickness;

    CvTracks tracks;
    CvBlobs blobs;
    CvBlob* blob;

    unsigned int result = 0;

    bool quit = false;
    ///////////////////////////////////////////////////////////////////////

    cvNamedWindow("Processed Video Frames", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Processed Video Frames", 750, 400);
    cvNamedWindow("Webcam Preview", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Webcam Preview", 200, 100);

    capture = cvCaptureFromCAM(-1);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, captureWidth);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, captureHeight);
    cvGrabFrame(capture);
    image = cvRetrieveFrame(capture);

    if (image == NULL) {
        return -1;
    }

    imgSize = cvGetSize(image);
    cout << endl << "Width (pixels): " << image->width;
    cout << endl << "Height (pixels): " << image->height << endl << endl;

    frame = cvCreateImage(imgSize, image->depth, image->nChannels);

    while (!quit && cvGrabFrame(capture)) {
        image = cvRetrieveFrame(capture);

        cvConvertScale(image, frame, 1, 0);

        segmentated = cvCreateImage(imgSize, 8, 1);

        cvInRangeS(image, CV_RGB(200, 200, 200), CV_RGB(255, 255, 255), segmentated);
        cvSmooth(segmentated, segmentated, CV_MEDIAN, 7, 7);

        labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);

        result = cvLabel(segmentated, labelImg, blobs);
        cvFilterByArea(blobs, 500, 1000000);
        cvRenderBlobs(labelImg, blobs, frame, frame,
                CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_COLOR, 1.);
        cvUpdateTracks(blobs, tracks, 200., 5);
        cvRenderTracks(tracks, frame, frame, CV_TRACK_RENDER_BOUNDING_BOX, NULL);

        red = CV_RGB(250, 0, 0);
        green = CV_RGB(0, 250, 0);
        blue = CV_RGB(0, 0, 250);

        thickness = 1;
        picWidth = frame->width;
        picHeight = frame->height;

        pt1 = cvPoint(picWidth / 2, 0);
        pt2 = cvPoint(picWidth / 2, picHeight);
        cvLine(frame, pt1, pt2, red, thickness);

        pt3 = cvPoint(0, picHeight / 2);
        pt4 = cvPoint(picWidth, picHeight / 2);
        cvLine(frame, pt3, pt4, red, thickness);

        cvShowImage("Webcam Preview", frame);
        cvShowImage("Processed Video Frames", segmentated);

        if (cvGreaterBlob(blobs)) {
            blob = blobs[cvGreaterBlob(blobs)];
            pt5 = cvPoint(picWidth / 2, picHeight / 2);
            pt6 = cvPoint(blob->centroid.x, blob->centroid.y);
            cvLine(frame, pt5, pt6, green, thickness);
            cvCircle(frame, pt6, 3, green, 2, CV_FILLED, 0);

            cvShowImage("Webcam Preview", frame);
            cvShowImage("Processed Video Frames", segmentated);

            cout << "Blobs found: " << blobs.size() << endl;
            cout << "Pixels labeled: " << result << endl;
            cout << "center-x: " << blob->centroid.x
                    << "   center-y: " << blob->centroid.y
                    << endl;
            cout << "offset-x: " << ((picWidth / 2)-(blob->centroid.x))
                    << "   offset-y: " << (picHeight / 2)-(blob->centroid.y)
                    << endl;
            cout << "\n";
        }

        char k = cvWaitKey(10)&0xff;
        switch (k) {
            case 27:
            case 'q':
            case 'Q':
                quit = true;
                break;
        }

        cvReleaseBlobs(blobs);
        cvReleaseImage(&labelImg);
        cvReleaseImage(&segmentated);
    }

    cvReleaseBlobs(blobs);

    cvReleaseImage(&labelImg);
    cvReleaseImage(&segmentated);
    cvReleaseImage(&frame);
    cvReleaseImage(&image);

    cvDestroyAllWindows();

    cvReleaseCapture(&capture);

    return 0;
}
