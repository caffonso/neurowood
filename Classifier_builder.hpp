#ifndef CLASSIFIER_BUILDER
#define CLASSIFIER_BUILDER

// Classifier_builder é uma classe responsável por instanciar, em tempo de execução, diferentes 
// especializações das classes bases que compõe um classificador
class Classifier_builder
{
	cv::Mat *_parameters;					// Genérico. Armazenara dados temporariamente para passagem de parâmetros aos métodos 
	Im_processing *_improc;				// Lista de objetos da classe Im_processing. Um classificador pode ter 0 ou mais destes objetos. 
	Ftr_extractor *_extractor;				// Lista de objetos da classe Ftr_extractor. Um classificador pode ter 0 ou mais destes objetos.
	Model *_model;							// Modelo utilizado pelo classificador. Um classificador possui um modelo.
	Model_trainer *_trainer;				// Módulo de treinamento do classificador. Um classificador possui um módulo de treinamento.
public:

    // Construtor.
    Classifier_builder();					                                
    
    /* Gerencia a criação e composição das partes do classificador.

    Recebe o nome do arquivo contendo os parâmetros para criação do classificador.
    Interpreta o arquivo, constroi os elementos ali especificados e retorna o ponteiro para um classificador montado, pronto para treinamento.
  
    */    
    Classifier* build_classifier(char *nome_arquivo_destino);

    /* Constroi objetos responsaveis pelo processamento de imagem .
     
    */
	Im_processing* build_img_processing(IMGPROC_DATA &data const);

    /* Constroi os extratores de características concretos,
     
    */
	Ftr_extractor* build_ftr_extractor(EXTRACTOR_DATA &data const);	
	
    // Constroi o modelo de acordo com os parâmetros fornecidos.
    //
    Model* build_model(MODEL_DATA &data const);					    

    // Constroi o módulo de treinamento do classificador.
	Model_trainer* build_trainer();			                                
	

};

#endif
