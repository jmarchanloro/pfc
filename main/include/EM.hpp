#include "clustering.hpp"
#include <vector>

#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/core/metrics/mahalanobis_distance.hpp>

using namespace mlpack::gmm;

class EM: public Clustering{
public:
  
  EM(arma::mat data){
    this->data = data;
  }
  void clustering(){
    
//     mlpack::data::Load(input_file, data, true);
//     data.print();
    EMFit<> em(maxIterations, tolerance);
    // Calculate mixture of Gaussians.
    // Set up a mixture of 2 gaussians in a 2-dimensional space (uses the default
    // EM fitting mechanism) See data_2.csv file.
    GMM<> gmm(size_t(gaussians), data.n_rows, em);
    // Compute the parameters of the model using the EM algorithm.
    // Train the GMM given the data observations.
    likelihood = gmm.Estimate(data);
    // Save results
    gmm.Save(output_model_file);
    gmm.Classify(data,labels);
    mlpack::data::Save(output_result_file, labels);

    // Prepare data to get_histogram. If that method is not 
    // called, means and covs are not used.
    means = gmm.Means();
    covs  = gmm.Covariances();

  }
  
  std::vector<std::vector<double> > get_histogram(){
    // Mahalanobis distance to gaussian 0,1,..,n
    std::vector<mlpack::metric::MahalanobisDistance<>> mahalanobis;
    for(int g=0; g<gaussians; g++){
	mlpack::metric::MahalanobisDistance<> m(covs.at(g));
	mahalanobis.push_back(m);
    }
    
    // Calculate histogram: Distance of each point to each gaussian
    std::vector<std::vector<double> > histogram;
    mlpack::metric::MahalanobisDistance<> m;
    for (unsigned int i=0; i < data.n_cols; i++){
// 	std::cout << data.col(i) << std::endl; 
	std::vector<double> distance_to_gaussians;
	for(int g=0; g < gaussians; g++){
	    m = mahalanobis.at(g);
	    double distance = m.Evaluate(data.col(i), means.at(g));
	    std::cout << "to " << g << ": " << distance << std::endl;
	    distance_to_gaussians.push_back(distance);	  
	}
	histogram.push_back(distance_to_gaussians);
    } 
    return histogram;
  
  }
  
  arma::Col<size_t> get_classification(){
    return labels;    
  }
  
private:
  // The number of Gaussians in the model.
  const int gaussians = 2;
  // The name of the model file
  const std::string output_model_file= "data/model.xml";
//   //The dataset we are clustering
//   arma::mat data;
  // The resultant classifications are stored in the 'labels' object
  arma::Col<size_t> labels;
  
  // Gather parameters for EMFit object
  // Log-likelihood tolerance required for convergence
  const double tolerance = 1.0; //REVISE THIS VALUE
  // Maximum number of iterations for EM
  const size_t maxIterations = 1000; //if 0, EM algorithm will iterate until convergence (with the given tolerance)
  double likelihood;
  // Vector of means of the gmm model
  std::vector<arma::vec> means;
  // Vector of covariance matrices of the gmm model
  std::vector<arma::mat> covs;
  
};