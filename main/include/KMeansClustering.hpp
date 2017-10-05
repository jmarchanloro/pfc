#ifndef KMEANS_H_
#define KMEANS_H_

#include "clustering.hpp"

#include <mlpack/methods/kmeans/kmeans.hpp>
#include <string>

// using namespace mlpack::kmeans;
using namespace std;
using namespace mlpack;

class KMeansClustering: public Clustering{
public:
  
  KMeansClustering(arma::mat data);
  void clustering();
  vector<vector<double> > get_histogram();

private:
  const size_t clusters = 2;
  const string centr_file = "data/centroids.csv";
  
  double euclidean_distance(arma::subview_col<double> a, arma::subview_col<double> b);
//   //The dataset we are clustering
//   arma::mat data;
  //The assignments and centroids will be stored in this vector
  arma::Col<size_t> assignments;
  arma::mat centroids;
  
};

#endif /*KMEANS_H_*/
