
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "luv_color_histogram.hh"
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

using namespace std;
using namespace jir;
using namespace boost;
using namespace boost::filesystem;

bool verify_folder(path& p){
	if (!exists(p)){
		cerr<< "Folder "<< p.c_str()<< " does not exist"<< endl;
		return false;
	}
	if (!(is_directory(p))){
		cerr<< p.c_str()<< " is not a folder."<< endl;
		return false;
	}
	return true;
}

void load(path& p, vector<LuvColorHistogram>& hist_vector, const char* h, const char* s, const char* v){
	directory_iterator it(p);
	directory_iterator end_it;


	for(;it != end_it; ++it)
    {

            LuvColorHistogram inp(atoi(h),atoi(s),atoi(v));
            inp.load(it->path().string(),false);
            hist_vector.push_back(inp);
    }
}

void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2, path& test, path& train){
	//h1 test h2 training
	double min1,min2;
	int min1_c,min2_c;

	vector<LuvColorHistogram>::const_iterator it1= h1.begin();
	int c1(0);
	for (; it1 != h1.end(); ++it1){
		vector<LuvColorHistogram>::const_iterator it2= h2.begin();
		int c2(0);
		for (; it2 != h2.end(); ++it2){
			//init min1 values
			if(c2==0){
				min1=it1->compare(*it2);
				min1_c=c2;
				min2=it1->compare(*it2);
				min2_c=c2;
			} else if(c2==1){
				if(it1->compare(*it2)<=min1){
					min1=it1->compare(*it2);
					min1_c=c2;
				} else {
					min2=it1->compare(*it2);
					min2_c=c2;
				}
			} else {
				if(it1->compare(*it2)<=min1){
					min1=it1->compare(*it2);
					min1_c=c2;
				} else  if(it1->compare(*it2)<=min1){
					min2=it1->compare(*it2);
					min2_c=c2;
				}
			}
			c2++;
		}

		cv::namedWindow("TestPic");
		cv::imshow("TestPic",h1[c1].color_img);
		cv::namedWindow("TrainPic1");
		cv::imshow("TrainPic1",h2[min1_c].color_img);
		cv::namedWindow("TrainPic2");
		cv::imshow("TrainPic2",h2[min2_c].color_img);
		cout<<c1<<": TrainPic1: ["<<min1<<"] || TrainPic2: ["<<min2<<"]"<<endl;
		cv::waitKey();

		c1++;
	}
}

int main(int argc, const char* argv[]) {

	if (argc < 5){
		cerr<< "Usage: \n"<< argv[0]<< " [folder name] [H bins] [S bins] [V Bins]"<< endl;
		return -1;
	}

	path p (argv[1]);
	if (!verify_folder(p)) return -1;
	path train (p.string()+"/train/");
	path test (p.string()+"/test/");

	vector<LuvColorHistogram> hist_train;
	vector<LuvColorHistogram> hist_test;

	load(test, hist_test, argv[2], argv[3], argv[4]);
	cout<< "*** loaded "<< hist_test.size()<< " test samples."<< endl;
	load(train, hist_train, argv[2], argv[3], argv[4]);
	cout<< "*** loaded "<< hist_test.size()<< " training samples."<< endl;

	cout<< "Comparing histograms"<< endl;
	compare_hist_vectors(hist_test, hist_train, test, train);

	cout<< endl<< endl;

}
