//===------- dppl_sycl_context_interface.cpp - dpctl-C_API  ---*--- C++ -*-===//
//
//               Data Parallel Control Library (dpCtl)
//
// Copyright 2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file implements the data types and functions declared in
/// dppl_sycl_context_interface.h.
///
//===----------------------------------------------------------------------===//

#include "dppl_sycl_context_interface.h"
#include "Support/CBindingWrapping.h"
#include <CL/sycl.hpp>

using namespace cl::sycl;

namespace
{
// Create wrappers for C Binding types (see CBindingWrapping.h).
DEFINE_SIMPLE_CONVERSION_FUNCTIONS(context, DPPLSyclContextRef)
} /* end of anonymous namespace */

bool DPPLContext_AreEq (__dppl_keep const DPPLSyclContextRef CtxRef1,
                        __dppl_keep const DPPLSyclContextRef CtxRef2)
{
    if(!(CtxRef1 && CtxRef2))
        // \todo handle error
        return false;
    return (*unwrap(CtxRef1) == *unwrap(CtxRef2));
}

bool DPPLContext_IsHost (__dppl_keep const DPPLSyclContextRef CtxRef)
{
    return unwrap(CtxRef)->is_host();
}

void DPPLContext_Delete (__dppl_take DPPLSyclContextRef CtxRef)
{
    delete unwrap(CtxRef);
}

DPPLSyclBackendType
DPPLContext_GetBackend (__dppl_keep const DPPLSyclContextRef CtxRef)
{
    auto BE = unwrap(CtxRef)->get_platform().get_backend();

    switch(BE)
    {
        case backend::host:
            return DPPL_HOST;
        case backend::opencl:
            return DPPL_OPENCL;
        case backend::level_zero:
            return DPPL_LEVEL_ZERO;
        case backend::cuda:
            return DPPL_CUDA;
        default:
            return DPPL_UNKNOWN_BACKEND;
    }
}
