#ifndef KNN_HPP
#define KNN_H
#include <vector>
#include "data.hpp"

class knn
{
    int k;
    std::vector<data *> *neighbours;
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;

public:
    knn(int);
    knn();
    ~knn();

    void find_k_nearest(data *);

    void set_training_data(std::vector<data *> *);
    void set_test_data(std::vector<data *> *);
    void set_validation_data(std::vector<data *> *);
    void set_k(int);

    int prediction();
    double calculate_distance(data *, data *);
    double validate_performance();
    double test_performance();
};

#endif