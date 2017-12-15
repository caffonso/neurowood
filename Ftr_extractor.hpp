#ifndef FTR_EXTRACTOR
#define FTR_EXTRACTOR

// Estruturas auxiliares para passagem de parâmetro
// Algoritmos para extração de características
enum enumDescriptors
{
	LBP_DESCRIPTOR = 0,
	HARALICK_DESCRIPTOR
}; 

// Estrutura base, abstrata. Interface para passagem de parâmetros aos construtores.  
struct EXTRACTOR_PARAMS
{
    enumDescriptors type;
};

struct LBP_PARAMS 
{
    // parametros
};

struct HARALICK_PARAMS 
{
    // parametros
};



// Classe abstrata
class Ftr_extractor
{
public:
	virtual int* calculate_vector(int *n) = 0;
};

// Haralick
class Haralick_extractor: virtual public Ftr_extractor
{
    HARALICK_PARAMS parameters;
public:
	int* calculate_vector(int *n);
};

// LBP
class LBP_extractor: virtual public Ftr_extractor
{
    LBP_PARAMS parameters;
public:
	int* calculate_vector(int *n);
};

#endif
