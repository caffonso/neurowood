#ifndef CLASSIFIER_BUILDER
#define CLASSIFIER_BUILDER

// Classifier_builder é uma classe responsável por instanciar, em tempo de execução, diferentes 
// especializações das classes bases que compõe um classificador
class Classifier_builder
{
	cv::Mat* _parameters;					// Genérico.
	Im_processing* _filters;				// Lista de objetos da classe Im_processing. Um classificador pode ter 0 ou mais destes objetos. 
	Ftr_extractor* _extractor;				// Lista de objetos da classe Ftr_extractor. Um classificador pode ter 0 ou mais destes objetos.
	Model* _model;							// Modelo utilizado pelo classificador. Um classificador possui um modelo.
	Model_trainer* _trainer;				// Módulo de treinamento do classificador. Um classificador possui um módulo de treinamento.
public:
	Classifier_builder();					// Construtor.
	Im_processing* build_img_processing();	// Constroi os objetos concretos responsáveis pelo processamento de imagem.
	Ftr_extractor* build_ftr_extractor();	// Constroi os extratores de características concretos, de acordo com parâmetros lidos.
	Model* build_model();					// Constroi o modelo de acordo com os parâmetros fornecidos.
	Model_trainer* build_trainer();			// Constroi o módulo de treinamento do classificador.
	Classifier* build_classifier();			// Constroi o classificador.
};

#endif
