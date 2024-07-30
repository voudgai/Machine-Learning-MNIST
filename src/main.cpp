#include "../include/data_handler.hpp"

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("./MNIST_DATA/train-images-idx3-ubyte");
    dh->read_feature_labels("./MNIST_DATA/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    return 0;
}