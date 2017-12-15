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
	virtual int classify() = 0;
	
	// É necessário declarar destruidor virtual
	virtual ~Model();
};	

#endif
