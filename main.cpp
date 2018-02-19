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

using namespace cv;
using namespace cv::ml;
using namespace std;

void help() {
    std::cout << "$./Teste -data=<path> 0=mlp 1=knn" << std::endl;
}  

int main(int argc, char *argv[])
{
    String classifier_save_filename;
    String classifier_load_filename;
    String data_filename;

    int method = 0;
 
 	CommandLineParser parser(argc, argv, keys);
 	parser.about("NeuroWood v0.0.3");

 	if (parser.has("test")) {
	 	if (parser.has("knn")) {
	 		method = 1;
	 	}
	    if (parser.has("mlp")) {
	 		method = 0;
	 	}
	 	data_filename = parser.get<String>(0);
	 	cout << data_filename << endl;
	}
 	if (parser.has("train")) {
 		data_filename = parser.get<String>(0);
 		data_load_filename = parser.get<String>(1);
 		data_save_filename = (parser.get<String>(2) != NULL ? parser.get<String>(2) : parser.get<String>(1));
 	

 	}

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


