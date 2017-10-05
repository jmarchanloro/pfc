#include "include/BoWPredictHeadSet.hpp"
#include "include/BoWSystem.hpp"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum condition{
  HEALTHY = 0,
  EPILEPTIC
};

int main(int argc, char** argv)
{
  cout << "main" << endl;
  const double A=173.61, B=173.61, C=173.61, D=173.61, E=173.61;
  const double F=511.99550, G=511.99550;
  const double K=200, H=200;
  const double I=256, J=256;

  //vector<string> datasets_paths  = {"data/Hset/"};
  //vector<int>    datasets_labels = {  EPILEPTIC   };
  vector<double> freq            = {      128     };
  //vector<int>    datasets_labels = {  HEALTHY };
  BoWSystem *BoWTestBonn = new BoWPredictHeadSet(freq);
  BoWTestBonn->execute();
 /*while (!khbit){
    BoWTestBonn->execute();  // Cada ejecucion captura 3 segundos
  }*/


}
