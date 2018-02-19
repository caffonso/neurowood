#include "Classifier.hpp"

/**
 * Construtor
 */
Classifier::Classifier(Im_processing* filters, Ftr_extractor* extractor, Model* model, Model_trainer* trainer) 
{
	_filters = filters;
	_extractor = extractor;
	_model = model;
	_trainer = trainer;
}

int Classifier::classify(cv::Mat input_img) {
	
	int categoria;
	int i;
	cv::Mat image;
	cv::Mat descriptor[sizeof(_extractor)/sizeof(Ftr_extractor*)];
	input_img.copyTo(image);

	for (i = 0; i < (sizeof(_filters)/sizeof(Im_processing*)); ++i) {
		_filters[i].apply(image);
	}

	
	for (i = 0; i < (sizeof(_extractor)/sizeof(Ftr_extractor*)); ++i) {
		cv::Mat temp;
		temp = _extractor[i].calculate_vector(image);
		temp.copyTo(descriptor[i]);
	}
	cv::Mat sample;
	
	return _model->_model->predict(sample);
}




