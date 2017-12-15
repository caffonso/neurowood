#ifndef IM_PROCESSING
#define IM_PROCESSING

// Estruturas para passagem de parâmetros do processamento de imagem

// Opções de processamento de imagem
enum enumImProcessing
{
    PASS  = 0,      
	CROP,           
	NOISE,          
	COLOR          
};

// Estrutura base, abstrata. Interface para passagem de parâmetros aos construtores.  
struct IMPROC_PARAMS
{
    enumImProcessing type;
};

// Estrutura derivada, concreta. Registra parâmetros específicos à esse algoritmo.
struct CROP_PARAMS : IMPROC_PARAMS
{
    // parametros exemplo
    int par1 = 0; // pode ter valores default
    float par2;
};

struct NOISE_PARAMS : IMPROC_PARAMS 
{
    // parametros
};

struct COLOR_PARAMS : IMPROC_PARAMS 
{
    // parametros
};

// Classes para processamento de imagem

// Classe base, abstrata
class Im_processing
{
public:
	virtual void apply(int *n) = 0;
};

// Classe concreta que implementa métodos para croping da imagem
class Crop_image: public Im_processing
{
	CROP_PARAMS parameters;
public:
    Crop_image();
	void apply(int *n);
};



// Classe concreta que implementa chamada à metodos para redução de ruído
class Noise_filter: public Im_processing
{
	NOISE_PARAMS parameters;
public:
    Noise_filter();
	void apply(int *n);
};


// Classe concreta que implementa chamada à metodos para transformações de cor
class Color_filter: public Im_processing
{
    COLOR_PARAMS parameters;
public:
    Color_filter();
	void apply(int *n);
};


#endif
