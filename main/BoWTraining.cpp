#include "include/BoWTraining.hpp"

#include <iostream>
#include <armadillo>
#include <list>

#include "include/Signal.hpp"
#include "include/SlideWindow.h"
#include "include/FeatureVector.hpp"
#include "include/KMeansClustering.hpp"
#include "include/Classifier.hpp"

using namespace std;

BoWTraining::BoWTraining(vector< string >& datasets_paths, vector<int>& datasets_labels, vector<double> &freqs)
{
  this->datasets_paths = datasets_paths;
  this->datasets_labels= datasets_labels;
  this->freqs = freqs;  
}

void BoWTraining::obtain_feature_vectors_reduct()
{
  cout << "BoW-obtain_feature_vectors_reduct" << endl;
  KMeansClustering c(feature_vectors_matrix);
  cout << "ncols " << feature_vectors_matrix.n_cols << endl;
  c.clustering();
  feature_vector_reduct = c.get_histogram();    
}

void BoWTraining::classify()
{
  Classifier classifier;
  classifier.training(feature_vector_reduct, feature_vectors_labels);
}

void BoWTraining::myprint(std::vector< vector<double> >& vv)
{

    for (auto &v : vv){
        for (auto &i : v)
            std::cout << i << "|";
    }
    std::cout << endl;
}

