#include "BoWSystem.hpp"

#include <vector>

using namespace std;

class BoWPredictDataSet : public BoWSystem{
  
public:
  BoWPredictDataSet(vector<string>& dataset_path, vector<int> &datasets_labels, vector<double> &freq);
  
private:
  void obtain_feature_vectors_reduct();
  void classify();
  void myprint(std::vector< vector<double> >& vv);
};
