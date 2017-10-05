#include "svm.h"

#include <iostream>
#include <armadillo>

using namespace std;

class Classifier{
public:
  void training(const vector<vector<double>>& histogram, vector<int>& labels);
  void testing (const vector<vector<double>>& histogram, vector<int>& labels);
  
private:
  /* 
   * This function creates the problem from the previous step histogram
   * We called problem to the structure used to train the svm
   */
  void create_problem(const vector<vector<double>>& histogram, vector<int>& labels);
  void myprint(std::vector<int> &labels);
  void myprint(std::vector<double> &labels);
  
  /*
   * This function stablish the parameters used to obtain the model.
   * See README to learn about the parameters
   */
  void stablish_parameters();
  
  //char model_file[1024] = "data/svm_model";
  char model_file[1024] = "data/model";
  
  /* FOR TRAINING*/
  /*
   * Describe de problem. We called problem to the structure used to
   * train the svm
   */
  struct svm_problem problem; 
  
  struct svm_node *x_space;
  
  struct svm_parameter param;
  
  struct svm_model *model;
  
  
  /* FOR PREDICT*/
  /*
   * Points to a sparse representation of one training vector   
   */
  struct svm_node *x;
};
