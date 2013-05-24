#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "findBlob.h"

using namespace std;

int main(int argc, char* argv[]) {
    int captureWidth = 800;
    int captureHeight = 800;

    DetectBlobsShowVideo(captureWidth, captureHeight);
    

    return 0;
}
