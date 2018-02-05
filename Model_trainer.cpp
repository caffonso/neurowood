#include "Model_trainer.hpp"

using namespace std;

void Model_trainer::build_train_data(char *filename) 
{
    ifstream inputfile(filename);
    string current_line;
    vector< vector<float> > all_data;
    
    while(getline(inputfile, current_line)) {
        vector<float> values;
        
        stringstream temp(current_line);
        string single_value;
        
        while(getline(temp,single_value,',')) {
           values.push_back(atof(single_value.c_str()));
        }

        all_data.push_back(values);
}
   
    _samples = cv::Mat::zeros((int)all_data.size(), (int)all_data[0].size()-1, CV_32F);  
    _responses = cv::Mat::zeros((int)all_data.size(), 1, CV_32F);

    int rows, cols;

    for(rows = 0; rows < (int)all_data.size(); rows++) {
        for(cols = 0; cols < (int)all_data[0].size()-1; cols++) {
            _samples.at<float>(rows,cols) = all_data[rows][cols];
        }
        _responses.at<float>(rows) = (int)all_data[rows][cols]; 
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
}

float KNN_trainer::knn_kfold_hit_ratio(Model *model_pointer, int kfold)
{
    int num_samples;
    int num_features;
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
    
    num_samples = (int)_samples.rows;
    num_features = (int)_samples.cols;
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
                testSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            testResponses.at<int>(i) = _responses.at<int>(row);
        }

        // Preenche o vetor de treinamento (antes do slice)
        for(row = 0, i = 0; row < split_ini; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            trainResponses.at<int>(i) = _responses.at<int>(row);
        }

        // Preenche o vetor de treinamento (depois do slice)
         for(row = split_end; row < num_samples; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            trainResponses.at<int>(i) = _responses.at<int>(row);
        }   
        
        cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
        knn->setDefaultK(k);

        // Forma o conjunto de treinamento no formato requisitado pelo opencv
        cv::Ptr<cv::ml::TrainData> kfold_data = cv::ml::TrainData::create(trainSamples, cv::ml::ROW_SAMPLE, trainResponses);


        knn->train(kfold_data);  
    
        cv::Mat output = cv::Mat::zeros(split_size, 1, cv::DataType<int>::type);

        knn->findNearest(testSamples,k,output);

        for (i = 0; i < output.rows; i++) {
            if(output.at<int>(i) == testResponses.at<int>(i)) {
                hit_count++;
            }
        }

        // Console verbose
        std::cout << "hit_count: " << hit_count << std::endl << std::endl;
         
        hit_ratio += (float)hit_count * 100/(float)output.rows;
        hit_count = 0;
        split_ini += split_size;
        split_end += split_size;    
    }    

    hit_ratio = hit_ratio / (float)kfold;
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
    
    num_samples = (int)_samples.rows;
    num_features = (int)_samples.cols;
    hit_count = 0;

    split_ini = 0;
    split_end = num_samples / kfold;    
    int split_size = split_end - split_ini; 

    trainSamples = cv::Mat::zeros(num_samples - split_size, num_features, CV_32F);
    trainResponses = cv::Mat::zeros(num_samples - split_size, 1, CV_32S); 

    testSamples = cv::Mat::zeros(split_size, num_features, CV_32F);
    testResponses = cv::Mat::zeros(split_size, 1, CV_32S);

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
                testSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            testResponses.at<int>(i) = _responses.at<int>(row);
        }

        // Preenche o vetor de treinamento (antes do slice)
        for(row = 0, i = 0; row < split_ini; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            trainResponses.at<int>(i) = _responses.at<int>(row);
        }

        // Preenche o vetor de treinamento (depois do slice)
         for(row = split_end; row < num_samples; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<float>(i,col) = _samples.at<float>(row,col);
            }
            trainResponses.at<int>(i) = _responses.at<int>(row);
        }   
        
        cv::Ptr<cv::ml::ANN_MLP> mlp = cv::ml::ANN_MLP::create();
        
        int std_layer_size = num_features;
        int layers_vec[4] = {num_features,std_layer_size,std_layer_size,1};
        cv::Mat layers = cv::Mat(1,4,cv::DataType<int>::type, layers_vec);

        mlp->setLayerSizes(layers);

        // Forma o conjunto de treinamento no formato requisitado pelo opencv
        cv::Ptr<cv::ml::TrainData> kfold_data = cv::ml::TrainData::create(trainSamples, cv::ml::ROW_SAMPLE, trainResponses);


        mlp->train(kfold_data);  
    
        cv::Mat output = cv::Mat::zeros(split_size, 1, CV_32F);

        mlp->predict(testSamples,output);

        for (i = 0; i < output.rows; i++) {
            if(output.at<int>(i) == testResponses.at<int>(i)) {
                hit_count++;
            }
            //Console verbose
            std::cout << "output[" << i << "]: " << output.at<int>(i) << std::endl;
        }

        // Console verbose
        std::cout << "hit_count: " << hit_count << std::endl << std::endl;
         
        hit_ratio += (float)hit_count * 100/(float)output.rows;
        hit_count = 0;
        split_ini += split_size;
        split_end += split_size;    
    }    

    hit_ratio = hit_ratio / (float)kfold;
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
