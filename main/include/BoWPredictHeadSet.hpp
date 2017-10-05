#include "BoWSystem.hpp"

#include <vector>

using namespace std;

class BoWPredictHeadSet : public BoWSystem{

public:
  BoWPredictHeadSet(vector<double> &freq);

private:
  /**
   * @brief Obtain signal from a Head set
   */
  virtual void obtain_signal();
  void obtain_feature_vectors_reduct();
  void classify();
  void myprint(std::vector< vector<double> >& vv);
};
