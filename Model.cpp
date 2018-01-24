#include "Model.hpp"

// Construtor MLP
MLP_Model::MLP_Model (ANN_MLP::Params *p)
{
	network = ANN_MLP::create(p);
}

// 
float MLP_Model::classify(Mat *descriptor)
{
	return network.predict(vetor_descriptor);
}
	

// Construtor KNN
KNN_Model::KNN_Model (Mat *params)
{
	model = KNearest::create(params);
}


Mat * MLP_Model::classify(Mat *descriptor)
{
	return model.predict(descriptor);
}

