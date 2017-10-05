#ifndef BOW_H
#define BOW_H

#include <armadillo>
#include <iostream>
#include <vector>
#include <list>

#include "BoWSystem.hpp"

using namespace std;

class BoWTraining : public BoWSystem
{
public:
   /**
   * @brief BoWTraining Constructor for training
   * @param datasets_paths
   * @param datasets_labels
   * @param freq Frecuency of each dataset
   */
  BoWTraining(vector<string>& datasets_paths, vector<int>& datasets_labels, vector<double> &freq);
  
private:
  /**
   * @brief obtain_feature_vectors_reduct of the signal. (Signal is an attribute of the superclass
   *        BoWSystem
   */
  void obtain_feature_vectors_reduct();

  /**
   * @brief To train the classifier
   */
  void classify();

  void myprint(std::vector< vector<double> >& vv);
};

#endif // BOW_H
