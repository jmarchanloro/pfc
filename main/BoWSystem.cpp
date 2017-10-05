#include "include/BoWSystem.hpp"

#include <iostream>
#include <vector>
#include <string>
//#include "myutil.hpp"

void BoWSystem::execute()
{
  {
    obtain_signal();
    obtain_feature_vectors_matrix();
    obtain_feature_vectors_reduct();
    classify();
  }

}

void BoWSystem::obtain_signal()
{
  cout << "BoW-obtain_signal_from_datasets" << endl;
  Signal s;
  vector<double> dataset_signal;  
  vector<double> tmp_signal;
  for (string path: datasets_paths){

    dataset_signal = s.read_signal_from_dir(path);
    cout << "read " << path << endl;
    signal.push_back(dataset_signal);
  }
}
void BoWSystem::obtain_feature_vectors_matrix()
{
  cout << "BoW-obtain_feature_vectors_matrix" << endl;
  /*
   * Slide Window parameters
   */
    
  int window_size = 3;
  int overlap     = 1;

  /*
   * DWT parameters
   */
  int level = 5;
  string filter = "db4";
  
  int ncol = 0; // indice para ir almacenando los feature vectors
  for (unsigned int i=0; i<signal.size(); i++){
    // Create a slide window over the signal
    SlideWindow sw(signal.at(i),window_size,overlap,freqs.at(i));
    vector<double> window;
    
    // Create object that give us the feature_vector
    FeatureVector feature_vector(level, filter);

    vector<double> tmp_feature_vector;
  
    int n=0;

    while (!(window = sw.get_next_window()).empty()){
        ++n;
        tmp_feature_vector = feature_vector.get_feature_vector(window);
        feature_vectors_matrix.insert_cols(ncol, arma::mat(tmp_feature_vector));
        ncol++;
    }
    cout << "n: " << n << endl;
    
    // Only for training
    if (! datasets_labels.empty()){
    feature_vectors_labels.insert(feature_vectors_labels.end(),
				  sw.get_nwindows()-1,
				  datasets_labels.at(i));
    }
  }
  
  // Se puede comprobar que feature_vector_matrix y 
  // feature_vectors_labels tienen la misma longitud para 
  // comprobar que todo ha salido bien
  // cout << BoW::feature_vectors_matrix.n_cols << endl;
  // cout << feature_vectors_labels.size() << endl;  
}

//void BoWSystem::myprint(std::vector< vector<double> >& vv)
//{

//    for (auto &v : vv){
//        for (auto &i : v)
//            std::cout << i << "|";
//    }
//    std::cout << endl;
//}

void BoWSystem::myprintsimple(std::vector< double >& v)
{
   int j=0;
   for (auto &i : v){
       std::cout << i << " ";
       j++;
   }

    std::cout << endl;

}

void BoWSystem::myprintsimple(std::vector< int >& v)
{
   int j=0;
   for (auto &i : v){
       std::cout << i << " ";
       j++;
   }

    std::cout << endl;

}
