#ifndef CLASSIFIER
#define CLASSIFIER

// Classifier define toda a informação e operações necessárias para realizar a classificação.
// É uma composição de diferentes módulos, que atuam sobre as imagens fornecidas na chamada
// ao método "predict" para produzir classificações.
class Classifier
{
	Im_processing* _filters;				// Lista de objetos da classe Im_processing
	Ftr_extractor* _extractor;				// Lista de objetos da classe Ftr_extractor
	Model* _model;							// Modelo utilizado pelo classificador
	Model_trainer* _trainer;				// Módulo responsável pelas rotinas de treinamento do classificador
public:
	
	Classifier();    	// Construtor
	// Função principal: recebe uma imagem e retorna a previsão de categoria	
	int classify(cv::Mat* input_img);
	

     			
};

#endif
