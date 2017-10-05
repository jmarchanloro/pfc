#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/methods/kmeans/refined_start.hpp>

#include <mlpack/core/metrics/mahalanobis_distance.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <string>

//para probrar la estructura svm ///////////////////////
#include "svm.h"
struct svm_problem problem; /* describe the problem*/
struct svm_node *x_space;
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
////////////////////////////////////////////////////////7

using namespace mlpack::gmm;
using namespace std;

void read_problem(vector< vector< double > > histogram, arma::Col<size_t> labels);

int main(int argc, char** argv){
  
  const string input_file = "data/data.csv";
  const string output_model_file= "data/model.xml";
  const string output_result_file="data/labels.csv";
  const int gaussians = 3;
  
  //The dataset we are clustering
  arma::mat data;
  mlpack::data::Load(input_file, data, true);
  
  // The resultant classifications are stored in the 'labels' object
  arma::Col<size_t> labels;
  
  
  //Gather parameters for EMFit object
  const double tolerance = 1.0; 
  const size_t maxIterations = 1000; //if 0, EM algorithm will iterate until convergence (with the given tolerance)
  const bool force_positive = true;
    
  // Depending on the value of forcePositive, we have to use different types.
  if (force_positive){
      double likelihood;
      EMFit<> em(maxIterations, tolerance);
    
      // Calculate mixture of Gaussians.
      // Set up a mixture of 2 gaussians in a 2-dimensional space (uses the default
      // EM fitting mechanism) See data_2.csv file.
      GMM<> gmm(size_t(gaussians), data.n_rows, em);

      // Compute the parameters of the model using the EM algorithm.
      // Train the GMM given the data observations.
      likelihood = gmm.Estimate(data);

      // Save results.
      gmm.Save(output_model_file);
      
      gmm.Classify(data,labels);
      mlpack::data::Save(output_result_file, labels);
      
        std::vector<arma::vec> means = gmm.Means();
  std::vector<arma::mat> covs = gmm.Covariances();  
  
  // Mahalanobis distance to gaussian 0,1,..,n
  vector<mlpack::metric::MahalanobisDistance<>> mahalanobis;
  for(int g=0; g<gaussians; g++){
    mlpack::metric::MahalanobisDistance<> m(covs.at(g));
    mahalanobis.push_back(m);
  }
      
  // Calculate histogram
  // Distance point of each gaussian
  vector<vector<double>> histograma;
  mlpack::metric::MahalanobisDistance<> m;
  for (int i=0; i < data.n_cols; i++){
    cout << data.col(i) << endl; 
    vector<double> distance_to_gaussians;
    for(int g=0; g < gaussians; g++){
      m = mahalanobis.at(g);
      double distance = m.Evaluate(data.col(i), means.at(g));
      cout << "to " << g << ": " << distance << endl;
      distance_to_gaussians.push_back(distance);	  
    }
    histograma.push_back(distance_to_gaussians);
  } 
  
  read_problem(histograma, labels);
 }
}

/* This function creates the problem from the previous step histogram
 It is called problem to the structure used to train the svm*/
void read_problem(vector< vector< double > > histogram, arma::Col<size_t> labels)
{
  /* numbers of elements of each training vector. All training
   * vectors have the same size.
   * (We know that now will be 2 because the clustering
   * step make two clusters)*/
  vector<double> training_vector = histogram.front();
  long unsigned int elements = training_vector.size();
  cout << "elements: "<< elements << endl;
  /* Number of training data*/
  problem.l = (int)histogram.size();
  cout << "l: "<< problem.l << endl;
  /**/
  problem.y = Malloc(double, problem.l);
  problem.x = Malloc(struct svm_node *, problem.l);
  x_space   = Malloc(struct svm_node, ((int)elements + 1) * problem.l);

  //   Now create the array of pointers to a sparse representation of 
  //   training vectors
  int j=0;
  for (int i=0; i<problem.l; i++){
      problem.x[i] = &x_space[j];
      problem.y[i] = (int)labels(i);
      
      training_vector = histogram.at(i);
      double value;
      for (unsigned int n=1; n <= elements; n++){
	x_space[j].index = n;
	value = training_vector.at(n-1);
	x_space[j].value = value;
	++j;
      }
      x_space[++j].index = -1;      
  }
  
// BORRAR. esto imprime la estructura. Se crea y se almacena bien.  
//   for (int i=0; i<problem.l ; i++){
//   cout << *((problem.y)++) << endl;
//   }
//   
//   struct svm_node **node;
//   struct svm_node *x_space;
//   node = problem.x;
//   for (int i=0; i<problem.l; i++){
//     x_space = *(node++);
//     for(int e=0; e<elements; e++){
//       cout << x_space[e].index << ":" << x_space[e].value << endl;
//     }
//   }
}