#ifndef BOWSYSTEM_H
#define BOWSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <armadillo>

#include "Signal.hpp"
#include "SlideWindow.h"
#include "FeatureVector.hpp"

using namespace std;

class BoWSystem{

protected:
  void virtual obtain_signal();
  void virtual obtain_feature_vectors_matrix();
  void virtual obtain_feature_vectors_reduct() = 0;
  void virtual classify() = 0;
  
  vector<string> datasets_paths;
  vector<int>    datasets_labels;
  vector <double> freqs;
  
  vector<vector<double>> signal;
  arma::mat feature_vectors_matrix;
  vector<int> feature_vectors_labels;
  vector<vector<double>> feature_vector_reduct;

  void myprintsimple(std::vector<int> &v);
  void myprintsimple(std::vector<double> &v);
  
public:
  /*
   * Skeleton of the BoW algorithm
   */
  void execute();

};

#endif // BOWSYSTEM_H
