#include "../include/CaberNet/tensor.h"
#include "../include/CaberNet/layers.h"

#include "internals/functions/internal_functions.hpp"

namespace net::layer {

/// constructors

Linear::Linear(size_type input_features, size_type output_features)
:   weight(shape_type{input_features, output_features})
,   bias(shape_type{1, output_features}) {
    for (auto& element : weight) element = 1;
    for (auto& element : bias) element = 2;
}

Softmax::Softmax(int axis) : axis(axis) {}
LogSoftmax::LogSoftmax(int axis) : axis(axis) {}

/// forward methods

Tensor Linear::forward(Tensor input) {
    return Tensor(std::make_shared<internal::Linear>(input.internal(), weight.internal(), bias.internal()));
}

Tensor ReLU::forward(Tensor input) {
    return Tensor(std::make_shared<internal::ReLU>(input.internal()));
}

Tensor Softmax::forward(Tensor input) {
    return Tensor(std::make_shared<internal::Softmax>(input.internal(), axis));
}

Tensor LogSoftmax::forward(Tensor input) {
    return Tensor(std::make_shared<internal::LogSoftmax>(input.internal(), axis));
}

} // namespace net::layer