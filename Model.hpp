#ifndef MODEL
#define MODEL


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
	// Método virtual. Interface para obter classificação dos modelos concretos
	virtual float classify(Mat *vetor_descritor) = 0;

};	


class MLP_Model: public Model
{
	Ptr<ANN_MLP> network;
public:
	MLP_Model(ANN_MLP::Params *p);
	float classify(Mat *vetor_descritor);
}

class KNN_Model: public Model
{
	Ptr<KNearest> model;
public:
	KNN_Model();
	float classify(Mat *vetor_descritor);
} 
#endif
