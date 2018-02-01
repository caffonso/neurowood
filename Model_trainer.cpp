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
    _responses = cv::Mat::zeros((int)all_data.size(), 1, cv::DataType<int>::type);

    int rows, cols;

    for(rows = 0; rows < (int)all_data.size(); rows++) {
        for(cols = 0; cols < (int)all_data[0].size()-1; cols++) {
            _samples.at<uchar>(rows,cols) = all_data[rows][cols];
        }
        _responses.at<uchar>(rows) = (int)all_data[rows][cols]; 
    }
    
}

float Model_trainer::kfold_hit_ratio(Model *model_pointer, int kfold)
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

    for(it = 0; it < kfold; ++it) {
        int i, j;  
        
        // Preenche o vetor de teste
        for(row = split_ini, i = 0; row < split_end; row++, i++) {
            for(col = 0; col < num_features; col++) {
                testSamples.at<uchar>(i,col) = _samples.at<uchar>(row,col);
            }
            testResponses.at<uchar>(i) = _responses.at<uchar>(row);
        }

        // Preenche o vetor de treinamento (antes do slice)
        for(row = 0, i = 0; row < split_ini; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<uchar>(i,col) = _samples.at<uchar>(row,col);
            }
            trainResponses.at<uchar>(i) = _responses.at<uchar>(row);
        }

        // Preenche o vetor de treinamento (depois do slice)
         for(row = split_end; row < num_samples; row++, i++) {
            for(col = 0; col < num_features; col++) {
                trainSamples.at<uchar>(i,col) = _samples.at<uchar>(row,col);
            }
            trainResponses.at<uchar>(i) = _responses.at<uchar>(row);
        }   
        
        cv::Ptr<cv::ml::KNearest> knn(trainSamples, trainResponses, cv::Mat(), false, k);
        knn->setDefaultK(k);
        knn->train(trainSamples,trainResponses);  
    
        cv::Mat output = cv::Mat::zeros(split_size, 1, cv::DataType<int>::type);

        for (i = 0; i < testSamples.rows; i++) {
            const cv::Mat sample = testSamples.row(i);
            output.at<uchar>(i,0) = (int)knn->find_nearest(sample,k);
        }
    
        for (i = 0; i < output.rows; i++) {
            if(output.at<uchar>(i,0) == testResponses.at<uchar>(i,0)) {
                hit_count++;
            }
        }
        
        hit_ratio += (float)hit_count * 100/(float)output.rows;
        hit_count = 0;
        split_ini += split_size -1;
        split_end += split_size;
    
    }    

    hit_ratio = hit_ratio / (float)kfold;
    return hit_ratio;
}

MLP_trainer::MLP_trainer() {
    
}

KNN_trainer::KNN_trainer() {

}
