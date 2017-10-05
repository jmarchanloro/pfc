#include "include/Engine.hpp"

#include "include/EmoStateDLL.h"
#include "include/edk.h"
#include "include/edkErrorCode.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

EE_DataChannel_t targetChannelList[] = {
        ED_AF3, ED_F7, ED_F3, ED_FC5, ED_T7,
        ED_P7, ED_O1, ED_O2, ED_P8, ED_T8,
        ED_FC6, ED_F4, ED_F8, ED_AF4,
};

void adjust_values(vector<double> &signal);

int _kbhit(void)
{
  struct timeval tv;
  fd_set read_fd;

  /* Do not wait at all, not even a microsecond */
  tv.tv_sec=0;
  tv.tv_usec=0;

  /* Must be done first to initialize read_fd */
  FD_ZERO(&read_fd);

  /* Makes select() ask if input is ready:
   * 0 is the file descriptor for stdin    */
  FD_SET(0,&read_fd);

  /* The first parameter is the number of the
   * largest file descriptor to check + 1. */
  if(select(1, &read_fd,NULL, /*No writes*/NULL, /*No exceptions*/&tv) == -1)
    return 0;  /* An error occured */

  /*  read_fd now holds a bit map of files that are
   * readable. We test the entry for the standard
   * input (file 0). */

if(FD_ISSET(0,&read_fd))
    /* Character pending on stdin */
    return 1;

  /* no characters were pending */
  return 0;
}

Engine::Engine(){
    cout << "Constructor" << endl;
    create_files();

}

std::vector<double> Engine::adquisition(){
    // Si se pone aqui solo los canales ED_X mejor no?
    //EE_DataChannel_t targetChannelList[] = {
    //        ED_COUNTER,
    //        ED_AF3, ED_F7, ED_F3, ED_FC5, ED_T7,
    //        ED_P7, ED_O1, ED_O2, ED_P8, ED_T8,
    //        ED_FC6, ED_F4, ED_F8, ED_AF4, ED_GYROX, ED_GYROY, ED_TIMESTAMP,
    //        ED_FUNC_ID, ED_FUNC_VALUE, ED_MARKER, ED_SYNC_SIGNAL
    //    };


    cout << "Hi, Engine!" << endl;

    EmoEngineEventHandle eEvent	= EE_EmoEngineEventCreate();
    float seconds = 4;
    unsigned int data_rate = 0;
    unsigned int user_ID   = 0;
    unsigned int nsamples_taken = 0;
    int state = 0;
    int r;

    // Establish a connection to the EmoEngine
    if (EE_EngineConnect() == EDK_OK){
        sleep(1);
        std::cout << "Emotiv Engine start up sucessful." << std::endl;
        std::cout << "Start receiving EEG Data." << std::endl;

        // A handle to provide access to the EEG measurements
        DataHandle datah = EE_DataCreate();
//        std::cout << 1 << std::endl;
        // During the measurement process, EmoEngine will maintain a data buffer
        // of sampled data, measured in seconds. That buffer must be initialized:
        r = EE_DataSetBufferSizeInSec(seconds);
//        std::cout << 2 << std::endl;
//        std::cout << r << std::endl;

        // Check new user has been registered.
        state = EE_EngineGetNextEvent(eEvent);
//        std::cout << 3 << std::endl;
//        std::cout << state << std::endl;
        if (state == EDK_OK){
//            std::cout << 4 << std::endl;
            EE_Event_t eventType = EE_EmoEngineEventGetType(eEvent);
            EE_EmoEngineEventGetUserId(eEvent, &user_ID);

            if (eventType == EE_UserAdded){
                std::cout << "User added" << std::endl;

                // Once the user is registered, enable data acquisition
                r = EE_DataAcquisitionEnable(user_ID, true);
                // Loss first second
//                std::cout << r << std::endl;
                std::cout << "Press any key to continue..." << endl;
               while(!_kbhit()){
                usleep(3000000);
                 // Initiate retrieval of the latest EEG buffered data.
                 r = EE_DataUpdateHandle(user_ID, datah);
                 //std::cout << r << std::endl;
                 // How much buffered data is currently available
                 r = EE_DataGetNumberOfSample(datah, &nsamples_taken);
                 r = EE_DataGetSamplingRate(user_ID, &data_rate);
                 std::cout << "data rate: " << data_rate << std::endl;

                 InputSensorDescriptor_t p_descriptor;
                 EmoStateHandle esh;
                 EE_EEG_ContactQuality_t quality;
                 //EE_InputChannels_t

                 if (nsamples_taken != 0){
                     //std::cout << "nsamples: " << nsamples_taken << std::endl;
                     double* data = new double[nsamples_taken];
                     for (unsigned int i=0; i < sizeof(targetChannelList)/sizeof(EE_DataChannel_t); i++){
                         //for (unsigned int i=1; i < 15; i++){
                         for (int sample_idx = 0; sample_idx < (int)nsamples_taken; ++sample_idx){
                             EE_DataGet(datah, targetChannelList[i], data, nsamples_taken);
                             //EE_EEG_ContactQuality_t

                             //quality = ES_GetContactQuality(esh, targetChannelList[i]);
                             //if (quality == EEG_CQ_GOOD) std::cout << "sensor " << sample_idx << "GOOD" << ",";
                             //if (quality == EEG_CQ_POOR) std::cout << "sensor " << sample_idx << "POOR" << ",";
                             //if (quality == EEG_CQ_VERY_BAD) std::cout << "sensor " << sample_idx << "VERY BAD" << ",";
                             //if (quality == EEG_CQ_NO_SIGNAL) std::cout << "sensor " << sample_idx << "NO SIGNAL" << ",";
                             //if (quality == EEG_CQ_FAIR) std::cout << "sensor " << sample_idx << "FAIR" << ",";
                             //std::cout << data[sample_idx] << ",";
                             //files[i] << data[sample_idx] / 100.0 << std::endl; //Escribir con los valores ajustados
                             files[i] << data[sample_idx] << std::endl;

                             //(signal.at(i)).push_back(data[sample_idx]);

                             (channels.at(i)).push_back(data[sample_idx]);
                             //signal.push_back(data[sample_idx]);

                         }
                         //std::cout << std::endl;
                     }
                     delete [] data;

                 }
               } //while

            }
        }

        EE_DataFree(datah);

        EE_EngineDisconnect();
        EE_EmoEngineEventFree(eEvent);

    }

    //write all channels in one vector
    for (int i=0; i<channels.size(); i++){
        signal.insert(signal.end(), channels.at(i).begin(), channels.at(i).end());
    }

    adjust_values(signal);
    return signal;
}

void adjust_values(vector<double> &signal){

    std::transform(signal.begin(), signal.end(), signal.begin(),
                std::bind1st(std::multiplies<double>(),1.0/100.0));

}

void Engine::create_files(){

    // cojo solo los 14 canales, el resto (creo) que no hace falta
    //for (unsigned int i=1; i <= 14; i++){

    for (unsigned int i=0; i < sizeof(targetChannelList)/sizeof(EE_DataChannel_t); i++){
    //for (unsigned int i=1; i < 15; i++){

        std::string path = "data/HeadSet/";
        std::stringstream ss;
        ss << "data/HeadSet/" << i << "_" << get_data_time();
        //path.append(get_data_time());
//        std::cout << path << std::endl;
//        std::cout << ss.str() << std::endl;
        files[i].open((ss.str()).c_str(), std::ofstream::app);

        std::vector<double> channel;
        channels.push_back(channel);
        //signal.push_back(chanel);

    }

}

string Engine::get_data_time(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y-%I-%M-%S",timeinfo);
    std::string str(buffer);

    return str;
}


