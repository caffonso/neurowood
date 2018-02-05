#ifndef MODEL
#define MODEL

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>

// Tipos de classificadores
enum enumModels
{
	MLP_MODEL = 0,
	KNN_MODEL
};

// Define uma interface para lidas com os modelos de classificador possíveis
class Model
{
    
public:
    cv::Ptr<cv::ml::StatModel> _model;
	// Método virtual. Interface para obter classificação dos modelos concretos
	virtual cv::Mat classify(cv::Mat vetor_descritor)=0;
};	


class MLP_Model: public Model
{
public:
	MLP_Model();
	cv::Mat classify(cv::Mat vetor_descritor);
    void train(cv::Ptr<cv::ml::TrainData> data);
};

class KNN_Model: public Model
{
public:
	KNN_Model();
	cv::Mat classify(cv::Mat vetor_descritor);
    void train(cv::Ptr<cv::ml::TrainData> data);
}; 
#endif
