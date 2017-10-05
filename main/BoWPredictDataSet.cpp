#include "include/BoWPredictDataSet.hpp"

#include "include/KMeansClustering.hpp"
#include "include/Classifier.hpp"

BoWPredictDataSet::BoWPredictDataSet(vector< string >& dataset_path, vector<int>& datasets_labels, vector<double>& freqs)
{
  this->datasets_paths = dataset_path;
  this->datasets_labels= datasets_labels;
  this->freqs = freqs;

}

void BoWPredictDataSet::obtain_feature_vectors_reduct()
{
  KMeansClustering c(feature_vectors_matrix);
  //feature_vectors_matrix.print();
//   c.clustering();
  feature_vector_reduct = c.get_histogram();
  //myprint(feature_vector_reduct);


}

void BoWPredictDataSet::classify()
{
  //vector<int> labels; //borrar de testing, no tiene lables
  Classifier classifier;
  classifier.testing(feature_vector_reduct, feature_vectors_labels);
}

void BoWPredictDataSet::myprint(std::vector< vector<double> >& vv)
{

    for (auto &v : vv){
        for (auto &i : v)
            std::cout << i << "|";
    }
    std::cout << endl;
}
