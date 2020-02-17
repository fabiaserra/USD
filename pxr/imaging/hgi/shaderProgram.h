//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HGI_SHADERPROGRAM_H
#define PXR_IMAGING_HGI_SHADERPROGRAM_H

#include "pxr/pxr.h"
#include "pxr/imaging/hgi/api.h"
#include "pxr/imaging/hgi/enums.h"
#include "pxr/imaging/hgi/shaderFunction.h"
#include "pxr/imaging/hgi/types.h"

#include <vector>


PXR_NAMESPACE_OPEN_SCOPE

struct HgiShaderProgramDesc;


///
/// \class HgiShaderProgram
///
/// Represents a collection of shader functions.
///
class HgiShaderProgram {
public:
    HGI_API
    virtual ~HgiShaderProgram();

    /// Returns false if any shader compile errors occured.
    HGI_API
    virtual bool IsValid() const = 0;

    /// Returns shader compile errors.
    HGI_API
    virtual std::string const& GetCompileErrors() = 0;

    /// Returns the shader functions that are part of this program.
    HGI_API
    virtual HgiShaderFunctionHandleVector const& GetShaderFunctions() const = 0;


protected:
    HGI_API
    HgiShaderProgram(HgiShaderProgramDesc const& desc);

private:
    HgiShaderProgram() = delete;
    HgiShaderProgram & operator=(const HgiShaderProgram&) = delete;
    HgiShaderProgram(const HgiShaderProgram&) = delete;
};

typedef HgiShaderProgram* HgiShaderProgramHandle;
typedef std::vector<HgiShaderProgramHandle> HgiShaderProgramHandleVector;


/// \struct HgiShaderProgramDesc
///
/// Describes the properties needed to create a GPU shader program.
///
/// <ul>
/// <li>shaderFunctions:
///   Holds handles to shader functions for each shader stage.</li>
/// </ul>
///
struct HgiShaderProgramDesc {
    HGI_API
    HgiShaderProgramDesc();

    std::string debugName;
    HgiShaderFunctionHandleVector shaderFunctions;
};

HGI_API
inline bool operator==(
    const HgiShaderProgramDesc& lhs,
    const HgiShaderProgramDesc& rhs);

HGI_API
inline bool operator!=(
    const HgiShaderProgramDesc& lhs,
    const HgiShaderProgramDesc& rhs);


PXR_NAMESPACE_CLOSE_SCOPE

#endif