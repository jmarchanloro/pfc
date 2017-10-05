CC	= g++
DEBUG   = -g
INCLUDEXML = -I/usr/include/libxml2
IPYTHON = -I /usr/include/python2.7
FLAGS	= -ansi -Wall -std=c++11 -pedantic -O3 $(DEBUG)
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -#L/home/javierml/git/pfc/steps/raw_data/get_chanels/../lib/ -ledk 
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L./lib/ -ledk 
EMBEDPY = -lpython2.7 `python-config --cflags` `python-config --ldflags`

EXECTRAIN = main-train
EXECPREDICT = main-predict
EXECHEAD    = main-headset
INC          =  include
BIN =  bin
OBJ = obj
DATA = data

all: main-train main-predict main-headset

main-train:  $(OBJ)/svm.o $(OBJ)/Classifier.o $(OBJ)/SlideWindow.o $(OBJ)/Signal.o $(OBJ)/FeatureVector.o $(OBJ)/KMeansClustering.o $(OBJ)/BoWSystem.o $(OBJ)/BoWTraining.o
	$(CC) -o $(BIN)/$(EXECTRAIN)     $(FLAGS) $(IPYTHON) main-train.cpp $^  -lmlpack $(EMBEDPY)

main-predict: $(OBJ)/svm.o $(OBJ)/Classifier.o $(OBJ)/SlideWindow.o $(OBJ)/Signal.o $(OBJ)/FeatureVector.o $(OBJ)/KMeansClustering.o $(OBJ)/BoWSystem.o $(OBJ)/BoWPredictDataSet.o
	$(CC) -o $(BIN)/$(EXECPREDICT) $(FLAGS) $(IPYTHON) main-predict.cpp $^ -lmlpack $(EMBEDPY)
	
main-headset: $(OBJ)/svm.o $(OBJ)/Classifier.o $(OBJ)/SlideWindow.o $(OBJ)/Signal.o $(OBJ)/FeatureVector.o $(OBJ)/KMeansClustering.o $(OBJ)/BoWSystem.o $(OBJ)/BoWPredictHeadSet.o $(OBJ)/Engine.o
	$(CC) -o $(BIN)/$(EXECHEAD) $(FLAGS) $(IPYTHON) main-headset.cpp $^ -lmlpack $(EMBEDPY) $(LIBS)

$(OBJ)/Engine.o: Engine.cpp $(INC)/Engine.hpp $(INC)/IEngine.hpp
	$(CC) $(LFLAGS) $(FLAGS) -c Engine.cpp -o obj/Engine.o
	
	
$(OBJ)/BoWPredictHeadSet.o: $(OBJ)/BoWSystem.o BoWPredictHeadSet.cpp $(INC)/BoWPredictHeadSet.hpp
	$(CC) $(FLAGS) $(IPYTHON) $(INCLUDEXML) -c BoWPredictHeadSet.cpp -o $(@)

$(OBJ)/BoWPredictDataSet.o: $(OBJ)/BoWSystem.o BoWPredictDataSet.cpp $(INC)/BoWPredictDataSet.hpp
	$(CC) $(FLAGS) $(IPYTHON) $(INCLUDEXML) -c BoWPredictDataSet.cpp -o $(@)
	
$(OBJ)/BoWTraining.o: $(OBJ)/BoWSystem.o BoWTraining.cpp $(INC)/BoWTraining.hpp
	$(CC) $(FLAGS) $(IPYTHON) $(INCLUDEXML) -c BoWTraining.cpp -o $(@)

$(OBJ)/BoWSystem.o: BoWSystem.cpp $(INC)/BoWSystem.hpp
	$(CC) $(FLAGS) $(IPYTHON) -c $< -o $(@)

$(OBJ)/KMeansClustering.o: KMeansClustering.cpp $(INC)/KMeansClustering.hpp include/clustering.hpp
	$(CC) $(FLAGS) $(INCLUDEXML) -c $< -o $(@) -larmadillo -lmlpack -lm

$(OBJ)/FeatureVector.o: FeatureVector.cpp $(INC)/FeatureVector.hpp
	$(CC) $(FLAGS)  $(IPYTHON) -c $<  -o $(@) $(EMBEDPY) 
	echo 'FeatureVector compiled'
	
$(OBJ)/Signal.o: Signal.cpp $(INC)/Signal.hpp
	$(CC) $(FLAGS) -c $<  -o $(@)
	echo 'Signal compiled'

$(OBJ)/SlideWindow.o: SlideWindow.cpp $(INC)/SlideWindow.h
	$(CC) $(FLAGS) -c $<  -o $(@)
	echo 'SlideWindow compiled'

$(OBJ)/Classifier.o: Classifier.cpp $(INC)/Classifier.hpp $(INC)/svm.h
	$(CC) $(FLAGS) -c $<  -o $(@)
	echo 'Classifier compiled'

$(OBJ)/svm.o : svm.cpp $(INC)/svm.h
	$(CC) -Wall -Wconversion -O3 -fPIC $(DEBUG) -c svm.cpp -o $(@)
	echo 'svm compiled'	

clean:
	rm -f  $(BIN)/$(EXECTRAIN) $(BIN)/$(EXECPREDICT) $(DATA)/centroids.csv $(DATA)/labels.csv $(DATA)/svm_model $(OBJ)/*.o



# CC	= g++
# DEBUG   = -g
# INCLUDEXML = -I/usr/include/libxml2
# IPYTHON = -I /usr/include/python2.7
# FLAGS	= -ansi -Wall -std=c++11 -pedantic -O3 $(DEBUG) $(INCLUDEXML) $(IPYTHON)
# EMBEDPY = -lpython2.7 `python-config --cflags` `python-config --ldflags`
# 
# 
# SOURCES	= BoWSystem.cpp BoW.cpp BoWPredictDataSet.cpp Signal.cpp SlideWindow.cpp FeatureVector.cpp KMeansClustering.hpp Classifier.cpp
# EXECTRAIN = main-train
# EXECPREDICT = main-predict
# BIN =  bin
# DATA = data
# 
# all: main-train main-predict
# 
# main-train: $(OBJECTS) svm.o
# 	mkdir -p $(BIN) 
# 	mkdir -p $(BIN)/coeff
# 	$(CC) -o $(BIN)/$(EXECTRAIN) $(FLAGS) main-train.cpp $(SOURCES) svm.o -larmadillo -lmlpack -lm $(EMBEDPY)
# 
# main-predict: $(OBJECTS) svm.o
# 	mkdir -p $(BIN)
# 	mkdir -p $(BIN)/coeff
# 	$(CC) -o $(BIN)/$(EXECPREDICT) $(FLAGS) main-predict.cpp $(SOURCES) svm.o -larmadillo -lmlpack -lm $(EMBEDPY)
# 	
# svm.o : svm.cpp svm.h
# 	$(CC) -Wall -Wconversion -O3 -fPIC $(DEBUG) -c svm.cpp
# 
# clean:
# 	rm -f details* smoothing* $(BIN)/$(EXECTRAIN) $(BIN)/$(EXECPREDICT) -r $(BIN)/coeff $(DATA)/centroids.csv $(DATA)/labels.csv $(DATA)/svm_model
