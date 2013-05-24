/* 
 * File:        main.cpp
 * Author:      Gary Stafford
 * Description: Program entry point
 * Created:     February 3, 2013
 */

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
        // // test 3 and 4 don't require width and height parameters
        // if (captureMethod != 3 && captureMethod != 4) {
        //     cout << endl << "Input capture width (pixels): ";
        //     cin >> captureWidth;
        //     cout << endl << "Input capture height (pixels): ";
        //     cin >> captureHeight;
        //     cout << endl;

        //     if (!captureWidth > 0) {
        //         cout << endl << "Width value incorrect" << endl;
        //         return -1;
        //     }

        //     if (!captureHeight > 0) {
        //         cout << endl << "Height value incorrect" << endl;
        //         return -1;
        //     }
        // }
    

    return 0;
}
