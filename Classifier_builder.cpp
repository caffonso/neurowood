#include "Classifier_builder.hpp"


/* 
    Construtor    
*/
Classifier_builder::Classifier_builder()
{
    
}

/*
Classifier* Classifier_builder::build_classifier(char *nome_arquivo_parametros)
{
    FILE *fp;
    int count;
    int num_objetos;
    Im_processing *improc_pointer;
    // Abre o arquivo

    // Interpreta e extrai os parâmetros do arquivo
    
    // Constroi objetos de processamento de imagem 
    // É preciso alocar o vetor antes
    for (count = 0; count < num_objetos; count++) {
        _improc[count] =  build_img_processing(parametros_imp[count]);
    }
    
    // Constroi objetos de extração de características
    // É preciso alocar o vetor antes
    for (count = 0; count < num_objetos; count++) {
        _extractor[count] = build_ftr_extractor(parametros_ext[count])
    }
 
    // Constroi o modelo
    _model = build_model(parametros_mod); 
    
    // Constroi o objeto para treinamento         
    _trainer = build_trainer(parametros_tra);

    return Classifier(_improc, _extractor, _model, _trainer);
}
*/



