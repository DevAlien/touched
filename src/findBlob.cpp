#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvblob.h>

#include "findBlob.h"

//using namespace cvb;
//using namespace std;

bool FindBlob::manageKeys(char key) {
    //if(key != '\0')
        //std::cout << std::endl << "key: " << key << std::endl;
    switch (key) {
            case 27:
            case 'q':
            case 'Q':
                return true;
                break;
            case 'r':
                std::cout << std::endl << "Width (pixels): " << imgSize.width - scanArea.x;
                if((imgSize.width - scanArea.x - 20) <= 100) {
                    scanArea.x = imgSize.width - 100;
                    scanArea.width = 100;
                }
                else if((scanArea.width + scanArea.x + 20 ) < imgSize.width)
                    scanArea.x = scanArea.x + 20;
                else {

                    scanArea.width = imgSize.width - scanArea.x - 20;
                    scanArea.x = scanArea.x + 20;
                }
                break;
            case 'R':
                if(imgSize.width > (scanArea.x + scanArea.width + 20))
                    scanArea.width = scanArea.width + 20;
                else
                    scanArea.width = imgSize.width - scanArea.x;
                break;
            case 'd':
                if((imgSize.height - scanArea.y - 20) <= 100) {
                    scanArea.y = imgSize.height - 100;
                    scanArea.height = 100;
                }
                else if((scanArea.height + scanArea.y + 20 ) < imgSize.height)
                    scanArea.y = scanArea.y + 20;
                else {

                    scanArea.height = imgSize.height - scanArea.y - 20;
                    scanArea.y = scanArea.y + 20;
                }
                break;
            case 'D':
                if(imgSize.height > (scanArea.y + scanArea.height + 20))
                    scanArea.height = scanArea.height + 20;
                else
                    scanArea.height = imgSize.height - scanArea.y;
                break;
            case 'l':
                if((imgSize.width - scanArea.x - 20) <= 100) {
                    scanArea.x = imgSize.width - 100;
                    scanArea.width = 100;
                }
                else if((scanArea.x - 20 ) > 100)
                    scanArea.x = scanArea.x - 20;
                else {

                    scanArea.width = imgSize.width - scanArea.x - 20;
                    scanArea.x = scanArea.x + 20;
                }
                break;
            case 'L':
                if(scanArea.width - 20 > 100)
                    scanArea.width = scanArea.width - 20;
                else
                    scanArea.width = 100;
                break;
            case 'b':
                setCam(0);
        break;
            case 'a':
                setCam(1);
            case 'e':
                std::cout << "test: " << std::endl;
    currentTime = TUIO::TuioTime::getSessionTime();
    tuioServer->initFrame(currentTime);
            cursor = tuioServer->addTuioCursor(0.0765625,0.141667);currentTime = TUIO::TuioTime::getSessionTime();tuioServer->initFrame(currentTime);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
        tuioServer->updateTuioCursor(cursor,0.0865625,0.141667);currentTime = TUIO::TuioTime::getSessionTime();tuioServer->initFrame(currentTime);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.090625,0.141667);currentTime = TUIO::TuioTime::getSessionTime();tuioServer->initFrame(currentTime);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.11875,0.141667);
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.139062,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.167187,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.2,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.226562,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.242188,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.264062,0.141667);tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
tuioServer->updateTuioCursor(cursor,0.28125,0.141667);
tuioServer->updateTuioCursor(cursor,0.285937,0.141667);
tuioServer->updateTuioCursor(cursor,0.303125,0.147917);
tuioServer->updateTuioCursor(cursor,0.3125,0.152083);
tuioServer->updateTuioCursor(cursor,0.340625,0.1625);
currentTime = TUIO::TuioTime::getSessionTime();tuioServer->initFrame(currentTime);tuioServer->stopUntouchedMovingCursors();
    break;
        break;
        }

        return false;
}

void FindBlob::setCam(int cam) {
    cvReleaseCapture(&capture);
                capture = cvCaptureFromCAM(cam);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, captureWidth);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, captureHeight);
    cvGrabFrame(capture);
    image = cvRetrieveFrame(capture);
}

IplImage* cropImage(const IplImage *img, const CvRect region)
{
    IplImage *imageCropped;
    CvSize size;

    if (img->width <= 0 || img->height <= 0
        || region.width <= 0 || region.height <= 0) {
        //cerr << "ERROR in cropImage(): invalid dimensions." << endl;
        exit(1);
    }

    if (img->depth != IPL_DEPTH_8U) {
        //cerr << "ERROR in cropImage(): image depth is not 8." << endl;
        exit(1);
    }

    // Set the desired region of interest.
    cvSetImageROI((IplImage*)img, region);
    // Copy region of interest into a new iplImage and return it.
    size.width = region.width;
    size.height = region.height;
    imageCropped = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
    cvCopy(img, imageCropped);  // Copy just the region.

    return imageCropped;
}



void FindBlob::run(int captureWidth, int captureHeight) {
    FindBlob::captureWidth = captureWidth;
    FindBlob::captureHeight = captureHeight;
    loadVariables();
    loadTuioServer("127.0.0.1", 3333);
    while (!quit && cvGrabFrame(capture)) {
        currentTime = TUIO::TuioTime::getSessionTime();
        tuioServer->initFrame(currentTime);
        process();
        tuioServer->stopUntouchedMovingCursors();
        tuioServer->commitFrame();
    }
    cvReleaseBlobs(blobs);

    cvReleaseImage(&labelImg);
    cvReleaseImage(&segmentated);
    cvReleaseImage(&frame);
    cvReleaseImage(&image);

    cvDestroyAllWindows();

    cvReleaseCapture(&capture);
}

int FindBlob::loadVariables() {
    result = 0;
    quit = false;

    ///////////////////////////////////////////////////////////////////////
    red = CV_RGB(250, 0, 0);

    cvNamedWindow("Processed Video Frames", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Processed Video Frames", 750, 400);
    cvNamedWindow("Webcam Preview", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Webcam Preview", 200, 100);

    capture = cvCaptureFromCAM(0);
    setCam(1);

    if (image == NULL) {
        return -1;
    }
    imgSize = cvGetSize(image);
    imgSize2 = imgSize;
    imgSize2.width = imgSize2.width - 300;
    imgSize2.height = imgSize2.height - 300;
    scanArea.x = 1;
    scanArea.y = 1;
    scanArea.width = imgSize2.width;
    scanArea.height = imgSize2.height;
    std::cout << std::endl << "Width (pixels): " << imgSize2.width;
    std::cout << std::endl << "Width (pixels): " << image->width;
    std::cout << std::endl << "Height (pixels): " << image->height << std::endl << std::endl;
    
    frame = cvCreateImage(imgSize, image->depth, image->nChannels);
}

void FindBlob::process() {
    image = cvRetrieveFrame(capture);
    flipImage();

    segmentated = cvCreateImage(cvSize(scanArea.width, scanArea.height), 8, 1);
    image2 = cropImage(image, scanArea);
    cvSetImageROI((IplImage*)image,scanArea);
    cvCopy(image,image2);

    findBlobs();
    showScanningArea();

    cvSetImageROI((IplImage*)image,cvRect(1,1,imgSize.width,imgSize.height));
        cvShowImage("Webcam Preview", image);
        cvShowImage("Processed Video Frames", image2);

    manageBlobs();

    char k = cvWaitKey(10);
    quit = manageKeys(k);

    cvReleaseBlobs(blobs);
    cvReleaseImage(&labelImg);
    cvReleaseImage(&segmentated);
    cvReleaseImage(&image2);
}

void FindBlob::manageBlobs() {
    if (cvGreaterBlob(blobs)) {
        cvUpdateTracks(blobs, tracks, 1.0, 1, 0);

        i = cursors.begin();
            while (i != cursors.end()) {
                jt=tracks.begin();
                found = false;
            while (jt!=tracks.end()) {
                if(jt->second->id == i->first) {
                    xToSend = (100 * jt->second->centroid.x) / scanArea.width/100;
                    yToSend = (100 * jt->second->centroid.y) / scanArea.height/100;
                    tuioServer->updateTuioCursor(i->second,xToSend, yToSend);
                    found = true;
                }

                ++jt;
            }

              if (found == false) {
                std::cout << "FOUND " << cursors.size() <<  std::endl;
                tuioServer->removeTuioCursor(i->second);
                cursors.erase(i++);
                
              } else {
                ++i;
              }
        }

            
        jt=tracks.begin();
        found = false;
        while (jt!=tracks.end()) {
            i = cursors.find(jt->second->id);
            if(i == cursors.end()) {
                xToSend = (100 * jt->second->centroid.x) / scanArea.width / 100;
                yToSend = (100 * jt->second->centroid.y) / scanArea.height / 100;
                cursor = tuioServer->addTuioCursor(xToSend, yToSend);
                cursors.insert (std::make_pair (jt->second->id, cursor));
                std::cout << "FOUND " <<  std::endl;
            }
                
                
            

            ++jt;
        }
            // blob = blobs[cvGreaterBlob(blobs)];
            // pt5 = cvPoint(picWidth / 2, picHeight / 2);
            // pt6 = cvPoint(blob->centroid.x, blob->centroid.y);
            // cvLine(frame, pt5, pt6, green, thickness);
            // cvCircle(frame, pt6, 3, green, 2, CV_FILLED, 0);

            // std::cout << "Blobs found: " << blobs.size() << std::endl;
            // std::cout << "Pixels labeled: " << result << std::endl;
            // std::cout << "center-x: " << blob->centroid.x
            //         << "   center-y: " << blob->centroid.y
            //         << std::endl;
            // std::cout << "offset-x: " << ((picWidth / 2)-(blob->centroid.x))
            //         << "   offset-y: " << (picHeight / 2)-(blob->centroid.y)
            //         << std::endl;
            // std::cout << "\n";
        }
        else {
            Cursors::iterator i = cursors.begin();
                while (i != cursors.end()) {
                    tuioServer->removeTuioCursor(i->second);
                    cursors.erase(i++);
            }
        }
}

void FindBlob::showScanningArea() {
    

    thickness = 1;
    picWidth = image2->width;
    picHeight = image2->height;

    pt1 = cvPoint(picWidth / 2, 0);
    pt2 = cvPoint(picWidth / 2, picHeight);
    cvLine(image, pt1, pt2, red, thickness);

    cvLine(image, cvPoint(0, 0), cvPoint(0, picHeight), red, thickness);
    cvLine(image, cvPoint(0, 0), cvPoint(picWidth, 0), red, thickness);
    cvLine(image, cvPoint(picWidth-1, 0), cvPoint(picWidth-1, picHeight), red, thickness);

    cvLine(image, cvPoint(0, picHeight-1), cvPoint(picWidth, picHeight-1), red, thickness);

    pt3 = cvPoint(0, picHeight / 2);
    pt4 = cvPoint(picWidth, picHeight / 2);
    cvLine(image, pt3, pt4, red, thickness);
}

void FindBlob::findBlobs() {
    cvInRangeS(image2, CV_RGB(200, 200, 200), CV_RGB(255, 255, 255), segmentated);
    cvSmooth(segmentated, segmentated, CV_MEDIAN, 7, 7);

    labelImg = cvCreateImage(cvGetSize(image2), IPL_DEPTH_LABEL, 1);

    result = cvLabel(segmentated, labelImg, blobs);
    cvFilterByArea(blobs, 500, 1000000);
    cvRenderBlobs(labelImg, blobs, image, image,
            CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_COLOR, 1.);
    cvUpdateTracks(blobs, tracks, 200., 5);
    cvRenderTracks(tracks, image, image, CV_TRACK_RENDER_BOUNDING_BOX, NULL);
}

void FindBlob::flipImage() {
        cv::Mat matCon(image);
        cv:flip(matCon,matCon,1);

        dst_img = matCon;

        image = &dst_img;
}
void FindBlob::loadTuioServer(const char *host, int port) {
    if ((strcmp(host,"default")==0) && (port==0))
        tuioServer = new TUIO::TuioServer();
    else 
        tuioServer = new TUIO::TuioServer(host, port);
    std::cout << "test: " << std::endl;
    currentTime = TUIO::TuioTime::getSessionTime();
    }