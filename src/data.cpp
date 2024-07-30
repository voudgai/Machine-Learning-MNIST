#include "../include/data.hpp"

data::data()
{
    feature_vector = new std::vector<uint8_t>;
}
data::~data()
{
    // TODO free mem
}

void data::set_feature_vector(std::vector<uint8_t> *vect)
{
    if (feature_vector)
        delete feature_vector;

    feature_vector = vect;
}
void data::append_to_feature_vector(uint8_t val)
{
    if (feature_vector)
        feature_vector->push_back(val);
}
void data::set_label(uint8_t val)
{
    label = val;
}
void data::set_enumerated_label(int val)
{
    enum_label = val;
}

int data::get_feature_vector_size()
{
    if (feature_vector)
        return feature_vector->size();
    return 0;
}
uint8_t data::get_label()
{
    return label;
}
uint8_t data::get_enumerated_label()
{
    return enum_label;
}

std::vector<uint8_t> *data::get_feature_vector()
{
    return feature_vector;
}