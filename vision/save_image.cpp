#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include <cv.h>

#include <stdio.h>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Image.h>
#include <yarp/os/Time.h>
#include <yarp/os/Property.h>


#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include <iomanip>
#include <sstream>
#include <string>

#include <iomanip>
#include <sstream>

using namespace yarp::sig;
using namespace yarp::os;

using namespace std;
using namespace cv;
int saveimg()
{ 
/*	VideoCapture cap(1);
	VideoCapture cap2(2);

    if(!cap.isOpened()) return -1;
	if(!cap2.isOpened()) return -1;
*/
// Set up the yarp network and connect the ports
    Network yarp;

    BufferedPort<Image> iplinLeft;
    BufferedPort<Image> iplinRight;

    iplinLeft.open("/stereo/image/inLeft");
    iplinRight.open("/stereo/image/inRight");

//    Network::connect("/icub/camcalib/left/out","/stereo/image/inLeft");
//    Network::connect("/icub/camcalib/right/out","/stereo/image/inRight");

    Network::connect("/icubSim/cam/left", "/stereo/image/inLeft");
    Network::connect("/icubSim/cam/right", "/stereo/image/inRight");
// -----------------

    IplImage* tmp_ipl_left = NULL;
    IplImage* tmp_ipl_right = NULL;

	//const char* dir = "calimg/";
	const char* dir = "";
	string filename;
	string filenameR;
	string datapath = "./data/";

	Mat img1, dimg1;
        Mat img2, dimg2;

//	stringstream ss;

	printf("Trying to capture images\n\n");
	int num_pics;
	printf("Please type in the number of pictures you want for each iteration!\n");
	cin >> num_pics;
	int cnt = 1;
	for(cnt = 1; cnt <= num_pics; cnt ++)
	{
		int key;
		//printf("your current cnt is: \n");
		//printf(cnt);
		cout << cnt;
		do
		{
			key = waitKey(100);
			cout << key;
			//key = key + 1;
		    // Read images from buffer and store them as <Image> type
		    Image *iplcvtL = iplinLeft.read();
		    Image *iplcvtR = iplinRight.read();
			// Converts the <Image> type from yarp to openCV <IplImage> type
		    tmp_ipl_left = (IplImage*)(iplcvtL->getIplImage());
		    tmp_ipl_right = (IplImage*)(iplcvtR->getIplImage());

			// Converts openCV <IplImage> type to openCV <Mat> type
		    dimg2 = tmp_ipl_left;        dimg1 = tmp_ipl_right;
//			cap >> dimg2;
//			cap2 >> dimg1;
		    //printf("Hi, now we imshow Yo ^-^!");
			namedWindow("left", 1);
			imshow("left", dimg1);
			namedWindow("right", 1);
			imshow("right", dimg2);
		}while(key <= -1);

		cout << "Image " << cnt << endl;

		// I tried to use RGB altough I think OpenCV uses BGR by default:
		//cvtColor(dimg1, img1, CV_BGR2GRAY);
		cvtColor(dimg1, img1, CV_RGB2BGR);
		cvtColor(dimg2, img2, CV_BGR2RGB);

		filename.clear();
		filename = dir;
		filename += datapath;
		filename += "left";
		//filename += ZeroPad(2, cnt).c_str();
		filename += cnt;
		filename += ".jpg";

		filenameR.clear();
		filenameR = dir;
		filenameR += datapath;
		filenameR += "right";
		filenameR += cnt;
		//filenameR += ZeroPad(2, cnt).c_str();
		filenameR += ".jpg";

		cout << "Saving: " << filename << "\t";
		cout << "Saving: " << filenameR << endl;

		imwrite(filename, img1);
		imwrite(filenameR, img2);
		// I manually reset key to take more pictures!:
		//key = 0;
		if((key == 'q'))
			break;
	}
	printf("Your iteration has ended!");
	cout << "I have taken %d pictures * 2 for you~" << cnt;
}

std::string ZeroPad(int width, int num)
{
	stringstream ss;

	ss << std::setw(width) << std::setfill('0') << num;

	return ss.str();
}
int main(){
	saveimg();
}
