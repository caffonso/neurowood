#include "Model_trainer.hpp"

using namespace std;

// Comparação entre floats crua, aproveitando a característica dos resultados
// nossos de serem proximos de 1 ou de 0
static bool fcmp(float a, float b)
{
    return ((int)a == (int)b);
}

// Embaralha as linhas da matriz
cv::Mat shuffleRows(const cv::Mat &matrix)
{
  std::vector <int> seeds;
  for (int cont = 0; cont < matrix.rows; cont++)
    seeds.push_back(cont);

  cv::randShuffle(seeds);

  cv::Mat output;
  for (int cont = 0; cont < matrix.rows; cont++)
    output.push_back(matrix.row(seeds[cont]));

  return output;
}

bool Model_trainer::build_train_data(char *filename, int class_count) 
{
    ifstream input_file(filename);              // Leitura de arquivos através da biblioteca ifstream
    
    if (!input_file.is_open()) {
        cout << "Could not open input data file." << endl;
        return false;
    }
    
    string line;                                // Buffer 
    vector< vector<float> > all_data;           // Armazenara os valores lidos do arquivo
    
    // Percorre cada linha do arquivo
    while(getline(input_file, line)) {
        vector<float> values;                  // valores da linha atual
        
        stringstream temp(line);                
        string single_value;        
        
        // Isola cada valor em uma string, converte em float e adiciona no vetor de valores
        while(getline(temp,single_value,',')) {
           values.push_back(atof(single_value.c_str()));
        }
        // Adiciona a linha atual ao conjunto de dados
        all_data.push_back(values);
    }
     
     // Aloca os membros do treinador com as dimensões dos dados extraídos do arquivo   
    _samples = cv::Mat::zeros((int)all_data.size(), (int)all_data[0].size(), CV_32F);  
    _responses = cv::Mat::zeros((int)all_data.size(), 1, CV_32S);

    int rows, cols;
    int j;

    for(rows = 0; rows < (int)all_data.size(); rows++) {
        // Lê as colunas de características
        for(cols = 0; cols < (int)all_data[0].size()-1; cols++) {
            _samples.at<float>(rows,cols) = all_data[rows][cols];
        }
            _responses.at<int>(rows) = all_data[rows][cols]; 
    }


    // Console verbose 
    int num_samples = (int)_samples.rows;
    int feature_vec_size = (int)_samples.cols;
    int output_vec_size = (int)_responses.cols;
   
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Read the csv data file: " << filename << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "num_samples: " << num_samples << std::endl;
    std::cout << "feature_vec_size: " << feature_vec_size << std::endl;
    std::cout << "output_vec_size: " << output_vec_size << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    return true;
}

float KNN_trainer::knn_kfold_hit_ratio(Model *model_pointer, int kfold)
{
    int num_samples;
    int num_features;
    int class_count;
    int hit_count;
    int split_ini, split_end;    
    float hit_ratio;
    int row, col;
    int i;
    int k = 3;

    cv::Mat trainSamples;
    cv::Mat trainResponses;
    cv::Mat testSamples;
    cv::Mat testResponses;
    
    cv::Mat shuf_samples;
    cv::Mat shuf_responses;
    shuf_samples = shuffleRows(_samples);
    shuf_responses = shuffleRows(_responses);
    
    
    num_samples = (int)_samples.rows;
    num_features = (int)_samples.cols;
    class_count = (int)_responses.cols;
    hit_count = 0;

    split_ini = 0;
    split_end = num_samples / kfold;    
    int split_size = split_end - split_ini; 

    trainSamples = cv::Mat::zeros(num_samples - split_size, num_features, CV_32F);
    trainResponses = cv::Mat::zeros(num_samples - split_size, 1, cv::DataType<int>::type); 

    testSamples = cv::Mat::zeros(split_size, num_features, CV_32F);
    testResponses = cv::Mat::zeros(split_size, 1, cv::DataType<int>::type);
    
    

    int it;

    // Console Verbose
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Training KNN_Model" << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "num_folds: " << kfold << std::endl;
    std::cout << "num_samples: " << num_samples << std::endl;
    std::cout << "num_features: " << num_features << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Beggining "<< kfold <<"-fold crossvalidation:" << std::endl << std::endl;


    int t=0;
    int f=0;
    for(it = 0; it < kfold; ++it) {
        int i, j;  

        // Console Verbose
        std::cout <<  "it: " << it+1 << std::endl;
        std::cout << "split_ini: " << split_ini << std::endl;
        std::cout << "split_end: " << split_end << std::endl;
        std::cout << "split_size: " << split_size << std::endl; 
        
        // Preenche o vetor de teste
        for(row = split_ini, i = 0; row < split_end; row++, i++) {
            for(col = 0; col < num_features; col++) {
                testSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                testResponses.at<float>(i,col) = shuf_responses.at<float>(row,col); 
            }
        }

        // Preenche o vetor de treinamento (antes do slice)
        for(row = 0, i = 0; row < split_ini; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                trainResponses.at<float>(i,col) = shuf_responses.at<float>(row,col); 
            }
        }

        // Preenche o vetor de treinamento (depois do slice)
         for(row = split_end; row < num_samples; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                trainResponses.at<float>(i,col) = shuf_responses.at<float>(row,col); 
            }
        }   
        
        cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
        knn->setDefaultK(k);

        // Forma o conjunto de treinamento no formato requisitado pelo opencv
        cv::Ptr<cv::ml::TrainData> kfold_data = cv::ml::TrainData::create(trainSamples, cv::ml::ROW_SAMPLE, trainResponses);


        knn->train(kfold_data);  
    
        cv::Mat output = cv::Mat::zeros(split_size, 1, cv::DataType<int>::type);

        knn->findNearest(testSamples,k,output);

        for (i = 0; i < output.rows; i++) {
            int output_hit = 0;
            for (j = 0, output_hit; j < output.cols; j++) {
               if (fcmp(output.at<float>(i,j),testResponses.at<float>(i,j))) {
                   output_hit++;
               }
            }
            if (output_hit == class_count) {
                t++;
                hit_count++;
            }
            else {
                f++;
            }
            //Console verbose
        }

        // Console verbose
        std::cout << "hit_count: " << hit_count << std::endl << std::endl;
         
  
        hit_count = 0;
        split_ini += split_size;
        split_end += split_size;    
    }    

    hit_ratio = 100.0*((t*1.0)/(t+f));;
    // Console verbose
    std::cout << "Test End!" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << kfold << "-fold Crossvalidation Hit Ratio: " << hit_ratio << "%" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    
    
    return hit_ratio;
}

float MLP_trainer::mlp_kfold_hit_ratio(Model *model_pointer, int kfold)
{
    int num_samples;
    int num_features;
    int class_count;
    int hit_count;
    int split_ini, split_end;    
    float hit_ratio;
    int row, col;
    int i,j;
    int k = 3;

    cv::Mat trainSamples;
    cv::Mat trainResponses;
    cv::Mat testSamples;
    cv::Mat testResponses;
    
    cv::Mat shuf_samples;
    cv::Mat shuf_responses;
    shuf_samples = shuffleRows(_samples);
    shuf_responses = shuffleRows(_responses);
    
    num_samples = (int)_samples.rows;
    num_features = (int)_samples.cols;
    class_count = (int)_responses.cols;
    hit_count = 0;

    split_ini = 0;
    split_end = num_samples / kfold;    
    int split_size = split_end - split_ini; 

    trainSamples = cv::Mat::zeros(num_samples - split_size, num_features, CV_32F);
    trainResponses = cv::Mat::zeros(num_samples - split_size, class_count, CV_32F); 

    testSamples = cv::Mat::zeros(split_size, num_features, CV_32F);
    testResponses = cv::Mat::zeros(split_size, class_count, CV_32F);

    int it;

    // Console Verbose
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Training MLP_Model" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "num_folds: " << kfold << std::endl;
    std::cout << "num_samples: " << num_samples << std::endl;
    std::cout << "num_features: " << num_features << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Beggining "<< kfold <<"-fold crossvalidation:" << std::endl << std::endl;
   
    int t=0;
    int f=0;
    for(it = 0; it < kfold; ++it) {
        int i, j;  

        // Console Verbose
        std::cout <<  "it: " << it+1 << std::endl;
        std::cout << "split_ini: " << split_ini << std::endl;
        std::cout << "split_end: " << split_end << std::endl;
        std::cout << "split_size: " << split_size << std::endl; 
        
       // Preenche o vetor de teste
        for(row = split_ini, i = 0; row < split_end; row++, i++) {
            for(col = 0; col < num_features; col++) {
                testSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                if (shuf_responses.at<int>(row) == col)
                    testResponses.at<float>(i,col) = 1.f; 
            }
        }

        // Preenche o vetor de treinamento (antes do slice)
        for(row = 0, i = 0; row < split_ini; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                if (shuf_responses.at<int>(row) == col)
                    trainResponses.at<float>(i,col) = 1.f; 
            }
        }

        // Preenche o vetor de treinamento (depois do slice)
         for(row = split_end; row < num_samples; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = shuf_samples.at<float>(row,col);
            }
            for(col = 0; col < class_count; col++) {
                if (shuf_responses.at<int>(row) == col)
                    trainResponses.at<float>(i,col) = 1.f; 
            }
        }  
        
         // Forma o conjunto de treinamento no formato requisitado pelo opencv
        cv::Ptr<cv::ml::TrainData> kfold_data = cv::ml::TrainData::create(trainSamples, cv::ml::ROW_SAMPLE, trainResponses);
        
        int std_layer_size = 100;
        int layers_vec[4] = {num_features,std_layer_size,std_layer_size,class_count};
        cv::Mat layers = cv::Mat(1,4,cv::DataType<int>::type, layers_vec);
        int method = cv::ml::ANN_MLP::BACKPROP;
        double method_param = 0.1;
        // Tipo do critério de parada, num_iterações, precisão
        cv::TermCriteria termCrit = cv::TermCriteria(
            1,
            100,
            0.001
        );
      
        cv::Ptr<cv::ml::ANN_MLP> model;
        
        model = cv::ml::ANN_MLP::create();
        model->setLayerSizes(layers);
        model->setActivationFunction(cv::ml::ANN_MLP::SIGMOID_SYM,0,0); 
        model->setTermCriteria(termCrit);
        model->setTrainMethod(method,method_param);
        
        
        model->train(kfold_data);
        
        std::cout << "treinou?: " << model->isTrained() << std::endl;  

        cv::Mat output = cv::Mat::zeros(split_size, class_count, CV_32F);       

        model->predict(testSamples,output);

        
        for (i = 0; i < output.rows; i++) {
            int output_hit = 0;
            for (j = 0, output_hit; j < output.cols; j++) {
               if (fcmp(output.at<float>(i,j),testResponses.at<float>(i,j))) {
                   output_hit++;
               }
            }
            if (output_hit == class_count) {
                t++;
                hit_count++;
            }
            else {
                f++;
            }
            //Console verbose
        }

        // Console verbose
        std::cout << "hit_count: " << hit_count << std::endl << std::endl;
         
        hit_count = 0;
        split_ini += split_size;
        split_end += split_size;    
    }    

    hit_ratio = 100.0*((t*1.0)/(t+f));
    // Console verbose
    std::cout << "Test End!" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << kfold << "-fold Crossvalidation Hit Ratio: " << hit_ratio << "%" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    
    return hit_ratio;
}

MLP_trainer::MLP_trainer() {
    
}

KNN_trainer::KNN_trainer() {

}
