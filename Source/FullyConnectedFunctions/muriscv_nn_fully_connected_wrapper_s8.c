// Modifications copyright (C) 2024 Chair of Electronic Design Automation, TUM
/*
 * SPDX-FileCopyrightText: Copyright 2010-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* ----------------------------------------------------------------------
 * Project:      CMSIS NN Library
 * Title:        muriscv_nn_fully_connected_s8
 * Description:  Fully connected function compatible with TF Lite.
 *
 * $Date:        19 Aug 2024
 * $Revision:    V.1.0.0
 *
 * Target :  Arm(R) M-Profile Architecture
 *
 * -------------------------------------------------------------------- */

#include "muriscv_nn_functions.h"
#include "muriscv_nn_support_functions.h"

/**
 *  @ingroup Public
 */

/**
 * @addtogroup FC
 * @{
 */

/*
 * S8 basic fully-connected and matrix multiplication layer function for TensorFlow Lite
 *
 * Refer header file for details.
 *
 */

muriscv_nn_status muriscv_nn_fully_connected_wrapper_s8(const muriscv_nn_context *ctx,
                                                   const muriscv_nn_fc_params *fc_params,
                                                   const muriscv_nn_quant_params *quant_params,
                                                   const muriscv_nn_dims *input_dims,
                                                   const int8_t *input_data,
                                                   const muriscv_nn_dims *filter_dims,
                                                   const int8_t *filter_data,
                                                   const muriscv_nn_dims *bias_dims,
                                                   const int32_t *bias_data,
                                                   const muriscv_nn_dims *output_dims,
                                                   int8_t *output_data)
{

    if (quant_params->is_per_channel)
    {
        const muriscv_nn_per_channel_quant_params per_channel_quant_params = {quant_params->multiplier,
                                                                            quant_params->shift};

        return muriscv_nn_fully_connected_per_channel_s8(ctx,
                                                  fc_params,
                                                  &per_channel_quant_params,
                                                  input_dims,
                                                  input_data,
                                                  filter_dims,
                                                  filter_data,
                                                  bias_dims,
                                                  bias_data,
                                                  output_dims,
                                                  output_data);
    }
    else
    {
        const muriscv_nn_per_tensor_quant_params per_tensor_quant_params = {*quant_params->multiplier,
                                                                          *quant_params->shift};
        return muriscv_nn_fully_connected_s8(ctx,
                                      fc_params,
                                      &per_tensor_quant_params,
                                      input_dims,
                                      input_data,
                                      filter_dims,
                                      filter_data,
                                      bias_dims,
                                      bias_data,
                                      output_dims,
                                      output_data);
    }
}

/**
 * @} end of FC group
 */