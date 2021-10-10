/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_TF2XLA_LIB_BATCH_DOT_H_
#define TENSORFLOW_COMPILER_TF2XLA_LIB_BATCH_DOT_H_

#include "tensorflow/compiler/xla/client/computation.h"
#include "tensorflow/compiler/xla/client/computation_builder.h"

namespace tensorflow {

// Multiplies slices of two tensors in batches.

// Multiplies all slices of `Tensor` `x` and `y` (each slice can be
// viewed as an element of a batch), and arranges the individual results
// in a single output tensor of the same batch size. Each of the
// individual slices can optionally be transposed before multiplication by
// setting the `transpose_x` or `transpose_y` flag to `true`.
//
// The input tensors `x` and `y` are 2-D or higher with shape `[..., r_x, c_x]`
// and `[..., r_y, c_y]`.
//
// The output tensor is 2-D or higher with shape `[..., r_o, c_o]`, where:
//
//     r_o = c_x if transpose_x else r_x
//     c_o = r_y if transpose_y else c_y
//
// It is computed as:
//
//     output[..., :, :] = matrix(x[..., :, :]) * matrix(y[..., :, :])
// TODO(phawkins): add an option to take the complex conjugate of the LHS or
// RHS.
xla::StatusOr<xla::ComputationDataHandle> BatchDot(
    xla::ComputationBuilder* builder, xla::ComputationDataHandle x,
    xla::ComputationDataHandle y, bool transpose_x, bool transpose_y);

}  // namespace tensorflow

#endif  // TENSORFLOW_COMPILER_TF2XLA_LIB_BATCH_DOT_H_
