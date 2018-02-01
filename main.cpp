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
    cv::Ptr<cv::ml::KNearest> knn_model(cv::ml::KNearest::create());
    KNN_trainer *trainer = new KNN_trainer();
    trainer->build_train_data("haraLBP.csv");
    std::cout << trainer->kfold_hit_ratio(knn_model,10) << std::endl;
       
    return 0;
};


