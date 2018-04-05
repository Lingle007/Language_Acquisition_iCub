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
//#include <sstream>
//#include <string>

#include <iomanip>
//#include <sstream>
//#include <stdio.h>
 
 /* Get all OS and signal processing YARP classes */
 
 #include <yarp/os/all.h>
 #include <yarp/sig/all.h>
 #include <fstream>
 #include <sstream>
 #include <iostream>
 #include <string>
 using namespace yarp::os;
 using namespace yarp::sig;
 using namespace std;
 using namespace cv;

 int main() {
 Network yarp; // set up yarp
 //BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
 //BufferedPort<ImageOf<PixelRgb> > imagePort_right;
 //BufferedPort<Vector> targetPort;
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
 const char* dir = "";
 string filename;
 string filenameR;
 string datapath = "./data/";
 Mat img1, dimg1;
 Mat img2, dimg2;
 //Mat img1, dimg1;
 //       Mat img2, dimg2;

 //imagePort.open("/tutorial/image/in");  // give the port a name
 //targetPort.open("/tutorial/target/out");
 //Network::connect("/icubSim/cam/left","/tutorial/image/in");
 //TODO:
 // Read a text file of cluster indices of testing objects
 std::ifstream infile1("./label_files/size_cluster.txt");
 // Read the entire text documents and stort relevant
 // clustering information:
 // Need to have everything in one line without '\n':
 // They are just numbers separated by spaces:
 //string cluster_info;
 string cluster_size[15];
 string cluster_color[15];
 string cluster_shape[15];
 string prediction_size[15];
 string prediction_color[15];
 string prediction_shape[15];
 // Please manually fill in the mapping:
 // This might be the fastest:
 // Or create a text file and read the 
 // Correct mapping from there:
 //int mapping;
 //int i = 0;

 for (int i = 0; i < 30; i++){
	infile1 >> cluster_size[i];
	//cout << cluster_size[i];
 }
 std::ifstream infile2("./label_files/color_cluster.txt");
 for (int j = 0; j < 30; j++){
	infile2 >> cluster_size[j];
	//cout << cluster_size[j];
 }
 std::ifstream infile3("./label_files/shape_cluster.txt");
 for (int m = 0; m < 30; m++){
	infile3 >> cluster_size[m];
	//cout << cluster_size[m];
 }
 std::ifstream infile4("./label_files/recognized_size_cluster.txt");
 for (int k = 0; k < 15; k++){
	infile4 >> prediction_size[k];
	//cout << prediction_size[k]; 
 }

 std::ifstream infile5("./label_files/recognized_color_cluster.txt");
 for (int k = 0; k < 15; k++){
	infile5 >> prediction_color[k];
	//cout << prediction_color[k];
 }

 std::ifstream infile6("./label_files/recognized_shape_cluster.txt");
 for (int k = 0; k < 15; k++){
	infile6 >> prediction_shape[k];
	//cout << prediciton_shape[k];
 }
 int current_size;
 int current_color;
 int current_shape;
 bool sess_end = false;	
 while (!sess_end) { // repeat unless users specify
   //ImageOf<PixelRgb> *image = imagePort.read();  // read an image
   Image *iplcvtL = iplinLeft.read();
   Image *iplcvtR = iplinRight.read();
   //int key;
   if (iplcvtL != NULL && iplcvtR != NULL) { // check we actually got something
      printf("I got an image of size %dx%d\n", iplcvtL->width(), iplcvtL->height());
      //printf("To continue, please type any key");
   }
   int key;
   int cnt = 0;
   printf("How many pictures today?\n");
   cin >> cnt;
   printf("You want %d picture(s), Kool!\n", cnt); 
   for (int i = 0; i < cnt; i++){
       //int key;
       do{
       	key = waitKey(100);
       	cout << key;
       	// Read images from buffer and store them as <Image> type
       	//Image *iplcvtL = iplinLeft.read();
		//Image *iplcvtR = iplinRight.read();
	    // Converts the <Image> type from yarp to openCV <IplImage> type
		tmp_ipl_left = (IplImage*)(iplcvtL->getIplImage());
		tmp_ipl_right = (IplImage*)(iplcvtR->getIplImage());
		// Converts openCV <IplImage> type to openCV <Mat> type
		dimg2 = tmp_ipl_left;
		dimg1 = tmp_ipl_right;
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
	filename += to_string(cnt);
	filename += ".jpg";

	filenameR.clear();
	filenameR = dir;
	filenameR += datapath;
	filenameR += "right";
	filenameR += to_string(cnt);
	//filenameR += ZeroPad(2, cnt).c_str();
	filenameR += ".jpg";

	cout << "Saving: " << filename << "\t";
	cout << "Saving: " << filenameR << endl;

	imwrite(filename, img1);
	imwrite(filenameR, img2);
	// I manually reset key to take more pictures!:
	//key = 0;
	if((key == 'q')){
		break;	
	}
   // Sorry if I cheated a little bit:
   // This is just a proof of concept:
   // After taking the image,
   // We pretend we have processed this image
   // And assign corresponding clusters
   // Note to myself: Use consistent clustering indices
   // GMM-EM should be ran before all of this
   printf("Please enter processed cluster information for this image!\n");
   printf("Please enter the size cluster index\n");
   cin >> current_size;
   printf("Please enter the color cluster index\n");
   cin >> current_color;
   printf("Please enter the shape cluster index\n");
   cin >> current_shape;
   if (current_color != stoi(prediction_color[i])){
   	printf("I don't think this object has the color you just describe!\n");
   }
   if (current_size != stoi(prediction_size[i])){
   	printf("I don't think this object has the size you just described!\n");
   }
   if (current_shape != stoi(prediction_shape[i])){
   	printf("I don't think this object has the shape you just described!\n");
   }
   if (current_size == stoi(prediction_size[i]) && current_color == stoi(prediction_color[i]) && current_shape == stoi(prediction_shape[i])){
   	printf("Ah, I see what you just described!\n");
   	printf("Thank you, Lingle!\n");
   }
   printf("Session %d just ended\n", (i + 1));
   printf("Continue.....\n");
 }
 int end;
 printf("Or do you want to end for now?\n");
 printf("1 / 0\n");
 cin >> end;
 if (end == 1){
 	sess_end = true;
 }
 }
 printf("Your session has ended.\n");
}