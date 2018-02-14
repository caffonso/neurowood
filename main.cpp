#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/ml.hpp>

#include <cstdio>
#include <iostream>
#include <time.h>

#include "Im_processing.hpp"
#include "Ftr_extractor.hpp"
#include "Model.hpp"
#include "Model_trainer.hpp"
#include "Classifier.hpp"
#include "Classifier_builder.hpp"

void help() {
    std::cout << "$./Teste -data=<path> 0=mlp 1=knn" << std::endl;
}  

int main(int argc, char *argv[])
{
    char *data_filename;
    int method = 0;
    
    cv::Mat img = cv::imread("test.png");
    cv::imshow("imgOriginal",img);
    Color_filter *gray = new Color_filter();
    gray->apply(img);
    cv::waitKey(0);  
    
    data_filename = argv[1];
    method = atoi(argv[2]);

    help();
    
    if (method == 0) {
        MLP_Model *mlp_model = new MLP_Model();
        MLP_trainer *mlp_trainer = new MLP_trainer();
        mlp_trainer->build_train_data(data_filename,2);
        mlp_trainer->mlp_kfold_hit_ratio(mlp_model,10);
    }
    if (method == 1) {
        KNN_Model *knn_model = new KNN_Model();
        KNN_trainer *knn_trainer = new KNN_trainer();
        knn_trainer->build_train_data(data_filename,2);
        knn_trainer->knn_kfold_hit_ratio(knn_model,10);
    }
    return 0;
};


