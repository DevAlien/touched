#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvblob.h>

#include "findBlob.h"

using namespace std;

int main(int argc, char* argv[]) {
    int captureWidth = 800;//load from config
    int captureHeight = 600;//load from config

    FindBlob findBlob;

    findBlob.run(captureWidth, captureHeight);
    
    //Here is the beginning of everything, I should make an introduction, load profiles or something, load config file etc.

    
    return 0;
}