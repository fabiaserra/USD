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
#ifndef PXR_IMAGING_HGIGL_OPS_H
#define PXR_IMAGING_HGIGL_OPS_H

#include "pxr/pxr.h"
#include "pxr/base/gf/vec4i.h"

#include "pxr/imaging/hgi/buffer.h"
#include "pxr/imaging/hgi/blitEncoderOps.h"
#include "pxr/imaging/hgi/graphicsEncoderDesc.h"
#include "pxr/imaging/hgi/pipeline.h"
#include "pxr/imaging/hgi/resourceBindings.h"

#include "pxr/imaging/hgiGL/api.h"
#include "pxr/imaging/hgiGL/device.h"

#include <cstdint>
#include <functional>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

using HgiGLOpsFn = std::function<void(void)>;

/// \class HgiGLOps
///
/// A collection of functions used by encoder to do deferred command recording.
/// Modern API's support command buffer recording of gfx commands ('deferred').
/// OpenGL uses 'immediate' mode instead where gfx commands are immediately
/// processed. We use 'Ops' functions to record our OpenGL function in a list
/// and only emit them to OpenGL during Commit.
class HgiGLOps
{
public:
    HGIGL_API
    static HgiGLOpsFn PushDebugGroup(const char* label);

    HGIGL_API
    static HgiGLOpsFn PopDebugGroup();

    HGIGL_API
    static HgiGLOpsFn CopyTextureGpuToCpu(HgiTextureGpuToCpuOp const& copyOp);

    HGIGL_API
    static HgiGLOpsFn CopyBufferCpuToGpu(HgiBufferCpuToGpuOp const& copyOp);

    HGIGL_API
    static HgiGLOpsFn ResolveImage(HgiResolveImageOp const& resolveOp);
    
    HGIGL_API
    static HgiGLOpsFn SetViewport(GfVec4i const& vp);

    HGIGL_API
    static HgiGLOpsFn SetScissor(GfVec4i const& sc);

    HGIGL_API
    static HgiGLOpsFn BindPipeline(HgiPipelineHandle pipeline);

    HGIGL_API
    static HgiGLOpsFn BindResources(HgiResourceBindingsHandle resources);

    HGIGL_API
    static HgiGLOpsFn BindVertexBuffers(
        uint32_t firstBinding,
        HgiBufferHandleVector const& buffers,
        std::vector<uint32_t> const& byteOffsets);

    HGIGL_API
    static HgiGLOpsFn DrawIndexed(
        HgiBufferHandle const& indexBuffer,
        uint32_t indexCount,
        uint32_t indexBufferByteOffset,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t instanceCount);

    HGIGL_API
    static HgiGLOpsFn BindFramebufferOp(
        HgiGLDevice* device,
        HgiGraphicsEncoderDesc const& desc);

};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
