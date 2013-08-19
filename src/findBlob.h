#ifndef FINDBLOB_H
#define	FINDBLOB_H

#include "TUIO/TuioServer.h"
#include "TUIO/TuioCursor.h"

class FindBlob{

public:
	void run(int captureWidth, int captureHeight);
	TUIO::TuioServer *tuioServer;
	TUIO::TuioCursor *cursor;
private:
	//attributes
	CvCapture *capture;
    CvSize imgSize;

    IplImage *image, *image2, *frame, *segmentated, *segmentated2, *labelImg;
    IplImage dst_img;
    CvPoint pt1, pt2, pt3, pt4, pt5, pt6;
    CvScalar red, green, blue;
    CvRect scanArea;

    cvb::CvTracks tracks;
    cvb::CvBlobs blobs;
    cvb::CvBlob* blob;
    int captureWidth, captureHeight;
	
	TUIO::TuioTime currentTime;

	int picWidth, picHeight, thickness;
    CvSize imgSize2;
    unsigned int result;

    typedef std::map<int, TUIO::TuioCursor *> Cursors;
    Cursors cursors;

    bool quit;
    Cursors::iterator i;
    cvb::CvTracks::iterator jt;
    cvb::CvBlobs::iterator it;
    float xToSend;
    float yToSend;
    bool found;

    //methods
	bool manageKeys(char key);
	void setCam(int i);
	void loadTuioServer(const char *host, int port);
	int loadVariables();
	void process();
	void manageBlobs();
	void showScanningArea();
	void findBlobs();
	void flipImage();


};
#endif	/* FINDBLOB_H */

