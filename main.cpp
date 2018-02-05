#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/ml.hpp>

#include <iostream>
#include <time.h>

#include "Im_processing.hpp"
#include "Ftr_extractor.hpp"
#include "Model.hpp"
#include "Model_trainer.hpp"
#include "Classifier.hpp"
#include "Classifier_builder.hpp"

int main(int argc, char *argv[])
{
    /*
    KNN_Model *knn_model = new KNN_Model();
    KNN_trainer *knn_trainer = new KNN_trainer();
    knn_trainer->build_train_data("haraLBP.csv");
    knn_trainer->knn_kfold_hit_ratio(knn_model,10);
    */
    MLP_Model *mlp_model = new MLP_Model();
    MLP_trainer *mlp_trainer = new MLP_trainer();
    mlp_trainer->build_train_data("haraLBP.csv");
    mlp_trainer->mlp_kfold_hit_ratio(mlp_model,10);
    
/*
    cv::Ptr<cv::ml::TrainData> data = cv::ml::TrainData::loadFromCSV("haraLBP.csv",0,-1,-1);
    data->setTrainTestSplitRatio(0.3, true); 
    cv::Mat output = cv::Mat::zeros(165, 1, CV_32F);


    int layers_vec[4] = {73,73,73,1};
    cv::Mat layers = cv::Mat(1,4,cv::DataType<int>::type, layers_vec); 

    cv::Ptr<cv::ml::ANN_MLP> mlp = cv::ml::ANN_MLP::create();
    mlp->setLayerSizes(layers);

    mlp->train(data);
    std::cout << "Hit Ratio: " << (1 - mlp->calcError(data,true,output))*100 << "%" << std::endl;
*/
    return 0;
};


