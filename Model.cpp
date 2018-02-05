#include "Model.hpp"

// Construtor MLP
MLP_Model::MLP_Model()
{
	_model = cv::ml::ANN_MLP::create();

}

// 
cv::Mat MLP_Model::classify(cv::Mat vetor_descritor)
{
    cv::Mat results;
    results = cv::Mat(1,1,1); 
    _model->predict(vetor_descritor, results, 0);

    return results;
}

void MLP_Model::train(cv::Ptr<cv::ml::TrainData> data)
{
    _model->train(data);
}
	

// Construtor KNN
KNN_Model::KNN_Model ()
{
	_model = cv::ml::KNearest::create();
}


cv::Mat KNN_Model::classify(cv::Mat vetor_descritor)
{
    cv::Mat results;
    results = cv::Mat::zeros(1, 1, cv::DataType<float>::type);
    _model->predict(vetor_descritor, results);

    return results;
}

void KNN_Model::train(cv::Ptr<cv::ml::TrainData> data)
{
    _model->train(data);
}
