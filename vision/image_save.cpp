/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
//using namespace cv;
//using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::sig::draw;
using namespace yarp::sig::file;


int main(int argc, char *argv[]) {
    printf("Lingle inserted codes here ...... ^_^\n");
    Network yarp; // set up yarp
    BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
    BufferedPort<Vector> targetPort;
    imagePort.open("/tutorial/image/in");  // give the port a name
    targetPort.open("/tutorial/target/out");
    Network::connect("/icubSim/cam/left","/tutorial/image/in");
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    
    printf("My code ended here\n");
    printf("Show an Image for 3 seconds...\n");
    ImageOf<PixelRgb> yarpImage;


    printf("Creating a YARP image\n");
    yarpImage.resize(300,200);
    addCircle(yarpImage,PixelRgb(255,0,0),
              yarpImage.width()/2,yarpImage.height()/2,
              yarpImage.height()/4);
    addCircle(yarpImage,PixelRgb(255,50,50),
              yarpImage.width()/2,yarpImage.height()/2,
              yarpImage.height()/5);


    printf("Copying YARP image to an OpenCV/IPL image\n");
    IplImage *cvImage = cvCreateImage(cvSize(yarpImage.width(),  
                                             yarpImage.height()), 
                                      IPL_DEPTH_8U, 3 );
    cvCvtColor((IplImage*)yarpImage.getIplImage(), cvImage, CV_RGB2BGR);

    printf("Showing OpenCV/IPL image\n");
    cvNamedWindow("test",1);
    cvShowImage("test",cvImage);

    printf("Taking image back into YARP...\n");
    ImageOf<PixelBgr> yarpReturnImage;
    yarpReturnImage.wrapIplImage(cvImage);
    yarp::sig::file::write(yarpReturnImage,"test_2.ppm");
    printf("Saving YARP image to test_2.ppm\n");
    Vector& target = targetPort.prepare();
    targetPort.write();
    //imwrite("testing_1.ppm", image);
    //yarp::sig::file::write(image, "testing_YARP_write.ppm");

    cvWaitKey(3000);

    cvDestroyWindow("test");

    cvReleaseImage(&cvImage);

    printf("...done\n");
    return 0;
}
