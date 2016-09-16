
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "luv_color_histogram.hh"

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

void load(path& p, vector<LuvColorHistogram>& hist_vector){
	directory_iterator it(p);
	directory_iterator end_it;
        // Fill-in
}

void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2){

	vector<LuvColorHistogram>::const_iterator it1= h1.begin();
	int c1(0);
	for (; it1 != h1.end(); ++it1){
		vector<LuvColorHistogram>::const_iterator it2= h2.begin();
		int c2(0);
		// Fill-in: iterate over h2 and compare it1 and it2
                // For each histogram in h1, find the closest two in h2.
                // Ideally, you should also show the corresponding images, or at least the file-names for quick verification.
		
	}
}

int main(int argc, const char* argv[]) {

	if (argc < 2){
		cerr<< "Usage: \n"<< argv[0]<< " [folder name]"<< endl;
		return -1;
	}

	path p (argv[1]);
	if (!verify_folder(p)) return -1;


	vector<LuvColorHistogram> histograms;

	load(p, histograms);
	cout<< "*** loaded "<< histograms.size()<< " samples."<< endl;

	cout<< "Comparing histograms"<< endl;
	compare_hist_vectors(histograms, histograms);

	cout<< endl<< endl;


}
