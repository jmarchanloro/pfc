#!/bin/bash

#script para escalar, entrenar y predecir con datasets.train y datasets.test 
./svm-scale -l -1 -u 1 -s range datasets.train > train.scale
echo "datasets.train scaled"
./svm-scale -r range datasets.tests > test.scale
echo "datasets.tests scaled"
./svm-train train.scale model
echo "trained"
./svm-predict test.scale model predictions 
echo "Done"
