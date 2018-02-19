#include "Classifier_builder.hpp"


/*
    Construtor    
*/
Classifier_builder::Classifier_builder()
{
    
}


Classifier* Classifier_builder::build_classifier(char *nome_arquivo_parametros)
{
    FILE *fp;
    int count;
    int num_objetos;
    
    Im_processing *improc_pointer[];
    Ftr_extractor *extractor_pointer[];
    Model *model_pointer;
    Model_trainer *trainer_pointer;
    
    struct IMPROC_DATA *improc_data[];
    struct EXTRACTOR_DATA *extractor_data[];
    struct MODEL_DATA *model_data[];
    struct TRAINER_DATA *trainer_data[];
    // Abre o arquivo
    
    // Interpreta e extrai os parâmetros do arquivo
    
    
    // Constroi objetos de processamento de imagem 
    // É preciso alocar o vetor antes
    for (count = 0; count < num_objetos; count++) {
        _improc[count] =  build_img_processing(improc_data[count]);
    }
    
    // Constroi objetos de extração de características
    // É preciso alocar o vetor antes
    for (count = 0; count < num_objetos; count++) {
        _extractor[count] = build_ftr_extractor(extractor_data[count]);
    }
 
    // Constroi o modelo
    _model = build_model(model_data); 
    
    // Constroi o objeto para treinamento         
    _trainer = build_trainer(trainer_data);

    return Classifier(_improc, _extractor, _model, _trainer);
}

Im_processing * Classifier_builder::build_img_processing(struct IMGPROC_Data *data) {
	
	int i;
	Im_processing *improc_vet = malloc(data.size() * sizeof(Im_processing*));

	for (i = 0; i < data.size(); ++i) {
		Im_processing *new_obj;
		switch (data[i].type) {
			case 0: {
				new_obj = NULL;
			}; break;
			case 1: {
				new_obj = new Crop_image(data[i].parametros);
			}; break;
			case 3: {
				new_obj = new Noise_filter(data[i].parametros);
			}; break;
			case 4: {
				new_obj = new Color_filter(data[i].parametros);
			}; break;
			default:
		}
		improc_vet[i] = new_obj;
	}
	return improc_vet;
}

Ftr_extractor * Classifier_builder::build_ftr_extractor(struct EXTRACTOR_DATA *data) {
	int i;
	Ftr_extractor *extractor_vet = malloc(data.size() * sizeof(Ftr_extractor*));
	for (i = 0; i < data.size(); ++i) {
		Ftr_extractor *new_obj;
		switch (data[i].type) {
			case 0: {
				new_obj = NULL;
			}; break;
			case 1: {
				new_obj = new LBP_extractor(data[i].parametros);
			}; break;
			case 3: {
				new_obj = new Haralick_extractor(data[i].parametros);
			}; break;
			default:
		}
		extractor_vet[i] = new_obj;
	}
	return extractor_vet;
}

 Model * Classifier_builder::build_model(struct MODEL_DATA *data) {
 	int i;
	Model *model;
	switch (data[i].type) {
		case 0: {
			new_obj = new MLP_Model(data.parametros));
		}; break;
		case 1: {
			new_obj = new KNN_Model(data.parametros);
		}; break;
		default:
	}
	return model;	
 }

 Model_trainer * Classifier_builder::build_trainer(struct TRAINER_DATA *data) {
 	int i;
	Model *model_trainer;
	switch (data[i].type) {
		case 0: {
			new_obj = new MLP_trainer(data.parametros));
		}; break;
		case 1: {
			new_obj = new KNN_trainer(data.parametros);
		}; break;
		default:
	}
	return model;		
 }
