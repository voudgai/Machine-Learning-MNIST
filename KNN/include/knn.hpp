#ifndef KNN_HPP
#define KNN_H
#include <vector>
#include "data.hpp"
#include "common.hpp"
class knn : public common_data
{
    int k;
    std::vector<data *> *neighbours;

public:
    knn(int);
    knn();
    ~knn();

    void find_k_nearest(data *);

    void set_k(int);

    int prediction();
    double calculate_distance(data *, data *);
    double validate_performance();
    double test_performance();
};

#endif