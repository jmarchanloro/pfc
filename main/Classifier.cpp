#include "include/Classifier.hpp"
#include "include/svm.h"

#include <iostream>
#include <vector>
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

void Classifier::training(const vector< std::vector< double > >& histogram, vector<int>& labels)
{

    create_problem(histogram, labels);
    stablish_parameters();
    model = svm_train(&problem, &param);
    if(svm_save_model(model_file, model)){
      std::cerr << "can't save model to file " << model_file << endl;
    }
    else{
      std::cout << "nr_classes: " << svm_get_nr_class(model) << endl;
      int label[3];
      svm_get_labels(model,label);
      std::cout << "labels: " << label[0] <<"," << label[1] <<  endl;

      svm_free_and_destroy_model(&model);
      svm_destroy_param(&param);
      free(problem.x);
      free(problem.y);
    }

}

void Classifier::testing(const vector< std::vector< double > >& histogram, vector<int>& labels)
{
  double predict_label;
  double target_label;

  if ( !labels.empty()) target_label = labels.at(0); // ¿Por quE asI en lugar de hacer
                                                     // labels.at(ntest) dentro del for?
                                                     // Porque todo el dataset de testing es o 0 o 1 y
                                                     // se hace directamente
  int correct = 0;
  int total   = 0;
  int predict_zero = 0;
 
  if((model = svm_load_model(model_file)) == NULL){
    cout << "model file not found. Please, run ./bin/main-train before" << endl;
    return;
  }
  cout << 2 << endl;
  int ntest = histogram.size();
  //cout << "n vectors: " << ntest << endl;
  vector<double> testing_vector = histogram.front();
  long unsigned int elements = testing_vector.size();
  //cout << "n elements: " << elements << endl;
  x = Malloc(struct svm_node, elements+1);

  for (int i=0; i<ntest; i++){

    testing_vector = histogram.at(i);
    double value;
    unsigned int n=0;
    for(;n<elements;n++){
      value = testing_vector.at(n);
      x[n].index = n+1;
      x[n].value = value;
    }
    x[n].index = -1;

    // ver estructura
    //for(n=0;n<elements;n++){
    //    cout << x[n].index << ":" << x[n].value << " ";
    //}
    //


    //write the file
    //cout << "empiezo a leer datos" << endl;
    ofstream data;
    //cout << 1 << endl;
    data.open("datasets.tests", std::ofstream::app);
    //cout << 2 << endl;
    data << "+" << target_label;
    for(unsigned int e=0; e<elements; e++){
        data << " ";
        data << x[e].index << ":" << x[e].value;
    }
    data << endl;

    predict_label = svm_predict(model, x);
    if (!labels.empty()) {
        if (predict_label == target_label) correct++;

        total++;
    }
    else{
        if ( predict_label == 0) predict_zero++;

        total++;
    }

    //cout << predict_label << endl;

    // BORRAR. esto imprime la estructura. Se crea y se almacena bien.
//     for(unsigned int e=0; e<elements; e++){
//       cout << x[e].index << ":" << x[e].value << endl;
//     }
    /////////////////////////////////////////
  }
  if (!labels.empty())
      cout << "Accuracy = " << (double)correct/total*100 << "% (" << correct << "/" << total << ")" << " classification" << endl;
  else
      cout << "Predict Healthy = " << (double)predict_zero/total*100 << "% (" << predict_zero << "/" << total << ")" << " classification" << endl;
  free(x);


}

void Classifier::create_problem(const vector< std::vector< double > >& histogram, vector<int>& labels){

    vector<double> training_vector = histogram.front();
    long unsigned int elements = training_vector.size();

    /* Number of training data*/
    problem.l = (int)histogram.size();
    /* Number of labels */
    problem.y = Malloc(double, problem.l);
    /* Data */
    problem.x = Malloc(struct svm_node *, problem.l);
    x_space   = Malloc(struct svm_node, ((int)elements + 1) * problem.l);

    /*   Now create the array of pointers to a sparse representation of */
    /*   training vectors */
    int j=0;
    for (int i=0; i<problem.l; i++){
        problem.x[i] = &x_space[j];
        problem.y[i] = labels.at(i);

        training_vector = histogram.at(i);
        double value;
        for (unsigned int n=1; n <= elements; n++){
            x_space[j].index = n;
            value = training_vector.at(n-1);
            x_space[j].value = value;
            ++j;
        }
        x_space[j++].index = -1;
    }

    // BORRAR. esto imprime la estructura. Se crea y se almacena bien.
//     cout << "Estructura" << endl;
//      for (int i=0; i<problem.l ; i++){
//      cout << *((problem.y)++) << endl;
//      }

    struct svm_node **node;
    struct svm_node *x_space;
    node = problem.x;
  //   for (int i=0; i<problem.l; i++){
  //     x_space = *(node++);
  //     for(unsigned int e=0; e<elements; e++){
  //       cout << x_space[e].index << ":" << x_space[e].value;
  //     }
  //     cout << endl;
  //   }

    //write the file
    //cout << "empiezo a leer datos" << endl;
    ofstream data;
    //cout << 1 << endl;
    data.open("datasets.train");
    //cout << 2 << endl;

    for (int i=0; i<problem.l; i++){
      x_space = *(node++);
      data << "+" << problem.y[i];
      //cout << "+" << problem.y[i];
      for(unsigned int e=0; e<elements; e++){
        data << " ";
        //cout << " ";
        data << x_space[e].index << ":" << x_space[e].value;
        //cout << x_space[e].index << ":" << x_space[e].value;
  //       cout << x_space[e].index << ":" << x_space[e].value;
      }
      data << endl;
      //cout << endl;
    }

}

//  // BORRAR. esto imprime la estructura. Se crea y se almacena bien.
////   for (int i=0; i<problem.l ; i++){
////   cout << *((problem.y)++) << endl;
////   }
////
////   struct svm_node **node;
////   struct svm_node *x_space;
////   node = problem.x;
////   for (int i=0; i<problem.l; i++){
////     x_space = *(node++);
////     for(unsigned int e=0; e<elements; e++){
////       cout << x_space[e].index << ":" << x_space[e].value << endl;
////     }
////   }

//}
void Classifier::stablish_parameters()
{
    /* Use default values of library example*/
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.degree = 3;
    param.gamma = 0.5;	// 1/num_features
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 1;
    param.eps = 1e-3;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;

}

void Classifier::myprint(std::vector< int >& v)
{

    for (auto &i : v){
        std::cout << i << endl;
    }
}

void Classifier::myprint(std::vector< double >& v)
{

    for (auto &i : v){
        std::cout << i << endl;
    }
}
