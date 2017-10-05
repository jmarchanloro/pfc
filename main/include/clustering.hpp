#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <armadillo>

class Clustering{
public:
  virtual void clustering() = 0;
  virtual std::vector<std::vector<double> > get_histogram() = 0;
  //virtual arma::Col<size_t> get_classification() = 0;
protected:
  //The dataset we are clustering
  arma::mat data;
  
  const std::string input_file = "data/data.csv";
//   const std::string output_model_file= "data/model.xml";
  const std::string output_result_file="data/labels.csv";
  
};

#endif /*CLUSTERING_H_*/