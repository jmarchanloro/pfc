#include "include/KMeansClustering.hpp"
#include "include/clustering.hpp"

#include <mlpack/methods/kmeans/kmeans.hpp>
#include <string>

#include <cmath>

// using namespace mlpack::kmeans;
using namespace std;
using namespace mlpack;

 KMeansClustering::KMeansClustering(arma::mat d){
     data = d;
 }
  
void KMeansClustering::clustering(){
      
//     mlpack::data::Load(input_file, data, true);
    
    //Initialize with the default arguments
    mlpack::kmeans::KMeans<metric::ManhattanDistance> k;
    k.Cluster(data, clusters, assignments, centroids);
    
    //Save only the labels
    arma::Mat<size_t> output = trans(assignments);
    mlpack::data::Save(output_result_file, output);
    
    //Save the centroids
    mlpack::data::Save(centr_file, centroids);
  }
  
  std::vector<std::vector<double> > KMeansClustering::get_histogram(){
    
    // Load centroids to calculate the distances to them.
    // The centr_file must has been created previously
    mlpack::data::Load(centr_file, centroids, true);
    
    // Calculate histogram: Distance of each point to each gaussian
    std::vector<std::vector<double> > histogram;
       mlpack::metric::EuclideanDistance euclidean;
//     mlpack::metric::MahalanobisDistance<> m;
       
       //cout << "data" << endl;
       //data.print();
       double sumando=0, sum=0;
    for (unsigned int i=0; i < data.n_cols; i++){
 	//if (i<4) std::cout << data.col(i) << std::endl; 
	std::vector<double> distance_to_centroids;
	for(unsigned int c=0; c < clusters; c++){
// 	  std::cout << centroids.col(c) << std::endl;
	    //double distance = euclidean.Evaluate(data.col(i), centroids.col(c));
	  double distance = sqrt(accu(square(data.col(i) - centroids.col(c))));
	  
// 	    sum = 0;
// 	     for(int i=0; i<24; i++){
// 	       sumando = 0;
// 	       arma::subview_col<double> cola = data.col(i);
// 	       arma::subview_col<double> colb = centroids.col(c);
// 	       sumando = cola(i) - colb(i);
// 	       sum += sumando*sumando;
// 	     }
// 	     double distance = sqrt(sum);
	  
	  
// 	    double distance = data.col(i) - centroids.at(c);
// 	    std::cout << "to " << c << ": " << distance << std::endl;
	    distance_to_centroids.push_back(distance);	  
	}
// 	if (euclidean.Evaluate(data.col(i), centroids.col(0)) < euclidean.Evaluate(data.col(i), centroids.col(1))){
// 	  distance_to_centroids.push_back(0);
// 	  distance_to_centroids.push_back(1);
// 	}
// 	else{
// 	  distance_to_centroids.push_back(1);
// 	  distance_to_centroids.push_back(0);
// 	}
	
	histogram.push_back(distance_to_centroids);
	//cout << distance_to_centroids.at(0) << "," << distance_to_centroids.at(1);
    }
    return histogram;
  }
  
  
  //arma::Col<size_t> KMeansClustering::get_classification(){
  //    return assignments;
  //}