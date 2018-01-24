#ifndef MODEL_TRAINER
#define MODEL_TRAINER

class Model_trainer
{
public:
    // Método virtual puro. O procedimento específico de treinamento deve ser 
    // adequado ao tipo de modelo, portanto a implementação do método cabe a
    // cada classe concreta.
    virtual void train() = 0;
	
    // A avaliação do classificador é uma operação genérica, que pode ser aplicada
    // sobre qualquer modelo. Este método é concreto.
    float evaluate();
};	

#endif
