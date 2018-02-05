#ifndef MODEL_TRAINER
#define MODEL_TRAINER

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>

#include "Model.hpp"

class Model_trainer
{    
    
public:
    cv::Mat _samples;
    cv::Mat _responses;
    
    

    // A avaliação do classificador é uma operação genérica, que pode ser aplicada
    // sobre qualquer modelo. Este método é concreto.
    void build_train_data(char *filename);
};

class MLP_trainer : public Model_trainer
{
    
public:
    MLP_trainer();
    float mlp_kfold_hit_ratio(Model *model_pointer, int kfold);
};

class KNN_trainer : public Model_trainer
{
    
public:
	KNN_trainer();
    float knn_kfold_hit_ratio(Model *model_pointer, int kfold);
};
#endif
