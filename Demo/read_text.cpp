#include <fstream>

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main(){
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
	int mapping;
	//int i = 0;

	for (int i = 0; i < 30; i++){
		infile1 >> cluster_size[i];
		//cout << cluster_size[i];
	}
	std::ifstream infile2("./label_files/color_cluster.txt");
	for (int j = 0; j < 30; j++){
		infile2 >> cluster_color[j];
		//cout << cluster_size[j];
	}
	std::ifstream infile3("./label_files/shape_cluster.txt");
	for (int m = 0; m < 30; m++){
		infile3 >> cluster_shape[m];
		//cout << cluster_shape[m];
	}
	
	std::ifstream infile4("./label_files/recognized_size_cluster.txt");
	for (int k = 0; k < 15; k++){
		infile4 >> prediction_size[k];
		cout << prediction_size[k]; 
	}

	std::ifstream infile5("./label_files/recognized_color_cluster.txt");
	for (int k = 0; k < 15; k++){
		infile5 >> prediction_color[k];
		//cout << prediction_color[k];
	}

	std::ifstream infile6("./label_files/recognized_shape_cluster.txt");
	for (int k = 0; k < 15; k++){
		infile6 >> prediction_shape[k];
		//cout << prediction_shape[k];
	}
	//return 0;
}

//for (std::string line; getline(infile, line)){
//	cluster_size[i] = line[]
//}