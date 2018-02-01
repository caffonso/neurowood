#include "Model.hpp"

// Construtor MLP
MLP_Model::MLP_Model(cv::Mat *params)
{
	_model = cv::ml::ANN_MLP::create();
}

// 
cv::Mat MLP_Model::classify(cv::InputArray vetor_descritor)
{
    cv::Mat results;
    results = cv::Mat(1,1,1); 
	_model->predict(vetor_descritor, results, 0);

    return results;
}

void MLP_Model::train(cv::Mat& samples, cv::Mat& responses)
{
    _model->train(samples, cv::ml::ROW_SAMPLE, responses);
}
	

// Construtor KNN
KNN_Model::KNN_Model (cv::Mat *params)
{
	_model = cv::ml::KNearest::create();
}


cv::Mat KNN_Model::classify(cv::InputArray vetor_descritor)
{
    cv::Mat results;
    results = cv::Mat(1,1,1); 	
	_model->predict(vetor_descritor, results);

    return results;
}

void KNN_Model::train(cv::Mat& samples, cv::Mat& responses)
{
    _model->train(samples, cv::ml::ROW_SAMPLE, responses);
}
