#include "include/BoWTraining.hpp"
#include "include/BoWSystem.hpp"

#include <iostream>
#include <vector>
#include <string>

#include <chrono>

using namespace std;

enum condition{
  HEALTHY = 0,
  EPILEPTIC
};

int main(int argc, char** argv)
{
  cout << "main" << endl;
  vector<string> datasets_paths  = {"data/Aset/", "data/Eset/"};
  vector<int>    datasets_labels = {  HEALTHY   ,   EPILEPTIC};
  vector<double> freqs           = {   173.61    ,   173.61};
  
    auto start = std::chrono::high_resolution_clock::now();
  BoWSystem *BoWBonn = new BoWTraining(datasets_paths, datasets_labels, freqs);
  BoWBonn->execute();
  
    auto finish = std::chrono::high_resolution_clock::now();
  
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000000.0 << "s\n";    
  
  
  
  
}
/*
 * BONN
 * Sets A and B consisted of segments taken from surface EEG recordings that were carried
 * out on five health volunteers using a standardized electrode placement
 * scheme. volunteers were relaxed in an awake state with eyes open (A) and eyes closed (B)
 * , respectively, Sets C, D, and E originated form our EEG archive of presurgical diagnosis
 * For the present study EEGs from five patients were selected, all of whom had achieved complete seizure control after resection of one of
 * the hippocampal formations, which was therefore correctly diagnosed to be the
 * epileptogenic zone ͑cf. Fig. 2͒. Segments in set D were recorded from within the 
 * epileptogenic zone, and those in set C from the hippocampal formation of the
 * opposite hemisphere of the brain. While sets C and D contained only activity measured during
 * seizure free intervals, set E only contained seizure activity. Here segments were
 * selected from all recording sites exhibiting ictal activity
 * 
 * Table 3 articulo tambien resume
 */
