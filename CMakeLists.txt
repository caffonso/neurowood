cmake_minimum_required(VERSION 2.8)
project( Classifier )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Cada biblioteca deve ser adicionada como na linha abaixo:
add_library(Im_processing Im_processing.cpp)
add_library(Model Model.cpp)
add_library(Model_trainer Model_trainer.cpp)
add_library(Ftr_extractor Ftr_extractor.cpp)
add_library(Classifier Classifier.cpp)
add_library(Classifier_builder Classifier_builder.cpp)

# Nome do arquivo fonte que contem a função main
add_executable( Teste main.cpp )

# Nome de todas as bibliotecas para linkar
target_link_libraries( Teste Im_processing Model Model_trainer Ftr_extractor Classifier Classifier_builder ${OpenCV_LIBS} )
