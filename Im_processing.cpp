#include "Im_processing.hpp"

// Classe concreta: Crop_image
// Extrai uma região da imagem

// Construtor
Crop_image::Crop_image() {}

// Aplica
void Crop_image::apply(int *n) {
    (*n) = 2 * (*n);
}

// Classe concreta: Noise_filter
// Aplica filtros de redução de ruído

// Construtor
Noise_filter::Noise_filter() {}

// Aplica
void Noise_filter::apply(int *n) {
    (*n) = 2 * (*n);
}

// Classe concreta: Noise_filter
// Aplica filtros de cor

// Construtor
Color_filter::Color_filter() {}

// Aplica
void Color_filter::apply(int *n) {
    (*n) = 2 * (*n);
}
