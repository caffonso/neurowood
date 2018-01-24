#ifndef FTR_EXTRACTOR
#define FTR_EXTRACTOR

/*
    Estruturas auxiliares para passagem de parâmetro
 
    Algoritmos para extração de características
    No caso de adição de qualquer outro método de extração de características, é preciso
    inserir suas entradas nestas estruturas. 
*/


enum enumDescriptors
{
	LBP_DESCRIPTOR = 0,
	HARALICK_DESCRIPTOR
}; 



struct EXTRACTOR_PARAMS
{

};

struct LBP_PARAMS : public EXTRACTOR_PARAMS
{
    // parametros
};

struct HARALICK_PARAMS : public EXTRACTOR_PARAMS
{
    // parametros
};

// Estrutura base, abstrata. Interface para passagem de parâmetros aos construtores.  
struct EXTRACTOR_DATA
{   
    enumDescriptors tipo;
    EXTRACOTR_PARAMS parametros;    
};


// Classe abstrata
class Ftr_extractor
{
public:
	virtual Mat* calculate_vector(int *n) = 0;
};

// Haralick
class Haralick_extractor: public Ftr_extractor
{
    HARALICK_PARAMS parameters;
public:
	Mat* calculate_vector(int *n);
};

// LBP
class LBP_extractor: public Ftr_extractor
{
    LBP_PARAMS parameters;
public:
	MAT* calculate_vector(int *n);
};

#endif
