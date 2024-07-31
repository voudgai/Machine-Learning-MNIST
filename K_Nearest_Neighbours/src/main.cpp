#include "data_handler.hpp"
#include "../include/knn.hpp"

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../MNIST_DATA/train-images-idx3-ubyte");
    dh->read_feature_labels("../MNIST_DATA/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();

    knn *knearest = new knn();
    knearest->set_training_data(dh->get_training_data());
    knearest->set_test_data(dh->get_test_data());
    knearest->set_validation_data(dh->get_validation_data());

    double performance = 0;
    double best = 0;
    int best_k = -1;
    for (int i = 1; i <= 4; i++)
    {
        knearest->set_k(i);
        performance = knearest->validate_performance();
        if (performance > best)
        {
            best = performance;
            best_k = i;
        }
    }
    knearest->set_k(best_k);
    knearest->test_performance();
    return 0;
}