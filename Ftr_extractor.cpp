#include "Ftr_extractor.hpp"


// Classe concreta: Haralick_extractor
// Calcula um vetor de características usando método de Haralick

// Construtor
Haralick_extractor::Haralick_extractor() {}

// Calcula o vetor
int * Haralick_extractor::calculate_vector(int *n)
{
    // implementação haralick
	int * vet = new int(3);
    vet[0] = (*n);
    vet[1] = (*n);
    vet[2] = (*n);
	return vet;
}

// Classe concreta: LBP_extractor
// Calcula um vetor de características com algoritmo Local Binary Pattern

// Construtor
LBP_extractor::LBP_extractor() {}

// Calcula o vetor
int* LBP_extractor::calculate_vector(int *n)
{
	// implementação rotina LBP
	int * vet = new int(3);
    vet[0] = (*n);
    vet[1] = (*n);
    vet[2] = (*n);
	return vet;
}

