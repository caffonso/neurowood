#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

#include "Im_processing.hpp"

using namespace std;
int main(void)
{
    
    int n = 2;
    

    
    // Teste do mecanismo de polimorfismo para os filtros
    Im_processing *improc[3];
    improc[0] = new Color_filter;
    improc[1] = new Crop_image;
    improc[2] = new Noise_filter;

    for (int i = 0; i < 3; i++) {
        improc[i]->apply(&n);
    }    
 
    cout << "Hello world!" << endl;
    cout << n << endl;
    return 0;
};


