#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include "SlideWindow.h"
#include "Signal.hpp"
#include "FeatureVector.hpp"
// #include "EM.hpp"
#include "KMeansClustering.hpp"
#include "Classifier.hpp"

using namespace std;

typedef double T;

void print(vector<T> v){
	
	for (auto &i : v){
		std::cout << i << " | ";
	}
	std::cout << endl;    
}

void print(vector<vector<double>> v){
  
    for (auto &i : v){
      for (auto &j : i){
	std::cout << j << ",";
      }
      std::cout << endl;
    }
}

int main(int argc, char** argv)
{
  // DWT parameters
  int level = 5;
  string filter = "d4";
  vector<T> window;
  FeatureVector feature_vector(level, filter);
  
  Signal s;
  vector< double > signal = s.read_signal_from_dir("data/borrar/");
  SlideWindow sw(signal,4,0,173.61);  // Create a slide window over the signal
  
//   int n_rows = feature_vector_object.get_size_of_feature_vector();
//   int n_cols = sw.get_nwindows();
  
 
  // Alternative to create the feature vectors matrix. Faster, BUT
  // it needs to be known in compile time
  /*arma::mat::fixed<24,5> fv;
  arma::mat aux(col);
  fv.col(0) = aux;  
  fv.print();
  */
  vector<double> tmp_feature_vector;
  arma::mat feature_vectors_matrix;
  while (!(window = sw.get_next_window()).empty()){
    feature_vector.calculate_dwt(window);
    tmp_feature_vector = feature_vector.get_feature_vector("", level);
    feature_vectors_matrix.insert_cols(sw.get_current_window()-1, arma::mat(tmp_feature_vector));
  } 
  feature_vectors_matrix.print();
  
//   EM c(feature_vectors_matrix);
  KMeansClustering c(feature_vectors_matrix);
  c.clustering();
  vector<vector<double>> histogram = c.get_histogram();
//   print(histogram);
  Classifier classifer;
  arma::Col<size_t> labels = c.get_classification();
  cout << "labels: " << endl;
  labels.print();
  
  classifer.training(histogram, labels);
}