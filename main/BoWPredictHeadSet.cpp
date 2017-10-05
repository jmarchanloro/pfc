#include "include/BoWPredictHeadSet.hpp"

#include "include/KMeansClustering.hpp"
#include "include/Classifier.hpp"
#include "include/IEngine.hpp"
#include "include/Engine.hpp"

#include <vector>

BoWPredictHeadSet::BoWPredictHeadSet(vector<double>& freq)
{
    this->freqs = freq;
}

void BoWPredictHeadSet::obtain_signal()
{
  cout << "BoW-obtain_signal_from_headset" << endl;
  IEngine *engine = new Engine();
  vector<double> signal = engine->adquisition();
  this->signal.push_back(signal);
}

void BoWPredictHeadSet::obtain_feature_vectors_reduct()
{
  KMeansClustering c(feature_vectors_matrix);
  //c.clustering();
  feature_vector_reduct = c.get_histogram();
}

void BoWPredictHeadSet::classify()
{
  Classifier classifier;
  classifier.testing(feature_vector_reduct, feature_vectors_labels);
}

void BoWPredictHeadSet::myprint(std::vector< vector<double> >& vv)
{

    for (auto &v : vv){
        for (auto &i : v)
            std::cout << i << "|";
    }
    std::cout << endl;
}
