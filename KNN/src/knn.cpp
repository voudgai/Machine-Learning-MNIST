#include "../include/knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.hpp"

knn::knn(int val)
{
    k = val;
}
knn::knn() {}
knn::~knn() {}

void knn::find_k_nearest(data *query_point)
{
    neighbours = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;
    int index = 0;
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < training_data->size(); j++)
            {
                double distance = calculate_distance(query_point, training_data->at(j));
                training_data->at(j)->set_distance(distance);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
        }
        else
        {
            for (int j = 0; j < training_data->size(); j++)
            {
                double distance = calculate_distance(query_point, training_data->at(j));
                if (distance > previous_min && distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
        }
        neighbours->push_back(training_data->at(index));
        previous_min = min;
        min = std::numeric_limits<double>::max();
    }
}

void knn::set_k(int val)
{
    k = val;
}

int knn::prediction()
{
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbours->size(); i++)
    {
        if (class_freq.find(neighbours->at(i)->get_label()) == class_freq.end())
        {
            class_freq[neighbours->at(i)->get_label()] = 1;
        }
        else
        {
            class_freq[neighbours->at(i)->get_label()]++;
        }
    }

    int best = 0;
    int max = 0;
    for (auto key_value : class_freq)
    {
        if (key_value.second > max)
        {
            max = key_value.second;
            best = key_value.first;
        }
    }
    delete neighbours;
    return best;
}
double knn::calculate_distance(data *query_point, data *input)
{
    double distance = 0.0;
    if (query_point->get_feature_vector_size() != input->get_feature_vector_size())
    {
        printf("ERR Mismatch vector size!\n");
        exit(3);
    }
#ifdef EUCLID
    for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++)
    {
        distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
    }
    distance = sqrt(distance);
#elif defined MANHATTAN
// PUT MANHATTAN IMPLEMENTATION HERE
#endif
    return distance;
}
double knn::validate_performance()
{
    double current_performance = 0;
    int count = 0;
    int data_index = 0;

    for (data *query_point : *validation_data)
    {
        find_k_nearest(query_point);
        int predict = prediction();
        if (predict == query_point->get_label())
        {
            count++;
        }
        data_index++;
        printf("%d -> %d\n", predict, query_point->get_label());
        printf("Current performance for K=%d : %.3f %%, %d/%d \n\n", k, (double)count / (double)data_index * 100, data_index, validation_data->size());
    }
    current_performance = (double)count / (double)validation_data->size() * 100;
    printf("Validation Performance for K = %d: %.3f %% \n", k, current_performance);

    return current_performance;
}
double knn::test_performance()
{
    double current_performance = 0;
    int count = 0;

    for (data *query_point : *test_data)
    {
        find_k_nearest(query_point);
        int predict = prediction();
        if (predict == query_point->get_label())
        {
            count++;
        }
    }
    current_performance = (double)count / (double)test_data->size() * 100;
    printf("Test Performance = %.3f %% \n", current_performance);

    return current_performance;
}
