
#pragma once


#include <glbinding/glbinding_api.h>

#include <glbinding/nogl.h>
#include <glbinding/gl/types.h>


namespace gl {


    GLBINDING_API void glAccum(GLenum op, GLfloat value);

    GLBINDING_API void glAccumxOES(GLenum op, GLfixed value);

    GLBINDING_API GLboolean
    glAcquireKeyedMutexWin32EXT(GLuint
    memory,
    GLuint64 key, GLuint
    timeout);
    GLBINDING_API void glActiveProgramEXT(GLuint
    program);
    GLBINDING_API void glActiveShaderProgram(GLuint
    pipeline,
    GLuint program
    );

    GLBINDING_API void glActiveStencilFaceEXT(GLenum face);

    GLBINDING_API void glActiveTexture(GLenum texture);

    GLBINDING_API void glActiveTextureARB(GLenum texture);

    GLBINDING_API void glActiveVaryingNV(GLuint
    program,
    const GLchar *name
    );

    GLBINDING_API void
    glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);

    GLBINDING_API void
    glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod,
                          GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);

    GLBINDING_API void
    glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod,
                          GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);

    GLBINDING_API void glAlphaFunc(GLenum func, GLfloat ref);

    GLBINDING_API void glAlphaFuncxOES(GLenum func, GLfixed ref);

    GLBINDING_API void glAlphaToCoverageDitherControlNV(GLenum mode);

    GLBINDING_API void glApplyFramebufferAttachmentCMAAINTEL();

    GLBINDING_API void glApplyTextureEXT(GLenum mode);

    GLBINDING_API GLboolean
    glAreProgramsResidentNV(GLsizei
    n,
    const GLuint *programs, GLboolean
    * residences);
    GLBINDING_API GLboolean
    glAreTexturesResident(GLsizei
    n,
    const GLuint *textures, GLboolean
    * residences);
    GLBINDING_API GLboolean
    glAreTexturesResidentEXT(GLsizei
    n,
    const GLuint *textures, GLboolean
    * residences);

    GLBINDING_API void glArrayElement(GLint i);

    GLBINDING_API void glArrayElementEXT(GLint i);

    GLBINDING_API void
    glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);

    GLBINDING_API void glAsyncMarkerSGIX(GLuint
    marker);

    GLBINDING_API void glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj);

    GLBINDING_API void glAttachShader(GLuint
    program,
    GLuint shader
    );

    GLBINDING_API void glBegin(GLenum mode);

    GLBINDING_API void glBeginConditionalRender(GLuint
    id,
    GLenum mode
    );
    GLBINDING_API void glBeginConditionalRenderNV(GLuint
    id,
    GLenum mode
    );
    GLBINDING_API void glBeginConditionalRenderNVX(GLuint
    id);

    GLBINDING_API void glBeginFragmentShaderATI();

    GLBINDING_API void glBeginOcclusionQueryNV(GLuint
    id);
    GLBINDING_API void glBeginPerfMonitorAMD(GLuint
    monitor);
    GLBINDING_API void glBeginPerfQueryINTEL(GLuint
    queryHandle);

    GLBINDING_API void glBeginQuery(GLenum target, GLuint id);

    GLBINDING_API void glBeginQueryARB(GLenum target, GLuint id);

    GLBINDING_API void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id);

    GLBINDING_API void glBeginTransformFeedback(GLenum primitiveMode);

    GLBINDING_API void glBeginTransformFeedbackEXT(GLenum primitiveMode);

    GLBINDING_API void glBeginTransformFeedbackNV(GLenum primitiveMode);

    GLBINDING_API void glBeginVertexShaderEXT();

    GLBINDING_API void glBeginVideoCaptureNV(GLuint
    video_capture_slot);
    GLBINDING_API void glBindAttribLocation(GLuint
    program,
    GLuint index,
    const GLchar *name
    );

    GLBINDING_API void glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB *name);

    GLBINDING_API void glBindBuffer(GLenum target, GLuint buffer);

    GLBINDING_API void glBindBufferARB(GLenum target, GLuint buffer);

    GLBINDING_API void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);

    GLBINDING_API void glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer);

    GLBINDING_API void glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer);

    GLBINDING_API void glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset);

    GLBINDING_API void glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset);

    GLBINDING_API void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);

    GLBINDING_API void
    glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);

    GLBINDING_API void
    glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);

    GLBINDING_API void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);

    GLBINDING_API void
    glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets,
                       const GLsizeiptr *sizes);

    GLBINDING_API void glBindFragDataLocation(GLuint
    program,
    GLuint color,
    const GLchar *name
    );
    GLBINDING_API void glBindFragDataLocationEXT(GLuint
    program,
    GLuint color,
    const GLchar *name
    );
    GLBINDING_API void glBindFragDataLocationIndexed(GLuint
    program,
    GLuint colorNumber, GLuint
    index,
    const GLchar *name
    );
    GLBINDING_API void glBindFragmentShaderATI(GLuint
    id);

    GLBINDING_API void glBindFramebuffer(GLenum target, GLuint framebuffer);

    GLBINDING_API void glBindFramebufferEXT(GLenum target, GLuint framebuffer);

    GLBINDING_API void glBindImageTexture(GLuint
    unit,
    GLuint texture, GLint
    level,
    GLboolean layered, GLint
    layer,
    GLenum access, GLenum
    format);
    GLBINDING_API void glBindImageTextureEXT(GLuint
    index,
    GLuint texture, GLint
    level,
    GLboolean layered, GLint
    layer,
    GLenum access, GLint
    format);
    GLBINDING_API void glBindImageTextures(GLuint
    first,
    GLsizei count,
    const GLuint *textures
    );
    GLBINDING_API GLuint
    glBindLightParameterEXT(GLenum
    light,
    GLenum value
    );
    GLBINDING_API GLuint
    glBindMaterialParameterEXT(GLenum
    face,
    GLenum value
    );
    GLBINDING_API void glBindMultiTextureEXT(GLenum
    texunit,
    GLenum target, GLuint
    texture);
    GLBINDING_API GLuint
    glBindParameterEXT(GLenum
    value);
    GLBINDING_API void glBindProgramARB(GLenum
    target,
    GLuint program
    );
    GLBINDING_API void glBindProgramNV(GLenum
    target,
    GLuint id
    );
    GLBINDING_API void glBindProgramPipeline(GLuint
    pipeline);
    GLBINDING_API void glBindRenderbuffer(GLenum
    target,
    GLuint renderbuffer
    );
    GLBINDING_API void glBindRenderbufferEXT(GLenum
    target,
    GLuint renderbuffer
    );
    GLBINDING_API void glBindSampler(GLuint
    unit,
    GLuint sampler
    );
    GLBINDING_API void glBindSamplers(GLuint
    first,
    GLsizei count,
    const GLuint *samplers
    );
    GLBINDING_API void glBindShadingRateImageNV(GLuint
    texture);
    GLBINDING_API GLuint
    glBindTexGenParameterEXT(GLenum
    unit,
    GLenum coord, GLenum
    value);
    GLBINDING_API void glBindTexture(GLenum
    target,
    GLuint texture
    );
    GLBINDING_API void glBindTextureEXT(GLenum
    target,
    GLuint texture
    );
    GLBINDING_API void glBindTextureUnit(GLuint
    unit,
    GLuint texture
    );
    GLBINDING_API GLuint
    glBindTextureUnitParameterEXT(GLenum
    unit,
    GLenum value
    );
    GLBINDING_API void glBindTextures(GLuint
    first,
    GLsizei count,
    const GLuint *textures
    );
    GLBINDING_API void glBindTransformFeedback(GLenum
    target,
    GLuint id
    );
    GLBINDING_API void glBindTransformFeedbackNV(GLenum
    target,
    GLuint id
    );
    GLBINDING_API void glBindVertexArray(GLuint
    array);
    GLBINDING_API void glBindVertexArrayAPPLE(GLuint
    array);
    GLBINDING_API void glBindVertexBuffer(GLuint
    bindingindex,
    GLuint buffer, GLintptr
    offset,
    GLsizei stride
    );
    GLBINDING_API void glBindVertexBuffers(GLuint
    first,
    GLsizei count,
    const GLuint *buffers,
    const GLintptr *offsets,
    const GLsizei *strides
    );
    GLBINDING_API void glBindVertexShaderEXT(GLuint
    id);
    GLBINDING_API void glBindVideoCaptureStreamBufferNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    frame_region,
    GLintptrARB offset
    );
    GLBINDING_API void glBindVideoCaptureStreamTextureNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    frame_region,
    GLenum target, GLuint
    texture);

    GLBINDING_API void glBinormal3bEXT(GLbyte bx, GLbyte by, GLbyte bz);

    GLBINDING_API void glBinormal3bvEXT(const GLbyte *v);

    GLBINDING_API void glBinormal3dEXT(GLdouble bx, GLdouble by, GLdouble bz);

    GLBINDING_API void glBinormal3dvEXT(const GLdouble *v);

    GLBINDING_API void glBinormal3fEXT(GLfloat bx, GLfloat by, GLfloat bz);

    GLBINDING_API void glBinormal3fvEXT(const GLfloat *v);

    GLBINDING_API void glBinormal3iEXT(GLint
    bx,
    GLint by, GLint
    bz);

    GLBINDING_API void glBinormal3ivEXT(const GLint *v);

    GLBINDING_API void glBinormal3sEXT(GLshort bx, GLshort by, GLshort bz);

    GLBINDING_API void glBinormal3svEXT(const GLshort *v);

    GLBINDING_API void glBinormalPointerEXT(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glBitmap(GLsizei
    width,
    GLsizei height, GLfloat
    xorig,
    GLfloat yorig, GLfloat
    xmove,
    GLfloat ymove,
    const GLubyte *bitmap
    );
    GLBINDING_API void glBitmapxOES(GLsizei
    width,
    GLsizei height, GLfixed
    xorig,
    GLfixed yorig, GLfixed
    xmove,
    GLfixed ymove,
    const GLubyte *bitmap
    );

    GLBINDING_API void glBlendBarrierKHR();

    GLBINDING_API void glBlendBarrierNV();

    GLBINDING_API void glBlendColor(GLfloat
    red,
    GLfloat green, GLfloat
    blue,
    GLfloat alpha
    );
    GLBINDING_API void glBlendColorEXT(GLfloat
    red,
    GLfloat green, GLfloat
    blue,
    GLfloat alpha
    );
    GLBINDING_API void glBlendColorxOES(GLfixed
    red,
    GLfixed green, GLfixed
    blue,
    GLfixed alpha
    );
    GLBINDING_API void glBlendEquation(GLenum
    mode);
    GLBINDING_API void glBlendEquationEXT(GLenum
    mode);
    GLBINDING_API void glBlendEquationIndexedAMD(GLuint
    buf,
    GLenum mode
    );
    GLBINDING_API void glBlendEquationSeparate(GLenum
    modeRGB,
    GLenum modeAlpha
    );
    GLBINDING_API void glBlendEquationSeparateEXT(GLenum
    modeRGB,
    GLenum modeAlpha
    );
    GLBINDING_API void glBlendEquationSeparateIndexedAMD(GLuint
    buf,
    GLenum modeRGB, GLenum
    modeAlpha);
    GLBINDING_API void glBlendEquationSeparatei(GLuint
    buf,
    GLenum modeRGB, GLenum
    modeAlpha);
    GLBINDING_API void glBlendEquationSeparateiARB(GLuint
    buf,
    GLenum modeRGB, GLenum
    modeAlpha);
    GLBINDING_API void glBlendEquationi(GLuint
    buf,
    GLenum mode
    );
    GLBINDING_API void glBlendEquationiARB(GLuint
    buf,
    GLenum mode
    );
    GLBINDING_API void glBlendFunc(GLenum
    sfactor,
    GLenum dfactor
    );
    GLBINDING_API void glBlendFuncIndexedAMD(GLuint
    buf,
    GLenum src, GLenum
    dst);
    GLBINDING_API void glBlendFuncSeparate(GLenum
    sfactorRGB,
    GLenum dfactorRGB, GLenum
    sfactorAlpha,
    GLenum dfactorAlpha
    );
    GLBINDING_API void glBlendFuncSeparateEXT(GLenum
    sfactorRGB,
    GLenum dfactorRGB, GLenum
    sfactorAlpha,
    GLenum dfactorAlpha
    );
    GLBINDING_API void glBlendFuncSeparateINGR(GLenum
    sfactorRGB,
    GLenum dfactorRGB, GLenum
    sfactorAlpha,
    GLenum dfactorAlpha
    );
    GLBINDING_API void glBlendFuncSeparateIndexedAMD(GLuint
    buf,
    GLenum srcRGB, GLenum
    dstRGB,
    GLenum srcAlpha, GLenum
    dstAlpha);
    GLBINDING_API void glBlendFuncSeparatei(GLuint
    buf,
    GLenum srcRGB, GLenum
    dstRGB,
    GLenum srcAlpha, GLenum
    dstAlpha);
    GLBINDING_API void glBlendFuncSeparateiARB(GLuint
    buf,
    GLenum srcRGB, GLenum
    dstRGB,
    GLenum srcAlpha, GLenum
    dstAlpha);
    GLBINDING_API void glBlendFunci(GLuint
    buf,
    GLenum src, GLenum
    dst);
    GLBINDING_API void glBlendFunciARB(GLuint
    buf,
    GLenum src, GLenum
    dst);
    GLBINDING_API void glBlendParameteriNV(GLenum
    pname,
    GLint value
    );
    GLBINDING_API void glBlitFramebuffer(GLint
    srcX0,
    GLint srcY0, GLint
    srcX1,
    GLint srcY1, GLint
    dstX0,
    GLint dstY0, GLint
    dstX1,
    GLint dstY1, ClearBufferMask
    mask,
    GLenum filter
    );
    GLBINDING_API void glBlitFramebufferEXT(GLint
    srcX0,
    GLint srcY0, GLint
    srcX1,
    GLint srcY1, GLint
    dstX0,
    GLint dstY0, GLint
    dstX1,
    GLint dstY1, ClearBufferMask
    mask,
    GLenum filter
    );
    GLBINDING_API void glBlitNamedFramebuffer(GLuint
    readFramebuffer,
    GLuint drawFramebuffer, GLint
    srcX0,
    GLint srcY0, GLint
    srcX1,
    GLint srcY1, GLint
    dstX0,
    GLint dstY0, GLint
    dstX1,
    GLint dstY1, ClearBufferMask
    mask,
    GLenum filter
    );
    GLBINDING_API void glBufferAddressRangeNV(GLenum
    pname,
    GLuint index, GLuint64EXT
    address,
    GLsizeiptr length
    );
    GLBINDING_API void glBufferAttachMemoryNV(GLenum
    target,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glBufferData(GLenum
    target,
    GLsizeiptr size,
    const void *data, GLenum
    usage);
    GLBINDING_API void glBufferDataARB(GLenum
    target,
    GLsizeiptrARB size,
    const void *data, GLenum
    usage);
    GLBINDING_API void glBufferPageCommitmentARB(GLenum
    target,
    GLintptr offset, GLsizeiptr
    size,
    GLboolean commit
    );
    GLBINDING_API void glBufferParameteriAPPLE(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glBufferStorage(GLenum
    target,
    GLsizeiptr size,
    const void *data, BufferStorageMask
    flags);
    GLBINDING_API void glBufferStorageExternalEXT(GLenum
    target,
    GLintptr offset, GLsizeiptr
    size,
    GLeglClientBufferEXT clientBuffer, BufferStorageMask
    flags);
    GLBINDING_API void glBufferStorageMemEXT(GLenum
    target,
    GLsizeiptr size, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glBufferSubData(GLenum
    target,
    GLintptr offset, GLsizeiptr
    size,
    const void *data
    );
    GLBINDING_API void glBufferSubDataARB(GLenum
    target,
    GLintptrARB offset, GLsizeiptrARB
    size,
    const void *data
    );

    GLBINDING_API void glCallCommandListNV(GLuint
    list);
    GLBINDING_API void glCallList(GLuint
    list);
    GLBINDING_API void glCallLists(GLsizei
    n,
    GLenum type,
    const void *lists
    );
    GLBINDING_API GLenum
    glCheckFramebufferStatus(GLenum
    target);
    GLBINDING_API GLenum
    glCheckFramebufferStatusEXT(GLenum
    target);
    GLBINDING_API GLenum
    glCheckNamedFramebufferStatus(GLuint
    framebuffer,
    GLenum target
    );
    GLBINDING_API GLenum
    glCheckNamedFramebufferStatusEXT(GLuint
    framebuffer,
    GLenum target
    );
    GLBINDING_API void glClampColor(GLenum
    target,
    GLboolean clamp
    );
    GLBINDING_API void glClampColorARB(GLenum
    target,
    GLboolean clamp
    );
    GLBINDING_API void glClear(ClearBufferMask
    mask);
    GLBINDING_API void glClearAccum(GLfloat
    red,
    GLfloat green, GLfloat
    blue,
    GLfloat alpha
    );
    GLBINDING_API void glClearAccumxOES(GLfixed
    red,
    GLfixed green, GLfixed
    blue,
    GLfixed alpha
    );
    GLBINDING_API void glClearBufferData(GLenum
    target,
    GLenum internalformat, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearBufferSubData(GLenum
    target,
    GLenum internalformat, GLintptr
    offset,
    GLsizeiptr size, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearBufferfi(GLenum
    buffer,
    GLint drawbuffer, GLfloat
    depth,
    GLint stencil
    );
    GLBINDING_API void glClearBufferfv(GLenum
    buffer,
    GLint drawbuffer,
    const GLfloat *value
    );
    GLBINDING_API void glClearBufferiv(GLenum
    buffer,
    GLint drawbuffer,
    const GLint *value
    );
    GLBINDING_API void glClearBufferuiv(GLenum
    buffer,
    GLint drawbuffer,
    const GLuint *value
    );
    GLBINDING_API void glClearColor(GLfloat
    red,
    GLfloat green, GLfloat
    blue,
    GLfloat alpha
    );
    GLBINDING_API void glClearColorIiEXT(GLint
    red,
    GLint green, GLint
    blue,
    GLint alpha
    );
    GLBINDING_API void glClearColorIuiEXT(GLuint
    red,
    GLuint green, GLuint
    blue,
    GLuint alpha
    );
    GLBINDING_API void glClearColorxOES(GLfixed
    red,
    GLfixed green, GLfixed
    blue,
    GLfixed alpha
    );

    GLBINDING_API void glClearDepth(GLdouble depth);

    GLBINDING_API void glClearDepthdNV(GLdouble depth);

    GLBINDING_API void glClearDepthf(GLfloat
    d);

    GLBINDING_API void glClearDepthfOES(GLclampf depth);

    GLBINDING_API void glClearDepthxOES(GLfixed
    depth);
    GLBINDING_API void glClearIndex(GLfloat
    c);
    GLBINDING_API void glClearNamedBufferData(GLuint
    buffer,
    GLenum internalformat, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearNamedBufferDataEXT(GLuint
    buffer,
    GLenum internalformat, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearNamedBufferSubData(GLuint
    buffer,
    GLenum internalformat, GLintptr
    offset,
    GLsizeiptr size, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearNamedBufferSubDataEXT(GLuint
    buffer,
    GLenum internalformat, GLsizeiptr
    offset,
    GLsizeiptr size, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearNamedFramebufferfi(GLuint
    framebuffer,
    GLenum buffer, GLint
    drawbuffer,
    GLfloat depth, GLint
    stencil);
    GLBINDING_API void glClearNamedFramebufferfv(GLuint
    framebuffer,
    GLenum buffer, GLint
    drawbuffer,
    const GLfloat *value
    );
    GLBINDING_API void glClearNamedFramebufferiv(GLuint
    framebuffer,
    GLenum buffer, GLint
    drawbuffer,
    const GLint *value
    );
    GLBINDING_API void glClearNamedFramebufferuiv(GLuint
    framebuffer,
    GLenum buffer, GLint
    drawbuffer,
    const GLuint *value
    );
    GLBINDING_API void glClearStencil(GLint
    s);
    GLBINDING_API void glClearTexImage(GLuint
    texture,
    GLint level, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClearTexSubImage(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLenum type,
    const void *data
    );
    GLBINDING_API void glClientActiveTexture(GLenum
    texture);
    GLBINDING_API void glClientActiveTextureARB(GLenum
    texture);
    GLBINDING_API void glClientActiveVertexStreamATI(GLenum
    stream);

    GLBINDING_API void glClientAttribDefaultEXT(ClientAttribMask mask);

    GLBINDING_API GLenum
    glClientWaitSync(GLsync
    sync,
    SyncObjectMask flags, GLuint64
    timeout);
    GLBINDING_API void glClipControl(GLenum
    origin,
    GLenum depth
    );
    GLBINDING_API void glClipPlane(GLenum
    plane,
    const GLdouble *equation
    );
    GLBINDING_API void glClipPlanefOES(GLenum
    plane,
    const GLfloat *equation
    );
    GLBINDING_API void glClipPlanexOES(GLenum
    plane,
    const GLfixed *equation
    );

    GLBINDING_API void glColor3b(GLbyte red, GLbyte green, GLbyte blue);

    GLBINDING_API void glColor3bv(const GLbyte *v);

    GLBINDING_API void glColor3d(GLdouble red, GLdouble green, GLdouble blue);

    GLBINDING_API void glColor3dv(const GLdouble *v);

    GLBINDING_API void glColor3f(GLfloat
    red,
    GLfloat green, GLfloat
    blue);
    GLBINDING_API void glColor3fVertex3fSUN(GLfloat
    r,
    GLfloat g, GLfloat
    b,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glColor3fVertex3fvSUN(const GLfloat *c, const GLfloat *v);

    GLBINDING_API void glColor3fv(const GLfloat *v);

    GLBINDING_API void glColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue);

    GLBINDING_API void glColor3hvNV(const GLhalfNV *v);

    GLBINDING_API void glColor3i(GLint
    red,
    GLint green, GLint
    blue);

    GLBINDING_API void glColor3iv(const GLint *v);

    GLBINDING_API void glColor3s(GLshort red, GLshort green, GLshort blue);

    GLBINDING_API void glColor3sv(const GLshort *v);

    GLBINDING_API void glColor3ub(GLubyte red, GLubyte green, GLubyte blue);

    GLBINDING_API void glColor3ubv(const GLubyte *v);

    GLBINDING_API void glColor3ui(GLuint
    red,
    GLuint green, GLuint
    blue);

    GLBINDING_API void glColor3uiv(const GLuint *v);

    GLBINDING_API void glColor3us(GLushort red, GLushort green, GLushort blue);

    GLBINDING_API void glColor3usv(const GLushort *v);

    GLBINDING_API void glColor3xOES(GLfixed
    red,
    GLfixed green, GLfixed
    blue);

    GLBINDING_API void glColor3xvOES(const GLfixed *components);

    GLBINDING_API void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);

    GLBINDING_API void glColor4bv(const GLbyte *v);

    GLBINDING_API void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);

    GLBINDING_API void glColor4dv(const GLdouble *v);

    GLBINDING_API void glColor4f(GLfloat
    red,
    GLfloat green, GLfloat
    blue,
    GLfloat alpha
    );
    GLBINDING_API void glColor4fNormal3fVertex3fSUN(GLfloat
    r,
    GLfloat g, GLfloat
    b,
    GLfloat a, GLfloat
    nx,
    GLfloat ny, GLfloat
    nz,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glColor4fNormal3fVertex3fvSUN(const GLfloat *c, const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glColor4fv(const GLfloat *v);

    GLBINDING_API void glColor4hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha);

    GLBINDING_API void glColor4hvNV(const GLhalfNV *v);

    GLBINDING_API void glColor4i(GLint
    red,
    GLint green, GLint
    blue,
    GLint alpha
    );

    GLBINDING_API void glColor4iv(const GLint *v);

    GLBINDING_API void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha);

    GLBINDING_API void glColor4sv(const GLshort *v);

    GLBINDING_API void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

    GLBINDING_API void glColor4ubVertex2fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y);

    GLBINDING_API void glColor4ubVertex2fvSUN(const GLubyte *c, const GLfloat *v);

    GLBINDING_API void
    glColor4ubVertex3fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);

    GLBINDING_API void glColor4ubVertex3fvSUN(const GLubyte *c, const GLfloat *v);

    GLBINDING_API void glColor4ubv(const GLubyte *v);

    GLBINDING_API void glColor4ui(GLuint
    red,
    GLuint green, GLuint
    blue,
    GLuint alpha
    );

    GLBINDING_API void glColor4uiv(const GLuint *v);

    GLBINDING_API void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha);

    GLBINDING_API void glColor4usv(const GLushort *v);

    GLBINDING_API void glColor4xOES(GLfixed
    red,
    GLfixed green, GLfixed
    blue,
    GLfixed alpha
    );

    GLBINDING_API void glColor4xvOES(const GLfixed *components);

    GLBINDING_API void glColorFormatNV(GLint
    size,
    GLenum type, GLsizei
    stride);
    GLBINDING_API void glColorFragmentOp1ATI(GLenum
    op,
    GLuint dst, GLuint
    dstMask,
    GLuint dstMod, GLuint
    arg1,
    GLuint arg1Rep, GLuint
    arg1Mod);
    GLBINDING_API void glColorFragmentOp2ATI(GLenum
    op,
    GLuint dst, GLuint
    dstMask,
    GLuint dstMod, GLuint
    arg1,
    GLuint arg1Rep, GLuint
    arg1Mod,
    GLuint arg2, GLuint
    arg2Rep,
    GLuint arg2Mod
    );
    GLBINDING_API void glColorFragmentOp3ATI(GLenum
    op,
    GLuint dst, GLuint
    dstMask,
    GLuint dstMod, GLuint
    arg1,
    GLuint arg1Rep, GLuint
    arg1Mod,
    GLuint arg2, GLuint
    arg2Rep,
    GLuint arg2Mod, GLuint
    arg3,
    GLuint arg3Rep, GLuint
    arg3Mod);
    GLBINDING_API void glColorMask(GLboolean
    red,
    GLboolean green, GLboolean
    blue,
    GLboolean alpha
    );
    GLBINDING_API void glColorMaskIndexedEXT(GLuint
    index,
    GLboolean r, GLboolean
    g,
    GLboolean b, GLboolean
    a);
    GLBINDING_API void glColorMaski(GLuint
    index,
    GLboolean r, GLboolean
    g,
    GLboolean b, GLboolean
    a);
    GLBINDING_API void glColorMaterial(GLenum
    face,
    GLenum mode
    );
    GLBINDING_API void glColorP3ui(GLenum
    type,
    GLuint color
    );
    GLBINDING_API void glColorP3uiv(GLenum
    type,
    const GLuint *color
    );
    GLBINDING_API void glColorP4ui(GLenum
    type,
    GLuint color
    );
    GLBINDING_API void glColorP4uiv(GLenum
    type,
    const GLuint *color
    );
    GLBINDING_API void glColorPointer(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glColorPointerEXT(GLint
    size,
    GLenum type, GLsizei
    stride,
    GLsizei count,
    const void *pointer
    );
    GLBINDING_API void glColorPointerListIBM(GLint
    size,
    GLenum type, GLint
    stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glColorPointervINTEL(GLint
    size,
    GLenum type,
    const void **pointer
    );
    GLBINDING_API void glColorSubTable(GLenum
    target,
    GLsizei start, GLsizei
    count,
    GLenum format, GLenum
    type,
    const void *data
    );
    GLBINDING_API void glColorSubTableEXT(GLenum
    target,
    GLsizei start, GLsizei
    count,
    GLenum format, GLenum
    type,
    const void *data
    );
    GLBINDING_API void glColorTable(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *table
    );
    GLBINDING_API void glColorTableEXT(GLenum
    target,
    GLenum internalFormat, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *table
    );
    GLBINDING_API void glColorTableParameterfv(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glColorTableParameterfvSGI(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glColorTableParameteriv(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glColorTableParameterivSGI(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glColorTableSGI(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *table
    );
    GLBINDING_API void glCombinerInputNV(GLenum
    stage,
    GLenum portion, GLenum
    variable,
    GLenum input, GLenum
    mapping,
    GLenum componentUsage
    );
    GLBINDING_API void glCombinerOutputNV(GLenum
    stage,
    GLenum portion, GLenum
    abOutput,
    GLenum cdOutput, GLenum
    sumOutput,
    GLenum scale, GLenum
    bias,
    GLboolean abDotProduct, GLboolean
    cdDotProduct,
    GLboolean muxSum
    );
    GLBINDING_API void glCombinerParameterfNV(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glCombinerParameterfvNV(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glCombinerParameteriNV(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glCombinerParameterivNV(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glCombinerStageParameterfvNV(GLenum
    stage,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glCommandListSegmentsNV(GLuint
    list,
    GLuint segments
    );
    GLBINDING_API void glCompileCommandListNV(GLuint
    list);
    GLBINDING_API void glCompileShader(GLuint
    shader);

    GLBINDING_API void glCompileShaderARB(GLhandleARB shaderObj);

    GLBINDING_API void glCompileShaderIncludeARB(GLuint
    shader,
    GLsizei count,
    const GLchar *const *path,
    const GLint *length
    );
    GLBINDING_API void glCompressedMultiTexImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLint border, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedMultiTexImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLint
    border,
    GLsizei imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedMultiTexImage3DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLint border, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedMultiTexSubImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLsizei
    width,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedMultiTexSubImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLsizei width, GLsizei
    height,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedMultiTexSubImage3DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTexImage1D(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLint
    border,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexImage1DARB(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLint
    border,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexImage2D(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLint border, GLsizei
    imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexImage2DARB(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLint border, GLsizei
    imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexImage3D(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLint
    border,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexImage3DARB(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLint
    border,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage1D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage1DARB(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage2D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage2DARB(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage3D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTexSubImage3DARB(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTextureImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLint border, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTextureImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLint
    border,
    GLsizei imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTextureImage3DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLint border, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTextureSubImage1D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTextureSubImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLsizei
    width,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTextureSubImage2D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTextureSubImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLsizei width, GLsizei
    height,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glCompressedTextureSubImage3D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLsizei imageSize,
    const void *data
    );
    GLBINDING_API void glCompressedTextureSubImage3DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLenum format, GLsizei
    imageSize,
    const void *bits
    );
    GLBINDING_API void glConservativeRasterParameterfNV(GLenum
    pname,
    GLfloat value
    );
    GLBINDING_API void glConservativeRasterParameteriNV(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glConvolutionFilter1D(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *image
    );
    GLBINDING_API void glConvolutionFilter1DEXT(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *image
    );
    GLBINDING_API void glConvolutionFilter2D(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *image
    );
    GLBINDING_API void glConvolutionFilter2DEXT(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *image
    );
    GLBINDING_API void glConvolutionParameterf(GLenum
    target,
    GLenum pname, GLfloat
    params);
    GLBINDING_API void glConvolutionParameterfEXT(GLenum
    target,
    GLenum pname, GLfloat
    params);
    GLBINDING_API void glConvolutionParameterfv(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glConvolutionParameterfvEXT(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glConvolutionParameteri(GLenum
    target,
    GLenum pname, GLint
    params);
    GLBINDING_API void glConvolutionParameteriEXT(GLenum
    target,
    GLenum pname, GLint
    params);
    GLBINDING_API void glConvolutionParameteriv(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glConvolutionParameterivEXT(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glConvolutionParameterxOES(GLenum
    target,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glConvolutionParameterxvOES(GLenum
    target,
    GLenum pname,
    const GLfixed *params
    );
    GLBINDING_API void glCopyBufferSubData(GLenum
    readTarget,
    GLenum writeTarget, GLintptr
    readOffset,
    GLintptr writeOffset, GLsizeiptr
    size);
    GLBINDING_API void glCopyColorSubTable(GLenum
    target,
    GLsizei start, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyColorSubTableEXT(GLenum
    target,
    GLsizei start, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyColorTable(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyColorTableSGI(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyConvolutionFilter1D(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyConvolutionFilter1DEXT(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyConvolutionFilter2D(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyConvolutionFilter2DEXT(GLenum
    target,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyImageSubData(GLuint
    srcName,
    GLenum srcTarget, GLint
    srcLevel,
    GLint srcX, GLint
    srcY,
    GLint srcZ, GLuint
    dstName,
    GLenum dstTarget, GLint
    dstLevel,
    GLint dstX, GLint
    dstY,
    GLint dstZ, GLsizei
    srcWidth,
    GLsizei srcHeight, GLsizei
    srcDepth);
    GLBINDING_API void glCopyImageSubDataNV(GLuint
    srcName,
    GLenum srcTarget, GLint
    srcLevel,
    GLint srcX, GLint
    srcY,
    GLint srcZ, GLuint
    dstName,
    GLenum dstTarget, GLint
    dstLevel,
    GLint dstX, GLint
    dstY,
    GLint dstZ, GLsizei
    width,
    GLsizei height, GLsizei
    depth);
    GLBINDING_API void glCopyMultiTexImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLint border
    );
    GLBINDING_API void glCopyMultiTexImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLint
    border);
    GLBINDING_API void glCopyMultiTexSubImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyMultiTexSubImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glCopyMultiTexSubImage3DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyNamedBufferSubData(GLuint
    readBuffer,
    GLuint writeBuffer, GLintptr
    readOffset,
    GLintptr writeOffset, GLsizeiptr
    size);
    GLBINDING_API void glCopyPathNV(GLuint
    resultPath,
    GLuint srcPath
    );
    GLBINDING_API void glCopyPixels(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLenum
    type);
    GLBINDING_API void glCopyTexImage1D(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLint x, GLint
    y,
    GLsizei width, GLint
    border);
    GLBINDING_API void glCopyTexImage1DEXT(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLint x, GLint
    y,
    GLsizei width, GLint
    border);
    GLBINDING_API void glCopyTexImage2D(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height,
    GLint border
    );
    GLBINDING_API void glCopyTexImage2DEXT(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height,
    GLint border
    );
    GLBINDING_API void glCopyTexSubImage1D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint x, GLint
    y,
    GLsizei width
    );
    GLBINDING_API void glCopyTexSubImage1DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint x, GLint
    y,
    GLsizei width
    );
    GLBINDING_API void glCopyTexSubImage2D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyTexSubImage2DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyTexSubImage3D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glCopyTexSubImage3DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glCopyTextureImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLint border
    );
    GLBINDING_API void glCopyTextureImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum internalformat, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLint
    border);
    GLBINDING_API void glCopyTextureSubImage1D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint x, GLint
    y,
    GLsizei width
    );
    GLBINDING_API void glCopyTextureSubImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    x,
    GLint y, GLsizei
    width);
    GLBINDING_API void glCopyTextureSubImage2D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCopyTextureSubImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glCopyTextureSubImage3D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLint x, GLint
    y,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glCopyTextureSubImage3DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glCoverFillPathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLenum coverMode, GLenum
    transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glCoverFillPathNV(GLuint
    path,
    GLenum coverMode
    );
    GLBINDING_API void glCoverStrokePathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLenum coverMode, GLenum
    transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glCoverStrokePathNV(GLuint
    path,
    GLenum coverMode
    );
    GLBINDING_API void glCoverageModulationNV(GLenum
    components);
    GLBINDING_API void glCoverageModulationTableNV(GLsizei
    n,
    const GLfloat *v
    );
    GLBINDING_API void glCreateBuffers(GLsizei
    n,
    GLuint *buffers
    );
    GLBINDING_API void glCreateCommandListsNV(GLsizei
    n,
    GLuint *lists
    );
    GLBINDING_API void glCreateFramebuffers(GLsizei
    n,
    GLuint *framebuffers
    );
    GLBINDING_API void glCreateMemoryObjectsEXT(GLsizei
    n,
    GLuint *memoryObjects
    );
    GLBINDING_API void glCreatePerfQueryINTEL(GLuint
    queryId,
    GLuint *queryHandle
    );
    GLBINDING_API GLuint

    glCreateProgram();

    GLBINDING_API GLhandleARB

    glCreateProgramObjectARB();

    GLBINDING_API void glCreateProgramPipelines(GLsizei
    n,
    GLuint *pipelines
    );
    GLBINDING_API void glCreateQueries(GLenum
    target,
    GLsizei n, GLuint
    * ids);
    GLBINDING_API void glCreateRenderbuffers(GLsizei
    n,
    GLuint *renderbuffers
    );
    GLBINDING_API void glCreateSamplers(GLsizei
    n,
    GLuint *samplers
    );
    GLBINDING_API GLuint
    glCreateShader(GLenum
    type);
    GLBINDING_API GLhandleARB
    glCreateShaderObjectARB(GLenum
    shaderType);
    GLBINDING_API GLuint
    glCreateShaderProgramEXT(GLenum
    type,
    const GLchar *string
    );
    GLBINDING_API GLuint
    glCreateShaderProgramv(GLenum
    type,
    GLsizei count,
    const GLchar *const *strings
    );
    GLBINDING_API void glCreateStatesNV(GLsizei
    n,
    GLuint *states
    );
    GLBINDING_API GLsync
    glCreateSyncFromCLeventARB(_cl_context
    * context,
    _cl_event *event, UnusedMask
    flags);
    GLBINDING_API void glCreateTextures(GLenum
    target,
    GLsizei n, GLuint
    * textures);
    GLBINDING_API void glCreateTransformFeedbacks(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API void glCreateVertexArrays(GLsizei
    n,
    GLuint *arrays
    );
    GLBINDING_API void glCullFace(GLenum
    mode);
    GLBINDING_API void glCullParameterdvEXT(GLenum
    pname,
    GLdouble *params
    );
    GLBINDING_API void glCullParameterfvEXT(GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glCurrentPaletteMatrixARB(GLint
    index);

    GLBINDING_API void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam);

    GLBINDING_API void glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void *userParam);

    GLBINDING_API void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void *userParam);

    GLBINDING_API void glDebugMessageControl(GLenum
    source,
    GLenum type, GLenum
    severity,
    GLsizei count,
    const GLuint *ids, GLboolean
    enabled);
    GLBINDING_API void glDebugMessageControlARB(GLenum
    source,
    GLenum type, GLenum
    severity,
    GLsizei count,
    const GLuint *ids, GLboolean
    enabled);
    GLBINDING_API void glDebugMessageEnableAMD(GLenum
    category,
    GLenum severity, GLsizei
    count,
    const GLuint *ids, GLboolean
    enabled);
    GLBINDING_API void glDebugMessageInsert(GLenum
    source,
    GLenum type, GLuint
    id,
    GLenum severity, GLsizei
    length,
    const GLchar *buf
    );
    GLBINDING_API void glDebugMessageInsertAMD(GLenum
    category,
    GLenum severity, GLuint
    id,
    GLsizei length,
    const GLchar *buf
    );
    GLBINDING_API void glDebugMessageInsertARB(GLenum
    source,
    GLenum type, GLuint
    id,
    GLenum severity, GLsizei
    length,
    const GLchar *buf
    );

    GLBINDING_API void glDeformSGIX(FfdMaskSGIX mask);

    GLBINDING_API void glDeformationMap3dSGIX(GLenum
    target,
    GLdouble u1, GLdouble
    u2,
    GLint ustride, GLint
    uorder,
    GLdouble v1, GLdouble
    v2,
    GLint vstride, GLint
    vorder,
    GLdouble w1, GLdouble
    w2,
    GLint wstride, GLint
    worder,
    const GLdouble *points
    );
    GLBINDING_API void glDeformationMap3fSGIX(GLenum
    target,
    GLfloat u1, GLfloat
    u2,
    GLint ustride, GLint
    uorder,
    GLfloat v1, GLfloat
    v2,
    GLint vstride, GLint
    vorder,
    GLfloat w1, GLfloat
    w2,
    GLint wstride, GLint
    worder,
    const GLfloat *points
    );
    GLBINDING_API void glDeleteAsyncMarkersSGIX(GLuint
    marker,
    GLsizei range
    );
    GLBINDING_API void glDeleteBuffers(GLsizei
    n,
    const GLuint *buffers
    );
    GLBINDING_API void glDeleteBuffersARB(GLsizei
    n,
    const GLuint *buffers
    );
    GLBINDING_API void glDeleteCommandListsNV(GLsizei
    n,
    const GLuint *lists
    );
    GLBINDING_API void glDeleteFencesAPPLE(GLsizei
    n,
    const GLuint *fences
    );
    GLBINDING_API void glDeleteFencesNV(GLsizei
    n,
    const GLuint *fences
    );
    GLBINDING_API void glDeleteFragmentShaderATI(GLuint
    id);
    GLBINDING_API void glDeleteFramebuffers(GLsizei
    n,
    const GLuint *framebuffers
    );
    GLBINDING_API void glDeleteFramebuffersEXT(GLsizei
    n,
    const GLuint *framebuffers
    );
    GLBINDING_API void glDeleteLists(GLuint
    list,
    GLsizei range
    );
    GLBINDING_API void glDeleteMemoryObjectsEXT(GLsizei
    n,
    const GLuint *memoryObjects
    );
    GLBINDING_API void glDeleteNamedStringARB(GLint
    namelen,
    const GLchar *name
    );
    GLBINDING_API void glDeleteNamesAMD(GLenum
    identifier,
    GLuint num,
    const GLuint *names
    );
    GLBINDING_API void glDeleteObjectARB(GLhandleARB
    obj);
    GLBINDING_API void glDeleteOcclusionQueriesNV(GLsizei
    n,
    const GLuint *ids
    );
    GLBINDING_API void glDeletePathsNV(GLuint
    path,
    GLsizei range
    );
    GLBINDING_API void glDeletePerfMonitorsAMD(GLsizei
    n,
    GLuint *monitors
    );
    GLBINDING_API void glDeletePerfQueryINTEL(GLuint
    queryHandle);
    GLBINDING_API void glDeleteProgram(GLuint
    program);
    GLBINDING_API void glDeleteProgramPipelines(GLsizei
    n,
    const GLuint *pipelines
    );
    GLBINDING_API void glDeleteProgramsARB(GLsizei
    n,
    const GLuint *programs
    );
    GLBINDING_API void glDeleteProgramsNV(GLsizei
    n,
    const GLuint *programs
    );
    GLBINDING_API void glDeleteQueries(GLsizei
    n,
    const GLuint *ids
    );
    GLBINDING_API void glDeleteQueriesARB(GLsizei
    n,
    const GLuint *ids
    );
    GLBINDING_API void glDeleteQueryResourceTagNV(GLsizei
    n,
    const GLint *tagIds
    );
    GLBINDING_API void glDeleteRenderbuffers(GLsizei
    n,
    const GLuint *renderbuffers
    );
    GLBINDING_API void glDeleteRenderbuffersEXT(GLsizei
    n,
    const GLuint *renderbuffers
    );
    GLBINDING_API void glDeleteSamplers(GLsizei
    count,
    const GLuint *samplers
    );
    GLBINDING_API void glDeleteSemaphoresEXT(GLsizei
    n,
    const GLuint *semaphores
    );
    GLBINDING_API void glDeleteShader(GLuint
    shader);
    GLBINDING_API void glDeleteStatesNV(GLsizei
    n,
    const GLuint *states
    );
    GLBINDING_API void glDeleteSync(GLsync
    sync);
    GLBINDING_API void glDeleteTextures(GLsizei
    n,
    const GLuint *textures
    );
    GLBINDING_API void glDeleteTexturesEXT(GLsizei
    n,
    const GLuint *textures
    );
    GLBINDING_API void glDeleteTransformFeedbacks(GLsizei
    n,
    const GLuint *ids
    );
    GLBINDING_API void glDeleteTransformFeedbacksNV(GLsizei
    n,
    const GLuint *ids
    );
    GLBINDING_API void glDeleteVertexArrays(GLsizei
    n,
    const GLuint *arrays
    );
    GLBINDING_API void glDeleteVertexArraysAPPLE(GLsizei
    n,
    const GLuint *arrays
    );
    GLBINDING_API void glDeleteVertexShaderEXT(GLuint
    id);

    GLBINDING_API void glDepthBoundsEXT(GLclampd zmin, GLclampd zmax);

    GLBINDING_API void glDepthBoundsdNV(GLdouble
    zmin,
    GLdouble zmax
    );
    GLBINDING_API void glDepthFunc(GLenum
    func);
    GLBINDING_API void glDepthMask(GLboolean
    flag);
    GLBINDING_API void glDepthRange(GLdouble
    n,
    GLdouble f
    );
    GLBINDING_API void glDepthRangeArrayv(GLuint
    first,
    GLsizei count,
    const GLdouble *v
    );
    GLBINDING_API void glDepthRangeIndexed(GLuint
    index,
    GLdouble n, GLdouble
    f);
    GLBINDING_API void glDepthRangedNV(GLdouble
    zNear,
    GLdouble zFar
    );
    GLBINDING_API void glDepthRangef(GLfloat
    n,
    GLfloat f
    );

    GLBINDING_API void glDepthRangefOES(GLclampf n, GLclampf f);

    GLBINDING_API void glDepthRangexOES(GLfixed
    n,
    GLfixed f
    );
    GLBINDING_API void glDetachObjectARB(GLhandleARB
    containerObj,
    GLhandleARB attachedObj
    );
    GLBINDING_API void glDetachShader(GLuint
    program,
    GLuint shader
    );
    GLBINDING_API void glDetailTexFuncSGIS(GLenum
    target,
    GLsizei n,
    const GLfloat *points
    );
    GLBINDING_API void glDisable(GLenum
    cap);
    GLBINDING_API void glDisableClientState(GLenum
    array);
    GLBINDING_API void glDisableClientStateIndexedEXT(GLenum
    array,
    GLuint index
    );
    GLBINDING_API void glDisableClientStateiEXT(GLenum
    array,
    GLuint index
    );
    GLBINDING_API void glDisableIndexedEXT(GLenum
    target,
    GLuint index
    );
    GLBINDING_API void glDisableVariantClientStateEXT(GLuint
    id);
    GLBINDING_API void glDisableVertexArrayAttrib(GLuint
    vaobj,
    GLuint index
    );
    GLBINDING_API void glDisableVertexArrayAttribEXT(GLuint
    vaobj,
    GLuint index
    );
    GLBINDING_API void glDisableVertexArrayEXT(GLuint
    vaobj,
    GLenum array
    );
    GLBINDING_API void glDisableVertexAttribAPPLE(GLuint
    index,
    GLenum pname
    );
    GLBINDING_API void glDisableVertexAttribArray(GLuint
    index);
    GLBINDING_API void glDisableVertexAttribArrayARB(GLuint
    index);
    GLBINDING_API void glDisablei(GLenum
    target,
    GLuint index
    );
    GLBINDING_API void glDispatchCompute(GLuint
    num_groups_x,
    GLuint num_groups_y, GLuint
    num_groups_z);
    GLBINDING_API void glDispatchComputeGroupSizeARB(GLuint
    num_groups_x,
    GLuint num_groups_y, GLuint
    num_groups_z,
    GLuint group_size_x, GLuint
    group_size_y,
    GLuint group_size_z
    );
    GLBINDING_API void glDispatchComputeIndirect(GLintptr
    indirect);
    GLBINDING_API void glDrawArrays(GLenum
    mode,
    GLint first, GLsizei
    count);
    GLBINDING_API void glDrawArraysEXT(GLenum
    mode,
    GLint first, GLsizei
    count);
    GLBINDING_API void glDrawArraysIndirect(GLenum
    mode,
    const void *indirect
    );
    GLBINDING_API void glDrawArraysInstanced(GLenum
    mode,
    GLint first, GLsizei
    count,
    GLsizei instancecount
    );
    GLBINDING_API void glDrawArraysInstancedARB(GLenum
    mode,
    GLint first, GLsizei
    count,
    GLsizei primcount
    );
    GLBINDING_API void glDrawArraysInstancedBaseInstance(GLenum
    mode,
    GLint first, GLsizei
    count,
    GLsizei instancecount, GLuint
    baseinstance);
    GLBINDING_API void glDrawArraysInstancedEXT(GLenum
    mode,
    GLint start, GLsizei
    count,
    GLsizei primcount
    );
    GLBINDING_API void glDrawBuffer(GLenum
    buf);
    GLBINDING_API void glDrawBuffers(GLsizei
    n,
    const GLenum *bufs
    );
    GLBINDING_API void glDrawBuffersARB(GLsizei
    n,
    const GLenum *bufs
    );
    GLBINDING_API void glDrawBuffersATI(GLsizei
    n,
    const GLenum *bufs
    );
    GLBINDING_API void glDrawCommandsAddressNV(GLenum
    primitiveMode,
    const GLuint64 *indirects,
    const GLsizei *sizes, GLuint
    count);
    GLBINDING_API void glDrawCommandsNV(GLenum
    primitiveMode,
    GLuint buffer,
    const GLintptr *indirects,
    const GLsizei *sizes, GLuint
    count);

    GLBINDING_API void
    glDrawCommandsStatesAddressNV(const GLuint64 *indirects, const GLsizei *sizes, const GLuint *states,
                                  const GLuint *fbos, GLuint count);

    GLBINDING_API void glDrawCommandsStatesNV(GLuint
    buffer,
    const GLintptr *indirects,
    const GLsizei *sizes,
    const GLuint *states,
    const GLuint *fbos, GLuint
    count);
    GLBINDING_API void glDrawElementArrayAPPLE(GLenum
    mode,
    GLint first, GLsizei
    count);
    GLBINDING_API void glDrawElementArrayATI(GLenum
    mode,
    GLsizei count
    );
    GLBINDING_API void glDrawElements(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices
    );
    GLBINDING_API void glDrawElementsBaseVertex(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLint
    basevertex);
    GLBINDING_API void glDrawElementsIndirect(GLenum
    mode,
    GLenum type,
    const void *indirect
    );
    GLBINDING_API void glDrawElementsInstanced(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    instancecount);
    GLBINDING_API void glDrawElementsInstancedARB(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    primcount);
    GLBINDING_API void glDrawElementsInstancedBaseInstance(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    instancecount,
    GLuint baseinstance
    );
    GLBINDING_API void glDrawElementsInstancedBaseVertex(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    instancecount,
    GLint basevertex
    );
    GLBINDING_API void glDrawElementsInstancedBaseVertexBaseInstance(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    instancecount,
    GLint basevertex, GLuint
    baseinstance);
    GLBINDING_API void glDrawElementsInstancedEXT(GLenum
    mode,
    GLsizei count, GLenum
    type,
    const void *indices, GLsizei
    primcount);
    GLBINDING_API void glDrawMeshArraysSUN(GLenum
    mode,
    GLint first, GLsizei
    count,
    GLsizei width
    );
    GLBINDING_API void glDrawMeshTasksIndirectNV(GLintptr
    indirect);
    GLBINDING_API void glDrawMeshTasksNV(GLuint
    first,
    GLuint count
    );
    GLBINDING_API void glDrawPixels(GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glDrawRangeElementArrayAPPLE(GLenum
    mode,
    GLuint start, GLuint
    end,
    GLint first, GLsizei
    count);
    GLBINDING_API void glDrawRangeElementArrayATI(GLenum
    mode,
    GLuint start, GLuint
    end,
    GLsizei count
    );
    GLBINDING_API void glDrawRangeElements(GLenum
    mode,
    GLuint start, GLuint
    end,
    GLsizei count, GLenum
    type,
    const void *indices
    );
    GLBINDING_API void glDrawRangeElementsBaseVertex(GLenum
    mode,
    GLuint start, GLuint
    end,
    GLsizei count, GLenum
    type,
    const void *indices, GLint
    basevertex);
    GLBINDING_API void glDrawRangeElementsEXT(GLenum
    mode,
    GLuint start, GLuint
    end,
    GLsizei count, GLenum
    type,
    const void *indices
    );
    GLBINDING_API void glDrawTextureNV(GLuint
    texture,
    GLuint sampler, GLfloat
    x0,
    GLfloat y0, GLfloat
    x1,
    GLfloat y1, GLfloat
    z,
    GLfloat s0, GLfloat
    t0,
    GLfloat s1, GLfloat
    t1);
    GLBINDING_API void glDrawTransformFeedback(GLenum
    mode,
    GLuint id
    );
    GLBINDING_API void glDrawTransformFeedbackInstanced(GLenum
    mode,
    GLuint id, GLsizei
    instancecount);
    GLBINDING_API void glDrawTransformFeedbackNV(GLenum
    mode,
    GLuint id
    );
    GLBINDING_API void glDrawTransformFeedbackStream(GLenum
    mode,
    GLuint id, GLuint
    stream);
    GLBINDING_API void glDrawTransformFeedbackStreamInstanced(GLenum
    mode,
    GLuint id, GLuint
    stream,
    GLsizei instancecount
    );
    GLBINDING_API void glDrawVkImageNV(GLuint64
    vkImage,
    GLuint sampler, GLfloat
    x0,
    GLfloat y0, GLfloat
    x1,
    GLfloat y1, GLfloat
    z,
    GLfloat s0, GLfloat
    t0,
    GLfloat s1, GLfloat
    t1);

    GLBINDING_API void glEGLImageTargetTexStorageEXT(GLenum
    target,
    GLeglImageOES image,
    const GLint *attrib_list
    );
    GLBINDING_API void glEGLImageTargetTextureStorageEXT(GLuint
    texture,
    GLeglImageOES image,
    const GLint *attrib_list
    );
    GLBINDING_API void glEdgeFlag(GLboolean
    flag);
    GLBINDING_API void glEdgeFlagFormatNV(GLsizei
    stride);
    GLBINDING_API void glEdgeFlagPointer(GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glEdgeFlagPointerEXT(GLsizei
    stride,
    GLsizei count,
    const GLboolean *pointer
    );
    GLBINDING_API void glEdgeFlagPointerListIBM(GLint
    stride,
    const GLboolean **pointer, GLint
    ptrstride);

    GLBINDING_API void glEdgeFlagv(const GLboolean *flag);

    GLBINDING_API void glElementPointerAPPLE(GLenum
    type,
    const void *pointer
    );
    GLBINDING_API void glElementPointerATI(GLenum
    type,
    const void *pointer
    );
    GLBINDING_API void glEnable(GLenum
    cap);
    GLBINDING_API void glEnableClientState(GLenum
    array);
    GLBINDING_API void glEnableClientStateIndexedEXT(GLenum
    array,
    GLuint index
    );
    GLBINDING_API void glEnableClientStateiEXT(GLenum
    array,
    GLuint index
    );
    GLBINDING_API void glEnableIndexedEXT(GLenum
    target,
    GLuint index
    );
    GLBINDING_API void glEnableVariantClientStateEXT(GLuint
    id);
    GLBINDING_API void glEnableVertexArrayAttrib(GLuint
    vaobj,
    GLuint index
    );
    GLBINDING_API void glEnableVertexArrayAttribEXT(GLuint
    vaobj,
    GLuint index
    );
    GLBINDING_API void glEnableVertexArrayEXT(GLuint
    vaobj,
    GLenum array
    );
    GLBINDING_API void glEnableVertexAttribAPPLE(GLuint
    index,
    GLenum pname
    );
    GLBINDING_API void glEnableVertexAttribArray(GLuint
    index);
    GLBINDING_API void glEnableVertexAttribArrayARB(GLuint
    index);
    GLBINDING_API void glEnablei(GLenum
    target,
    GLuint index
    );

    GLBINDING_API void glEnd();

    GLBINDING_API void glEndConditionalRender();

    GLBINDING_API void glEndConditionalRenderNV();

    GLBINDING_API void glEndConditionalRenderNVX();

    GLBINDING_API void glEndFragmentShaderATI();

    GLBINDING_API void glEndList();

    GLBINDING_API void glEndOcclusionQueryNV();

    GLBINDING_API void glEndPerfMonitorAMD(GLuint
    monitor);
    GLBINDING_API void glEndPerfQueryINTEL(GLuint
    queryHandle);
    GLBINDING_API void glEndQuery(GLenum
    target);
    GLBINDING_API void glEndQueryARB(GLenum
    target);
    GLBINDING_API void glEndQueryIndexed(GLenum
    target,
    GLuint index
    );

    GLBINDING_API void glEndTransformFeedback();

    GLBINDING_API void glEndTransformFeedbackEXT();

    GLBINDING_API void glEndTransformFeedbackNV();

    GLBINDING_API void glEndVertexShaderEXT();

    GLBINDING_API void glEndVideoCaptureNV(GLuint
    video_capture_slot);
    GLBINDING_API void glEvalCoord1d(GLdouble
    u);

    GLBINDING_API void glEvalCoord1dv(const GLdouble *u);

    GLBINDING_API void glEvalCoord1f(GLfloat
    u);

    GLBINDING_API void glEvalCoord1fv(const GLfloat *u);

    GLBINDING_API void glEvalCoord1xOES(GLfixed
    u);

    GLBINDING_API void glEvalCoord1xvOES(const GLfixed *coords);

    GLBINDING_API void glEvalCoord2d(GLdouble
    u,
    GLdouble v
    );

    GLBINDING_API void glEvalCoord2dv(const GLdouble *u);

    GLBINDING_API void glEvalCoord2f(GLfloat
    u,
    GLfloat v
    );

    GLBINDING_API void glEvalCoord2fv(const GLfloat *u);

    GLBINDING_API void glEvalCoord2xOES(GLfixed
    u,
    GLfixed v
    );

    GLBINDING_API void glEvalCoord2xvOES(const GLfixed *coords);

    GLBINDING_API void glEvalMapsNV(GLenum
    target,
    GLenum mode
    );
    GLBINDING_API void glEvalMesh1(GLenum
    mode,
    GLint i1, GLint
    i2);
    GLBINDING_API void glEvalMesh2(GLenum
    mode,
    GLint i1, GLint
    i2,
    GLint j1, GLint
    j2);
    GLBINDING_API void glEvalPoint1(GLint
    i);
    GLBINDING_API void glEvalPoint2(GLint
    i,
    GLint j
    );

    GLBINDING_API void glEvaluateDepthValuesARB();

    GLBINDING_API void glExecuteProgramNV(GLenum
    target,
    GLuint id,
    const GLfloat *params
    );
    GLBINDING_API void glExtractComponentEXT(GLuint
    res,
    GLuint src, GLuint
    num);

    GLBINDING_API void glFeedbackBuffer(GLsizei
    size,
    GLenum type, GLfloat
    * buffer);
    GLBINDING_API void glFeedbackBufferxOES(GLsizei
    n,
    GLenum type,
    const GLfixed *buffer
    );
    GLBINDING_API GLsync
    glFenceSync(GLenum
    condition,
    UnusedMask flags
    );
    GLBINDING_API void glFinalCombinerInputNV(GLenum
    variable,
    GLenum input, GLenum
    mapping,
    GLenum componentUsage
    );

    GLBINDING_API void glFinish();

    GLBINDING_API GLint
    glFinishAsyncSGIX(GLuint
    * markerp);
    GLBINDING_API void glFinishFenceAPPLE(GLuint
    fence);
    GLBINDING_API void glFinishFenceNV(GLuint
    fence);
    GLBINDING_API void glFinishObjectAPPLE(GLenum
    object,
    GLint name
    );

    GLBINDING_API void glFinishTextureSUNX();

    GLBINDING_API void glFlush();

    GLBINDING_API void glFlushMappedBufferRange(GLenum
    target,
    GLintptr offset, GLsizeiptr
    length);
    GLBINDING_API void glFlushMappedBufferRangeAPPLE(GLenum
    target,
    GLintptr offset, GLsizeiptr
    size);
    GLBINDING_API void glFlushMappedNamedBufferRange(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    length);
    GLBINDING_API void glFlushMappedNamedBufferRangeEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    length);
    GLBINDING_API void glFlushPixelDataRangeNV(GLenum
    target);

    GLBINDING_API void glFlushRasterSGIX();

    GLBINDING_API void glFlushStaticDataIBM(GLenum
    target);
    GLBINDING_API void glFlushVertexArrayRangeAPPLE(GLsizei
    length,
    void *pointer
    );

    GLBINDING_API void glFlushVertexArrayRangeNV();

    GLBINDING_API void glFogCoordFormatNV(GLenum
    type,
    GLsizei stride
    );
    GLBINDING_API void glFogCoordPointer(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glFogCoordPointerEXT(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glFogCoordPointerListIBM(GLenum
    type,
    GLint stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glFogCoordd(GLdouble
    coord);
    GLBINDING_API void glFogCoorddEXT(GLdouble
    coord);

    GLBINDING_API void glFogCoorddv(const GLdouble *coord);

    GLBINDING_API void glFogCoorddvEXT(const GLdouble *coord);

    GLBINDING_API void glFogCoordf(GLfloat
    coord);
    GLBINDING_API void glFogCoordfEXT(GLfloat
    coord);

    GLBINDING_API void glFogCoordfv(const GLfloat *coord);

    GLBINDING_API void glFogCoordfvEXT(const GLfloat *coord);

    GLBINDING_API void glFogCoordhNV(GLhalfNV fog);

    GLBINDING_API void glFogCoordhvNV(const GLhalfNV *fog);

    GLBINDING_API void glFogFuncSGIS(GLsizei
    n,
    const GLfloat *points
    );
    GLBINDING_API void glFogf(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glFogfv(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glFogi(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glFogiv(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glFogxOES(GLenum
    pname,
    GLfixed param
    );
    GLBINDING_API void glFogxvOES(GLenum
    pname,
    const GLfixed *param
    );
    GLBINDING_API void glFragmentColorMaterialSGIX(GLenum
    face,
    GLenum mode
    );
    GLBINDING_API void glFragmentCoverageColorNV(GLuint
    color);
    GLBINDING_API void glFragmentLightModelfSGIX(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glFragmentLightModelfvSGIX(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glFragmentLightModeliSGIX(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glFragmentLightModelivSGIX(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glFragmentLightfSGIX(GLenum
    light,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glFragmentLightfvSGIX(GLenum
    light,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glFragmentLightiSGIX(GLenum
    light,
    GLenum pname, GLint
    param);
    GLBINDING_API void glFragmentLightivSGIX(GLenum
    light,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glFragmentMaterialfSGIX(GLenum
    face,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glFragmentMaterialfvSGIX(GLenum
    face,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glFragmentMaterialiSGIX(GLenum
    face,
    GLenum pname, GLint
    param);
    GLBINDING_API void glFragmentMaterialivSGIX(GLenum
    face,
    GLenum pname,
    const GLint *params
    );

    GLBINDING_API void glFrameTerminatorGREMEDY();

    GLBINDING_API void glFrameZoomSGIX(GLint
    factor);
    GLBINDING_API void glFramebufferDrawBufferEXT(GLuint
    framebuffer,
    GLenum mode
    );
    GLBINDING_API void glFramebufferDrawBuffersEXT(GLuint
    framebuffer,
    GLsizei n,
    const GLenum *bufs
    );

    GLBINDING_API void glFramebufferFetchBarrierEXT();

    GLBINDING_API void glFramebufferParameteri(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glFramebufferReadBufferEXT(GLuint
    framebuffer,
    GLenum mode
    );
    GLBINDING_API void glFramebufferRenderbuffer(GLenum
    target,
    GLenum attachment, GLenum
    renderbuffertarget,
    GLuint renderbuffer
    );
    GLBINDING_API void glFramebufferRenderbufferEXT(GLenum
    target,
    GLenum attachment, GLenum
    renderbuffertarget,
    GLuint renderbuffer
    );
    GLBINDING_API void glFramebufferSampleLocationsfvARB(GLenum
    target,
    GLuint start, GLsizei
    count,
    const GLfloat *v
    );
    GLBINDING_API void glFramebufferSampleLocationsfvNV(GLenum
    target,
    GLuint start, GLsizei
    count,
    const GLfloat *v
    );
    GLBINDING_API void glFramebufferSamplePositionsfvAMD(GLenum
    target,
    GLuint numsamples, GLuint
    pixelindex,
    const GLfloat *values
    );
    GLBINDING_API void glFramebufferTexture(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glFramebufferTexture1D(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glFramebufferTexture1DEXT(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glFramebufferTexture2D(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glFramebufferTexture2DEXT(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glFramebufferTexture3D(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level,
    GLint zoffset
    );
    GLBINDING_API void glFramebufferTexture3DEXT(GLenum
    target,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level,
    GLint zoffset
    );
    GLBINDING_API void glFramebufferTextureARB(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glFramebufferTextureEXT(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glFramebufferTextureFaceARB(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLenum
    face);
    GLBINDING_API void glFramebufferTextureFaceEXT(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLenum
    face);
    GLBINDING_API void glFramebufferTextureLayer(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    layer);
    GLBINDING_API void glFramebufferTextureLayerARB(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    layer);
    GLBINDING_API void glFramebufferTextureLayerEXT(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    layer);
    GLBINDING_API void glFramebufferTextureMultiviewOVR(GLenum
    target,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    baseViewIndex,
    GLsizei numViews
    );
    GLBINDING_API void glFreeObjectBufferATI(GLuint
    buffer);
    GLBINDING_API void glFrontFace(GLenum
    mode);
    GLBINDING_API void glFrustum(GLdouble
    left,
    GLdouble right, GLdouble
    bottom,
    GLdouble top, GLdouble
    zNear,
    GLdouble zFar
    );
    GLBINDING_API void glFrustumfOES(GLfloat
    l,
    GLfloat r, GLfloat
    b,
    GLfloat t, GLfloat
    n,
    GLfloat f
    );
    GLBINDING_API void glFrustumxOES(GLfixed
    l,
    GLfixed r, GLfixed
    b,
    GLfixed t, GLfixed
    n,
    GLfixed f
    );

    GLBINDING_API GLuint
    glGenAsyncMarkersSGIX(GLsizei
    range);
    GLBINDING_API void glGenBuffers(GLsizei
    n,
    GLuint *buffers
    );
    GLBINDING_API void glGenBuffersARB(GLsizei
    n,
    GLuint *buffers
    );
    GLBINDING_API void glGenFencesAPPLE(GLsizei
    n,
    GLuint *fences
    );
    GLBINDING_API void glGenFencesNV(GLsizei
    n,
    GLuint *fences
    );
    GLBINDING_API GLuint
    glGenFragmentShadersATI(GLuint
    range);
    GLBINDING_API void glGenFramebuffers(GLsizei
    n,
    GLuint *framebuffers
    );
    GLBINDING_API void glGenFramebuffersEXT(GLsizei
    n,
    GLuint *framebuffers
    );
    GLBINDING_API GLuint
    glGenLists(GLsizei
    range);
    GLBINDING_API void glGenNamesAMD(GLenum
    identifier,
    GLuint num, GLuint
    * names);
    GLBINDING_API void glGenOcclusionQueriesNV(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API GLuint
    glGenPathsNV(GLsizei
    range);
    GLBINDING_API void glGenPerfMonitorsAMD(GLsizei
    n,
    GLuint *monitors
    );
    GLBINDING_API void glGenProgramPipelines(GLsizei
    n,
    GLuint *pipelines
    );
    GLBINDING_API void glGenProgramsARB(GLsizei
    n,
    GLuint *programs
    );
    GLBINDING_API void glGenProgramsNV(GLsizei
    n,
    GLuint *programs
    );
    GLBINDING_API void glGenQueries(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API void glGenQueriesARB(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API void glGenQueryResourceTagNV(GLsizei
    n,
    GLint *tagIds
    );
    GLBINDING_API void glGenRenderbuffers(GLsizei
    n,
    GLuint *renderbuffers
    );
    GLBINDING_API void glGenRenderbuffersEXT(GLsizei
    n,
    GLuint *renderbuffers
    );
    GLBINDING_API void glGenSamplers(GLsizei
    count,
    GLuint *samplers
    );
    GLBINDING_API void glGenSemaphoresEXT(GLsizei
    n,
    GLuint *semaphores
    );
    GLBINDING_API GLuint
    glGenSymbolsEXT(GLenum
    datatype,
    GLenum storagetype, GLenum
    range,
    GLuint components
    );
    GLBINDING_API void glGenTextures(GLsizei
    n,
    GLuint *textures
    );
    GLBINDING_API void glGenTexturesEXT(GLsizei
    n,
    GLuint *textures
    );
    GLBINDING_API void glGenTransformFeedbacks(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API void glGenTransformFeedbacksNV(GLsizei
    n,
    GLuint *ids
    );
    GLBINDING_API void glGenVertexArrays(GLsizei
    n,
    GLuint *arrays
    );
    GLBINDING_API void glGenVertexArraysAPPLE(GLsizei
    n,
    GLuint *arrays
    );
    GLBINDING_API GLuint
    glGenVertexShadersEXT(GLuint
    range);
    GLBINDING_API void glGenerateMipmap(GLenum
    target);
    GLBINDING_API void glGenerateMipmapEXT(GLenum
    target);
    GLBINDING_API void glGenerateMultiTexMipmapEXT(GLenum
    texunit,
    GLenum target
    );
    GLBINDING_API void glGenerateTextureMipmap(GLuint
    texture);
    GLBINDING_API void glGenerateTextureMipmapEXT(GLuint
    texture,
    GLenum target
    );
    GLBINDING_API void glGetActiveAtomicCounterBufferiv(GLuint
    program,
    GLuint bufferIndex, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetActiveAttrib(GLuint
    program,
    GLuint index, GLsizei
    bufSize,
    GLsizei *length, GLint
    * size,
    GLenum *type, GLchar
    * name);
    GLBINDING_API void glGetActiveAttribARB(GLhandleARB
    programObj,
    GLuint index, GLsizei
    maxLength,
    GLsizei *length, GLint
    * size,
    GLenum *type, GLcharARB
    * name);
    GLBINDING_API void glGetActiveSubroutineName(GLuint
    program,
    GLenum shadertype, GLuint
    index,
    GLsizei bufsize, GLsizei
    * length,
    GLchar *name
    );
    GLBINDING_API void glGetActiveSubroutineUniformName(GLuint
    program,
    GLenum shadertype, GLuint
    index,
    GLsizei bufsize, GLsizei
    * length,
    GLchar *name
    );
    GLBINDING_API void glGetActiveSubroutineUniformiv(GLuint
    program,
    GLenum shadertype, GLuint
    index,
    GLenum pname, GLint
    * values);
    GLBINDING_API void glGetActiveUniform(GLuint
    program,
    GLuint index, GLsizei
    bufSize,
    GLsizei *length, GLint
    * size,
    GLenum *type, GLchar
    * name);
    GLBINDING_API void glGetActiveUniformARB(GLhandleARB
    programObj,
    GLuint index, GLsizei
    maxLength,
    GLsizei *length, GLint
    * size,
    GLenum *type, GLcharARB
    * name);
    GLBINDING_API void glGetActiveUniformBlockName(GLuint
    program,
    GLuint uniformBlockIndex, GLsizei
    bufSize,
    GLsizei *length, GLchar
    * uniformBlockName);
    GLBINDING_API void glGetActiveUniformBlockiv(GLuint
    program,
    GLuint uniformBlockIndex, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetActiveUniformName(GLuint
    program,
    GLuint uniformIndex, GLsizei
    bufSize,
    GLsizei *length, GLchar
    * uniformName);
    GLBINDING_API void glGetActiveUniformsiv(GLuint
    program,
    GLsizei uniformCount,
    const GLuint *uniformIndices, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetActiveVaryingNV(GLuint
    program,
    GLuint index, GLsizei
    bufSize,
    GLsizei *length, GLsizei
    * size,
    GLenum *type, GLchar
    * name);
    GLBINDING_API void glGetArrayObjectfvATI(GLenum
    array,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetArrayObjectivATI(GLenum
    array,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetAttachedObjectsARB(GLhandleARB
    containerObj,
    GLsizei maxCount, GLsizei
    * count,
    GLhandleARB *obj
    );
    GLBINDING_API void glGetAttachedShaders(GLuint
    program,
    GLsizei maxCount, GLsizei
    * count,
    GLuint *shaders
    );
    GLBINDING_API GLint
    glGetAttribLocation(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetAttribLocationARB(GLhandleARB
    programObj,
    const GLcharARB *name
    );
    GLBINDING_API void glGetBooleanIndexedvEXT(GLenum
    target,
    GLuint index, GLboolean
    * data);
    GLBINDING_API void glGetBooleani_v(GLenum
    target,
    GLuint index, GLboolean
    * data);
    GLBINDING_API void glGetBooleanv(GLenum
    pname,
    GLboolean *data
    );
    GLBINDING_API void glGetBufferParameteri64v(GLenum
    target,
    GLenum pname, GLint64
    * params);
    GLBINDING_API void glGetBufferParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetBufferParameterivARB(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetBufferParameterui64vNV(GLenum
    target,
    GLenum pname, GLuint64EXT
    * params);
    GLBINDING_API void glGetBufferPointerv(GLenum
    target,
    GLenum pname,
    void **params
    );
    GLBINDING_API void glGetBufferPointervARB(GLenum
    target,
    GLenum pname,
    void **params
    );
    GLBINDING_API void glGetBufferSubData(GLenum
    target,
    GLintptr offset, GLsizeiptr
    size,
    void *data
    );
    GLBINDING_API void glGetBufferSubDataARB(GLenum
    target,
    GLintptrARB offset, GLsizeiptrARB
    size,
    void *data
    );
    GLBINDING_API void glGetClipPlane(GLenum
    plane,
    GLdouble *equation
    );
    GLBINDING_API void glGetClipPlanefOES(GLenum
    plane,
    GLfloat *equation
    );
    GLBINDING_API void glGetClipPlanexOES(GLenum
    plane,
    GLfixed *equation
    );
    GLBINDING_API void glGetColorTable(GLenum
    target,
    GLenum format, GLenum
    type,
    void *table
    );
    GLBINDING_API void glGetColorTableEXT(GLenum
    target,
    GLenum format, GLenum
    type,
    void *data
    );
    GLBINDING_API void glGetColorTableParameterfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetColorTableParameterfvEXT(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetColorTableParameterfvSGI(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetColorTableParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetColorTableParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetColorTableParameterivSGI(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetColorTableSGI(GLenum
    target,
    GLenum format, GLenum
    type,
    void *table
    );
    GLBINDING_API void glGetCombinerInputParameterfvNV(GLenum
    stage,
    GLenum portion, GLenum
    variable,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetCombinerInputParameterivNV(GLenum
    stage,
    GLenum portion, GLenum
    variable,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetCombinerOutputParameterfvNV(GLenum
    stage,
    GLenum portion, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetCombinerOutputParameterivNV(GLenum
    stage,
    GLenum portion, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetCombinerStageParameterfvNV(GLenum
    stage,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API GLuint
    glGetCommandHeaderNV(GLenum
    tokenID,
    GLuint size
    );
    GLBINDING_API void glGetCompressedMultiTexImageEXT(GLenum
    texunit,
    GLenum target, GLint
    lod,
    void *img
    );
    GLBINDING_API void glGetCompressedTexImage(GLenum
    target,
    GLint level,
    void *img
    );
    GLBINDING_API void glGetCompressedTexImageARB(GLenum
    target,
    GLint level,
    void *img
    );
    GLBINDING_API void glGetCompressedTextureImage(GLuint
    texture,
    GLint level, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetCompressedTextureImageEXT(GLuint
    texture,
    GLenum target, GLint
    lod,
    void *img
    );
    GLBINDING_API void glGetCompressedTextureSubImage(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetConvolutionFilter(GLenum
    target,
    GLenum format, GLenum
    type,
    void *image
    );
    GLBINDING_API void glGetConvolutionFilterEXT(GLenum
    target,
    GLenum format, GLenum
    type,
    void *image
    );
    GLBINDING_API void glGetConvolutionParameterfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetConvolutionParameterfvEXT(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetConvolutionParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetConvolutionParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetConvolutionParameterxvOES(GLenum
    target,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API void glGetCoverageModulationTableNV(GLsizei
    bufsize,
    GLfloat *v
    );
    GLBINDING_API GLuint
    glGetDebugMessageLog(GLuint
    count,
    GLsizei bufSize, GLenum
    * sources,
    GLenum *types, GLuint
    * ids,
    GLenum *severities, GLsizei
    * lengths,
    GLchar *messageLog
    );
    GLBINDING_API GLuint
    glGetDebugMessageLogAMD(GLuint
    count,
    GLsizei bufsize, GLenum
    * categories,
    GLuint *severities, GLuint
    * ids,
    GLsizei *lengths, GLchar
    * message);
    GLBINDING_API GLuint
    glGetDebugMessageLogARB(GLuint
    count,
    GLsizei bufSize, GLenum
    * sources,
    GLenum *types, GLuint
    * ids,
    GLenum *severities, GLsizei
    * lengths,
    GLchar *messageLog
    );
    GLBINDING_API void glGetDetailTexFuncSGIS(GLenum
    target,
    GLfloat *points
    );
    GLBINDING_API void glGetDoubleIndexedvEXT(GLenum
    target,
    GLuint index, GLdouble
    * data);
    GLBINDING_API void glGetDoublei_v(GLenum
    target,
    GLuint index, GLdouble
    * data);
    GLBINDING_API void glGetDoublei_vEXT(GLenum
    pname,
    GLuint index, GLdouble
    * params);
    GLBINDING_API void glGetDoublev(GLenum
    pname,
    GLdouble *data
    );
    GLBINDING_API GLenum

    glGetError();

    GLBINDING_API void glGetFenceivNV(GLuint
    fence,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetFinalCombinerInputParameterfvNV(GLenum
    variable,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetFinalCombinerInputParameterivNV(GLenum
    variable,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetFirstPerfQueryIdINTEL(GLuint * queryId);
    GLBINDING_API void glGetFixedvOES(GLenum
    pname,
    GLfixed *params
    );
    GLBINDING_API void glGetFloatIndexedvEXT(GLenum
    target,
    GLuint index, GLfloat
    * data);
    GLBINDING_API void glGetFloati_v(GLenum
    target,
    GLuint index, GLfloat
    * data);
    GLBINDING_API void glGetFloati_vEXT(GLenum
    pname,
    GLuint index, GLfloat
    * params);
    GLBINDING_API void glGetFloatv(GLenum
    pname,
    GLfloat *data
    );
    GLBINDING_API void glGetFogFuncSGIS(GLfloat * points);
    GLBINDING_API GLint
    glGetFragDataIndex(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetFragDataLocation(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetFragDataLocationEXT(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API void glGetFragmentLightfvSGIX(GLenum
    light,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetFragmentLightivSGIX(GLenum
    light,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetFragmentMaterialfvSGIX(GLenum
    face,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetFragmentMaterialivSGIX(GLenum
    face,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetFramebufferAttachmentParameteriv(GLenum
    target,
    GLenum attachment, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetFramebufferAttachmentParameterivEXT(GLenum
    target,
    GLenum attachment, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetFramebufferParameterfvAMD(GLenum
    target,
    GLenum pname, GLuint
    numsamples,
    GLuint pixelindex, GLsizei
    size,
    GLfloat *values
    );
    GLBINDING_API void glGetFramebufferParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetFramebufferParameterivEXT(GLuint
    framebuffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API GLenum

    glGetGraphicsResetStatus();

    GLBINDING_API GLenum

    glGetGraphicsResetStatusARB();

    GLBINDING_API GLhandleARB
    glGetHandleARB(GLenum
    pname);
    GLBINDING_API void glGetHistogram(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type,
    void *values
    );
    GLBINDING_API void glGetHistogramEXT(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type,
    void *values
    );
    GLBINDING_API void glGetHistogramParameterfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetHistogramParameterfvEXT(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetHistogramParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetHistogramParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetHistogramParameterxvOES(GLenum
    target,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API GLuint64
    glGetImageHandleARB(GLuint
    texture,
    GLint level, GLboolean
    layered,
    GLint layer, GLenum
    format);
    GLBINDING_API GLuint64
    glGetImageHandleNV(GLuint
    texture,
    GLint level, GLboolean
    layered,
    GLint layer, GLenum
    format);
    GLBINDING_API void glGetImageTransformParameterfvHP(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetImageTransformParameterivHP(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetInfoLogARB(GLhandleARB
    obj,
    GLsizei maxLength, GLsizei
    * length,
    GLcharARB *infoLog
    );
    GLBINDING_API GLint

    glGetInstrumentsSGIX();

    GLBINDING_API void glGetInteger64i_v(GLenum
    target,
    GLuint index, GLint64
    * data);
    GLBINDING_API void glGetInteger64v(GLenum
    pname,
    GLint64 *data
    );
    GLBINDING_API void glGetIntegerIndexedvEXT(GLenum
    target,
    GLuint index, GLint
    * data);
    GLBINDING_API void glGetIntegeri_v(GLenum
    target,
    GLuint index, GLint
    * data);
    GLBINDING_API void glGetIntegerui64i_vNV(GLenum
    value,
    GLuint index, GLuint64EXT
    * result);
    GLBINDING_API void glGetIntegerui64vNV(GLenum
    value,
    GLuint64EXT *result
    );
    GLBINDING_API void glGetIntegerv(GLenum
    pname,
    GLint *data
    );
    GLBINDING_API void glGetInternalformatSampleivNV(GLenum
    target,
    GLenum internalformat, GLsizei
    samples,
    GLenum pname, GLsizei
    bufSize,
    GLint *params
    );
    GLBINDING_API void glGetInternalformati64v(GLenum
    target,
    GLenum internalformat, GLenum
    pname,
    GLsizei bufSize, GLint64
    * params);
    GLBINDING_API void glGetInternalformativ(GLenum
    target,
    GLenum internalformat, GLenum
    pname,
    GLsizei bufSize, GLint
    * params);
    GLBINDING_API void glGetInvariantBooleanvEXT(GLuint
    id,
    GLenum value, GLboolean
    * data);
    GLBINDING_API void glGetInvariantFloatvEXT(GLuint
    id,
    GLenum value, GLfloat
    * data);
    GLBINDING_API void glGetInvariantIntegervEXT(GLuint
    id,
    GLenum value, GLint
    * data);
    GLBINDING_API void glGetLightfv(GLenum
    light,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetLightiv(GLenum
    light,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetLightxOES(GLenum
    light,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API void glGetListParameterfvSGIX(GLuint
    list,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetListParameterivSGIX(GLuint
    list,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetLocalConstantBooleanvEXT(GLuint
    id,
    GLenum value, GLboolean
    * data);
    GLBINDING_API void glGetLocalConstantFloatvEXT(GLuint
    id,
    GLenum value, GLfloat
    * data);
    GLBINDING_API void glGetLocalConstantIntegervEXT(GLuint
    id,
    GLenum value, GLint
    * data);
    GLBINDING_API void glGetMapAttribParameterfvNV(GLenum
    target,
    GLuint index, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetMapAttribParameterivNV(GLenum
    target,
    GLuint index, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetMapControlPointsNV(GLenum
    target,
    GLuint index, GLenum
    type,
    GLsizei ustride, GLsizei
    vstride,
    GLboolean packed,
    void *points
    );
    GLBINDING_API void glGetMapParameterfvNV(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetMapParameterivNV(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMapdv(GLenum
    target,
    GLenum query, GLdouble
    * v);
    GLBINDING_API void glGetMapfv(GLenum
    target,
    GLenum query, GLfloat
    * v);
    GLBINDING_API void glGetMapiv(GLenum
    target,
    GLenum query, GLint
    * v);
    GLBINDING_API void glGetMapxvOES(GLenum
    target,
    GLenum query, GLfixed
    * v);
    GLBINDING_API void glGetMaterialfv(GLenum
    face,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetMaterialiv(GLenum
    face,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMaterialxOES(GLenum
    face,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glGetMemoryObjectDetachedResourcesuivNV(GLuint
    memory,
    GLenum pname, GLint
    first,
    GLsizei count, GLuint
    * params);
    GLBINDING_API void glGetMemoryObjectParameterivEXT(GLuint
    memoryObject,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMinmax(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type,
    void *values
    );
    GLBINDING_API void glGetMinmaxEXT(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type,
    void *values
    );
    GLBINDING_API void glGetMinmaxParameterfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetMinmaxParameterfvEXT(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetMinmaxParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMinmaxParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMultiTexEnvfvEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetMultiTexEnvivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetMultiTexGendvEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLdouble *params
    );
    GLBINDING_API void glGetMultiTexGenfvEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetMultiTexGenivEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetMultiTexImageEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum format, GLenum
    type,
    void *pixels
    );
    GLBINDING_API void glGetMultiTexLevelParameterfvEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetMultiTexLevelParameterivEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetMultiTexParameterIivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetMultiTexParameterIuivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLuint *params
    );
    GLBINDING_API void glGetMultiTexParameterfvEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetMultiTexParameterivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetMultisamplefv(GLenum
    pname,
    GLuint index, GLfloat
    * val);
    GLBINDING_API void glGetMultisamplefvNV(GLenum
    pname,
    GLuint index, GLfloat
    * val);
    GLBINDING_API void glGetNamedBufferParameteri64v(GLuint
    buffer,
    GLenum pname, GLint64
    * params);
    GLBINDING_API void glGetNamedBufferParameteriv(GLuint
    buffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetNamedBufferParameterivEXT(GLuint
    buffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetNamedBufferParameterui64vNV(GLuint
    buffer,
    GLenum pname, GLuint64EXT
    * params);
    GLBINDING_API void glGetNamedBufferPointerv(GLuint
    buffer,
    GLenum pname,
    void **params
    );
    GLBINDING_API void glGetNamedBufferPointervEXT(GLuint
    buffer,
    GLenum pname,
    void **params
    );
    GLBINDING_API void glGetNamedBufferSubData(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    void *data
    );
    GLBINDING_API void glGetNamedBufferSubDataEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    void *data
    );
    GLBINDING_API void glGetNamedFramebufferAttachmentParameteriv(GLuint
    framebuffer,
    GLenum attachment, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetNamedFramebufferAttachmentParameterivEXT(GLuint
    framebuffer,
    GLenum attachment, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetNamedFramebufferParameterfvAMD(GLuint
    framebuffer,
    GLenum pname, GLuint
    numsamples,
    GLuint pixelindex, GLsizei
    size,
    GLfloat *values
    );
    GLBINDING_API void glGetNamedFramebufferParameteriv(GLuint
    framebuffer,
    GLenum pname, GLint
    * param);
    GLBINDING_API void glGetNamedFramebufferParameterivEXT(GLuint
    framebuffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetNamedProgramLocalParameterIivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLint *params
    );
    GLBINDING_API void glGetNamedProgramLocalParameterIuivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLuint *params
    );
    GLBINDING_API void glGetNamedProgramLocalParameterdvEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLdouble *params
    );
    GLBINDING_API void glGetNamedProgramLocalParameterfvEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLfloat *params
    );
    GLBINDING_API void glGetNamedProgramStringEXT(GLuint
    program,
    GLenum target, GLenum
    pname,
    void *string
    );
    GLBINDING_API void glGetNamedProgramivEXT(GLuint
    program,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetNamedRenderbufferParameteriv(GLuint
    renderbuffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetNamedRenderbufferParameterivEXT(GLuint
    renderbuffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetNamedStringARB(GLint
    namelen,
    const GLchar *name, GLsizei
    bufSize,
    GLint *stringlen, GLchar
    * string);
    GLBINDING_API void glGetNamedStringivARB(GLint
    namelen,
    const GLchar *name, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetNextPerfQueryIdINTEL(GLuint
    queryId,
    GLuint *nextQueryId
    );
    GLBINDING_API void glGetObjectBufferfvATI(GLuint
    buffer,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetObjectBufferivATI(GLuint
    buffer,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetObjectLabel(GLenum
    identifier,
    GLuint name, GLsizei
    bufSize,
    GLsizei *length, GLchar
    * label);
    GLBINDING_API void glGetObjectLabelEXT(GLenum
    type,
    GLuint object, GLsizei
    bufSize,
    GLsizei *length, GLchar
    * label);
    GLBINDING_API void glGetObjectParameterfvARB(GLhandleARB
    obj,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetObjectParameterivAPPLE(GLenum
    objectType,
    GLuint name, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetObjectParameterivARB(GLhandleARB
    obj,
    GLenum pname, GLint
    * params);

    GLBINDING_API void glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);

    GLBINDING_API void glGetOcclusionQueryivNV(GLuint
    id,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetOcclusionQueryuivNV(GLuint
    id,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetPathColorGenfvNV(GLenum
    color,
    GLenum pname, GLfloat
    * value);
    GLBINDING_API void glGetPathColorGenivNV(GLenum
    color,
    GLenum pname, GLint
    * value);
    GLBINDING_API void glGetPathCommandsNV(GLuint
    path,
    GLubyte *commands
    );
    GLBINDING_API void glGetPathCoordsNV(GLuint
    path,
    GLfloat *coords
    );
    GLBINDING_API void glGetPathDashArrayNV(GLuint
    path,
    GLfloat *dashArray
    );
    GLBINDING_API GLfloat
    glGetPathLengthNV(GLuint
    path,
    GLsizei startSegment, GLsizei
    numSegments);

    GLBINDING_API void
    glGetPathMetricRangeNV(PathRenderingMaskNV metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride,
                           GLfloat *metrics);

    GLBINDING_API void
    glGetPathMetricsNV(PathRenderingMaskNV metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void *paths,
                       GLuint pathBase, GLsizei stride, GLfloat *metrics);

    GLBINDING_API void glGetPathParameterfvNV(GLuint
    path,
    GLenum pname, GLfloat
    * value);
    GLBINDING_API void glGetPathParameterivNV(GLuint
    path,
    GLenum pname, GLint
    * value);
    GLBINDING_API void glGetPathSpacingNV(GLenum
    pathListMode,
    GLsizei numPaths, GLenum
    pathNameType,
    const void *paths, GLuint
    pathBase,
    GLfloat advanceScale, GLfloat
    kerningScale,
    GLenum transformType, GLfloat
    * returnedSpacing);
    GLBINDING_API void glGetPathTexGenfvNV(GLenum
    texCoordSet,
    GLenum pname, GLfloat
    * value);
    GLBINDING_API void glGetPathTexGenivNV(GLenum
    texCoordSet,
    GLenum pname, GLint
    * value);
    GLBINDING_API void glGetPerfCounterInfoINTEL(GLuint
    queryId,
    GLuint counterId, GLuint
    counterNameLength,
    GLchar *counterName, GLuint
    counterDescLength,
    GLchar *counterDesc, GLuint
    * counterOffset,
    GLuint *counterDataSize, GLuint
    * counterTypeEnum,
    GLuint *counterDataTypeEnum, GLuint64
    * rawCounterMaxValue);
    GLBINDING_API void glGetPerfMonitorCounterDataAMD(GLuint
    monitor,
    GLenum pname, GLsizei
    dataSize,
    GLuint *data, GLint
    * bytesWritten);
    GLBINDING_API void glGetPerfMonitorCounterInfoAMD(GLuint
    group,
    GLuint counter, GLenum
    pname,
    void *data
    );
    GLBINDING_API void glGetPerfMonitorCounterStringAMD(GLuint
    group,
    GLuint counter, GLsizei
    bufSize,
    GLsizei *length, GLchar
    * counterString);
    GLBINDING_API void glGetPerfMonitorCountersAMD(GLuint
    group,
    GLint *numCounters, GLint
    * maxActiveCounters,
    GLsizei counterSize, GLuint
    * counters);
    GLBINDING_API void glGetPerfMonitorGroupStringAMD(GLuint
    group,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *groupString
    );
    GLBINDING_API void glGetPerfMonitorGroupsAMD(GLint * numGroups, GLsizei
    groupsSize,
    GLuint *groups
    );
    GLBINDING_API void glGetPerfQueryDataINTEL(GLuint
    queryHandle,
    GLuint flags, GLsizei
    dataSize,
    void *data, GLuint
    * bytesWritten);
    GLBINDING_API void glGetPerfQueryIdByNameINTEL(GLchar * queryName, GLuint * queryId);
    GLBINDING_API void glGetPerfQueryInfoINTEL(GLuint
    queryId,
    GLuint queryNameLength, GLchar
    * queryName,
    GLuint *dataSize, GLuint
    * noCounters,
    GLuint *noInstances, GLuint
    * capsMask);
    GLBINDING_API void glGetPixelMapfv(GLenum
    map,
    GLfloat *values
    );
    GLBINDING_API void glGetPixelMapuiv(GLenum
    map,
    GLuint *values
    );
    GLBINDING_API void glGetPixelMapusv(GLenum
    map,
    GLushort *values
    );
    GLBINDING_API void glGetPixelMapxv(GLenum
    map,
    GLint size, GLfixed
    * values);
    GLBINDING_API void glGetPixelTexGenParameterfvSGIS(GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetPixelTexGenParameterivSGIS(GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetPixelTransformParameterfvEXT(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetPixelTransformParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetPointerIndexedvEXT(GLenum
    target,
    GLuint index,
    void **data
    );
    GLBINDING_API void glGetPointeri_vEXT(GLenum
    pname,
    GLuint index,
    void **params
    );
    GLBINDING_API void glGetPointerv(GLenum
    pname,
    void **params
    );
    GLBINDING_API void glGetPointervEXT(GLenum
    pname,
    void **params
    );

    GLBINDING_API void glGetPolygonStipple(GLubyte *mask);

    GLBINDING_API void glGetProgramBinary(GLuint
    program,
    GLsizei bufSize, GLsizei
    * length,
    GLenum *binaryFormat,
    void *binary
    );
    GLBINDING_API void glGetProgramEnvParameterIivNV(GLenum
    target,
    GLuint index, GLint
    * params);
    GLBINDING_API void glGetProgramEnvParameterIuivNV(GLenum
    target,
    GLuint index, GLuint
    * params);
    GLBINDING_API void glGetProgramEnvParameterdvARB(GLenum
    target,
    GLuint index, GLdouble
    * params);
    GLBINDING_API void glGetProgramEnvParameterfvARB(GLenum
    target,
    GLuint index, GLfloat
    * params);
    GLBINDING_API void glGetProgramInfoLog(GLuint
    program,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *infoLog
    );
    GLBINDING_API void glGetProgramInterfaceiv(GLuint
    program,
    GLenum programInterface, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetProgramLocalParameterIivNV(GLenum
    target,
    GLuint index, GLint
    * params);
    GLBINDING_API void glGetProgramLocalParameterIuivNV(GLenum
    target,
    GLuint index, GLuint
    * params);
    GLBINDING_API void glGetProgramLocalParameterdvARB(GLenum
    target,
    GLuint index, GLdouble
    * params);
    GLBINDING_API void glGetProgramLocalParameterfvARB(GLenum
    target,
    GLuint index, GLfloat
    * params);
    GLBINDING_API void glGetProgramNamedParameterdvNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name, GLdouble
    * params);
    GLBINDING_API void glGetProgramNamedParameterfvNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name, GLfloat
    * params);
    GLBINDING_API void glGetProgramParameterdvNV(GLenum
    target,
    GLuint index, GLenum
    pname,
    GLdouble *params
    );
    GLBINDING_API void glGetProgramParameterfvNV(GLenum
    target,
    GLuint index, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetProgramPipelineInfoLog(GLuint
    pipeline,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *infoLog
    );
    GLBINDING_API void glGetProgramPipelineiv(GLuint
    pipeline,
    GLenum pname, GLint
    * params);
    GLBINDING_API GLuint
    glGetProgramResourceIndex(GLuint
    program,
    GLenum programInterface,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetProgramResourceLocation(GLuint
    program,
    GLenum programInterface,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetProgramResourceLocationIndex(GLuint
    program,
    GLenum programInterface,
    const GLchar *name
    );
    GLBINDING_API void glGetProgramResourceName(GLuint
    program,
    GLenum programInterface, GLuint
    index,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *name
    );
    GLBINDING_API void glGetProgramResourcefvNV(GLuint
    program,
    GLenum programInterface, GLuint
    index,
    GLsizei propCount,
    const GLenum *props, GLsizei
    bufSize,
    GLsizei *length, GLfloat
    * params);
    GLBINDING_API void glGetProgramResourceiv(GLuint
    program,
    GLenum programInterface, GLuint
    index,
    GLsizei propCount,
    const GLenum *props, GLsizei
    bufSize,
    GLsizei *length, GLint
    * params);
    GLBINDING_API void glGetProgramStageiv(GLuint
    program,
    GLenum shadertype, GLenum
    pname,
    GLint *values
    );
    GLBINDING_API void glGetProgramStringARB(GLenum
    target,
    GLenum pname,
    void *string
    );
    GLBINDING_API void glGetProgramStringNV(GLuint
    id,
    GLenum pname, GLubyte
    * program);
    GLBINDING_API void glGetProgramSubroutineParameteruivNV(GLenum
    target,
    GLuint index, GLuint
    * param);
    GLBINDING_API void glGetProgramiv(GLuint
    program,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetProgramivARB(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetProgramivNV(GLuint
    id,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetQueryBufferObjecti64v(GLuint
    id,
    GLuint buffer, GLenum
    pname,
    GLintptr offset
    );
    GLBINDING_API void glGetQueryBufferObjectiv(GLuint
    id,
    GLuint buffer, GLenum
    pname,
    GLintptr offset
    );
    GLBINDING_API void glGetQueryBufferObjectui64v(GLuint
    id,
    GLuint buffer, GLenum
    pname,
    GLintptr offset
    );
    GLBINDING_API void glGetQueryBufferObjectuiv(GLuint
    id,
    GLuint buffer, GLenum
    pname,
    GLintptr offset
    );
    GLBINDING_API void glGetQueryIndexediv(GLenum
    target,
    GLuint index, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetQueryObjecti64v(GLuint
    id,
    GLenum pname, GLint64
    * params);
    GLBINDING_API void glGetQueryObjecti64vEXT(GLuint
    id,
    GLenum pname, GLint64
    * params);
    GLBINDING_API void glGetQueryObjectiv(GLuint
    id,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetQueryObjectivARB(GLuint
    id,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetQueryObjectui64v(GLuint
    id,
    GLenum pname, GLuint64
    * params);
    GLBINDING_API void glGetQueryObjectui64vEXT(GLuint
    id,
    GLenum pname, GLuint64
    * params);
    GLBINDING_API void glGetQueryObjectuiv(GLuint
    id,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetQueryObjectuivARB(GLuint
    id,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetQueryiv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetQueryivARB(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetRenderbufferParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetRenderbufferParameterivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetSamplerParameterIiv(GLuint
    sampler,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetSamplerParameterIuiv(GLuint
    sampler,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetSamplerParameterfv(GLuint
    sampler,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetSamplerParameteriv(GLuint
    sampler,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetSemaphoreParameterui64vEXT(GLuint
    semaphore,
    GLenum pname, GLuint64
    * params);
    GLBINDING_API void glGetSeparableFilter(GLenum
    target,
    GLenum format, GLenum
    type,
    void *row,
    void *column,
    void *span
    );
    GLBINDING_API void glGetSeparableFilterEXT(GLenum
    target,
    GLenum format, GLenum
    type,
    void *row,
    void *column,
    void *span
    );
    GLBINDING_API void glGetShaderInfoLog(GLuint
    shader,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *infoLog
    );
    GLBINDING_API void glGetShaderPrecisionFormat(GLenum
    shadertype,
    GLenum precisiontype, GLint
    * range,
    GLint *precision
    );
    GLBINDING_API void glGetShaderSource(GLuint
    shader,
    GLsizei bufSize, GLsizei
    * length,
    GLchar *source
    );
    GLBINDING_API void glGetShaderSourceARB(GLhandleARB
    obj,
    GLsizei maxLength, GLsizei
    * length,
    GLcharARB *source
    );
    GLBINDING_API void glGetShaderiv(GLuint
    shader,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetShadingRateImagePaletteNV(GLuint
    viewport,
    GLuint entry, GLenum
    * rate);
    GLBINDING_API void glGetShadingRateSampleLocationivNV(GLenum
    rate,
    GLuint samples, GLuint
    index,
    GLint *location
    );
    GLBINDING_API void glGetSharpenTexFuncSGIS(GLenum
    target,
    GLfloat *points
    );
    GLBINDING_API GLushort
    glGetStageIndexNV(GLenum
    shadertype);
    GLBINDING_API const GLubyte
    *
    glGetString(GLenum
    name);
    GLBINDING_API const GLubyte
    *
    glGetStringi(GLenum
    name,
    GLuint index
    );
    GLBINDING_API GLuint
    glGetSubroutineIndex(GLuint
    program,
    GLenum shadertype,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetSubroutineUniformLocation(GLuint
    program,
    GLenum shadertype,
    const GLchar *name
    );
    GLBINDING_API void glGetSynciv(GLsync
    sync,
    GLenum pname, GLsizei
    bufSize,
    GLsizei *length, GLint
    * values);
    GLBINDING_API void glGetTexBumpParameterfvATI(GLenum
    pname,
    GLfloat *param
    );
    GLBINDING_API void glGetTexBumpParameterivATI(GLenum
    pname,
    GLint *param
    );
    GLBINDING_API void glGetTexEnvfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetTexEnviv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTexEnvxvOES(GLenum
    target,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API void glGetTexFilterFuncSGIS(GLenum
    target,
    GLenum filter, GLfloat
    * weights);
    GLBINDING_API void glGetTexGendv(GLenum
    coord,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetTexGenfv(GLenum
    coord,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetTexGeniv(GLenum
    coord,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTexGenxvOES(GLenum
    coord,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API void glGetTexImage(GLenum
    target,
    GLint level, GLenum
    format,
    GLenum type,
    void *pixels
    );
    GLBINDING_API void glGetTexLevelParameterfv(GLenum
    target,
    GLint level, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetTexLevelParameteriv(GLenum
    target,
    GLint level, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetTexLevelParameterxvOES(GLenum
    target,
    GLint level, GLenum
    pname,
    GLfixed *params
    );
    GLBINDING_API void glGetTexParameterIiv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTexParameterIivEXT(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTexParameterIuiv(GLenum
    target,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetTexParameterIuivEXT(GLenum
    target,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetTexParameterPointervAPPLE(GLenum
    target,
    GLenum pname,
    void **params
    );
    GLBINDING_API void glGetTexParameterfv(GLenum
    target,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetTexParameteriv(GLenum
    target,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTexParameterxvOES(GLenum
    target,
    GLenum pname, GLfixed
    * params);
    GLBINDING_API GLuint64
    glGetTextureHandleARB(GLuint
    texture);
    GLBINDING_API GLuint64
    glGetTextureHandleNV(GLuint
    texture);
    GLBINDING_API void glGetTextureImage(GLuint
    texture,
    GLint level, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetTextureImageEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum format, GLenum
    type,
    void *pixels
    );
    GLBINDING_API void glGetTextureLevelParameterfv(GLuint
    texture,
    GLint level, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetTextureLevelParameterfvEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetTextureLevelParameteriv(GLuint
    texture,
    GLint level, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetTextureLevelParameterivEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTextureParameterIiv(GLuint
    texture,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTextureParameterIivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetTextureParameterIuiv(GLuint
    texture,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetTextureParameterIuivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLuint *params
    );
    GLBINDING_API void glGetTextureParameterfv(GLuint
    texture,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetTextureParameterfvEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetTextureParameteriv(GLuint
    texture,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetTextureParameterivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API GLuint64
    glGetTextureSamplerHandleARB(GLuint
    texture,
    GLuint sampler
    );
    GLBINDING_API GLuint64
    glGetTextureSamplerHandleNV(GLuint
    texture,
    GLuint sampler
    );
    GLBINDING_API void glGetTextureSubImage(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetTrackMatrixivNV(GLenum
    target,
    GLuint address, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetTransformFeedbackVarying(GLuint
    program,
    GLuint index, GLsizei
    bufSize,
    GLsizei *length, GLsizei
    * size,
    GLenum *type, GLchar
    * name);
    GLBINDING_API void glGetTransformFeedbackVaryingEXT(GLuint
    program,
    GLuint index, GLsizei
    bufSize,
    GLsizei *length, GLsizei
    * size,
    GLenum *type, GLchar
    * name);
    GLBINDING_API void glGetTransformFeedbackVaryingNV(GLuint
    program,
    GLuint index, GLint
    * location);
    GLBINDING_API void glGetTransformFeedbacki64_v(GLuint
    xfb,
    GLenum pname, GLuint
    index,
    GLint64 *param
    );
    GLBINDING_API void glGetTransformFeedbacki_v(GLuint
    xfb,
    GLenum pname, GLuint
    index,
    GLint *param
    );
    GLBINDING_API void glGetTransformFeedbackiv(GLuint
    xfb,
    GLenum pname, GLint
    * param);
    GLBINDING_API GLuint
    glGetUniformBlockIndex(GLuint
    program,
    const GLchar *uniformBlockName
    );
    GLBINDING_API GLint
    glGetUniformBufferSizeEXT(GLuint
    program,
    GLint location
    );
    GLBINDING_API void glGetUniformIndices(GLuint
    program,
    GLsizei uniformCount,
    const GLchar *const *uniformNames, GLuint
    * uniformIndices);
    GLBINDING_API GLint
    glGetUniformLocation(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API GLint
    glGetUniformLocationARB(GLhandleARB
    programObj,
    const GLcharARB *name
    );
    GLBINDING_API GLintptr
    glGetUniformOffsetEXT(GLuint
    program,
    GLint location
    );
    GLBINDING_API void glGetUniformSubroutineuiv(GLenum
    shadertype,
    GLint location, GLuint
    * params);
    GLBINDING_API void glGetUniformdv(GLuint
    program,
    GLint location, GLdouble
    * params);
    GLBINDING_API void glGetUniformfv(GLuint
    program,
    GLint location, GLfloat
    * params);
    GLBINDING_API void glGetUniformfvARB(GLhandleARB
    programObj,
    GLint location, GLfloat
    * params);
    GLBINDING_API void glGetUniformi64vARB(GLuint
    program,
    GLint location, GLint64
    * params);
    GLBINDING_API void glGetUniformi64vNV(GLuint
    program,
    GLint location, GLint64EXT
    * params);
    GLBINDING_API void glGetUniformiv(GLuint
    program,
    GLint location, GLint
    * params);
    GLBINDING_API void glGetUniformivARB(GLhandleARB
    programObj,
    GLint location, GLint
    * params);
    GLBINDING_API void glGetUniformui64vARB(GLuint
    program,
    GLint location, GLuint64
    * params);
    GLBINDING_API void glGetUniformui64vNV(GLuint
    program,
    GLint location, GLuint64EXT
    * params);
    GLBINDING_API void glGetUniformuiv(GLuint
    program,
    GLint location, GLuint
    * params);
    GLBINDING_API void glGetUniformuivEXT(GLuint
    program,
    GLint location, GLuint
    * params);
    GLBINDING_API void glGetUnsignedBytei_vEXT(GLenum
    target,
    GLuint index, GLubyte
    * data);
    GLBINDING_API void glGetUnsignedBytevEXT(GLenum
    pname,
    GLubyte *data
    );
    GLBINDING_API void glGetVariantArrayObjectfvATI(GLuint
    id,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetVariantArrayObjectivATI(GLuint
    id,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVariantBooleanvEXT(GLuint
    id,
    GLenum value, GLboolean
    * data);
    GLBINDING_API void glGetVariantFloatvEXT(GLuint
    id,
    GLenum value, GLfloat
    * data);
    GLBINDING_API void glGetVariantIntegervEXT(GLuint
    id,
    GLenum value, GLint
    * data);
    GLBINDING_API void glGetVariantPointervEXT(GLuint
    id,
    GLenum value,
    void **data
    );
    GLBINDING_API GLint
    glGetVaryingLocationNV(GLuint
    program,
    const GLchar *name
    );
    GLBINDING_API void glGetVertexArrayIndexed64iv(GLuint
    vaobj,
    GLuint index, GLenum
    pname,
    GLint64 *param
    );
    GLBINDING_API void glGetVertexArrayIndexediv(GLuint
    vaobj,
    GLuint index, GLenum
    pname,
    GLint *param
    );
    GLBINDING_API void glGetVertexArrayIntegeri_vEXT(GLuint
    vaobj,
    GLuint index, GLenum
    pname,
    GLint *param
    );
    GLBINDING_API void glGetVertexArrayIntegervEXT(GLuint
    vaobj,
    GLenum pname, GLint
    * param);
    GLBINDING_API void glGetVertexArrayPointeri_vEXT(GLuint
    vaobj,
    GLuint index, GLenum
    pname,
    void **param
    );
    GLBINDING_API void glGetVertexArrayPointervEXT(GLuint
    vaobj,
    GLenum pname,
    void **param
    );
    GLBINDING_API void glGetVertexArrayiv(GLuint
    vaobj,
    GLenum pname, GLint
    * param);
    GLBINDING_API void glGetVertexAttribArrayObjectfvATI(GLuint
    index,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetVertexAttribArrayObjectivATI(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVertexAttribIiv(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVertexAttribIivEXT(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVertexAttribIuiv(GLuint
    index,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetVertexAttribIuivEXT(GLuint
    index,
    GLenum pname, GLuint
    * params);
    GLBINDING_API void glGetVertexAttribLdv(GLuint
    index,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetVertexAttribLdvEXT(GLuint
    index,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetVertexAttribLi64vNV(GLuint
    index,
    GLenum pname, GLint64EXT
    * params);
    GLBINDING_API void glGetVertexAttribLui64vARB(GLuint
    index,
    GLenum pname, GLuint64EXT
    * params);
    GLBINDING_API void glGetVertexAttribLui64vNV(GLuint
    index,
    GLenum pname, GLuint64EXT
    * params);
    GLBINDING_API void glGetVertexAttribPointerv(GLuint
    index,
    GLenum pname,
    void **pointer
    );
    GLBINDING_API void glGetVertexAttribPointervARB(GLuint
    index,
    GLenum pname,
    void **pointer
    );
    GLBINDING_API void glGetVertexAttribPointervNV(GLuint
    index,
    GLenum pname,
    void **pointer
    );
    GLBINDING_API void glGetVertexAttribdv(GLuint
    index,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetVertexAttribdvARB(GLuint
    index,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetVertexAttribdvNV(GLuint
    index,
    GLenum pname, GLdouble
    * params);
    GLBINDING_API void glGetVertexAttribfv(GLuint
    index,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetVertexAttribfvARB(GLuint
    index,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetVertexAttribfvNV(GLuint
    index,
    GLenum pname, GLfloat
    * params);
    GLBINDING_API void glGetVertexAttribiv(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVertexAttribivARB(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVertexAttribivNV(GLuint
    index,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVideoCaptureStreamdvNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    GLdouble *params
    );
    GLBINDING_API void glGetVideoCaptureStreamfvNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    GLfloat *params
    );
    GLBINDING_API void glGetVideoCaptureStreamivNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glGetVideoCaptureivNV(GLuint
    video_capture_slot,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVideoi64vNV(GLuint
    video_slot,
    GLenum pname, GLint64EXT
    * params);
    GLBINDING_API void glGetVideoivNV(GLuint
    video_slot,
    GLenum pname, GLint
    * params);
    GLBINDING_API void glGetVideoui64vNV(GLuint
    video_slot,
    GLenum pname, GLuint64EXT
    * params);
    GLBINDING_API void glGetVideouivNV(GLuint
    video_slot,
    GLenum pname, GLuint
    * params);
    GLBINDING_API GLVULKANPROCNV

    glGetVkProcAddrNV(const GLchar *name);

    GLBINDING_API void glGetnColorTable(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei bufSize,
    void *table
    );
    GLBINDING_API void glGetnColorTableARB(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei bufSize,
    void *table
    );
    GLBINDING_API void glGetnCompressedTexImage(GLenum
    target,
    GLint lod, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetnCompressedTexImageARB(GLenum
    target,
    GLint lod, GLsizei
    bufSize,
    void *img
    );
    GLBINDING_API void glGetnConvolutionFilter(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei bufSize,
    void *image
    );
    GLBINDING_API void glGetnConvolutionFilterARB(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei bufSize,
    void *image
    );
    GLBINDING_API void glGetnHistogram(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *values
    );
    GLBINDING_API void glGetnHistogramARB(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *values
    );
    GLBINDING_API void glGetnMapdv(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLdouble *v
    );
    GLBINDING_API void glGetnMapdvARB(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLdouble *v
    );
    GLBINDING_API void glGetnMapfv(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLfloat *v
    );
    GLBINDING_API void glGetnMapfvARB(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLfloat *v
    );
    GLBINDING_API void glGetnMapiv(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLint *v
    );
    GLBINDING_API void glGetnMapivARB(GLenum
    target,
    GLenum query, GLsizei
    bufSize,
    GLint *v
    );
    GLBINDING_API void glGetnMinmax(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *values
    );
    GLBINDING_API void glGetnMinmaxARB(GLenum
    target,
    GLboolean reset, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *values
    );
    GLBINDING_API void glGetnPixelMapfv(GLenum
    map,
    GLsizei bufSize, GLfloat
    * values);
    GLBINDING_API void glGetnPixelMapfvARB(GLenum
    map,
    GLsizei bufSize, GLfloat
    * values);
    GLBINDING_API void glGetnPixelMapuiv(GLenum
    map,
    GLsizei bufSize, GLuint
    * values);
    GLBINDING_API void glGetnPixelMapuivARB(GLenum
    map,
    GLsizei bufSize, GLuint
    * values);
    GLBINDING_API void glGetnPixelMapusv(GLenum
    map,
    GLsizei bufSize, GLushort
    * values);
    GLBINDING_API void glGetnPixelMapusvARB(GLenum
    map,
    GLsizei bufSize, GLushort
    * values);
    GLBINDING_API void glGetnPolygonStipple(GLsizei
    bufSize,
    GLubyte *pattern
    );
    GLBINDING_API void glGetnPolygonStippleARB(GLsizei
    bufSize,
    GLubyte *pattern
    );
    GLBINDING_API void glGetnSeparableFilter(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei rowBufSize,
    void *row, GLsizei
    columnBufSize,
    void *column,
    void *span
    );
    GLBINDING_API void glGetnSeparableFilterARB(GLenum
    target,
    GLenum format, GLenum
    type,
    GLsizei rowBufSize,
    void *row, GLsizei
    columnBufSize,
    void *column,
    void *span
    );
    GLBINDING_API void glGetnTexImage(GLenum
    target,
    GLint level, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *pixels
    );
    GLBINDING_API void glGetnTexImageARB(GLenum
    target,
    GLint level, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *img
    );
    GLBINDING_API void glGetnUniformdv(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLdouble *params
    );
    GLBINDING_API void glGetnUniformdvARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLdouble *params
    );
    GLBINDING_API void glGetnUniformfv(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLfloat *params
    );
    GLBINDING_API void glGetnUniformfvARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLfloat *params
    );
    GLBINDING_API void glGetnUniformi64vARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLint64 *params
    );
    GLBINDING_API void glGetnUniformiv(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLint *params
    );
    GLBINDING_API void glGetnUniformivARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLint *params
    );
    GLBINDING_API void glGetnUniformui64vARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLuint64 *params
    );
    GLBINDING_API void glGetnUniformuiv(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLuint *params
    );
    GLBINDING_API void glGetnUniformuivARB(GLuint
    program,
    GLint location, GLsizei
    bufSize,
    GLuint *params
    );

    GLBINDING_API void glGlobalAlphaFactorbSUN(GLbyte factor);

    GLBINDING_API void glGlobalAlphaFactordSUN(GLdouble
    factor);
    GLBINDING_API void glGlobalAlphaFactorfSUN(GLfloat
    factor);
    GLBINDING_API void glGlobalAlphaFactoriSUN(GLint
    factor);

    GLBINDING_API void glGlobalAlphaFactorsSUN(GLshort factor);

    GLBINDING_API void glGlobalAlphaFactorubSUN(GLubyte
    factor);
    GLBINDING_API void glGlobalAlphaFactoruiSUN(GLuint
    factor);
    GLBINDING_API void glGlobalAlphaFactorusSUN(GLushort
    factor);

    GLBINDING_API void glHint(GLenum
    target,
    GLenum mode
    );
    GLBINDING_API void glHintPGI(GLenum
    target,
    GLint mode
    );
    GLBINDING_API void glHistogram(GLenum
    target,
    GLsizei width, GLenum
    internalformat,
    GLboolean sink
    );
    GLBINDING_API void glHistogramEXT(GLenum
    target,
    GLsizei width, GLenum
    internalformat,
    GLboolean sink
    );

    GLBINDING_API void glIglooInterfaceSGIX(GLenum
    pname,
    const void *params
    );
    GLBINDING_API void glImageTransformParameterfHP(GLenum
    target,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glImageTransformParameterfvHP(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glImageTransformParameteriHP(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glImageTransformParameterivHP(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glImportMemoryFdEXT(GLuint
    memory,
    GLuint64 size, GLenum
    handleType,
    GLint fd
    );
    GLBINDING_API void glImportMemoryWin32HandleEXT(GLuint
    memory,
    GLuint64 size, GLenum
    handleType,
    void *handle
    );
    GLBINDING_API void glImportMemoryWin32NameEXT(GLuint
    memory,
    GLuint64 size, GLenum
    handleType,
    const void *name
    );
    GLBINDING_API void glImportSemaphoreFdEXT(GLuint
    semaphore,
    GLenum handleType, GLint
    fd);
    GLBINDING_API void glImportSemaphoreWin32HandleEXT(GLuint
    semaphore,
    GLenum handleType,
    void *handle
    );
    GLBINDING_API void glImportSemaphoreWin32NameEXT(GLuint
    semaphore,
    GLenum handleType,
    const void *name
    );
    GLBINDING_API GLsync
    glImportSyncEXT(GLenum
    external_sync_type,
    GLintptr external_sync, UnusedMask
    flags);
    GLBINDING_API void glIndexFormatNV(GLenum
    type,
    GLsizei stride
    );
    GLBINDING_API void glIndexFuncEXT(GLenum
    func,
    GLclampf ref
    );
    GLBINDING_API void glIndexMask(GLuint
    mask);
    GLBINDING_API void glIndexMaterialEXT(GLenum
    face,
    GLenum mode
    );
    GLBINDING_API void glIndexPointer(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glIndexPointerEXT(GLenum
    type,
    GLsizei stride, GLsizei
    count,
    const void *pointer
    );
    GLBINDING_API void glIndexPointerListIBM(GLenum
    type,
    GLint stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glIndexd(GLdouble
    c);

    GLBINDING_API void glIndexdv(const GLdouble *c);

    GLBINDING_API void glIndexf(GLfloat
    c);

    GLBINDING_API void glIndexfv(const GLfloat *c);

    GLBINDING_API void glIndexi(GLint
    c);

    GLBINDING_API void glIndexiv(const GLint *c);

    GLBINDING_API void glIndexs(GLshort c);

    GLBINDING_API void glIndexsv(const GLshort *c);

    GLBINDING_API void glIndexub(GLubyte
    c);

    GLBINDING_API void glIndexubv(const GLubyte *c);

    GLBINDING_API void glIndexxOES(GLfixed
    component);

    GLBINDING_API void glIndexxvOES(const GLfixed *component);

    GLBINDING_API void glInitNames();

    GLBINDING_API void glInsertComponentEXT(GLuint
    res,
    GLuint src, GLuint
    num);
    GLBINDING_API void glInsertEventMarkerEXT(GLsizei
    length,
    const GLchar *marker
    );
    GLBINDING_API void glInstrumentsBufferSGIX(GLsizei
    size,
    GLint *buffer
    );
    GLBINDING_API void glInterleavedArrays(GLenum
    format,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glInterpolatePathsNV(GLuint
    resultPath,
    GLuint pathA, GLuint
    pathB,
    GLfloat weight
    );
    GLBINDING_API void glInvalidateBufferData(GLuint
    buffer);
    GLBINDING_API void glInvalidateBufferSubData(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    length);
    GLBINDING_API void glInvalidateFramebuffer(GLenum
    target,
    GLsizei numAttachments,
    const GLenum *attachments
    );
    GLBINDING_API void glInvalidateNamedFramebufferData(GLuint
    framebuffer,
    GLsizei numAttachments,
    const GLenum *attachments
    );
    GLBINDING_API void glInvalidateNamedFramebufferSubData(GLuint
    framebuffer,
    GLsizei numAttachments,
    const GLenum *attachments, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glInvalidateSubFramebuffer(GLenum
    target,
    GLsizei numAttachments,
    const GLenum *attachments, GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glInvalidateTexImage(GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glInvalidateTexSubImage(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth
    );
    GLBINDING_API GLboolean
    glIsAsyncMarkerSGIX(GLuint
    marker);
    GLBINDING_API GLboolean
    glIsBuffer(GLuint
    buffer);
    GLBINDING_API GLboolean
    glIsBufferARB(GLuint
    buffer);
    GLBINDING_API GLboolean
    glIsBufferResidentNV(GLenum
    target);
    GLBINDING_API GLboolean
    glIsCommandListNV(GLuint
    list);
    GLBINDING_API GLboolean
    glIsEnabled(GLenum
    cap);
    GLBINDING_API GLboolean
    glIsEnabledIndexedEXT(GLenum
    target,
    GLuint index
    );
    GLBINDING_API GLboolean
    glIsEnabledi(GLenum
    target,
    GLuint index
    );
    GLBINDING_API GLboolean
    glIsFenceAPPLE(GLuint
    fence);
    GLBINDING_API GLboolean
    glIsFenceNV(GLuint
    fence);
    GLBINDING_API GLboolean
    glIsFramebuffer(GLuint
    framebuffer);
    GLBINDING_API GLboolean
    glIsFramebufferEXT(GLuint
    framebuffer);
    GLBINDING_API GLboolean
    glIsImageHandleResidentARB(GLuint64
    handle);
    GLBINDING_API GLboolean
    glIsImageHandleResidentNV(GLuint64
    handle);
    GLBINDING_API GLboolean
    glIsList(GLuint
    list);
    GLBINDING_API GLboolean
    glIsMemoryObjectEXT(GLuint
    memoryObject);
    GLBINDING_API GLboolean
    glIsNameAMD(GLenum
    identifier,
    GLuint name
    );
    GLBINDING_API GLboolean
    glIsNamedBufferResidentNV(GLuint
    buffer);
    GLBINDING_API GLboolean
    glIsNamedStringARB(GLint
    namelen,
    const GLchar *name
    );
    GLBINDING_API GLboolean
    glIsObjectBufferATI(GLuint
    buffer);
    GLBINDING_API GLboolean
    glIsOcclusionQueryNV(GLuint
    id);
    GLBINDING_API GLboolean
    glIsPathNV(GLuint
    path);
    GLBINDING_API GLboolean
    glIsPointInFillPathNV(GLuint
    path,
    GLuint mask, GLfloat
    x,
    GLfloat y
    );
    GLBINDING_API GLboolean
    glIsPointInStrokePathNV(GLuint
    path,
    GLfloat x, GLfloat
    y);
    GLBINDING_API GLboolean
    glIsProgram(GLuint
    program);
    GLBINDING_API GLboolean
    glIsProgramARB(GLuint
    program);
    GLBINDING_API GLboolean
    glIsProgramNV(GLuint
    id);
    GLBINDING_API GLboolean
    glIsProgramPipeline(GLuint
    pipeline);
    GLBINDING_API GLboolean
    glIsQuery(GLuint
    id);
    GLBINDING_API GLboolean
    glIsQueryARB(GLuint
    id);
    GLBINDING_API GLboolean
    glIsRenderbuffer(GLuint
    renderbuffer);
    GLBINDING_API GLboolean
    glIsRenderbufferEXT(GLuint
    renderbuffer);
    GLBINDING_API GLboolean
    glIsSampler(GLuint
    sampler);
    GLBINDING_API GLboolean
    glIsSemaphoreEXT(GLuint
    semaphore);
    GLBINDING_API GLboolean
    glIsShader(GLuint
    shader);
    GLBINDING_API GLboolean
    glIsStateNV(GLuint
    state);
    GLBINDING_API GLboolean
    glIsSync(GLsync
    sync);
    GLBINDING_API GLboolean
    glIsTexture(GLuint
    texture);
    GLBINDING_API GLboolean
    glIsTextureEXT(GLuint
    texture);
    GLBINDING_API GLboolean
    glIsTextureHandleResidentARB(GLuint64
    handle);
    GLBINDING_API GLboolean
    glIsTextureHandleResidentNV(GLuint64
    handle);
    GLBINDING_API GLboolean
    glIsTransformFeedback(GLuint
    id);
    GLBINDING_API GLboolean
    glIsTransformFeedbackNV(GLuint
    id);
    GLBINDING_API GLboolean
    glIsVariantEnabledEXT(GLuint
    id,
    GLenum cap
    );
    GLBINDING_API GLboolean
    glIsVertexArray(GLuint
    array);
    GLBINDING_API GLboolean
    glIsVertexArrayAPPLE(GLuint
    array);
    GLBINDING_API GLboolean
    glIsVertexAttribEnabledAPPLE(GLuint
    index,
    GLenum pname
    );


    GLBINDING_API void glLGPUCopyImageSubDataNVX(GLuint
    sourceGpu,
    GLbitfield destinationGpuMask, GLuint
    srcName,
    GLenum srcTarget, GLint
    srcLevel,
    GLint srcX, GLint
    srxY,
    GLint srcZ, GLuint
    dstName,
    GLenum dstTarget, GLint
    dstLevel,
    GLint dstX, GLint
    dstY,
    GLint dstZ, GLsizei
    width,
    GLsizei height, GLsizei
    depth);

    GLBINDING_API void glLGPUInterlockNVX();

    GLBINDING_API void
    glLGPUNamedBufferSubDataNVX(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);

    GLBINDING_API void glLabelObjectEXT(GLenum
    type,
    GLuint object, GLsizei
    length,
    const GLchar *label
    );
    GLBINDING_API void glLightEnviSGIX(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glLightModelf(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glLightModelfv(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glLightModeli(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glLightModeliv(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glLightModelxOES(GLenum
    pname,
    GLfixed param
    );
    GLBINDING_API void glLightModelxvOES(GLenum
    pname,
    const GLfixed *param
    );
    GLBINDING_API void glLightf(GLenum
    light,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glLightfv(GLenum
    light,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glLighti(GLenum
    light,
    GLenum pname, GLint
    param);
    GLBINDING_API void glLightiv(GLenum
    light,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glLightxOES(GLenum
    light,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glLightxvOES(GLenum
    light,
    GLenum pname,
    const GLfixed *params
    );
    GLBINDING_API void glLineStipple(GLint
    factor,
    GLushort pattern
    );
    GLBINDING_API void glLineWidth(GLfloat
    width);
    GLBINDING_API void glLineWidthxOES(GLfixed
    width);
    GLBINDING_API void glLinkProgram(GLuint
    program);
    GLBINDING_API void glLinkProgramARB(GLhandleARB
    programObj);
    GLBINDING_API void glListBase(GLuint
    base);
    GLBINDING_API void glListDrawCommandsStatesClientNV(GLuint
    list,
    GLuint segment,
    const void **indirects,
    const GLsizei *sizes,
    const GLuint *states,
    const GLuint *fbos, GLuint
    count);
    GLBINDING_API void glListParameterfSGIX(GLuint
    list,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glListParameterfvSGIX(GLuint
    list,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glListParameteriSGIX(GLuint
    list,
    GLenum pname, GLint
    param);
    GLBINDING_API void glListParameterivSGIX(GLuint
    list,
    GLenum pname,
    const GLint *params
    );

    GLBINDING_API void glLoadIdentity();

    GLBINDING_API void glLoadIdentityDeformationMapSGIX(FfdMaskSGIX mask);

    GLBINDING_API void glLoadMatrixd(const GLdouble *m);

    GLBINDING_API void glLoadMatrixf(const GLfloat *m);

    GLBINDING_API void glLoadMatrixxOES(const GLfixed *m);

    GLBINDING_API void glLoadName(GLuint
    name);
    GLBINDING_API void glLoadProgramNV(GLenum
    target,
    GLuint id, GLsizei
    len,
    const GLubyte *program
    );

    GLBINDING_API void glLoadTransposeMatrixd(const GLdouble *m);

    GLBINDING_API void glLoadTransposeMatrixdARB(const GLdouble *m);

    GLBINDING_API void glLoadTransposeMatrixf(const GLfloat *m);

    GLBINDING_API void glLoadTransposeMatrixfARB(const GLfloat *m);

    GLBINDING_API void glLoadTransposeMatrixxOES(const GLfixed *m);

    GLBINDING_API void glLockArraysEXT(GLint
    first,
    GLsizei count
    );
    GLBINDING_API void glLogicOp(GLenum
    opcode);

    GLBINDING_API void glMakeBufferNonResidentNV(GLenum
    target);
    GLBINDING_API void glMakeBufferResidentNV(GLenum
    target,
    GLenum access
    );
    GLBINDING_API void glMakeImageHandleNonResidentARB(GLuint64
    handle);
    GLBINDING_API void glMakeImageHandleNonResidentNV(GLuint64
    handle);
    GLBINDING_API void glMakeImageHandleResidentARB(GLuint64
    handle,
    GLenum access
    );
    GLBINDING_API void glMakeImageHandleResidentNV(GLuint64
    handle,
    GLenum access
    );
    GLBINDING_API void glMakeNamedBufferNonResidentNV(GLuint
    buffer);
    GLBINDING_API void glMakeNamedBufferResidentNV(GLuint
    buffer,
    GLenum access
    );
    GLBINDING_API void glMakeTextureHandleNonResidentARB(GLuint64
    handle);
    GLBINDING_API void glMakeTextureHandleNonResidentNV(GLuint64
    handle);
    GLBINDING_API void glMakeTextureHandleResidentARB(GLuint64
    handle);
    GLBINDING_API void glMakeTextureHandleResidentNV(GLuint64
    handle);
    GLBINDING_API void glMap1d(GLenum
    target,
    GLdouble u1, GLdouble
    u2,
    GLint stride, GLint
    order,
    const GLdouble *points
    );
    GLBINDING_API void glMap1f(GLenum
    target,
    GLfloat u1, GLfloat
    u2,
    GLint stride, GLint
    order,
    const GLfloat *points
    );
    GLBINDING_API void glMap1xOES(GLenum
    target,
    GLfixed u1, GLfixed
    u2,
    GLint stride, GLint
    order,
    GLfixed points
    );
    GLBINDING_API void glMap2d(GLenum
    target,
    GLdouble u1, GLdouble
    u2,
    GLint ustride, GLint
    uorder,
    GLdouble v1, GLdouble
    v2,
    GLint vstride, GLint
    vorder,
    const GLdouble *points
    );
    GLBINDING_API void glMap2f(GLenum
    target,
    GLfloat u1, GLfloat
    u2,
    GLint ustride, GLint
    uorder,
    GLfloat v1, GLfloat
    v2,
    GLint vstride, GLint
    vorder,
    const GLfloat *points
    );
    GLBINDING_API void glMap2xOES(GLenum
    target,
    GLfixed u1, GLfixed
    u2,
    GLint ustride, GLint
    uorder,
    GLfixed v1, GLfixed
    v2,
    GLint vstride, GLint
    vorder,
    GLfixed points
    );
    GLBINDING_API void *glMapBuffer(GLenum
    target,
    GLenum access
    );
    GLBINDING_API void *glMapBufferARB(GLenum
    target,
    GLenum access
    );
    GLBINDING_API void *glMapBufferRange(GLenum
    target,
    GLintptr offset, GLsizeiptr
    length,
    MapBufferAccessMask access
    );
    GLBINDING_API void glMapControlPointsNV(GLenum
    target,
    GLuint index, GLenum
    type,
    GLsizei ustride, GLsizei
    vstride,
    GLint uorder, GLint
    vorder,
    GLboolean packed,
    const void *points
    );
    GLBINDING_API void glMapGrid1d(GLint
    un,
    GLdouble u1, GLdouble
    u2);
    GLBINDING_API void glMapGrid1f(GLint
    un,
    GLfloat u1, GLfloat
    u2);
    GLBINDING_API void glMapGrid1xOES(GLint
    n,
    GLfixed u1, GLfixed
    u2);
    GLBINDING_API void glMapGrid2d(GLint
    un,
    GLdouble u1, GLdouble
    u2,
    GLint vn, GLdouble
    v1,
    GLdouble v2
    );
    GLBINDING_API void glMapGrid2f(GLint
    un,
    GLfloat u1, GLfloat
    u2,
    GLint vn, GLfloat
    v1,
    GLfloat v2
    );
    GLBINDING_API void glMapGrid2xOES(GLint
    n,
    GLfixed u1, GLfixed
    u2,
    GLfixed v1, GLfixed
    v2);
    GLBINDING_API void *glMapNamedBuffer(GLuint
    buffer,
    GLenum access
    );
    GLBINDING_API void *glMapNamedBufferEXT(GLuint
    buffer,
    GLenum access
    );
    GLBINDING_API void *glMapNamedBufferRange(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    length,
    BufferAccessMask access
    );
    GLBINDING_API void *glMapNamedBufferRangeEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    length,
    MapBufferAccessMask access
    );
    GLBINDING_API void *glMapObjectBufferATI(GLuint
    buffer);
    GLBINDING_API void glMapParameterfvNV(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glMapParameterivNV(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void *glMapTexture2DINTEL(GLuint
    texture,
    GLint level, BufferAccessMask
    access,
    GLint *stride, GLenum
    * layout);
    GLBINDING_API void glMapVertexAttrib1dAPPLE(GLuint
    index,
    GLuint size, GLdouble
    u1,
    GLdouble u2, GLint
    stride,
    GLint order,
    const GLdouble *points
    );
    GLBINDING_API void glMapVertexAttrib1fAPPLE(GLuint
    index,
    GLuint size, GLfloat
    u1,
    GLfloat u2, GLint
    stride,
    GLint order,
    const GLfloat *points
    );
    GLBINDING_API void glMapVertexAttrib2dAPPLE(GLuint
    index,
    GLuint size, GLdouble
    u1,
    GLdouble u2, GLint
    ustride,
    GLint uorder, GLdouble
    v1,
    GLdouble v2, GLint
    vstride,
    GLint vorder,
    const GLdouble *points
    );
    GLBINDING_API void glMapVertexAttrib2fAPPLE(GLuint
    index,
    GLuint size, GLfloat
    u1,
    GLfloat u2, GLint
    ustride,
    GLint uorder, GLfloat
    v1,
    GLfloat v2, GLint
    vstride,
    GLint vorder,
    const GLfloat *points
    );
    GLBINDING_API void glMaterialf(GLenum
    face,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glMaterialfv(GLenum
    face,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glMateriali(GLenum
    face,
    GLenum pname, GLint
    param);
    GLBINDING_API void glMaterialiv(GLenum
    face,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glMaterialxOES(GLenum
    face,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glMaterialxvOES(GLenum
    face,
    GLenum pname,
    const GLfixed *param
    );
    GLBINDING_API void glMatrixFrustumEXT(GLenum
    mode,
    GLdouble left, GLdouble
    right,
    GLdouble bottom, GLdouble
    top,
    GLdouble zNear, GLdouble
    zFar);
    GLBINDING_API void glMatrixIndexPointerARB(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glMatrixIndexubvARB(GLint
    size,
    const GLubyte *indices
    );
    GLBINDING_API void glMatrixIndexuivARB(GLint
    size,
    const GLuint *indices
    );
    GLBINDING_API void glMatrixIndexusvARB(GLint
    size,
    const GLushort *indices
    );
    GLBINDING_API void glMatrixLoad3x2fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixLoad3x3fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixLoadIdentityEXT(GLenum
    mode);
    GLBINDING_API void glMatrixLoadTranspose3x3fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixLoadTransposedEXT(GLenum
    mode,
    const GLdouble *m
    );
    GLBINDING_API void glMatrixLoadTransposefEXT(GLenum
    mode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixLoaddEXT(GLenum
    mode,
    const GLdouble *m
    );
    GLBINDING_API void glMatrixLoadfEXT(GLenum
    mode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixMode(GLenum
    mode);
    GLBINDING_API void glMatrixMult3x2fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixMult3x3fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixMultTranspose3x3fNV(GLenum
    matrixMode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixMultTransposedEXT(GLenum
    mode,
    const GLdouble *m
    );
    GLBINDING_API void glMatrixMultTransposefEXT(GLenum
    mode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixMultdEXT(GLenum
    mode,
    const GLdouble *m
    );
    GLBINDING_API void glMatrixMultfEXT(GLenum
    mode,
    const GLfloat *m
    );
    GLBINDING_API void glMatrixOrthoEXT(GLenum
    mode,
    GLdouble left, GLdouble
    right,
    GLdouble bottom, GLdouble
    top,
    GLdouble zNear, GLdouble
    zFar);
    GLBINDING_API void glMatrixPopEXT(GLenum
    mode);
    GLBINDING_API void glMatrixPushEXT(GLenum
    mode);
    GLBINDING_API void glMatrixRotatedEXT(GLenum
    mode,
    GLdouble angle, GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glMatrixRotatefEXT(GLenum
    mode,
    GLfloat angle, GLfloat
    x,
    GLfloat y, GLfloat
    z);
    GLBINDING_API void glMatrixScaledEXT(GLenum
    mode,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glMatrixScalefEXT(GLenum
    mode,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glMatrixTranslatedEXT(GLenum
    mode,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glMatrixTranslatefEXT(GLenum
    mode,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glMaxShaderCompilerThreadsARB(GLuint
    count);
    GLBINDING_API void glMaxShaderCompilerThreadsKHR(GLuint
    count);

    GLBINDING_API void glMemoryBarrier(MemoryBarrierMask barriers);

    GLBINDING_API void glMemoryBarrierByRegion(MemoryBarrierMask barriers);

    GLBINDING_API void glMemoryBarrierEXT(MemoryBarrierMask barriers);

    GLBINDING_API void glMemoryObjectParameterivEXT(GLuint
    memoryObject,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glMinSampleShading(GLfloat
    value);
    GLBINDING_API void glMinSampleShadingARB(GLfloat
    value);
    GLBINDING_API void glMinmax(GLenum
    target,
    GLenum internalformat, GLboolean
    sink);
    GLBINDING_API void glMinmaxEXT(GLenum
    target,
    GLenum internalformat, GLboolean
    sink);

    GLBINDING_API void glMultMatrixd(const GLdouble *m);

    GLBINDING_API void glMultMatrixf(const GLfloat *m);

    GLBINDING_API void glMultMatrixxOES(const GLfixed *m);

    GLBINDING_API void glMultTransposeMatrixd(const GLdouble *m);

    GLBINDING_API void glMultTransposeMatrixdARB(const GLdouble *m);

    GLBINDING_API void glMultTransposeMatrixf(const GLfloat *m);

    GLBINDING_API void glMultTransposeMatrixfARB(const GLfloat *m);

    GLBINDING_API void glMultTransposeMatrixxOES(const GLfixed *m);

    GLBINDING_API void glMultiDrawArrays(GLenum
    mode,
    const GLint *first,
    const GLsizei *count, GLsizei
    drawcount);
    GLBINDING_API void glMultiDrawArraysEXT(GLenum
    mode,
    const GLint *first,
    const GLsizei *count, GLsizei
    primcount);
    GLBINDING_API void glMultiDrawArraysIndirect(GLenum
    mode,
    const void *indirect, GLsizei
    drawcount,
    GLsizei stride
    );
    GLBINDING_API void glMultiDrawArraysIndirectAMD(GLenum
    mode,
    const void *indirect, GLsizei
    primcount,
    GLsizei stride
    );
    GLBINDING_API void glMultiDrawArraysIndirectBindlessCountNV(GLenum
    mode,
    const void *indirect, GLsizei
    drawCount,
    GLsizei maxDrawCount, GLsizei
    stride,
    GLint vertexBufferCount
    );
    GLBINDING_API void glMultiDrawArraysIndirectBindlessNV(GLenum
    mode,
    const void *indirect, GLsizei
    drawCount,
    GLsizei stride, GLint
    vertexBufferCount);
    GLBINDING_API void glMultiDrawArraysIndirectCount(GLenum
    mode,
    const void *indirect, GLintptr
    drawcount,
    GLsizei maxdrawcount, GLsizei
    stride);
    GLBINDING_API void glMultiDrawArraysIndirectCountARB(GLenum
    mode,
    const void *indirect, GLintptr
    drawcount,
    GLsizei maxdrawcount, GLsizei
    stride);
    GLBINDING_API void glMultiDrawElementArrayAPPLE(GLenum
    mode,
    const GLint *first,
    const GLsizei *count, GLsizei
    primcount);
    GLBINDING_API void glMultiDrawElements(GLenum
    mode,
    const GLsizei *count, GLenum
    type,
    const void *const *indices, GLsizei
    drawcount);
    GLBINDING_API void glMultiDrawElementsBaseVertex(GLenum
    mode,
    const GLsizei *count, GLenum
    type,
    const void *const *indices, GLsizei
    drawcount,
    const GLint *basevertex
    );
    GLBINDING_API void glMultiDrawElementsEXT(GLenum
    mode,
    const GLsizei *count, GLenum
    type,
    const void *const *indices, GLsizei
    primcount);
    GLBINDING_API void glMultiDrawElementsIndirect(GLenum
    mode,
    GLenum type,
    const void *indirect, GLsizei
    drawcount,
    GLsizei stride
    );
    GLBINDING_API void glMultiDrawElementsIndirectAMD(GLenum
    mode,
    GLenum type,
    const void *indirect, GLsizei
    primcount,
    GLsizei stride
    );
    GLBINDING_API void glMultiDrawElementsIndirectBindlessCountNV(GLenum
    mode,
    GLenum type,
    const void *indirect, GLsizei
    drawCount,
    GLsizei maxDrawCount, GLsizei
    stride,
    GLint vertexBufferCount
    );
    GLBINDING_API void glMultiDrawElementsIndirectBindlessNV(GLenum
    mode,
    GLenum type,
    const void *indirect, GLsizei
    drawCount,
    GLsizei stride, GLint
    vertexBufferCount);
    GLBINDING_API void glMultiDrawElementsIndirectCount(GLenum
    mode,
    GLenum type,
    const void *indirect, GLintptr
    drawcount,
    GLsizei maxdrawcount, GLsizei
    stride);
    GLBINDING_API void glMultiDrawElementsIndirectCountARB(GLenum
    mode,
    GLenum type,
    const void *indirect, GLintptr
    drawcount,
    GLsizei maxdrawcount, GLsizei
    stride);
    GLBINDING_API void glMultiDrawMeshTasksIndirectCountNV(GLintptr
    indirect,
    GLintptr drawcount, GLsizei
    maxdrawcount,
    GLsizei stride
    );
    GLBINDING_API void glMultiDrawMeshTasksIndirectNV(GLintptr
    indirect,
    GLsizei drawcount, GLsizei
    stride);
    GLBINDING_API void glMultiDrawRangeElementArrayAPPLE(GLenum
    mode,
    GLuint start, GLuint
    end,
    const GLint *first,
    const GLsizei *count, GLsizei
    primcount);

    GLBINDING_API void
    glMultiModeDrawArraysIBM(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount,
                             GLint modestride);

    GLBINDING_API void
    glMultiModeDrawElementsIBM(const GLenum *mode, const GLsizei *count, GLenum type, const void *const *indices,
                               GLsizei primcount, GLint modestride);

    GLBINDING_API void glMultiTexBufferEXT(GLenum
    texunit,
    GLenum target, GLenum
    internalformat,
    GLuint buffer
    );
    GLBINDING_API void glMultiTexCoord1bOES(GLenum
    texture,
    GLbyte s
    );
    GLBINDING_API void glMultiTexCoord1bvOES(GLenum
    texture,
    const GLbyte *coords
    );
    GLBINDING_API void glMultiTexCoord1d(GLenum
    target,
    GLdouble s
    );
    GLBINDING_API void glMultiTexCoord1dARB(GLenum
    target,
    GLdouble s
    );
    GLBINDING_API void glMultiTexCoord1dv(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord1dvARB(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord1f(GLenum
    target,
    GLfloat s
    );
    GLBINDING_API void glMultiTexCoord1fARB(GLenum
    target,
    GLfloat s
    );
    GLBINDING_API void glMultiTexCoord1fv(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord1fvARB(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord1hNV(GLenum
    target,
    GLhalfNV s
    );
    GLBINDING_API void glMultiTexCoord1hvNV(GLenum
    target,
    const GLhalfNV *v
    );
    GLBINDING_API void glMultiTexCoord1i(GLenum
    target,
    GLint s
    );
    GLBINDING_API void glMultiTexCoord1iARB(GLenum
    target,
    GLint s
    );
    GLBINDING_API void glMultiTexCoord1iv(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord1ivARB(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord1s(GLenum
    target,
    GLshort s
    );
    GLBINDING_API void glMultiTexCoord1sARB(GLenum
    target,
    GLshort s
    );
    GLBINDING_API void glMultiTexCoord1sv(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord1svARB(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord1xOES(GLenum
    texture,
    GLfixed s
    );
    GLBINDING_API void glMultiTexCoord1xvOES(GLenum
    texture,
    const GLfixed *coords
    );
    GLBINDING_API void glMultiTexCoord2bOES(GLenum
    texture,
    GLbyte s, GLbyte
    t);
    GLBINDING_API void glMultiTexCoord2bvOES(GLenum
    texture,
    const GLbyte *coords
    );
    GLBINDING_API void glMultiTexCoord2d(GLenum
    target,
    GLdouble s, GLdouble
    t);
    GLBINDING_API void glMultiTexCoord2dARB(GLenum
    target,
    GLdouble s, GLdouble
    t);
    GLBINDING_API void glMultiTexCoord2dv(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord2dvARB(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord2f(GLenum
    target,
    GLfloat s, GLfloat
    t);
    GLBINDING_API void glMultiTexCoord2fARB(GLenum
    target,
    GLfloat s, GLfloat
    t);
    GLBINDING_API void glMultiTexCoord2fv(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord2fvARB(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord2hNV(GLenum
    target,
    GLhalfNV s, GLhalfNV
    t);
    GLBINDING_API void glMultiTexCoord2hvNV(GLenum
    target,
    const GLhalfNV *v
    );
    GLBINDING_API void glMultiTexCoord2i(GLenum
    target,
    GLint s, GLint
    t);
    GLBINDING_API void glMultiTexCoord2iARB(GLenum
    target,
    GLint s, GLint
    t);
    GLBINDING_API void glMultiTexCoord2iv(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord2ivARB(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord2s(GLenum
    target,
    GLshort s, GLshort
    t);
    GLBINDING_API void glMultiTexCoord2sARB(GLenum
    target,
    GLshort s, GLshort
    t);
    GLBINDING_API void glMultiTexCoord2sv(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord2svARB(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord2xOES(GLenum
    texture,
    GLfixed s, GLfixed
    t);
    GLBINDING_API void glMultiTexCoord2xvOES(GLenum
    texture,
    const GLfixed *coords
    );
    GLBINDING_API void glMultiTexCoord3bOES(GLenum
    texture,
    GLbyte s, GLbyte
    t,
    GLbyte r
    );
    GLBINDING_API void glMultiTexCoord3bvOES(GLenum
    texture,
    const GLbyte *coords
    );
    GLBINDING_API void glMultiTexCoord3d(GLenum
    target,
    GLdouble s, GLdouble
    t,
    GLdouble r
    );
    GLBINDING_API void glMultiTexCoord3dARB(GLenum
    target,
    GLdouble s, GLdouble
    t,
    GLdouble r
    );
    GLBINDING_API void glMultiTexCoord3dv(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord3dvARB(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord3f(GLenum
    target,
    GLfloat s, GLfloat
    t,
    GLfloat r
    );
    GLBINDING_API void glMultiTexCoord3fARB(GLenum
    target,
    GLfloat s, GLfloat
    t,
    GLfloat r
    );
    GLBINDING_API void glMultiTexCoord3fv(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord3fvARB(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord3hNV(GLenum
    target,
    GLhalfNV s, GLhalfNV
    t,
    GLhalfNV r
    );
    GLBINDING_API void glMultiTexCoord3hvNV(GLenum
    target,
    const GLhalfNV *v
    );
    GLBINDING_API void glMultiTexCoord3i(GLenum
    target,
    GLint s, GLint
    t,
    GLint r
    );
    GLBINDING_API void glMultiTexCoord3iARB(GLenum
    target,
    GLint s, GLint
    t,
    GLint r
    );
    GLBINDING_API void glMultiTexCoord3iv(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord3ivARB(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord3s(GLenum
    target,
    GLshort s, GLshort
    t,
    GLshort r
    );
    GLBINDING_API void glMultiTexCoord3sARB(GLenum
    target,
    GLshort s, GLshort
    t,
    GLshort r
    );
    GLBINDING_API void glMultiTexCoord3sv(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord3svARB(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord3xOES(GLenum
    texture,
    GLfixed s, GLfixed
    t,
    GLfixed r
    );
    GLBINDING_API void glMultiTexCoord3xvOES(GLenum
    texture,
    const GLfixed *coords
    );
    GLBINDING_API void glMultiTexCoord4bOES(GLenum
    texture,
    GLbyte s, GLbyte
    t,
    GLbyte r, GLbyte
    q);
    GLBINDING_API void glMultiTexCoord4bvOES(GLenum
    texture,
    const GLbyte *coords
    );
    GLBINDING_API void glMultiTexCoord4d(GLenum
    target,
    GLdouble s, GLdouble
    t,
    GLdouble r, GLdouble
    q);
    GLBINDING_API void glMultiTexCoord4dARB(GLenum
    target,
    GLdouble s, GLdouble
    t,
    GLdouble r, GLdouble
    q);
    GLBINDING_API void glMultiTexCoord4dv(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord4dvARB(GLenum
    target,
    const GLdouble *v
    );
    GLBINDING_API void glMultiTexCoord4f(GLenum
    target,
    GLfloat s, GLfloat
    t,
    GLfloat r, GLfloat
    q);
    GLBINDING_API void glMultiTexCoord4fARB(GLenum
    target,
    GLfloat s, GLfloat
    t,
    GLfloat r, GLfloat
    q);
    GLBINDING_API void glMultiTexCoord4fv(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord4fvARB(GLenum
    target,
    const GLfloat *v
    );
    GLBINDING_API void glMultiTexCoord4hNV(GLenum
    target,
    GLhalfNV s, GLhalfNV
    t,
    GLhalfNV r, GLhalfNV
    q);
    GLBINDING_API void glMultiTexCoord4hvNV(GLenum
    target,
    const GLhalfNV *v
    );
    GLBINDING_API void glMultiTexCoord4i(GLenum
    target,
    GLint s, GLint
    t,
    GLint r, GLint
    q);
    GLBINDING_API void glMultiTexCoord4iARB(GLenum
    target,
    GLint s, GLint
    t,
    GLint r, GLint
    q);
    GLBINDING_API void glMultiTexCoord4iv(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord4ivARB(GLenum
    target,
    const GLint *v
    );
    GLBINDING_API void glMultiTexCoord4s(GLenum
    target,
    GLshort s, GLshort
    t,
    GLshort r, GLshort
    q);
    GLBINDING_API void glMultiTexCoord4sARB(GLenum
    target,
    GLshort s, GLshort
    t,
    GLshort r, GLshort
    q);
    GLBINDING_API void glMultiTexCoord4sv(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord4svARB(GLenum
    target,
    const GLshort *v
    );
    GLBINDING_API void glMultiTexCoord4xOES(GLenum
    texture,
    GLfixed s, GLfixed
    t,
    GLfixed r, GLfixed
    q);
    GLBINDING_API void glMultiTexCoord4xvOES(GLenum
    texture,
    const GLfixed *coords
    );
    GLBINDING_API void glMultiTexCoordP1ui(GLenum
    texture,
    GLenum type, GLuint
    coords);
    GLBINDING_API void glMultiTexCoordP1uiv(GLenum
    texture,
    GLenum type,
    const GLuint *coords
    );
    GLBINDING_API void glMultiTexCoordP2ui(GLenum
    texture,
    GLenum type, GLuint
    coords);
    GLBINDING_API void glMultiTexCoordP2uiv(GLenum
    texture,
    GLenum type,
    const GLuint *coords
    );
    GLBINDING_API void glMultiTexCoordP3ui(GLenum
    texture,
    GLenum type, GLuint
    coords);
    GLBINDING_API void glMultiTexCoordP3uiv(GLenum
    texture,
    GLenum type,
    const GLuint *coords
    );
    GLBINDING_API void glMultiTexCoordP4ui(GLenum
    texture,
    GLenum type, GLuint
    coords);
    GLBINDING_API void glMultiTexCoordP4uiv(GLenum
    texture,
    GLenum type,
    const GLuint *coords
    );
    GLBINDING_API void glMultiTexCoordPointerEXT(GLenum
    texunit,
    GLint size, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glMultiTexEnvfEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glMultiTexEnvfvEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glMultiTexEnviEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glMultiTexEnvivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glMultiTexGendEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLdouble param
    );
    GLBINDING_API void glMultiTexGendvEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    const GLdouble *params
    );
    GLBINDING_API void glMultiTexGenfEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glMultiTexGenfvEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glMultiTexGeniEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glMultiTexGenivEXT(GLenum
    texunit,
    GLenum coord, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glMultiTexImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glMultiTexImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLsizei height, GLint
    border,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glMultiTexImage3DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glMultiTexParameterIivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glMultiTexParameterIuivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLuint *params
    );
    GLBINDING_API void glMultiTexParameterfEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glMultiTexParameterfvEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glMultiTexParameteriEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glMultiTexParameterivEXT(GLenum
    texunit,
    GLenum target, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glMultiTexRenderbufferEXT(GLenum
    texunit,
    GLenum target, GLuint
    renderbuffer);
    GLBINDING_API void glMultiTexSubImage1DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glMultiTexSubImage2DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLsizei width, GLsizei
    height,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glMultiTexSubImage3DEXT(GLenum
    texunit,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLenum format, GLenum
    type,
    const void *pixels
    );

    GLBINDING_API void glMulticastBarrierNV();

    GLBINDING_API void glMulticastBlitFramebufferNV(GLuint
    srcGpu,
    GLuint dstGpu, GLint
    srcX0,
    GLint srcY0, GLint
    srcX1,
    GLint srcY1, GLint
    dstX0,
    GLint dstY0, GLint
    dstX1,
    GLint dstY1, ClearBufferMask
    mask,
    GLenum filter
    );

    GLBINDING_API void
    glMulticastBufferSubDataNV(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);

    GLBINDING_API void glMulticastCopyBufferSubDataNV(GLuint
    readGpu,
    GLbitfield writeGpuMask, GLuint
    readBuffer,
    GLuint writeBuffer, GLintptr
    readOffset,
    GLintptr writeOffset, GLsizeiptr
    size);
    GLBINDING_API void glMulticastCopyImageSubDataNV(GLuint
    srcGpu,
    GLbitfield dstGpuMask, GLuint
    srcName,
    GLenum srcTarget, GLint
    srcLevel,
    GLint srcX, GLint
    srcY,
    GLint srcZ, GLuint
    dstName,
    GLenum dstTarget, GLint
    dstLevel,
    GLint dstX, GLint
    dstY,
    GLint dstZ, GLsizei
    srcWidth,
    GLsizei srcHeight, GLsizei
    srcDepth);
    GLBINDING_API void glMulticastFramebufferSampleLocationsfvNV(GLuint
    gpu,
    GLuint framebuffer, GLuint
    start,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glMulticastGetQueryObjecti64vNV(GLuint
    gpu,
    GLuint id, GLenum
    pname,
    GLint64 *params
    );
    GLBINDING_API void glMulticastGetQueryObjectivNV(GLuint
    gpu,
    GLuint id, GLenum
    pname,
    GLint *params
    );
    GLBINDING_API void glMulticastGetQueryObjectui64vNV(GLuint
    gpu,
    GLuint id, GLenum
    pname,
    GLuint64 *params
    );
    GLBINDING_API void glMulticastGetQueryObjectuivNV(GLuint
    gpu,
    GLuint id, GLenum
    pname,
    GLuint *params
    );
    GLBINDING_API void glMulticastWaitSyncNV(GLuint
    signalGpu,
    GLbitfield waitGpuMask
    );

    GLBINDING_API void glNamedBufferAttachMemoryNV(GLuint
    buffer,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glNamedBufferData(GLuint
    buffer,
    GLsizeiptr size,
    const void *data, GLenum
    usage);
    GLBINDING_API void glNamedBufferDataEXT(GLuint
    buffer,
    GLsizeiptr size,
    const void *data, GLenum
    usage);
    GLBINDING_API void glNamedBufferPageCommitmentARB(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    GLboolean commit
    );
    GLBINDING_API void glNamedBufferPageCommitmentEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    GLboolean commit
    );
    GLBINDING_API void glNamedBufferStorage(GLuint
    buffer,
    GLsizeiptr size,
    const void *data, BufferStorageMask
    flags);
    GLBINDING_API void glNamedBufferStorageEXT(GLuint
    buffer,
    GLsizeiptr size,
    const void *data, BufferStorageMask
    flags);
    GLBINDING_API void glNamedBufferStorageExternalEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    GLeglClientBufferEXT clientBuffer, BufferStorageMask
    flags);
    GLBINDING_API void glNamedBufferStorageMemEXT(GLuint
    buffer,
    GLsizeiptr size, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glNamedBufferSubData(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    const void *data
    );
    GLBINDING_API void glNamedBufferSubDataEXT(GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size,
    const void *data
    );
    GLBINDING_API void glNamedCopyBufferSubDataEXT(GLuint
    readBuffer,
    GLuint writeBuffer, GLintptr
    readOffset,
    GLintptr writeOffset, GLsizeiptr
    size);
    GLBINDING_API void glNamedFramebufferDrawBuffer(GLuint
    framebuffer,
    GLenum buf
    );
    GLBINDING_API void glNamedFramebufferDrawBuffers(GLuint
    framebuffer,
    GLsizei n,
    const GLenum *bufs
    );
    GLBINDING_API void glNamedFramebufferParameteri(GLuint
    framebuffer,
    GLenum pname, GLint
    param);
    GLBINDING_API void glNamedFramebufferParameteriEXT(GLuint
    framebuffer,
    GLenum pname, GLint
    param);
    GLBINDING_API void glNamedFramebufferReadBuffer(GLuint
    framebuffer,
    GLenum src
    );
    GLBINDING_API void glNamedFramebufferRenderbuffer(GLuint
    framebuffer,
    GLenum attachment, GLenum
    renderbuffertarget,
    GLuint renderbuffer
    );
    GLBINDING_API void glNamedFramebufferRenderbufferEXT(GLuint
    framebuffer,
    GLenum attachment, GLenum
    renderbuffertarget,
    GLuint renderbuffer
    );
    GLBINDING_API void glNamedFramebufferSampleLocationsfvARB(GLuint
    framebuffer,
    GLuint start, GLsizei
    count,
    const GLfloat *v
    );
    GLBINDING_API void glNamedFramebufferSampleLocationsfvNV(GLuint
    framebuffer,
    GLuint start, GLsizei
    count,
    const GLfloat *v
    );
    GLBINDING_API void glNamedFramebufferSamplePositionsfvAMD(GLuint
    framebuffer,
    GLuint numsamples, GLuint
    pixelindex,
    const GLfloat *values
    );
    GLBINDING_API void glNamedFramebufferTexture(GLuint
    framebuffer,
    GLenum attachment, GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glNamedFramebufferTexture1DEXT(GLuint
    framebuffer,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glNamedFramebufferTexture2DEXT(GLuint
    framebuffer,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level);
    GLBINDING_API void glNamedFramebufferTexture3DEXT(GLuint
    framebuffer,
    GLenum attachment, GLenum
    textarget,
    GLuint texture, GLint
    level,
    GLint zoffset
    );
    GLBINDING_API void glNamedFramebufferTextureEXT(GLuint
    framebuffer,
    GLenum attachment, GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glNamedFramebufferTextureFaceEXT(GLuint
    framebuffer,
    GLenum attachment, GLuint
    texture,
    GLint level, GLenum
    face);
    GLBINDING_API void glNamedFramebufferTextureLayer(GLuint
    framebuffer,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    layer);
    GLBINDING_API void glNamedFramebufferTextureLayerEXT(GLuint
    framebuffer,
    GLenum attachment, GLuint
    texture,
    GLint level, GLint
    layer);
    GLBINDING_API void glNamedProgramLocalParameter4dEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glNamedProgramLocalParameter4dvEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    const GLdouble *params
    );
    GLBINDING_API void glNamedProgramLocalParameter4fEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);
    GLBINDING_API void glNamedProgramLocalParameter4fvEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    const GLfloat *params
    );
    GLBINDING_API void glNamedProgramLocalParameterI4iEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLint x, GLint
    y,
    GLint z, GLint
    w);
    GLBINDING_API void glNamedProgramLocalParameterI4ivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    const GLint *params
    );
    GLBINDING_API void glNamedProgramLocalParameterI4uiEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLuint x, GLuint
    y,
    GLuint z, GLuint
    w);
    GLBINDING_API void glNamedProgramLocalParameterI4uivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    const GLuint *params
    );
    GLBINDING_API void glNamedProgramLocalParameters4fvEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLsizei count,
    const GLfloat *params
    );
    GLBINDING_API void glNamedProgramLocalParametersI4ivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLsizei count,
    const GLint *params
    );
    GLBINDING_API void glNamedProgramLocalParametersI4uivEXT(GLuint
    program,
    GLenum target, GLuint
    index,
    GLsizei count,
    const GLuint *params
    );
    GLBINDING_API void glNamedProgramStringEXT(GLuint
    program,
    GLenum target, GLenum
    format,
    GLsizei len,
    const void *string
    );
    GLBINDING_API void glNamedRenderbufferStorage(GLuint
    renderbuffer,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glNamedRenderbufferStorageEXT(GLuint
    renderbuffer,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glNamedRenderbufferStorageMultisample(GLuint
    renderbuffer,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glNamedRenderbufferStorageMultisampleAdvancedAMD(GLuint
    renderbuffer,
    GLsizei samples, GLsizei
    storageSamples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint
    renderbuffer,
    GLsizei coverageSamples, GLsizei
    colorSamples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glNamedRenderbufferStorageMultisampleEXT(GLuint
    renderbuffer,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glNamedStringARB(GLenum
    type,
    GLint namelen,
    const GLchar *name, GLint
    stringlen,
    const GLchar *string
    );
    GLBINDING_API void glNewList(GLuint
    list,
    GLenum mode
    );
    GLBINDING_API GLuint
    glNewObjectBufferATI(GLsizei
    size,
    const void *pointer, GLenum
    usage);
    GLBINDING_API void glNormal3b(GLbyte
    nx,
    GLbyte ny, GLbyte
    nz);

    GLBINDING_API void glNormal3bv(const GLbyte *v);

    GLBINDING_API void glNormal3d(GLdouble
    nx,
    GLdouble ny, GLdouble
    nz);

    GLBINDING_API void glNormal3dv(const GLdouble *v);

    GLBINDING_API void glNormal3f(GLfloat
    nx,
    GLfloat ny, GLfloat
    nz);
    GLBINDING_API void glNormal3fVertex3fSUN(GLfloat
    nx,
    GLfloat ny, GLfloat
    nz,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glNormal3fVertex3fvSUN(const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glNormal3fv(const GLfloat *v);

    GLBINDING_API void glNormal3hNV(GLhalfNV
    nx,
    GLhalfNV ny, GLhalfNV
    nz);

    GLBINDING_API void glNormal3hvNV(const GLhalfNV *v);

    GLBINDING_API void glNormal3i(GLint
    nx,
    GLint ny, GLint
    nz);

    GLBINDING_API void glNormal3iv(const GLint *v);

    GLBINDING_API void glNormal3s(GLshort
    nx,
    GLshort ny, GLshort
    nz);

    GLBINDING_API void glNormal3sv(const GLshort *v);

    GLBINDING_API void glNormal3xOES(GLfixed
    nx,
    GLfixed ny, GLfixed
    nz);

    GLBINDING_API void glNormal3xvOES(const GLfixed *coords);

    GLBINDING_API void glNormalFormatNV(GLenum
    type,
    GLsizei stride
    );
    GLBINDING_API void glNormalP3ui(GLenum
    type,
    GLuint coords
    );
    GLBINDING_API void glNormalP3uiv(GLenum
    type,
    const GLuint *coords
    );
    GLBINDING_API void glNormalPointer(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glNormalPointerEXT(GLenum
    type,
    GLsizei stride, GLsizei
    count,
    const void *pointer
    );
    GLBINDING_API void glNormalPointerListIBM(GLenum
    type,
    GLint stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glNormalPointervINTEL(GLenum
    type,
    const void **pointer
    );
    GLBINDING_API void glNormalStream3bATI(GLenum
    stream,
    GLbyte nx, GLbyte
    ny,
    GLbyte nz
    );
    GLBINDING_API void glNormalStream3bvATI(GLenum
    stream,
    const GLbyte *coords
    );
    GLBINDING_API void glNormalStream3dATI(GLenum
    stream,
    GLdouble nx, GLdouble
    ny,
    GLdouble nz
    );
    GLBINDING_API void glNormalStream3dvATI(GLenum
    stream,
    const GLdouble *coords
    );
    GLBINDING_API void glNormalStream3fATI(GLenum
    stream,
    GLfloat nx, GLfloat
    ny,
    GLfloat nz
    );
    GLBINDING_API void glNormalStream3fvATI(GLenum
    stream,
    const GLfloat *coords
    );
    GLBINDING_API void glNormalStream3iATI(GLenum
    stream,
    GLint nx, GLint
    ny,
    GLint nz
    );
    GLBINDING_API void glNormalStream3ivATI(GLenum
    stream,
    const GLint *coords
    );
    GLBINDING_API void glNormalStream3sATI(GLenum
    stream,
    GLshort nx, GLshort
    ny,
    GLshort nz
    );
    GLBINDING_API void glNormalStream3svATI(GLenum
    stream,
    const GLshort *coords
    );

    GLBINDING_API void glObjectLabel(GLenum
    identifier,
    GLuint name, GLsizei
    length,
    const GLchar *label
    );

    GLBINDING_API void glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label);

    GLBINDING_API GLenum
    glObjectPurgeableAPPLE(GLenum
    objectType,
    GLuint name, GLenum
    option);
    GLBINDING_API GLenum
    glObjectUnpurgeableAPPLE(GLenum
    objectType,
    GLuint name, GLenum
    option);
    GLBINDING_API void glOrtho(GLdouble
    left,
    GLdouble right, GLdouble
    bottom,
    GLdouble top, GLdouble
    zNear,
    GLdouble zFar
    );
    GLBINDING_API void glOrthofOES(GLfloat
    l,
    GLfloat r, GLfloat
    b,
    GLfloat t, GLfloat
    n,
    GLfloat f
    );
    GLBINDING_API void glOrthoxOES(GLfixed
    l,
    GLfixed r, GLfixed
    b,
    GLfixed t, GLfixed
    n,
    GLfixed f
    );

    GLBINDING_API void glPNTrianglesfATI(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPNTrianglesiATI(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPassTexCoordATI(GLuint
    dst,
    GLuint coord, GLenum
    swizzle);
    GLBINDING_API void glPassThrough(GLfloat
    token);
    GLBINDING_API void glPassThroughxOES(GLfixed
    token);
    GLBINDING_API void glPatchParameterfv(GLenum
    pname,
    const GLfloat *values
    );
    GLBINDING_API void glPatchParameteri(GLenum
    pname,
    GLint value
    );
    GLBINDING_API void glPathColorGenNV(GLenum
    color,
    GLenum genMode, GLenum
    colorFormat,
    const GLfloat *coeffs
    );
    GLBINDING_API void glPathCommandsNV(GLuint
    path,
    GLsizei numCommands,
    const GLubyte *commands, GLsizei
    numCoords,
    GLenum coordType,
    const void *coords
    );
    GLBINDING_API void glPathCoordsNV(GLuint
    path,
    GLsizei numCoords, GLenum
    coordType,
    const void *coords
    );
    GLBINDING_API void glPathCoverDepthFuncNV(GLenum
    func);
    GLBINDING_API void glPathDashArrayNV(GLuint
    path,
    GLsizei dashCount,
    const GLfloat *dashArray
    );
    GLBINDING_API void glPathFogGenNV(GLenum
    genMode);
    GLBINDING_API GLenum
    glPathGlyphIndexArrayNV(GLuint
    firstPathName,
    GLenum fontTarget,
    const void *fontName, PathFontStyle
    fontStyle,
    GLuint firstGlyphIndex, GLsizei
    numGlyphs,
    GLuint pathParameterTemplate, GLfloat
    emScale);
    GLBINDING_API GLenum
    glPathGlyphIndexRangeNV(GLenum
    fontTarget,
    const void *fontName, PathFontStyle
    fontStyle,
    GLuint pathParameterTemplate, GLfloat
    emScale,
    GLuint_array_2 baseAndCount
    );
    GLBINDING_API void glPathGlyphRangeNV(GLuint
    firstPathName,
    GLenum fontTarget,
    const void *fontName, PathFontStyle
    fontStyle,
    GLuint firstGlyph, GLsizei
    numGlyphs,
    GLenum handleMissingGlyphs, GLuint
    pathParameterTemplate,
    GLfloat emScale
    );
    GLBINDING_API void glPathGlyphsNV(GLuint
    firstPathName,
    GLenum fontTarget,
    const void *fontName, PathFontStyle
    fontStyle,
    GLsizei numGlyphs, GLenum
    type,
    const void *charcodes, GLenum
    handleMissingGlyphs,
    GLuint pathParameterTemplate, GLfloat
    emScale);
    GLBINDING_API GLenum
    glPathMemoryGlyphIndexArrayNV(GLuint
    firstPathName,
    GLenum fontTarget, GLsizeiptr
    fontSize,
    const void *fontData, GLsizei
    faceIndex,
    GLuint firstGlyphIndex, GLsizei
    numGlyphs,
    GLuint pathParameterTemplate, GLfloat
    emScale);
    GLBINDING_API void glPathParameterfNV(GLuint
    path,
    GLenum pname, GLfloat
    value);
    GLBINDING_API void glPathParameterfvNV(GLuint
    path,
    GLenum pname,
    const GLfloat *value
    );
    GLBINDING_API void glPathParameteriNV(GLuint
    path,
    GLenum pname, GLint
    value);
    GLBINDING_API void glPathParameterivNV(GLuint
    path,
    GLenum pname,
    const GLint *value
    );
    GLBINDING_API void glPathStencilDepthOffsetNV(GLfloat
    factor,
    GLfloat units
    );
    GLBINDING_API void glPathStencilFuncNV(GLenum
    func,
    GLint ref, GLuint
    mask);
    GLBINDING_API void glPathStringNV(GLuint
    path,
    GLenum format, GLsizei
    length,
    const void *pathString
    );
    GLBINDING_API void glPathSubCommandsNV(GLuint
    path,
    GLsizei commandStart, GLsizei
    commandsToDelete,
    GLsizei numCommands,
    const GLubyte *commands, GLsizei
    numCoords,
    GLenum coordType,
    const void *coords
    );
    GLBINDING_API void glPathSubCoordsNV(GLuint
    path,
    GLsizei coordStart, GLsizei
    numCoords,
    GLenum coordType,
    const void *coords
    );
    GLBINDING_API void glPathTexGenNV(GLenum
    texCoordSet,
    GLenum genMode, GLint
    components,
    const GLfloat *coeffs
    );

    GLBINDING_API void glPauseTransformFeedback();

    GLBINDING_API void glPauseTransformFeedbackNV();

    GLBINDING_API void glPixelDataRangeNV(GLenum
    target,
    GLsizei length,
    const void *pointer
    );
    GLBINDING_API void glPixelMapfv(GLenum
    map,
    GLsizei mapsize,
    const GLfloat *values
    );
    GLBINDING_API void glPixelMapuiv(GLenum
    map,
    GLsizei mapsize,
    const GLuint *values
    );
    GLBINDING_API void glPixelMapusv(GLenum
    map,
    GLsizei mapsize,
    const GLushort *values
    );
    GLBINDING_API void glPixelMapx(GLenum
    map,
    GLint size,
    const GLfixed *values
    );
    GLBINDING_API void glPixelStoref(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPixelStorei(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPixelStorex(GLenum
    pname,
    GLfixed param
    );
    GLBINDING_API void glPixelTexGenParameterfSGIS(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPixelTexGenParameterfvSGIS(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glPixelTexGenParameteriSGIS(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPixelTexGenParameterivSGIS(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glPixelTexGenSGIX(GLenum
    mode);
    GLBINDING_API void glPixelTransferf(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPixelTransferi(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPixelTransferxOES(GLenum
    pname,
    GLfixed param
    );
    GLBINDING_API void glPixelTransformParameterfEXT(GLenum
    target,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glPixelTransformParameterfvEXT(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glPixelTransformParameteriEXT(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glPixelTransformParameterivEXT(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glPixelZoom(GLfloat
    xfactor,
    GLfloat yfactor
    );
    GLBINDING_API void glPixelZoomxOES(GLfixed
    xfactor,
    GLfixed yfactor
    );
    GLBINDING_API GLboolean
    glPointAlongPathNV(GLuint
    path,
    GLsizei startSegment, GLsizei
    numSegments,
    GLfloat distance, GLfloat
    * x,
    GLfloat *y, GLfloat
    * tangentX,
    GLfloat *tangentY
    );
    GLBINDING_API void glPointParameterf(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPointParameterfARB(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPointParameterfEXT(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPointParameterfSGIS(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glPointParameterfv(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glPointParameterfvARB(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glPointParameterfvEXT(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glPointParameterfvSGIS(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glPointParameteri(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPointParameteriNV(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glPointParameteriv(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glPointParameterivNV(GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glPointParameterxvOES(GLenum
    pname,
    const GLfixed *params
    );
    GLBINDING_API void glPointSize(GLfloat
    size);
    GLBINDING_API void glPointSizexOES(GLfixed
    size);
    GLBINDING_API GLint
    glPollAsyncSGIX(GLuint
    * markerp);
    GLBINDING_API GLint
    glPollInstrumentsSGIX(GLint
    * marker_p);
    GLBINDING_API void glPolygonMode(GLenum
    face,
    GLenum mode
    );
    GLBINDING_API void glPolygonOffset(GLfloat
    factor,
    GLfloat units
    );
    GLBINDING_API void glPolygonOffsetClamp(GLfloat
    factor,
    GLfloat units, GLfloat
    clamp);
    GLBINDING_API void glPolygonOffsetClampEXT(GLfloat
    factor,
    GLfloat units, GLfloat
    clamp);
    GLBINDING_API void glPolygonOffsetEXT(GLfloat
    factor,
    GLfloat bias
    );
    GLBINDING_API void glPolygonOffsetxOES(GLfixed
    factor,
    GLfixed units
    );

    GLBINDING_API void glPolygonStipple(const GLubyte *mask);

    GLBINDING_API void glPopAttrib();

    GLBINDING_API void glPopClientAttrib();

    GLBINDING_API void glPopDebugGroup();

    GLBINDING_API void glPopGroupMarkerEXT();

    GLBINDING_API void glPopMatrix();

    GLBINDING_API void glPopName();

    GLBINDING_API void glPresentFrameDualFillNV(GLuint
    video_slot,
    GLuint64EXT minPresentTime, GLuint
    beginPresentTimeId,
    GLuint presentDurationId, GLenum
    type,
    GLenum target0, GLuint
    fill0,
    GLenum target1, GLuint
    fill1,
    GLenum target2, GLuint
    fill2,
    GLenum target3, GLuint
    fill3);
    GLBINDING_API void glPresentFrameKeyedNV(GLuint
    video_slot,
    GLuint64EXT minPresentTime, GLuint
    beginPresentTimeId,
    GLuint presentDurationId, GLenum
    type,
    GLenum target0, GLuint
    fill0,
    GLuint key0, GLenum
    target1,
    GLuint fill1, GLuint
    key1);
    GLBINDING_API void glPrimitiveBoundingBoxARB(GLfloat
    minX,
    GLfloat minY, GLfloat
    minZ,
    GLfloat minW, GLfloat
    maxX,
    GLfloat maxY, GLfloat
    maxZ,
    GLfloat maxW
    );
    GLBINDING_API void glPrimitiveRestartIndex(GLuint
    index);
    GLBINDING_API void glPrimitiveRestartIndexNV(GLuint
    index);

    GLBINDING_API void glPrimitiveRestartNV();

    GLBINDING_API void glPrioritizeTextures(GLsizei
    n,
    const GLuint *textures,
    const GLfloat *priorities
    );
    GLBINDING_API void glPrioritizeTexturesEXT(GLsizei
    n,
    const GLuint *textures,
    const GLclampf *priorities
    );
    GLBINDING_API void glPrioritizeTexturesxOES(GLsizei
    n,
    const GLuint *textures,
    const GLfixed *priorities
    );
    GLBINDING_API void glProgramBinary(GLuint
    program,
    GLenum binaryFormat,
    const void *binary, GLsizei
    length);
    GLBINDING_API void glProgramBufferParametersIivNV(GLenum
    target,
    GLuint bindingIndex, GLuint
    wordIndex,
    GLsizei count,
    const GLint *params
    );
    GLBINDING_API void glProgramBufferParametersIuivNV(GLenum
    target,
    GLuint bindingIndex, GLuint
    wordIndex,
    GLsizei count,
    const GLuint *params
    );
    GLBINDING_API void glProgramBufferParametersfvNV(GLenum
    target,
    GLuint bindingIndex, GLuint
    wordIndex,
    GLsizei count,
    const GLfloat *params
    );
    GLBINDING_API void glProgramEnvParameter4dARB(GLenum
    target,
    GLuint index, GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );
    GLBINDING_API void glProgramEnvParameter4dvARB(GLenum
    target,
    GLuint index,
    const GLdouble *params
    );
    GLBINDING_API void glProgramEnvParameter4fARB(GLenum
    target,
    GLuint index, GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );
    GLBINDING_API void glProgramEnvParameter4fvARB(GLenum
    target,
    GLuint index,
    const GLfloat *params
    );
    GLBINDING_API void glProgramEnvParameterI4iNV(GLenum
    target,
    GLuint index, GLint
    x,
    GLint y, GLint
    z,
    GLint w
    );
    GLBINDING_API void glProgramEnvParameterI4ivNV(GLenum
    target,
    GLuint index,
    const GLint *params
    );
    GLBINDING_API void glProgramEnvParameterI4uiNV(GLenum
    target,
    GLuint index, GLuint
    x,
    GLuint y, GLuint
    z,
    GLuint w
    );
    GLBINDING_API void glProgramEnvParameterI4uivNV(GLenum
    target,
    GLuint index,
    const GLuint *params
    );
    GLBINDING_API void glProgramEnvParameters4fvEXT(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLfloat *params
    );
    GLBINDING_API void glProgramEnvParametersI4ivNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLint *params
    );
    GLBINDING_API void glProgramEnvParametersI4uivNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLuint *params
    );
    GLBINDING_API void glProgramLocalParameter4dARB(GLenum
    target,
    GLuint index, GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );
    GLBINDING_API void glProgramLocalParameter4dvARB(GLenum
    target,
    GLuint index,
    const GLdouble *params
    );
    GLBINDING_API void glProgramLocalParameter4fARB(GLenum
    target,
    GLuint index, GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );
    GLBINDING_API void glProgramLocalParameter4fvARB(GLenum
    target,
    GLuint index,
    const GLfloat *params
    );
    GLBINDING_API void glProgramLocalParameterI4iNV(GLenum
    target,
    GLuint index, GLint
    x,
    GLint y, GLint
    z,
    GLint w
    );
    GLBINDING_API void glProgramLocalParameterI4ivNV(GLenum
    target,
    GLuint index,
    const GLint *params
    );
    GLBINDING_API void glProgramLocalParameterI4uiNV(GLenum
    target,
    GLuint index, GLuint
    x,
    GLuint y, GLuint
    z,
    GLuint w
    );
    GLBINDING_API void glProgramLocalParameterI4uivNV(GLenum
    target,
    GLuint index,
    const GLuint *params
    );
    GLBINDING_API void glProgramLocalParameters4fvEXT(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLfloat *params
    );
    GLBINDING_API void glProgramLocalParametersI4ivNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLint *params
    );
    GLBINDING_API void glProgramLocalParametersI4uivNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLuint *params
    );
    GLBINDING_API void glProgramNamedParameter4dNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name, GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );
    GLBINDING_API void glProgramNamedParameter4dvNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name,
    const GLdouble *v
    );
    GLBINDING_API void glProgramNamedParameter4fNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name, GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );
    GLBINDING_API void glProgramNamedParameter4fvNV(GLuint
    id,
    GLsizei len,
    const GLubyte *name,
    const GLfloat *v
    );
    GLBINDING_API void glProgramParameter4dNV(GLenum
    target,
    GLuint index, GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );
    GLBINDING_API void glProgramParameter4dvNV(GLenum
    target,
    GLuint index,
    const GLdouble *v
    );
    GLBINDING_API void glProgramParameter4fNV(GLenum
    target,
    GLuint index, GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );
    GLBINDING_API void glProgramParameter4fvNV(GLenum
    target,
    GLuint index,
    const GLfloat *v
    );
    GLBINDING_API void glProgramParameteri(GLuint
    program,
    GLenum pname, GLint
    value);
    GLBINDING_API void glProgramParameteriARB(GLuint
    program,
    GLenum pname, GLint
    value);
    GLBINDING_API void glProgramParameteriEXT(GLuint
    program,
    GLenum pname, GLint
    value);
    GLBINDING_API void glProgramParameters4dvNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLdouble *v
    );
    GLBINDING_API void glProgramParameters4fvNV(GLenum
    target,
    GLuint index, GLsizei
    count,
    const GLfloat *v
    );
    GLBINDING_API void glProgramPathFragmentInputGenNV(GLuint
    program,
    GLint location, GLenum
    genMode,
    GLint components,
    const GLfloat *coeffs
    );
    GLBINDING_API void glProgramStringARB(GLenum
    target,
    GLenum format, GLsizei
    len,
    const void *string
    );
    GLBINDING_API void glProgramSubroutineParametersuivNV(GLenum
    target,
    GLsizei count,
    const GLuint *params
    );
    GLBINDING_API void glProgramUniform1d(GLuint
    program,
    GLint location, GLdouble
    v0);
    GLBINDING_API void glProgramUniform1dEXT(GLuint
    program,
    GLint location, GLdouble
    x);
    GLBINDING_API void glProgramUniform1dv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform1dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform1f(GLuint
    program,
    GLint location, GLfloat
    v0);
    GLBINDING_API void glProgramUniform1fEXT(GLuint
    program,
    GLint location, GLfloat
    v0);
    GLBINDING_API void glProgramUniform1fv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform1fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform1i(GLuint
    program,
    GLint location, GLint
    v0);
    GLBINDING_API void glProgramUniform1i64ARB(GLuint
    program,
    GLint location, GLint64
    x);
    GLBINDING_API void glProgramUniform1i64NV(GLuint
    program,
    GLint location, GLint64EXT
    x);
    GLBINDING_API void glProgramUniform1i64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64 *value
    );
    GLBINDING_API void glProgramUniform1i64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64EXT *value
    );
    GLBINDING_API void glProgramUniform1iEXT(GLuint
    program,
    GLint location, GLint
    v0);
    GLBINDING_API void glProgramUniform1iv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform1ivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform1ui(GLuint
    program,
    GLint location, GLuint
    v0);
    GLBINDING_API void glProgramUniform1ui64ARB(GLuint
    program,
    GLint location, GLuint64
    x);
    GLBINDING_API void glProgramUniform1ui64NV(GLuint
    program,
    GLint location, GLuint64EXT
    x);
    GLBINDING_API void glProgramUniform1ui64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *value
    );
    GLBINDING_API void glProgramUniform1ui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glProgramUniform1uiEXT(GLuint
    program,
    GLint location, GLuint
    v0);
    GLBINDING_API void glProgramUniform1uiv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform1uivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform2d(GLuint
    program,
    GLint location, GLdouble
    v0,
    GLdouble v1
    );
    GLBINDING_API void glProgramUniform2dEXT(GLuint
    program,
    GLint location, GLdouble
    x,
    GLdouble y
    );
    GLBINDING_API void glProgramUniform2dv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform2dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform2f(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1
    );
    GLBINDING_API void glProgramUniform2fEXT(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1
    );
    GLBINDING_API void glProgramUniform2fv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform2fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform2i(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1
    );
    GLBINDING_API void glProgramUniform2i64ARB(GLuint
    program,
    GLint location, GLint64
    x,
    GLint64 y
    );
    GLBINDING_API void glProgramUniform2i64NV(GLuint
    program,
    GLint location, GLint64EXT
    x,
    GLint64EXT y
    );
    GLBINDING_API void glProgramUniform2i64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64 *value
    );
    GLBINDING_API void glProgramUniform2i64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64EXT *value
    );
    GLBINDING_API void glProgramUniform2iEXT(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1
    );
    GLBINDING_API void glProgramUniform2iv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform2ivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform2ui(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1
    );
    GLBINDING_API void glProgramUniform2ui64ARB(GLuint
    program,
    GLint location, GLuint64
    x,
    GLuint64 y
    );
    GLBINDING_API void glProgramUniform2ui64NV(GLuint
    program,
    GLint location, GLuint64EXT
    x,
    GLuint64EXT y
    );
    GLBINDING_API void glProgramUniform2ui64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *value
    );
    GLBINDING_API void glProgramUniform2ui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glProgramUniform2uiEXT(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1
    );
    GLBINDING_API void glProgramUniform2uiv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform2uivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform3d(GLuint
    program,
    GLint location, GLdouble
    v0,
    GLdouble v1, GLdouble
    v2);
    GLBINDING_API void glProgramUniform3dEXT(GLuint
    program,
    GLint location, GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glProgramUniform3dv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform3dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform3f(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1, GLfloat
    v2);
    GLBINDING_API void glProgramUniform3fEXT(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1, GLfloat
    v2);
    GLBINDING_API void glProgramUniform3fv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform3fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform3i(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1, GLint
    v2);
    GLBINDING_API void glProgramUniform3i64ARB(GLuint
    program,
    GLint location, GLint64
    x,
    GLint64 y, GLint64
    z);
    GLBINDING_API void glProgramUniform3i64NV(GLuint
    program,
    GLint location, GLint64EXT
    x,
    GLint64EXT y, GLint64EXT
    z);
    GLBINDING_API void glProgramUniform3i64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64 *value
    );
    GLBINDING_API void glProgramUniform3i64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64EXT *value
    );
    GLBINDING_API void glProgramUniform3iEXT(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1, GLint
    v2);
    GLBINDING_API void glProgramUniform3iv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform3ivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform3ui(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1, GLuint
    v2);
    GLBINDING_API void glProgramUniform3ui64ARB(GLuint
    program,
    GLint location, GLuint64
    x,
    GLuint64 y, GLuint64
    z);
    GLBINDING_API void glProgramUniform3ui64NV(GLuint
    program,
    GLint location, GLuint64EXT
    x,
    GLuint64EXT y, GLuint64EXT
    z);
    GLBINDING_API void glProgramUniform3ui64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *value
    );
    GLBINDING_API void glProgramUniform3ui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glProgramUniform3uiEXT(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1, GLuint
    v2);
    GLBINDING_API void glProgramUniform3uiv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform3uivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform4d(GLuint
    program,
    GLint location, GLdouble
    v0,
    GLdouble v1, GLdouble
    v2,
    GLdouble v3
    );
    GLBINDING_API void glProgramUniform4dEXT(GLuint
    program,
    GLint location, GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );
    GLBINDING_API void glProgramUniform4dv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform4dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniform4f(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1, GLfloat
    v2,
    GLfloat v3
    );
    GLBINDING_API void glProgramUniform4fEXT(GLuint
    program,
    GLint location, GLfloat
    v0,
    GLfloat v1, GLfloat
    v2,
    GLfloat v3
    );
    GLBINDING_API void glProgramUniform4fv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform4fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniform4i(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1, GLint
    v2,
    GLint v3
    );
    GLBINDING_API void glProgramUniform4i64ARB(GLuint
    program,
    GLint location, GLint64
    x,
    GLint64 y, GLint64
    z,
    GLint64 w
    );
    GLBINDING_API void glProgramUniform4i64NV(GLuint
    program,
    GLint location, GLint64EXT
    x,
    GLint64EXT y, GLint64EXT
    z,
    GLint64EXT w
    );
    GLBINDING_API void glProgramUniform4i64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64 *value
    );
    GLBINDING_API void glProgramUniform4i64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint64EXT *value
    );
    GLBINDING_API void glProgramUniform4iEXT(GLuint
    program,
    GLint location, GLint
    v0,
    GLint v1, GLint
    v2,
    GLint v3
    );
    GLBINDING_API void glProgramUniform4iv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform4ivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLint *value
    );
    GLBINDING_API void glProgramUniform4ui(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1, GLuint
    v2,
    GLuint v3
    );
    GLBINDING_API void glProgramUniform4ui64ARB(GLuint
    program,
    GLint location, GLuint64
    x,
    GLuint64 y, GLuint64
    z,
    GLuint64 w
    );
    GLBINDING_API void glProgramUniform4ui64NV(GLuint
    program,
    GLint location, GLuint64EXT
    x,
    GLuint64EXT y, GLuint64EXT
    z,
    GLuint64EXT w
    );
    GLBINDING_API void glProgramUniform4ui64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *value
    );
    GLBINDING_API void glProgramUniform4ui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glProgramUniform4uiEXT(GLuint
    program,
    GLint location, GLuint
    v0,
    GLuint v1, GLuint
    v2,
    GLuint v3
    );
    GLBINDING_API void glProgramUniform4uiv(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniform4uivEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint *value
    );
    GLBINDING_API void glProgramUniformHandleui64ARB(GLuint
    program,
    GLint location, GLuint64
    value);
    GLBINDING_API void glProgramUniformHandleui64NV(GLuint
    program,
    GLint location, GLuint64
    value);
    GLBINDING_API void glProgramUniformHandleui64vARB(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *values
    );
    GLBINDING_API void glProgramUniformHandleui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64 *values
    );
    GLBINDING_API void glProgramUniformMatrix2dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix2fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix2x3dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2x3dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2x3fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix2x3fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix2x4dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2x4dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix2x4fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix2x4fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3x2dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3x2dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3x2fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3x2fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3x4dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3x4dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix3x4fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix3x4fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4x2dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4x2dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4x2fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4x2fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4x3dv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4x3dvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLdouble *value
    );
    GLBINDING_API void glProgramUniformMatrix4x3fv(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformMatrix4x3fvEXT(GLuint
    program,
    GLint location, GLsizei
    count,
    GLboolean transpose,
    const GLfloat *value
    );
    GLBINDING_API void glProgramUniformui64NV(GLuint
    program,
    GLint location, GLuint64EXT
    value);
    GLBINDING_API void glProgramUniformui64vNV(GLuint
    program,
    GLint location, GLsizei
    count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glProgramVertexLimitNV(GLenum
    target,
    GLint limit
    );
    GLBINDING_API void glProvokingVertex(GLenum
    mode);
    GLBINDING_API void glProvokingVertexEXT(GLenum
    mode);

    GLBINDING_API void glPushAttrib(AttribMask mask);

    GLBINDING_API void glPushClientAttrib(ClientAttribMask mask);

    GLBINDING_API void glPushClientAttribDefaultEXT(ClientAttribMask mask);

    GLBINDING_API void glPushDebugGroup(GLenum
    source,
    GLuint id, GLsizei
    length,
    const GLchar *message
    );
    GLBINDING_API void glPushGroupMarkerEXT(GLsizei
    length,
    const GLchar *marker
    );

    GLBINDING_API void glPushMatrix();

    GLBINDING_API void glPushName(GLuint
    name);

    GLBINDING_API void glQueryCounter(GLuint
    id,
    GLenum target
    );
    GLBINDING_API GLbitfield
    glQueryMatrixxOES(GLfixed
    * mantissa,
    GLint *exponent
    );
    GLBINDING_API void glQueryObjectParameteruiAMD(GLenum
    target,
    GLuint id, GLenum
    pname,
    GLuint param
    );
    GLBINDING_API GLint
    glQueryResourceNV(GLenum
    queryType,
    GLint tagId, GLuint
    bufSize,
    GLint *buffer
    );
    GLBINDING_API void glQueryResourceTagNV(GLint
    tagId,
    const GLchar *tagString
    );

    GLBINDING_API void glRasterPos2d(GLdouble
    x,
    GLdouble y
    );

    GLBINDING_API void glRasterPos2dv(const GLdouble *v);

    GLBINDING_API void glRasterPos2f(GLfloat
    x,
    GLfloat y
    );

    GLBINDING_API void glRasterPos2fv(const GLfloat *v);

    GLBINDING_API void glRasterPos2i(GLint
    x,
    GLint y
    );

    GLBINDING_API void glRasterPos2iv(const GLint *v);

    GLBINDING_API void glRasterPos2s(GLshort
    x,
    GLshort y
    );

    GLBINDING_API void glRasterPos2sv(const GLshort *v);

    GLBINDING_API void glRasterPos2xOES(GLfixed
    x,
    GLfixed y
    );

    GLBINDING_API void glRasterPos2xvOES(const GLfixed *coords);

    GLBINDING_API void glRasterPos3d(GLdouble
    x,
    GLdouble y, GLdouble
    z);

    GLBINDING_API void glRasterPos3dv(const GLdouble *v);

    GLBINDING_API void glRasterPos3f(GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glRasterPos3fv(const GLfloat *v);

    GLBINDING_API void glRasterPos3i(GLint
    x,
    GLint y, GLint
    z);

    GLBINDING_API void glRasterPos3iv(const GLint *v);

    GLBINDING_API void glRasterPos3s(GLshort
    x,
    GLshort y, GLshort
    z);

    GLBINDING_API void glRasterPos3sv(const GLshort *v);

    GLBINDING_API void glRasterPos3xOES(GLfixed
    x,
    GLfixed y, GLfixed
    z);

    GLBINDING_API void glRasterPos3xvOES(const GLfixed *coords);

    GLBINDING_API void glRasterPos4d(GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );

    GLBINDING_API void glRasterPos4dv(const GLdouble *v);

    GLBINDING_API void glRasterPos4f(GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );

    GLBINDING_API void glRasterPos4fv(const GLfloat *v);

    GLBINDING_API void glRasterPos4i(GLint
    x,
    GLint y, GLint
    z,
    GLint w
    );

    GLBINDING_API void glRasterPos4iv(const GLint *v);

    GLBINDING_API void glRasterPos4s(GLshort
    x,
    GLshort y, GLshort
    z,
    GLshort w
    );

    GLBINDING_API void glRasterPos4sv(const GLshort *v);

    GLBINDING_API void glRasterPos4xOES(GLfixed
    x,
    GLfixed y, GLfixed
    z,
    GLfixed w
    );

    GLBINDING_API void glRasterPos4xvOES(const GLfixed *coords);

    GLBINDING_API void glRasterSamplesEXT(GLuint
    samples,
    GLboolean fixedsamplelocations
    );
    GLBINDING_API void glReadBuffer(GLenum
    src);
    GLBINDING_API void glReadInstrumentsSGIX(GLint
    marker);
    GLBINDING_API void glReadPixels(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    void *pixels
    );
    GLBINDING_API void glReadnPixels(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *data
    );
    GLBINDING_API void glReadnPixelsARB(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type, GLsizei
    bufSize,
    void *data
    );
    GLBINDING_API void glRectd(GLdouble
    x1,
    GLdouble y1, GLdouble
    x2,
    GLdouble y2
    );

    GLBINDING_API void glRectdv(const GLdouble *v1, const GLdouble *v2);

    GLBINDING_API void glRectf(GLfloat
    x1,
    GLfloat y1, GLfloat
    x2,
    GLfloat y2
    );

    GLBINDING_API void glRectfv(const GLfloat *v1, const GLfloat *v2);

    GLBINDING_API void glRecti(GLint
    x1,
    GLint y1, GLint
    x2,
    GLint y2
    );

    GLBINDING_API void glRectiv(const GLint *v1, const GLint *v2);

    GLBINDING_API void glRects(GLshort
    x1,
    GLshort y1, GLshort
    x2,
    GLshort y2
    );

    GLBINDING_API void glRectsv(const GLshort *v1, const GLshort *v2);

    GLBINDING_API void glRectxOES(GLfixed
    x1,
    GLfixed y1, GLfixed
    x2,
    GLfixed y2
    );

    GLBINDING_API void glRectxvOES(const GLfixed *v1, const GLfixed *v2);

    GLBINDING_API void glReferencePlaneSGIX(const GLdouble *equation);

    GLBINDING_API GLboolean
    glReleaseKeyedMutexWin32EXT(GLuint
    memory,
    GLuint64 key
    );

    GLBINDING_API void glReleaseShaderCompiler();

    GLBINDING_API void glRenderGpuMaskNV(GLbitfield
    mask);
    GLBINDING_API GLint
    glRenderMode(GLenum
    mode);
    GLBINDING_API void glRenderbufferStorage(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glRenderbufferStorageEXT(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glRenderbufferStorageMultisample(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glRenderbufferStorageMultisampleAdvancedAMD(GLenum
    target,
    GLsizei samples, GLsizei
    storageSamples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glRenderbufferStorageMultisampleCoverageNV(GLenum
    target,
    GLsizei coverageSamples, GLsizei
    colorSamples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glRenderbufferStorageMultisampleEXT(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glReplacementCodePointerSUN(GLenum
    type,
    GLsizei stride,
    const void **pointer
    );
    GLBINDING_API void glReplacementCodeubSUN(GLubyte
    code);

    GLBINDING_API void glReplacementCodeubvSUN(const GLubyte *code);

    GLBINDING_API void glReplacementCodeuiColor3fVertex3fSUN(GLuint
    rc,
    GLfloat r, GLfloat
    g,
    GLfloat b, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glReplacementCodeuiColor3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint
    rc,
    GLfloat r, GLfloat
    g,
    GLfloat b, GLfloat
    a,
    GLfloat nx, GLfloat
    ny,
    GLfloat nz, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void
    glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *c, const GLfloat *n,
                                                   const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiColor4ubVertex3fSUN(GLuint
    rc,
    GLubyte r, GLubyte
    g,
    GLubyte b, GLubyte
    a,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint *rc, const GLubyte *c, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiNormal3fVertex3fSUN(GLuint
    rc,
    GLfloat nx, GLfloat
    ny,
    GLfloat nz, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiSUN(GLuint
    code);
    GLBINDING_API void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint
    rc,
    GLfloat s, GLfloat
    t,
    GLfloat r, GLfloat
    g,
    GLfloat b, GLfloat
    a,
    GLfloat nx, GLfloat
    ny,
    GLfloat nz, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void
    glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *c,
                                                             const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint
    rc,
    GLfloat s, GLfloat
    t,
    GLfloat nx, GLfloat
    ny,
    GLfloat nz, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void
    glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *n,
                                                      const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint
    rc,
    GLfloat s, GLfloat
    t,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint *rc, const GLfloat *tc, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuiVertex3fSUN(GLuint
    rc,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glReplacementCodeuiVertex3fvSUN(const GLuint *rc, const GLfloat *v);

    GLBINDING_API void glReplacementCodeuivSUN(const GLuint *code);

    GLBINDING_API void glReplacementCodeusSUN(GLushort
    code);

    GLBINDING_API void glReplacementCodeusvSUN(const GLushort *code);

    GLBINDING_API void glRequestResidentProgramsNV(GLsizei
    n,
    const GLuint *programs
    );
    GLBINDING_API void glResetHistogram(GLenum
    target);
    GLBINDING_API void glResetHistogramEXT(GLenum
    target);
    GLBINDING_API void glResetMemoryObjectParameterNV(GLuint
    memory,
    GLenum pname
    );
    GLBINDING_API void glResetMinmax(GLenum
    target);
    GLBINDING_API void glResetMinmaxEXT(GLenum
    target);

    GLBINDING_API void glResizeBuffersMESA();

    GLBINDING_API void glResolveDepthValuesNV();

    GLBINDING_API void glResumeTransformFeedback();

    GLBINDING_API void glResumeTransformFeedbackNV();

    GLBINDING_API void glRotated(GLdouble
    angle,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glRotatef(GLfloat
    angle,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glRotatexOES(GLfixed
    angle,
    GLfixed x, GLfixed
    y,
    GLfixed z
    );

    GLBINDING_API void glSampleCoverage(GLfloat
    value,
    GLboolean invert
    );
    GLBINDING_API void glSampleCoverageARB(GLfloat
    value,
    GLboolean invert
    );
    GLBINDING_API void glSampleMapATI(GLuint
    dst,
    GLuint interp, GLenum
    swizzle);

    GLBINDING_API void glSampleMaskEXT(GLclampf value, GLboolean invert);

    GLBINDING_API void glSampleMaskIndexedNV(GLuint
    index,
    GLbitfield mask
    );

    GLBINDING_API void glSampleMaskSGIS(GLclampf value, GLboolean invert);

    GLBINDING_API void glSampleMaski(GLuint
    maskNumber,
    GLbitfield mask
    );
    GLBINDING_API void glSamplePatternEXT(GLenum
    pattern);
    GLBINDING_API void glSamplePatternSGIS(GLenum
    pattern);
    GLBINDING_API void glSamplerParameterIiv(GLuint
    sampler,
    GLenum pname,
    const GLint *param
    );
    GLBINDING_API void glSamplerParameterIuiv(GLuint
    sampler,
    GLenum pname,
    const GLuint *param
    );
    GLBINDING_API void glSamplerParameterf(GLuint
    sampler,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glSamplerParameterfv(GLuint
    sampler,
    GLenum pname,
    const GLfloat *param
    );
    GLBINDING_API void glSamplerParameteri(GLuint
    sampler,
    GLenum pname, GLint
    param);
    GLBINDING_API void glSamplerParameteriv(GLuint
    sampler,
    GLenum pname,
    const GLint *param
    );
    GLBINDING_API void glScaled(GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glScalef(GLfloat
    x,
    GLfloat y, GLfloat
    z);
    GLBINDING_API void glScalexOES(GLfixed
    x,
    GLfixed y, GLfixed
    z);
    GLBINDING_API void glScissor(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glScissorArrayv(GLuint
    first,
    GLsizei count,
    const GLint *v
    );
    GLBINDING_API void glScissorExclusiveArrayvNV(GLuint
    first,
    GLsizei count,
    const GLint *v
    );
    GLBINDING_API void glScissorExclusiveNV(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glScissorIndexed(GLuint
    index,
    GLint left, GLint
    bottom,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glScissorIndexedv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glSecondaryColor3b(GLbyte
    red,
    GLbyte green, GLbyte
    blue);
    GLBINDING_API void glSecondaryColor3bEXT(GLbyte
    red,
    GLbyte green, GLbyte
    blue);

    GLBINDING_API void glSecondaryColor3bv(const GLbyte *v);

    GLBINDING_API void glSecondaryColor3bvEXT(const GLbyte *v);

    GLBINDING_API void glSecondaryColor3d(GLdouble
    red,
    GLdouble green, GLdouble
    blue);
    GLBINDING_API void glSecondaryColor3dEXT(GLdouble
    red,
    GLdouble green, GLdouble
    blue);

    GLBINDING_API void glSecondaryColor3dv(const GLdouble *v);

    GLBINDING_API void glSecondaryColor3dvEXT(const GLdouble *v);

    GLBINDING_API void glSecondaryColor3f(GLfloat
    red,
    GLfloat green, GLfloat
    blue);
    GLBINDING_API void glSecondaryColor3fEXT(GLfloat
    red,
    GLfloat green, GLfloat
    blue);

    GLBINDING_API void glSecondaryColor3fv(const GLfloat *v);

    GLBINDING_API void glSecondaryColor3fvEXT(const GLfloat *v);

    GLBINDING_API void glSecondaryColor3hNV(GLhalfNV
    red,
    GLhalfNV green, GLhalfNV
    blue);

    GLBINDING_API void glSecondaryColor3hvNV(const GLhalfNV *v);

    GLBINDING_API void glSecondaryColor3i(GLint
    red,
    GLint green, GLint
    blue);
    GLBINDING_API void glSecondaryColor3iEXT(GLint
    red,
    GLint green, GLint
    blue);

    GLBINDING_API void glSecondaryColor3iv(const GLint *v);

    GLBINDING_API void glSecondaryColor3ivEXT(const GLint *v);

    GLBINDING_API void glSecondaryColor3s(GLshort
    red,
    GLshort green, GLshort
    blue);
    GLBINDING_API void glSecondaryColor3sEXT(GLshort
    red,
    GLshort green, GLshort
    blue);

    GLBINDING_API void glSecondaryColor3sv(const GLshort *v);

    GLBINDING_API void glSecondaryColor3svEXT(const GLshort *v);

    GLBINDING_API void glSecondaryColor3ub(GLubyte
    red,
    GLubyte green, GLubyte
    blue);
    GLBINDING_API void glSecondaryColor3ubEXT(GLubyte
    red,
    GLubyte green, GLubyte
    blue);

    GLBINDING_API void glSecondaryColor3ubv(const GLubyte *v);

    GLBINDING_API void glSecondaryColor3ubvEXT(const GLubyte *v);

    GLBINDING_API void glSecondaryColor3ui(GLuint
    red,
    GLuint green, GLuint
    blue);
    GLBINDING_API void glSecondaryColor3uiEXT(GLuint
    red,
    GLuint green, GLuint
    blue);

    GLBINDING_API void glSecondaryColor3uiv(const GLuint *v);

    GLBINDING_API void glSecondaryColor3uivEXT(const GLuint *v);

    GLBINDING_API void glSecondaryColor3us(GLushort
    red,
    GLushort green, GLushort
    blue);
    GLBINDING_API void glSecondaryColor3usEXT(GLushort
    red,
    GLushort green, GLushort
    blue);

    GLBINDING_API void glSecondaryColor3usv(const GLushort *v);

    GLBINDING_API void glSecondaryColor3usvEXT(const GLushort *v);

    GLBINDING_API void glSecondaryColorFormatNV(GLint
    size,
    GLenum type, GLsizei
    stride);
    GLBINDING_API void glSecondaryColorP3ui(GLenum
    type,
    GLuint color
    );
    GLBINDING_API void glSecondaryColorP3uiv(GLenum
    type,
    const GLuint *color
    );
    GLBINDING_API void glSecondaryColorPointer(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glSecondaryColorPointerEXT(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glSecondaryColorPointerListIBM(GLint
    size,
    GLenum type, GLint
    stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glSelectBuffer(GLsizei
    size,
    GLuint *buffer
    );
    GLBINDING_API void glSelectPerfMonitorCountersAMD(GLuint
    monitor,
    GLboolean enable, GLuint
    group,
    GLint numCounters, GLuint
    * counterList);
    GLBINDING_API void glSemaphoreParameterui64vEXT(GLuint
    semaphore,
    GLenum pname,
    const GLuint64 *params
    );
    GLBINDING_API void glSeparableFilter2D(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *row,
    const void *column
    );
    GLBINDING_API void glSeparableFilter2DEXT(GLenum
    target,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *row,
    const void *column
    );
    GLBINDING_API void glSetFenceAPPLE(GLuint
    fence);
    GLBINDING_API void glSetFenceNV(GLuint
    fence,
    GLenum condition
    );
    GLBINDING_API void glSetFragmentShaderConstantATI(GLuint
    dst,
    const GLfloat *value
    );
    GLBINDING_API void glSetInvariantEXT(GLuint
    id,
    GLenum type,
    const void *addr
    );
    GLBINDING_API void glSetLocalConstantEXT(GLuint
    id,
    GLenum type,
    const void *addr
    );
    GLBINDING_API void glSetMultisamplefvAMD(GLenum
    pname,
    GLuint index,
    const GLfloat *val
    );
    GLBINDING_API void glShadeModel(GLenum
    mode);
    GLBINDING_API void glShaderBinary(GLsizei
    count,
    const GLuint *shaders, GLenum
    binaryformat,
    const void *binary, GLsizei
    length);
    GLBINDING_API void glShaderOp1EXT(GLenum
    op,
    GLuint res, GLuint
    arg1);
    GLBINDING_API void glShaderOp2EXT(GLenum
    op,
    GLuint res, GLuint
    arg1,
    GLuint arg2
    );
    GLBINDING_API void glShaderOp3EXT(GLenum
    op,
    GLuint res, GLuint
    arg1,
    GLuint arg2, GLuint
    arg3);
    GLBINDING_API void glShaderSource(GLuint
    shader,
    GLsizei count,
    const GLchar *const *string,
    const GLint *length
    );
    GLBINDING_API void glShaderSourceARB(GLhandleARB
    shaderObj,
    GLsizei count,
    const GLcharARB **string,
    const GLint *length
    );
    GLBINDING_API void glShaderStorageBlockBinding(GLuint
    program,
    GLuint storageBlockIndex, GLuint
    storageBlockBinding);
    GLBINDING_API void glShadingRateImageBarrierNV(GLboolean
    synchronize);
    GLBINDING_API void glShadingRateImagePaletteNV(GLuint
    viewport,
    GLuint first, GLsizei
    count,
    const GLenum *rates
    );
    GLBINDING_API void glShadingRateSampleOrderCustomNV(GLenum
    rate,
    GLuint samples,
    const GLint *locations
    );
    GLBINDING_API void glShadingRateSampleOrderNV(GLenum
    order);
    GLBINDING_API void glSharpenTexFuncSGIS(GLenum
    target,
    GLsizei n,
    const GLfloat *points
    );
    GLBINDING_API void glSignalSemaphoreEXT(GLuint
    semaphore,
    GLuint numBufferBarriers,
    const GLuint *buffers, GLuint
    numTextureBarriers,
    const GLuint *textures,
    const GLenum *dstLayouts
    );
    GLBINDING_API void glSignalVkFenceNV(GLuint64
    vkFence);
    GLBINDING_API void glSignalVkSemaphoreNV(GLuint64
    vkSemaphore);
    GLBINDING_API void glSpecializeShader(GLuint
    shader,
    const GLchar *pEntryPoint, GLuint
    numSpecializationConstants,
    const GLuint *pConstantIndex,
    const GLuint *pConstantValue
    );
    GLBINDING_API void glSpecializeShaderARB(GLuint
    shader,
    const GLchar *pEntryPoint, GLuint
    numSpecializationConstants,
    const GLuint *pConstantIndex,
    const GLuint *pConstantValue
    );
    GLBINDING_API void glSpriteParameterfSGIX(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glSpriteParameterfvSGIX(GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glSpriteParameteriSGIX(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glSpriteParameterivSGIX(GLenum
    pname,
    const GLint *params
    );

    GLBINDING_API void glStartInstrumentsSGIX();

    GLBINDING_API void glStateCaptureNV(GLuint
    state,
    GLenum mode
    );
    GLBINDING_API void glStencilClearTagEXT(GLsizei
    stencilTagBits,
    GLuint stencilClearTag
    );
    GLBINDING_API void glStencilFillPathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLenum fillMode, GLuint
    mask,
    GLenum transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glStencilFillPathNV(GLuint
    path,
    GLenum fillMode, GLuint
    mask);
    GLBINDING_API void glStencilFunc(GLenum
    func,
    GLint ref, GLuint
    mask);
    GLBINDING_API void glStencilFuncSeparate(GLenum
    face,
    GLenum func, GLint
    ref,
    GLuint mask
    );
    GLBINDING_API void glStencilFuncSeparateATI(GLenum
    frontfunc,
    GLenum backfunc, GLint
    ref,
    GLuint mask
    );
    GLBINDING_API void glStencilMask(GLuint
    mask);
    GLBINDING_API void glStencilMaskSeparate(GLenum
    face,
    GLuint mask
    );
    GLBINDING_API void glStencilOp(GLenum
    fail,
    GLenum zfail, GLenum
    zpass);
    GLBINDING_API void glStencilOpSeparate(GLenum
    face,
    GLenum sfail, GLenum
    dpfail,
    GLenum dppass
    );
    GLBINDING_API void glStencilOpSeparateATI(GLenum
    face,
    GLenum sfail, GLenum
    dpfail,
    GLenum dppass
    );
    GLBINDING_API void glStencilOpValueAMD(GLenum
    face,
    GLuint value
    );
    GLBINDING_API void glStencilStrokePathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLint reference, GLuint
    mask,
    GLenum transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glStencilStrokePathNV(GLuint
    path,
    GLint reference, GLuint
    mask);
    GLBINDING_API void glStencilThenCoverFillPathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLenum fillMode, GLuint
    mask,
    GLenum coverMode, GLenum
    transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glStencilThenCoverFillPathNV(GLuint
    path,
    GLenum fillMode, GLuint
    mask,
    GLenum coverMode
    );
    GLBINDING_API void glStencilThenCoverStrokePathInstancedNV(GLsizei
    numPaths,
    GLenum pathNameType,
    const void *paths, GLuint
    pathBase,
    GLint reference, GLuint
    mask,
    GLenum coverMode, GLenum
    transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glStencilThenCoverStrokePathNV(GLuint
    path,
    GLint reference, GLuint
    mask,
    GLenum coverMode
    );
    GLBINDING_API void glStopInstrumentsSGIX(GLint
    marker);
    GLBINDING_API void glStringMarkerGREMEDY(GLsizei
    len,
    const void *string
    );
    GLBINDING_API void glSubpixelPrecisionBiasNV(GLuint
    xbits,
    GLuint ybits
    );
    GLBINDING_API void glSwizzleEXT(GLuint
    res,
    GLuint in, GLenum
    outX,
    GLenum outY, GLenum
    outZ,
    GLenum outW
    );
    GLBINDING_API void glSyncTextureINTEL(GLuint
    texture);

    GLBINDING_API void glTagSampleBufferSGIX();

    GLBINDING_API void glTangent3bEXT(GLbyte
    tx,
    GLbyte ty, GLbyte
    tz);

    GLBINDING_API void glTangent3bvEXT(const GLbyte *v);

    GLBINDING_API void glTangent3dEXT(GLdouble
    tx,
    GLdouble ty, GLdouble
    tz);

    GLBINDING_API void glTangent3dvEXT(const GLdouble *v);

    GLBINDING_API void glTangent3fEXT(GLfloat
    tx,
    GLfloat ty, GLfloat
    tz);

    GLBINDING_API void glTangent3fvEXT(const GLfloat *v);

    GLBINDING_API void glTangent3iEXT(GLint
    tx,
    GLint ty, GLint
    tz);

    GLBINDING_API void glTangent3ivEXT(const GLint *v);

    GLBINDING_API void glTangent3sEXT(GLshort
    tx,
    GLshort ty, GLshort
    tz);

    GLBINDING_API void glTangent3svEXT(const GLshort *v);

    GLBINDING_API void glTangentPointerEXT(GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glTbufferMask3DFX(GLuint
    mask);
    GLBINDING_API void glTessellationFactorAMD(GLfloat
    factor);
    GLBINDING_API void glTessellationModeAMD(GLenum
    mode);
    GLBINDING_API GLboolean
    glTestFenceAPPLE(GLuint
    fence);
    GLBINDING_API GLboolean
    glTestFenceNV(GLuint
    fence);
    GLBINDING_API GLboolean
    glTestObjectAPPLE(GLenum
    object,
    GLuint name
    );
    GLBINDING_API void glTexAttachMemoryNV(GLenum
    target,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glTexBuffer(GLenum
    target,
    GLenum internalformat, GLuint
    buffer);
    GLBINDING_API void glTexBufferARB(GLenum
    target,
    GLenum internalformat, GLuint
    buffer);
    GLBINDING_API void glTexBufferEXT(GLenum
    target,
    GLenum internalformat, GLuint
    buffer);
    GLBINDING_API void glTexBufferRange(GLenum
    target,
    GLenum internalformat, GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size);
    GLBINDING_API void glTexBumpParameterfvATI(GLenum
    pname,
    const GLfloat *param
    );
    GLBINDING_API void glTexBumpParameterivATI(GLenum
    pname,
    const GLint *param
    );
    GLBINDING_API void glTexCoord1bOES(GLbyte
    s);

    GLBINDING_API void glTexCoord1bvOES(const GLbyte *coords);

    GLBINDING_API void glTexCoord1d(GLdouble
    s);

    GLBINDING_API void glTexCoord1dv(const GLdouble *v);

    GLBINDING_API void glTexCoord1f(GLfloat
    s);

    GLBINDING_API void glTexCoord1fv(const GLfloat *v);

    GLBINDING_API void glTexCoord1hNV(GLhalfNV
    s);

    GLBINDING_API void glTexCoord1hvNV(const GLhalfNV *v);

    GLBINDING_API void glTexCoord1i(GLint
    s);

    GLBINDING_API void glTexCoord1iv(const GLint *v);

    GLBINDING_API void glTexCoord1s(GLshort
    s);

    GLBINDING_API void glTexCoord1sv(const GLshort *v);

    GLBINDING_API void glTexCoord1xOES(GLfixed
    s);

    GLBINDING_API void glTexCoord1xvOES(const GLfixed *coords);

    GLBINDING_API void glTexCoord2bOES(GLbyte
    s,
    GLbyte t
    );

    GLBINDING_API void glTexCoord2bvOES(const GLbyte *coords);

    GLBINDING_API void glTexCoord2d(GLdouble
    s,
    GLdouble t
    );

    GLBINDING_API void glTexCoord2dv(const GLdouble *v);

    GLBINDING_API void glTexCoord2f(GLfloat
    s,
    GLfloat t
    );
    GLBINDING_API void glTexCoord2fColor3fVertex3fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    r,
    GLfloat g, GLfloat
    b,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glTexCoord2fColor3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *v);

    GLBINDING_API void glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    r,
    GLfloat g, GLfloat
    b,
    GLfloat a, GLfloat
    nx,
    GLfloat ny, GLfloat
    nz,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void
    glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glTexCoord2fColor4ubVertex3fSUN(GLfloat
    s,
    GLfloat t, GLubyte
    r,
    GLubyte g, GLubyte
    b,
    GLubyte a, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glTexCoord2fColor4ubVertex3fvSUN(const GLfloat *tc, const GLubyte *c, const GLfloat *v);

    GLBINDING_API void glTexCoord2fNormal3fVertex3fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    nx,
    GLfloat ny, GLfloat
    nz,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );

    GLBINDING_API void glTexCoord2fNormal3fVertex3fvSUN(const GLfloat *tc, const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glTexCoord2fVertex3fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glTexCoord2fVertex3fvSUN(const GLfloat *tc, const GLfloat *v);

    GLBINDING_API void glTexCoord2fv(const GLfloat *v);

    GLBINDING_API void glTexCoord2hNV(GLhalfNV
    s,
    GLhalfNV t
    );

    GLBINDING_API void glTexCoord2hvNV(const GLhalfNV *v);

    GLBINDING_API void glTexCoord2i(GLint
    s,
    GLint t
    );

    GLBINDING_API void glTexCoord2iv(const GLint *v);

    GLBINDING_API void glTexCoord2s(GLshort
    s,
    GLshort t
    );

    GLBINDING_API void glTexCoord2sv(const GLshort *v);

    GLBINDING_API void glTexCoord2xOES(GLfixed
    s,
    GLfixed t
    );

    GLBINDING_API void glTexCoord2xvOES(const GLfixed *coords);

    GLBINDING_API void glTexCoord3bOES(GLbyte
    s,
    GLbyte t, GLbyte
    r);

    GLBINDING_API void glTexCoord3bvOES(const GLbyte *coords);

    GLBINDING_API void glTexCoord3d(GLdouble
    s,
    GLdouble t, GLdouble
    r);

    GLBINDING_API void glTexCoord3dv(const GLdouble *v);

    GLBINDING_API void glTexCoord3f(GLfloat
    s,
    GLfloat t, GLfloat
    r);

    GLBINDING_API void glTexCoord3fv(const GLfloat *v);

    GLBINDING_API void glTexCoord3hNV(GLhalfNV
    s,
    GLhalfNV t, GLhalfNV
    r);

    GLBINDING_API void glTexCoord3hvNV(const GLhalfNV *v);

    GLBINDING_API void glTexCoord3i(GLint
    s,
    GLint t, GLint
    r);

    GLBINDING_API void glTexCoord3iv(const GLint *v);

    GLBINDING_API void glTexCoord3s(GLshort
    s,
    GLshort t, GLshort
    r);

    GLBINDING_API void glTexCoord3sv(const GLshort *v);

    GLBINDING_API void glTexCoord3xOES(GLfixed
    s,
    GLfixed t, GLfixed
    r);

    GLBINDING_API void glTexCoord3xvOES(const GLfixed *coords);

    GLBINDING_API void glTexCoord4bOES(GLbyte
    s,
    GLbyte t, GLbyte
    r,
    GLbyte q
    );

    GLBINDING_API void glTexCoord4bvOES(const GLbyte *coords);

    GLBINDING_API void glTexCoord4d(GLdouble
    s,
    GLdouble t, GLdouble
    r,
    GLdouble q
    );

    GLBINDING_API void glTexCoord4dv(const GLdouble *v);

    GLBINDING_API void glTexCoord4f(GLfloat
    s,
    GLfloat t, GLfloat
    r,
    GLfloat q
    );
    GLBINDING_API void glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    p,
    GLfloat q, GLfloat
    r,
    GLfloat g, GLfloat
    b,
    GLfloat a, GLfloat
    nx,
    GLfloat ny, GLfloat
    nz,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);

    GLBINDING_API void
    glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);

    GLBINDING_API void glTexCoord4fVertex4fSUN(GLfloat
    s,
    GLfloat t, GLfloat
    p,
    GLfloat q, GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );

    GLBINDING_API void glTexCoord4fVertex4fvSUN(const GLfloat *tc, const GLfloat *v);

    GLBINDING_API void glTexCoord4fv(const GLfloat *v);

    GLBINDING_API void glTexCoord4hNV(GLhalfNV
    s,
    GLhalfNV t, GLhalfNV
    r,
    GLhalfNV q
    );

    GLBINDING_API void glTexCoord4hvNV(const GLhalfNV *v);

    GLBINDING_API void glTexCoord4i(GLint
    s,
    GLint t, GLint
    r,
    GLint q
    );

    GLBINDING_API void glTexCoord4iv(const GLint *v);

    GLBINDING_API void glTexCoord4s(GLshort
    s,
    GLshort t, GLshort
    r,
    GLshort q
    );

    GLBINDING_API void glTexCoord4sv(const GLshort *v);

    GLBINDING_API void glTexCoord4xOES(GLfixed
    s,
    GLfixed t, GLfixed
    r,
    GLfixed q
    );

    GLBINDING_API void glTexCoord4xvOES(const GLfixed *coords);

    GLBINDING_API void glTexCoordFormatNV(GLint
    size,
    GLenum type, GLsizei
    stride);
    GLBINDING_API void glTexCoordP1ui(GLenum
    type,
    GLuint coords
    );
    GLBINDING_API void glTexCoordP1uiv(GLenum
    type,
    const GLuint *coords
    );
    GLBINDING_API void glTexCoordP2ui(GLenum
    type,
    GLuint coords
    );
    GLBINDING_API void glTexCoordP2uiv(GLenum
    type,
    const GLuint *coords
    );
    GLBINDING_API void glTexCoordP3ui(GLenum
    type,
    GLuint coords
    );
    GLBINDING_API void glTexCoordP3uiv(GLenum
    type,
    const GLuint *coords
    );
    GLBINDING_API void glTexCoordP4ui(GLenum
    type,
    GLuint coords
    );
    GLBINDING_API void glTexCoordP4uiv(GLenum
    type,
    const GLuint *coords
    );
    GLBINDING_API void glTexCoordPointer(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glTexCoordPointerEXT(GLint
    size,
    GLenum type, GLsizei
    stride,
    GLsizei count,
    const void *pointer
    );
    GLBINDING_API void glTexCoordPointerListIBM(GLint
    size,
    GLenum type, GLint
    stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glTexCoordPointervINTEL(GLint
    size,
    GLenum type,
    const void **pointer
    );
    GLBINDING_API void glTexEnvf(GLenum
    target,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glTexEnvfv(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glTexEnvi(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glTexEnviv(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTexEnvxOES(GLenum
    target,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glTexEnvxvOES(GLenum
    target,
    GLenum pname,
    const GLfixed *params
    );
    GLBINDING_API void glTexFilterFuncSGIS(GLenum
    target,
    GLenum filter, GLsizei
    n,
    const GLfloat *weights
    );
    GLBINDING_API void glTexGend(GLenum
    coord,
    GLenum pname, GLdouble
    param);
    GLBINDING_API void glTexGendv(GLenum
    coord,
    GLenum pname,
    const GLdouble *params
    );
    GLBINDING_API void glTexGenf(GLenum
    coord,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glTexGenfv(GLenum
    coord,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glTexGeni(GLenum
    coord,
    GLenum pname, GLint
    param);
    GLBINDING_API void glTexGeniv(GLenum
    coord,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTexGenxOES(GLenum
    coord,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glTexGenxvOES(GLenum
    coord,
    GLenum pname,
    const GLfixed *params
    );
    GLBINDING_API void glTexImage1D(GLenum
    target,
    GLint level, GLint
    internalformat,
    GLsizei width, GLint
    border,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTexImage2D(GLenum
    target,
    GLint level, GLint
    internalformat,
    GLsizei width, GLsizei
    height,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexImage2DMultisample(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedsamplelocations
    );
    GLBINDING_API void glTexImage2DMultisampleCoverageNV(GLenum
    target,
    GLsizei coverageSamples, GLsizei
    colorSamples,
    GLint internalFormat, GLsizei
    width,
    GLsizei height, GLboolean
    fixedSampleLocations);
    GLBINDING_API void glTexImage3D(GLenum
    target,
    GLint level, GLint
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLint
    border,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTexImage3DEXT(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLint
    border,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTexImage3DMultisample(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedsamplelocations);
    GLBINDING_API void glTexImage3DMultisampleCoverageNV(GLenum
    target,
    GLsizei coverageSamples, GLsizei
    colorSamples,
    GLint internalFormat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLboolean fixedSampleLocations
    );
    GLBINDING_API void glTexImage4DSGIS(GLenum
    target,
    GLint level, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLsizei
    size4d,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexPageCommitmentARB(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    commit);
    GLBINDING_API void glTexParameterIiv(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTexParameterIivEXT(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTexParameterIuiv(GLenum
    target,
    GLenum pname,
    const GLuint *params
    );
    GLBINDING_API void glTexParameterIuivEXT(GLenum
    target,
    GLenum pname,
    const GLuint *params
    );
    GLBINDING_API void glTexParameterf(GLenum
    target,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glTexParameterfv(GLenum
    target,
    GLenum pname,
    const GLfloat *params
    );
    GLBINDING_API void glTexParameteri(GLenum
    target,
    GLenum pname, GLint
    param);
    GLBINDING_API void glTexParameteriv(GLenum
    target,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTexParameterxOES(GLenum
    target,
    GLenum pname, GLfixed
    param);
    GLBINDING_API void glTexParameterxvOES(GLenum
    target,
    GLenum pname,
    const GLfixed *params
    );
    GLBINDING_API void glTexRenderbufferNV(GLenum
    target,
    GLuint renderbuffer
    );
    GLBINDING_API void glTexStorage1D(GLenum
    target,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width
    );
    GLBINDING_API void glTexStorage2D(GLenum
    target,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glTexStorage2DMultisample(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedsamplelocations
    );
    GLBINDING_API void glTexStorage3D(GLenum
    target,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth
    );
    GLBINDING_API void glTexStorage3DMultisample(GLenum
    target,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedsamplelocations);
    GLBINDING_API void glTexStorageMem1DEXT(GLenum
    target,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTexStorageMem2DEXT(GLenum
    target,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glTexStorageMem2DMultisampleEXT(GLenum
    target,
    GLsizei samples, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedSampleLocations, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTexStorageMem3DEXT(GLenum
    target,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTexStorageMem3DMultisampleEXT(GLenum
    target,
    GLsizei samples, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedSampleLocations,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glTexStorageSparseAMD(GLenum
    target,
    GLenum internalFormat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLsizei layers, TextureStorageMaskAMD
    flags);
    GLBINDING_API void glTexSubImage1D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage1DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage2D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage2DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage3D(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage3DEXT(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTexSubImage4DSGIS(GLenum
    target,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLint woffset, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLsizei size4d, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureAttachMemoryNV(GLuint
    texture,
    GLuint memory, GLuint64
    offset);

    GLBINDING_API void glTextureBarrier();

    GLBINDING_API void glTextureBarrierNV();

    GLBINDING_API void glTextureBuffer(GLuint
    texture,
    GLenum internalformat, GLuint
    buffer);
    GLBINDING_API void glTextureBufferEXT(GLuint
    texture,
    GLenum target, GLenum
    internalformat,
    GLuint buffer
    );
    GLBINDING_API void glTextureBufferRange(GLuint
    texture,
    GLenum internalformat, GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size);
    GLBINDING_API void glTextureBufferRangeEXT(GLuint
    texture,
    GLenum target, GLenum
    internalformat,
    GLuint buffer, GLintptr
    offset,
    GLsizeiptr size
    );
    GLBINDING_API void glTextureColorMaskSGIS(GLboolean
    red,
    GLboolean green, GLboolean
    blue,
    GLboolean alpha
    );
    GLBINDING_API void glTextureImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLsizei height, GLint
    border,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTextureImage2DMultisampleCoverageNV(GLuint
    texture,
    GLenum target, GLsizei
    coverageSamples,
    GLsizei colorSamples, GLint
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedSampleLocations
    );
    GLBINDING_API void glTextureImage2DMultisampleNV(GLuint
    texture,
    GLenum target, GLsizei
    samples,
    GLint internalFormat, GLsizei
    width,
    GLsizei height, GLboolean
    fixedSampleLocations);
    GLBINDING_API void glTextureImage3DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLint border, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureImage3DMultisampleCoverageNV(GLuint
    texture,
    GLenum target, GLsizei
    coverageSamples,
    GLsizei colorSamples, GLint
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedSampleLocations);
    GLBINDING_API void glTextureImage3DMultisampleNV(GLuint
    texture,
    GLenum target, GLsizei
    samples,
    GLint internalFormat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLboolean fixedSampleLocations
    );
    GLBINDING_API void glTextureLightEXT(GLenum
    pname);
    GLBINDING_API void glTextureMaterialEXT(GLenum
    face,
    GLenum mode
    );
    GLBINDING_API void glTextureNormalEXT(GLenum
    mode);
    GLBINDING_API void glTexturePageCommitmentEXT(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    commit);
    GLBINDING_API void glTextureParameterIiv(GLuint
    texture,
    GLenum pname,
    const GLint *params
    );
    GLBINDING_API void glTextureParameterIivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glTextureParameterIuiv(GLuint
    texture,
    GLenum pname,
    const GLuint *params
    );
    GLBINDING_API void glTextureParameterIuivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    const GLuint *params
    );
    GLBINDING_API void glTextureParameterf(GLuint
    texture,
    GLenum pname, GLfloat
    param);
    GLBINDING_API void glTextureParameterfEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glTextureParameterfv(GLuint
    texture,
    GLenum pname,
    const GLfloat *param
    );
    GLBINDING_API void glTextureParameterfvEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glTextureParameteri(GLuint
    texture,
    GLenum pname, GLint
    param);
    GLBINDING_API void glTextureParameteriEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glTextureParameteriv(GLuint
    texture,
    GLenum pname,
    const GLint *param
    );
    GLBINDING_API void glTextureParameterivEXT(GLuint
    texture,
    GLenum target, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glTextureRangeAPPLE(GLenum
    target,
    GLsizei length,
    const void *pointer
    );
    GLBINDING_API void glTextureRenderbufferEXT(GLuint
    texture,
    GLenum target, GLuint
    renderbuffer);
    GLBINDING_API void glTextureStorage1D(GLuint
    texture,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width
    );
    GLBINDING_API void glTextureStorage1DEXT(GLuint
    texture,
    GLenum target, GLsizei
    levels,
    GLenum internalformat, GLsizei
    width);
    GLBINDING_API void glTextureStorage2D(GLuint
    texture,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width, GLsizei
    height);
    GLBINDING_API void glTextureStorage2DEXT(GLuint
    texture,
    GLenum target, GLsizei
    levels,
    GLenum internalformat, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glTextureStorage2DMultisample(GLuint
    texture,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedsamplelocations
    );
    GLBINDING_API void glTextureStorage2DMultisampleEXT(GLuint
    texture,
    GLenum target, GLsizei
    samples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLboolean
    fixedsamplelocations);
    GLBINDING_API void glTextureStorage3D(GLuint
    texture,
    GLsizei levels, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth
    );
    GLBINDING_API void glTextureStorage3DEXT(GLuint
    texture,
    GLenum target, GLsizei
    levels,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth);
    GLBINDING_API void glTextureStorage3DMultisample(GLuint
    texture,
    GLsizei samples, GLenum
    internalformat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedsamplelocations);
    GLBINDING_API void glTextureStorage3DMultisampleEXT(GLuint
    texture,
    GLenum target, GLsizei
    samples,
    GLenum internalformat, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLboolean fixedsamplelocations
    );
    GLBINDING_API void glTextureStorageMem1DEXT(GLuint
    texture,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTextureStorageMem2DEXT(GLuint
    texture,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glTextureStorageMem2DMultisampleEXT(GLuint
    texture,
    GLsizei samples, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLboolean fixedSampleLocations, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTextureStorageMem3DEXT(GLuint
    texture,
    GLsizei levels, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLuint
    memory,
    GLuint64 offset
    );
    GLBINDING_API void glTextureStorageMem3DMultisampleEXT(GLuint
    texture,
    GLsizei samples, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLboolean
    fixedSampleLocations,
    GLuint memory, GLuint64
    offset);
    GLBINDING_API void glTextureStorageSparseAMD(GLuint
    texture,
    GLenum target, GLenum
    internalFormat,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLsizei
    layers,
    TextureStorageMaskAMD flags
    );
    GLBINDING_API void glTextureSubImage1D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLsizei width, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureSubImage1DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLsizei
    width,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTextureSubImage2D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLsizei
    width,
    GLsizei height, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureSubImage2DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLsizei width, GLsizei
    height,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTextureSubImage3D(GLuint
    texture,
    GLint level, GLint
    xoffset,
    GLint yoffset, GLint
    zoffset,
    GLsizei width, GLsizei
    height,
    GLsizei depth, GLenum
    format,
    GLenum type,
    const void *pixels
    );
    GLBINDING_API void glTextureSubImage3DEXT(GLuint
    texture,
    GLenum target, GLint
    level,
    GLint xoffset, GLint
    yoffset,
    GLint zoffset, GLsizei
    width,
    GLsizei height, GLsizei
    depth,
    GLenum format, GLenum
    type,
    const void *pixels
    );
    GLBINDING_API void glTextureView(GLuint
    texture,
    GLenum target, GLuint
    origtexture,
    GLenum internalformat, GLuint
    minlevel,
    GLuint numlevels, GLuint
    minlayer,
    GLuint numlayers
    );
    GLBINDING_API void glTrackMatrixNV(GLenum
    target,
    GLuint address, GLenum
    matrix,
    GLenum transform
    );
    GLBINDING_API void glTransformFeedbackAttribsNV(GLsizei
    count,
    const GLint *attribs, GLenum
    bufferMode);
    GLBINDING_API void glTransformFeedbackBufferBase(GLuint
    xfb,
    GLuint index, GLuint
    buffer);
    GLBINDING_API void glTransformFeedbackBufferRange(GLuint
    xfb,
    GLuint index, GLuint
    buffer,
    GLintptr offset, GLsizeiptr
    size);
    GLBINDING_API void glTransformFeedbackStreamAttribsNV(GLsizei
    count,
    const GLint *attribs, GLsizei
    nbuffers,
    const GLint *bufstreams, GLenum
    bufferMode);
    GLBINDING_API void glTransformFeedbackVaryings(GLuint
    program,
    GLsizei count,
    const GLchar *const *varyings, GLenum
    bufferMode);
    GLBINDING_API void glTransformFeedbackVaryingsEXT(GLuint
    program,
    GLsizei count,
    const GLchar *const *varyings, GLenum
    bufferMode);
    GLBINDING_API void glTransformFeedbackVaryingsNV(GLuint
    program,
    GLsizei count,
    const GLint *locations, GLenum
    bufferMode);
    GLBINDING_API void glTransformPathNV(GLuint
    resultPath,
    GLuint srcPath, GLenum
    transformType,
    const GLfloat *transformValues
    );
    GLBINDING_API void glTranslated(GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glTranslatef(GLfloat
    x,
    GLfloat y, GLfloat
    z);
    GLBINDING_API void glTranslatexOES(GLfixed
    x,
    GLfixed y, GLfixed
    z);

    GLBINDING_API void glUniform1d(GLint
    location,
    GLdouble x
    );
    GLBINDING_API void glUniform1dv(GLint
    location,
    GLsizei count,
    const GLdouble *value
    );
    GLBINDING_API void glUniform1f(GLint
    location,
    GLfloat v0
    );
    GLBINDING_API void glUniform1fARB(GLint
    location,
    GLfloat v0
    );
    GLBINDING_API void glUniform1fv(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform1fvARB(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform1i(GLint
    location,
    GLint v0
    );
    GLBINDING_API void glUniform1i64ARB(GLint
    location,
    GLint64 x
    );
    GLBINDING_API void glUniform1i64NV(GLint
    location,
    GLint64EXT x
    );
    GLBINDING_API void glUniform1i64vARB(GLint
    location,
    GLsizei count,
    const GLint64 *value
    );
    GLBINDING_API void glUniform1i64vNV(GLint
    location,
    GLsizei count,
    const GLint64EXT *value
    );
    GLBINDING_API void glUniform1iARB(GLint
    location,
    GLint v0
    );
    GLBINDING_API void glUniform1iv(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform1ivARB(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform1ui(GLint
    location,
    GLuint v0
    );
    GLBINDING_API void glUniform1ui64ARB(GLint
    location,
    GLuint64 x
    );
    GLBINDING_API void glUniform1ui64NV(GLint
    location,
    GLuint64EXT x
    );
    GLBINDING_API void glUniform1ui64vARB(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniform1ui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glUniform1uiEXT(GLint
    location,
    GLuint v0
    );
    GLBINDING_API void glUniform1uiv(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform1uivEXT(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform2d(GLint
    location,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glUniform2dv(GLint
    location,
    GLsizei count,
    const GLdouble *value
    );
    GLBINDING_API void glUniform2f(GLint
    location,
    GLfloat v0, GLfloat
    v1);
    GLBINDING_API void glUniform2fARB(GLint
    location,
    GLfloat v0, GLfloat
    v1);
    GLBINDING_API void glUniform2fv(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform2fvARB(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform2i(GLint
    location,
    GLint v0, GLint
    v1);
    GLBINDING_API void glUniform2i64ARB(GLint
    location,
    GLint64 x, GLint64
    y);
    GLBINDING_API void glUniform2i64NV(GLint
    location,
    GLint64EXT x, GLint64EXT
    y);
    GLBINDING_API void glUniform2i64vARB(GLint
    location,
    GLsizei count,
    const GLint64 *value
    );
    GLBINDING_API void glUniform2i64vNV(GLint
    location,
    GLsizei count,
    const GLint64EXT *value
    );
    GLBINDING_API void glUniform2iARB(GLint
    location,
    GLint v0, GLint
    v1);
    GLBINDING_API void glUniform2iv(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform2ivARB(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform2ui(GLint
    location,
    GLuint v0, GLuint
    v1);
    GLBINDING_API void glUniform2ui64ARB(GLint
    location,
    GLuint64 x, GLuint64
    y);
    GLBINDING_API void glUniform2ui64NV(GLint
    location,
    GLuint64EXT x, GLuint64EXT
    y);
    GLBINDING_API void glUniform2ui64vARB(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniform2ui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glUniform2uiEXT(GLint
    location,
    GLuint v0, GLuint
    v1);
    GLBINDING_API void glUniform2uiv(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform2uivEXT(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform3d(GLint
    location,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glUniform3dv(GLint
    location,
    GLsizei count,
    const GLdouble *value
    );
    GLBINDING_API void glUniform3f(GLint
    location,
    GLfloat v0, GLfloat
    v1,
    GLfloat v2
    );
    GLBINDING_API void glUniform3fARB(GLint
    location,
    GLfloat v0, GLfloat
    v1,
    GLfloat v2
    );
    GLBINDING_API void glUniform3fv(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform3fvARB(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform3i(GLint
    location,
    GLint v0, GLint
    v1,
    GLint v2
    );
    GLBINDING_API void glUniform3i64ARB(GLint
    location,
    GLint64 x, GLint64
    y,
    GLint64 z
    );
    GLBINDING_API void glUniform3i64NV(GLint
    location,
    GLint64EXT x, GLint64EXT
    y,
    GLint64EXT z
    );
    GLBINDING_API void glUniform3i64vARB(GLint
    location,
    GLsizei count,
    const GLint64 *value
    );
    GLBINDING_API void glUniform3i64vNV(GLint
    location,
    GLsizei count,
    const GLint64EXT *value
    );
    GLBINDING_API void glUniform3iARB(GLint
    location,
    GLint v0, GLint
    v1,
    GLint v2
    );
    GLBINDING_API void glUniform3iv(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform3ivARB(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform3ui(GLint
    location,
    GLuint v0, GLuint
    v1,
    GLuint v2
    );
    GLBINDING_API void glUniform3ui64ARB(GLint
    location,
    GLuint64 x, GLuint64
    y,
    GLuint64 z
    );
    GLBINDING_API void glUniform3ui64NV(GLint
    location,
    GLuint64EXT x, GLuint64EXT
    y,
    GLuint64EXT z
    );
    GLBINDING_API void glUniform3ui64vARB(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniform3ui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glUniform3uiEXT(GLint
    location,
    GLuint v0, GLuint
    v1,
    GLuint v2
    );
    GLBINDING_API void glUniform3uiv(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform3uivEXT(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform4d(GLint
    location,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glUniform4dv(GLint
    location,
    GLsizei count,
    const GLdouble *value
    );
    GLBINDING_API void glUniform4f(GLint
    location,
    GLfloat v0, GLfloat
    v1,
    GLfloat v2, GLfloat
    v3);
    GLBINDING_API void glUniform4fARB(GLint
    location,
    GLfloat v0, GLfloat
    v1,
    GLfloat v2, GLfloat
    v3);
    GLBINDING_API void glUniform4fv(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform4fvARB(GLint
    location,
    GLsizei count,
    const GLfloat *value
    );
    GLBINDING_API void glUniform4i(GLint
    location,
    GLint v0, GLint
    v1,
    GLint v2, GLint
    v3);
    GLBINDING_API void glUniform4i64ARB(GLint
    location,
    GLint64 x, GLint64
    y,
    GLint64 z, GLint64
    w);
    GLBINDING_API void glUniform4i64NV(GLint
    location,
    GLint64EXT x, GLint64EXT
    y,
    GLint64EXT z, GLint64EXT
    w);
    GLBINDING_API void glUniform4i64vARB(GLint
    location,
    GLsizei count,
    const GLint64 *value
    );
    GLBINDING_API void glUniform4i64vNV(GLint
    location,
    GLsizei count,
    const GLint64EXT *value
    );
    GLBINDING_API void glUniform4iARB(GLint
    location,
    GLint v0, GLint
    v1,
    GLint v2, GLint
    v3);
    GLBINDING_API void glUniform4iv(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform4ivARB(GLint
    location,
    GLsizei count,
    const GLint *value
    );
    GLBINDING_API void glUniform4ui(GLint
    location,
    GLuint v0, GLuint
    v1,
    GLuint v2, GLuint
    v3);
    GLBINDING_API void glUniform4ui64ARB(GLint
    location,
    GLuint64 x, GLuint64
    y,
    GLuint64 z, GLuint64
    w);
    GLBINDING_API void glUniform4ui64NV(GLint
    location,
    GLuint64EXT x, GLuint64EXT
    y,
    GLuint64EXT z, GLuint64EXT
    w);
    GLBINDING_API void glUniform4ui64vARB(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniform4ui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64EXT *value
    );
    GLBINDING_API void glUniform4uiEXT(GLint
    location,
    GLuint v0, GLuint
    v1,
    GLuint v2, GLuint
    v3);
    GLBINDING_API void glUniform4uiv(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniform4uivEXT(GLint
    location,
    GLsizei count,
    const GLuint *value
    );
    GLBINDING_API void glUniformBlockBinding(GLuint
    program,
    GLuint uniformBlockIndex, GLuint
    uniformBlockBinding);
    GLBINDING_API void glUniformBufferEXT(GLuint
    program,
    GLint location, GLuint
    buffer);
    GLBINDING_API void glUniformHandleui64ARB(GLint
    location,
    GLuint64 value
    );
    GLBINDING_API void glUniformHandleui64NV(GLint
    location,
    GLuint64 value
    );
    GLBINDING_API void glUniformHandleui64vARB(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniformHandleui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64 *value
    );
    GLBINDING_API void glUniformMatrix2dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix2fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix2fvARB(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix2x3dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix2x3fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix2x4dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix2x4fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix3dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix3fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix3fvARB(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix3x2dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix3x2fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix3x4dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix3x4fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix4dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix4fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix4fvARB(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix4x2dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix4x2fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformMatrix4x3dv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLdouble *value
    );
    GLBINDING_API void glUniformMatrix4x3fv(GLint
    location,
    GLsizei count, GLboolean
    transpose,
    const GLfloat *value
    );
    GLBINDING_API void glUniformSubroutinesuiv(GLenum
    shadertype,
    GLsizei count,
    const GLuint *indices
    );
    GLBINDING_API void glUniformui64NV(GLint
    location,
    GLuint64EXT value
    );
    GLBINDING_API void glUniformui64vNV(GLint
    location,
    GLsizei count,
    const GLuint64EXT *value
    );

    GLBINDING_API void glUnlockArraysEXT();

    GLBINDING_API GLboolean
    glUnmapBuffer(GLenum
    target);
    GLBINDING_API GLboolean
    glUnmapBufferARB(GLenum
    target);
    GLBINDING_API GLboolean
    glUnmapNamedBuffer(GLuint
    buffer);
    GLBINDING_API GLboolean
    glUnmapNamedBufferEXT(GLuint
    buffer);
    GLBINDING_API void glUnmapObjectBufferATI(GLuint
    buffer);
    GLBINDING_API void glUnmapTexture2DINTEL(GLuint
    texture,
    GLint level
    );
    GLBINDING_API void glUpdateObjectBufferATI(GLuint
    buffer,
    GLuint offset, GLsizei
    size,
    const void *pointer, GLenum
    preserve);
    GLBINDING_API void glUseProgram(GLuint
    program);
    GLBINDING_API void glUseProgramObjectARB(GLhandleARB
    programObj);
    GLBINDING_API void glUseProgramStages(GLuint
    pipeline,
    UseProgramStageMask stages, GLuint
    program);
    GLBINDING_API void glUseShaderProgramEXT(GLenum
    type,
    GLuint program
    );

    GLBINDING_API void glVDPAUFiniNV();

    GLBINDING_API void
    glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

    GLBINDING_API void glVDPAUInitNV(const void *vdpDevice, const void *getProcAddress);

    GLBINDING_API GLboolean
    glVDPAUIsSurfaceNV(GLvdpauSurfaceNV
    surface);
    GLBINDING_API void glVDPAUMapSurfacesNV(GLsizei
    numSurfaces,
    const GLvdpauSurfaceNV *surfaces
    );
    GLBINDING_API GLvdpauSurfaceNV

    glVDPAURegisterOutputSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames,
                                   const GLuint *textureNames);

    GLBINDING_API GLvdpauSurfaceNV

    glVDPAURegisterVideoSurfaceNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames,
                                  const GLuint *textureNames);

    GLBINDING_API GLvdpauSurfaceNV

    glVDPAURegisterVideoSurfaceWithPictureStructureNV(const void *vdpSurface, GLenum target, GLsizei numTextureNames,
                                                      const GLuint *textureNames, GLboolean isFrameStructure);

    GLBINDING_API void glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV
    surface,
    GLenum access
    );
    GLBINDING_API void glVDPAUUnmapSurfacesNV(GLsizei
    numSurface,
    const GLvdpauSurfaceNV *surfaces
    );
    GLBINDING_API void glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV
    surface);
    GLBINDING_API void glValidateProgram(GLuint
    program);
    GLBINDING_API void glValidateProgramARB(GLhandleARB
    programObj);
    GLBINDING_API void glValidateProgramPipeline(GLuint
    pipeline);
    GLBINDING_API void glVariantArrayObjectATI(GLuint
    id,
    GLenum type, GLsizei
    stride,
    GLuint buffer, GLuint
    offset);
    GLBINDING_API void glVariantPointerEXT(GLuint
    id,
    GLenum type, GLuint
    stride,
    const void *addr
    );
    GLBINDING_API void glVariantbvEXT(GLuint
    id,
    const GLbyte *addr
    );
    GLBINDING_API void glVariantdvEXT(GLuint
    id,
    const GLdouble *addr
    );
    GLBINDING_API void glVariantfvEXT(GLuint
    id,
    const GLfloat *addr
    );
    GLBINDING_API void glVariantivEXT(GLuint
    id,
    const GLint *addr
    );
    GLBINDING_API void glVariantsvEXT(GLuint
    id,
    const GLshort *addr
    );
    GLBINDING_API void glVariantubvEXT(GLuint
    id,
    const GLubyte *addr
    );
    GLBINDING_API void glVariantuivEXT(GLuint
    id,
    const GLuint *addr
    );
    GLBINDING_API void glVariantusvEXT(GLuint
    id,
    const GLushort *addr
    );
    GLBINDING_API void glVertex2bOES(GLbyte
    x,
    GLbyte y
    );

    GLBINDING_API void glVertex2bvOES(const GLbyte *coords);

    GLBINDING_API void glVertex2d(GLdouble
    x,
    GLdouble y
    );

    GLBINDING_API void glVertex2dv(const GLdouble *v);

    GLBINDING_API void glVertex2f(GLfloat
    x,
    GLfloat y
    );

    GLBINDING_API void glVertex2fv(const GLfloat *v);

    GLBINDING_API void glVertex2hNV(GLhalfNV
    x,
    GLhalfNV y
    );

    GLBINDING_API void glVertex2hvNV(const GLhalfNV *v);

    GLBINDING_API void glVertex2i(GLint
    x,
    GLint y
    );

    GLBINDING_API void glVertex2iv(const GLint *v);

    GLBINDING_API void glVertex2s(GLshort
    x,
    GLshort y
    );

    GLBINDING_API void glVertex2sv(const GLshort *v);

    GLBINDING_API void glVertex2xOES(GLfixed
    x);

    GLBINDING_API void glVertex2xvOES(const GLfixed *coords);

    GLBINDING_API void glVertex3bOES(GLbyte
    x,
    GLbyte y, GLbyte
    z);

    GLBINDING_API void glVertex3bvOES(const GLbyte *coords);

    GLBINDING_API void glVertex3d(GLdouble
    x,
    GLdouble y, GLdouble
    z);

    GLBINDING_API void glVertex3dv(const GLdouble *v);

    GLBINDING_API void glVertex3f(GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glVertex3fv(const GLfloat *v);

    GLBINDING_API void glVertex3hNV(GLhalfNV
    x,
    GLhalfNV y, GLhalfNV
    z);

    GLBINDING_API void glVertex3hvNV(const GLhalfNV *v);

    GLBINDING_API void glVertex3i(GLint
    x,
    GLint y, GLint
    z);

    GLBINDING_API void glVertex3iv(const GLint *v);

    GLBINDING_API void glVertex3s(GLshort
    x,
    GLshort y, GLshort
    z);

    GLBINDING_API void glVertex3sv(const GLshort *v);

    GLBINDING_API void glVertex3xOES(GLfixed
    x,
    GLfixed y
    );

    GLBINDING_API void glVertex3xvOES(const GLfixed *coords);

    GLBINDING_API void glVertex4bOES(GLbyte
    x,
    GLbyte y, GLbyte
    z,
    GLbyte w
    );

    GLBINDING_API void glVertex4bvOES(const GLbyte *coords);

    GLBINDING_API void glVertex4d(GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );

    GLBINDING_API void glVertex4dv(const GLdouble *v);

    GLBINDING_API void glVertex4f(GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );

    GLBINDING_API void glVertex4fv(const GLfloat *v);

    GLBINDING_API void glVertex4hNV(GLhalfNV
    x,
    GLhalfNV y, GLhalfNV
    z,
    GLhalfNV w
    );

    GLBINDING_API void glVertex4hvNV(const GLhalfNV *v);

    GLBINDING_API void glVertex4i(GLint
    x,
    GLint y, GLint
    z,
    GLint w
    );

    GLBINDING_API void glVertex4iv(const GLint *v);

    GLBINDING_API void glVertex4s(GLshort
    x,
    GLshort y, GLshort
    z,
    GLshort w
    );

    GLBINDING_API void glVertex4sv(const GLshort *v);

    GLBINDING_API void glVertex4xOES(GLfixed
    x,
    GLfixed y, GLfixed
    z);

    GLBINDING_API void glVertex4xvOES(const GLfixed *coords);

    GLBINDING_API void glVertexArrayAttribBinding(GLuint
    vaobj,
    GLuint attribindex, GLuint
    bindingindex);
    GLBINDING_API void glVertexArrayAttribFormat(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLboolean
    normalized,
    GLuint relativeoffset
    );
    GLBINDING_API void glVertexArrayAttribIFormat(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLuint
    relativeoffset);
    GLBINDING_API void glVertexArrayAttribLFormat(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLuint
    relativeoffset);
    GLBINDING_API void glVertexArrayBindVertexBufferEXT(GLuint
    vaobj,
    GLuint bindingindex, GLuint
    buffer,
    GLintptr offset, GLsizei
    stride);
    GLBINDING_API void glVertexArrayBindingDivisor(GLuint
    vaobj,
    GLuint bindingindex, GLuint
    divisor);
    GLBINDING_API void glVertexArrayColorOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLint
    size,
    GLenum type, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexArrayEdgeFlagOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexArrayElementBuffer(GLuint
    vaobj,
    GLuint buffer
    );
    GLBINDING_API void glVertexArrayFogCoordOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayIndexOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayMultiTexCoordOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLenum
    texunit,
    GLint size, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayNormalOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayParameteriAPPLE(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glVertexArrayRangeAPPLE(GLsizei
    length,
    void *pointer
    );
    GLBINDING_API void glVertexArrayRangeNV(GLsizei
    length,
    const void *pointer
    );
    GLBINDING_API void glVertexArraySecondaryColorOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLint
    size,
    GLenum type, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexArrayTexCoordOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLint
    size,
    GLenum type, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexArrayVertexAttribBindingEXT(GLuint
    vaobj,
    GLuint attribindex, GLuint
    bindingindex);
    GLBINDING_API void glVertexArrayVertexAttribDivisorEXT(GLuint
    vaobj,
    GLuint index, GLuint
    divisor);
    GLBINDING_API void glVertexArrayVertexAttribFormatEXT(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLboolean
    normalized,
    GLuint relativeoffset
    );
    GLBINDING_API void glVertexArrayVertexAttribIFormatEXT(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLuint
    relativeoffset);
    GLBINDING_API void glVertexArrayVertexAttribIOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayVertexAttribLFormatEXT(GLuint
    vaobj,
    GLuint attribindex, GLint
    size,
    GLenum type, GLuint
    relativeoffset);
    GLBINDING_API void glVertexArrayVertexAttribLOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride, GLintptr
    offset);
    GLBINDING_API void glVertexArrayVertexAttribOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLuint
    index,
    GLint size, GLenum
    type,
    GLboolean normalized, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexArrayVertexBindingDivisorEXT(GLuint
    vaobj,
    GLuint bindingindex, GLuint
    divisor);
    GLBINDING_API void glVertexArrayVertexBuffer(GLuint
    vaobj,
    GLuint bindingindex, GLuint
    buffer,
    GLintptr offset, GLsizei
    stride);
    GLBINDING_API void glVertexArrayVertexBuffers(GLuint
    vaobj,
    GLuint first, GLsizei
    count,
    const GLuint *buffers,
    const GLintptr *offsets,
    const GLsizei *strides
    );
    GLBINDING_API void glVertexArrayVertexOffsetEXT(GLuint
    vaobj,
    GLuint buffer, GLint
    size,
    GLenum type, GLsizei
    stride,
    GLintptr offset
    );
    GLBINDING_API void glVertexAttrib1d(GLuint
    index,
    GLdouble x
    );
    GLBINDING_API void glVertexAttrib1dARB(GLuint
    index,
    GLdouble x
    );
    GLBINDING_API void glVertexAttrib1dNV(GLuint
    index,
    GLdouble x
    );
    GLBINDING_API void glVertexAttrib1dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib1dvARB(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib1dvNV(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib1f(GLuint
    index,
    GLfloat x
    );
    GLBINDING_API void glVertexAttrib1fARB(GLuint
    index,
    GLfloat x
    );
    GLBINDING_API void glVertexAttrib1fNV(GLuint
    index,
    GLfloat x
    );
    GLBINDING_API void glVertexAttrib1fv(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib1fvARB(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib1fvNV(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib1hNV(GLuint
    index,
    GLhalfNV x
    );
    GLBINDING_API void glVertexAttrib1hvNV(GLuint
    index,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttrib1s(GLuint
    index,
    GLshort x
    );
    GLBINDING_API void glVertexAttrib1sARB(GLuint
    index,
    GLshort x
    );
    GLBINDING_API void glVertexAttrib1sNV(GLuint
    index,
    GLshort x
    );
    GLBINDING_API void glVertexAttrib1sv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib1svARB(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib1svNV(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib2d(GLuint
    index,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexAttrib2dARB(GLuint
    index,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexAttrib2dNV(GLuint
    index,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexAttrib2dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib2dvARB(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib2dvNV(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib2f(GLuint
    index,
    GLfloat x, GLfloat
    y);
    GLBINDING_API void glVertexAttrib2fARB(GLuint
    index,
    GLfloat x, GLfloat
    y);
    GLBINDING_API void glVertexAttrib2fNV(GLuint
    index,
    GLfloat x, GLfloat
    y);
    GLBINDING_API void glVertexAttrib2fv(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib2fvARB(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib2fvNV(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib2hNV(GLuint
    index,
    GLhalfNV x, GLhalfNV
    y);
    GLBINDING_API void glVertexAttrib2hvNV(GLuint
    index,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttrib2s(GLuint
    index,
    GLshort x, GLshort
    y);
    GLBINDING_API void glVertexAttrib2sARB(GLuint
    index,
    GLshort x, GLshort
    y);
    GLBINDING_API void glVertexAttrib2sNV(GLuint
    index,
    GLshort x, GLshort
    y);
    GLBINDING_API void glVertexAttrib2sv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib2svARB(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib2svNV(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib3d(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexAttrib3dARB(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexAttrib3dNV(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexAttrib3dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib3dvARB(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib3dvNV(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib3f(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glVertexAttrib3fARB(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glVertexAttrib3fNV(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glVertexAttrib3fv(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib3fvARB(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib3fvNV(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib3hNV(GLuint
    index,
    GLhalfNV x, GLhalfNV
    y,
    GLhalfNV z
    );
    GLBINDING_API void glVertexAttrib3hvNV(GLuint
    index,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttrib3s(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z
    );
    GLBINDING_API void glVertexAttrib3sARB(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z
    );
    GLBINDING_API void glVertexAttrib3sNV(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z
    );
    GLBINDING_API void glVertexAttrib3sv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib3svARB(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib3svNV(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4Nbv(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttrib4NbvARB(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttrib4Niv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttrib4NivARB(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttrib4Nsv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4NsvARB(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4Nub(GLuint
    index,
    GLubyte x, GLubyte
    y,
    GLubyte z, GLubyte
    w);
    GLBINDING_API void glVertexAttrib4NubARB(GLuint
    index,
    GLubyte x, GLubyte
    y,
    GLubyte z, GLubyte
    w);
    GLBINDING_API void glVertexAttrib4Nubv(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttrib4NubvARB(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttrib4Nuiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttrib4NuivARB(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttrib4Nusv(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttrib4NusvARB(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttrib4bv(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttrib4bvARB(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttrib4d(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexAttrib4dARB(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexAttrib4dNV(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexAttrib4dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib4dvARB(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib4dvNV(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttrib4f(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);
    GLBINDING_API void glVertexAttrib4fARB(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);
    GLBINDING_API void glVertexAttrib4fNV(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);
    GLBINDING_API void glVertexAttrib4fv(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib4fvARB(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib4fvNV(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttrib4hNV(GLuint
    index,
    GLhalfNV x, GLhalfNV
    y,
    GLhalfNV z, GLhalfNV
    w);
    GLBINDING_API void glVertexAttrib4hvNV(GLuint
    index,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttrib4iv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttrib4ivARB(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttrib4s(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z, GLshort
    w);
    GLBINDING_API void glVertexAttrib4sARB(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z, GLshort
    w);
    GLBINDING_API void glVertexAttrib4sNV(GLuint
    index,
    GLshort x, GLshort
    y,
    GLshort z, GLshort
    w);
    GLBINDING_API void glVertexAttrib4sv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4svARB(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4svNV(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttrib4ubNV(GLuint
    index,
    GLubyte x, GLubyte
    y,
    GLubyte z, GLubyte
    w);
    GLBINDING_API void glVertexAttrib4ubv(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttrib4ubvARB(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttrib4ubvNV(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttrib4uiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttrib4uivARB(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttrib4usv(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttrib4usvARB(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttribArrayObjectATI(GLuint
    index,
    GLint size, GLenum
    type,
    GLboolean normalized, GLsizei
    stride,
    GLuint buffer, GLuint
    offset);
    GLBINDING_API void glVertexAttribBinding(GLuint
    attribindex,
    GLuint bindingindex
    );
    GLBINDING_API void glVertexAttribDivisor(GLuint
    index,
    GLuint divisor
    );
    GLBINDING_API void glVertexAttribDivisorARB(GLuint
    index,
    GLuint divisor
    );
    GLBINDING_API void glVertexAttribFormat(GLuint
    attribindex,
    GLint size, GLenum
    type,
    GLboolean normalized, GLuint
    relativeoffset);
    GLBINDING_API void glVertexAttribFormatNV(GLuint
    index,
    GLint size, GLenum
    type,
    GLboolean normalized, GLsizei
    stride);
    GLBINDING_API void glVertexAttribI1i(GLuint
    index,
    GLint x
    );
    GLBINDING_API void glVertexAttribI1iEXT(GLuint
    index,
    GLint x
    );
    GLBINDING_API void glVertexAttribI1iv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI1ivEXT(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI1ui(GLuint
    index,
    GLuint x
    );
    GLBINDING_API void glVertexAttribI1uiEXT(GLuint
    index,
    GLuint x
    );
    GLBINDING_API void glVertexAttribI1uiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI1uivEXT(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI2i(GLuint
    index,
    GLint x, GLint
    y);
    GLBINDING_API void glVertexAttribI2iEXT(GLuint
    index,
    GLint x, GLint
    y);
    GLBINDING_API void glVertexAttribI2iv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI2ivEXT(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI2ui(GLuint
    index,
    GLuint x, GLuint
    y);
    GLBINDING_API void glVertexAttribI2uiEXT(GLuint
    index,
    GLuint x, GLuint
    y);
    GLBINDING_API void glVertexAttribI2uiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI2uivEXT(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI3i(GLuint
    index,
    GLint x, GLint
    y,
    GLint z
    );
    GLBINDING_API void glVertexAttribI3iEXT(GLuint
    index,
    GLint x, GLint
    y,
    GLint z
    );
    GLBINDING_API void glVertexAttribI3iv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI3ivEXT(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI3ui(GLuint
    index,
    GLuint x, GLuint
    y,
    GLuint z
    );
    GLBINDING_API void glVertexAttribI3uiEXT(GLuint
    index,
    GLuint x, GLuint
    y,
    GLuint z
    );
    GLBINDING_API void glVertexAttribI3uiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI3uivEXT(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI4bv(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttribI4bvEXT(GLuint
    index,
    const GLbyte *v
    );
    GLBINDING_API void glVertexAttribI4i(GLuint
    index,
    GLint x, GLint
    y,
    GLint z, GLint
    w);
    GLBINDING_API void glVertexAttribI4iEXT(GLuint
    index,
    GLint x, GLint
    y,
    GLint z, GLint
    w);
    GLBINDING_API void glVertexAttribI4iv(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI4ivEXT(GLuint
    index,
    const GLint *v
    );
    GLBINDING_API void glVertexAttribI4sv(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribI4svEXT(GLuint
    index,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribI4ubv(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttribI4ubvEXT(GLuint
    index,
    const GLubyte *v
    );
    GLBINDING_API void glVertexAttribI4ui(GLuint
    index,
    GLuint x, GLuint
    y,
    GLuint z, GLuint
    w);
    GLBINDING_API void glVertexAttribI4uiEXT(GLuint
    index,
    GLuint x, GLuint
    y,
    GLuint z, GLuint
    w);
    GLBINDING_API void glVertexAttribI4uiv(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI4uivEXT(GLuint
    index,
    const GLuint *v
    );
    GLBINDING_API void glVertexAttribI4usv(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttribI4usvEXT(GLuint
    index,
    const GLushort *v
    );
    GLBINDING_API void glVertexAttribIFormat(GLuint
    attribindex,
    GLint size, GLenum
    type,
    GLuint relativeoffset
    );
    GLBINDING_API void glVertexAttribIFormatNV(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride
    );
    GLBINDING_API void glVertexAttribIPointer(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribIPointerEXT(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribL1d(GLuint
    index,
    GLdouble x
    );
    GLBINDING_API void glVertexAttribL1dEXT(GLuint
    index,
    GLdouble x
    );
    GLBINDING_API void glVertexAttribL1dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL1dvEXT(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL1i64NV(GLuint
    index,
    GLint64EXT x
    );
    GLBINDING_API void glVertexAttribL1i64vNV(GLuint
    index,
    const GLint64EXT *v
    );
    GLBINDING_API void glVertexAttribL1ui64ARB(GLuint
    index,
    GLuint64EXT x
    );
    GLBINDING_API void glVertexAttribL1ui64NV(GLuint
    index,
    GLuint64EXT x
    );
    GLBINDING_API void glVertexAttribL1ui64vARB(GLuint
    index,
    const GLuint64EXT *v
    );
    GLBINDING_API void glVertexAttribL1ui64vNV(GLuint
    index,
    const GLuint64EXT *v
    );
    GLBINDING_API void glVertexAttribL2d(GLuint
    index,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexAttribL2dEXT(GLuint
    index,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexAttribL2dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL2dvEXT(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL2i64NV(GLuint
    index,
    GLint64EXT x, GLint64EXT
    y);
    GLBINDING_API void glVertexAttribL2i64vNV(GLuint
    index,
    const GLint64EXT *v
    );
    GLBINDING_API void glVertexAttribL2ui64NV(GLuint
    index,
    GLuint64EXT x, GLuint64EXT
    y);
    GLBINDING_API void glVertexAttribL2ui64vNV(GLuint
    index,
    const GLuint64EXT *v
    );
    GLBINDING_API void glVertexAttribL3d(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexAttribL3dEXT(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexAttribL3dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL3dvEXT(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL3i64NV(GLuint
    index,
    GLint64EXT x, GLint64EXT
    y,
    GLint64EXT z
    );
    GLBINDING_API void glVertexAttribL3i64vNV(GLuint
    index,
    const GLint64EXT *v
    );
    GLBINDING_API void glVertexAttribL3ui64NV(GLuint
    index,
    GLuint64EXT x, GLuint64EXT
    y,
    GLuint64EXT z
    );
    GLBINDING_API void glVertexAttribL3ui64vNV(GLuint
    index,
    const GLuint64EXT *v
    );
    GLBINDING_API void glVertexAttribL4d(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexAttribL4dEXT(GLuint
    index,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexAttribL4dv(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL4dvEXT(GLuint
    index,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribL4i64NV(GLuint
    index,
    GLint64EXT x, GLint64EXT
    y,
    GLint64EXT z, GLint64EXT
    w);
    GLBINDING_API void glVertexAttribL4i64vNV(GLuint
    index,
    const GLint64EXT *v
    );
    GLBINDING_API void glVertexAttribL4ui64NV(GLuint
    index,
    GLuint64EXT x, GLuint64EXT
    y,
    GLuint64EXT z, GLuint64EXT
    w);
    GLBINDING_API void glVertexAttribL4ui64vNV(GLuint
    index,
    const GLuint64EXT *v
    );
    GLBINDING_API void glVertexAttribLFormat(GLuint
    attribindex,
    GLint size, GLenum
    type,
    GLuint relativeoffset
    );
    GLBINDING_API void glVertexAttribLFormatNV(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride
    );
    GLBINDING_API void glVertexAttribLPointer(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribLPointerEXT(GLuint
    index,
    GLint size, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribP1ui(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    GLuint value
    );
    GLBINDING_API void glVertexAttribP1uiv(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    const GLuint *value
    );
    GLBINDING_API void glVertexAttribP2ui(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    GLuint value
    );
    GLBINDING_API void glVertexAttribP2uiv(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    const GLuint *value
    );
    GLBINDING_API void glVertexAttribP3ui(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    GLuint value
    );
    GLBINDING_API void glVertexAttribP3uiv(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    const GLuint *value
    );
    GLBINDING_API void glVertexAttribP4ui(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    GLuint value
    );
    GLBINDING_API void glVertexAttribP4uiv(GLuint
    index,
    GLenum type, GLboolean
    normalized,
    const GLuint *value
    );
    GLBINDING_API void glVertexAttribParameteriAMD(GLuint
    index,
    GLenum pname, GLint
    param);
    GLBINDING_API void glVertexAttribPointer(GLuint
    index,
    GLint size, GLenum
    type,
    GLboolean normalized, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribPointerARB(GLuint
    index,
    GLint size, GLenum
    type,
    GLboolean normalized, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribPointerNV(GLuint
    index,
    GLint fsize, GLenum
    type,
    GLsizei stride,
    const void *pointer
    );
    GLBINDING_API void glVertexAttribs1dvNV(GLuint
    index,
    GLsizei count,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribs1fvNV(GLuint
    index,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttribs1hvNV(GLuint
    index,
    GLsizei n,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttribs1svNV(GLuint
    index,
    GLsizei count,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribs2dvNV(GLuint
    index,
    GLsizei count,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribs2fvNV(GLuint
    index,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttribs2hvNV(GLuint
    index,
    GLsizei n,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttribs2svNV(GLuint
    index,
    GLsizei count,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribs3dvNV(GLuint
    index,
    GLsizei count,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribs3fvNV(GLuint
    index,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttribs3hvNV(GLuint
    index,
    GLsizei n,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttribs3svNV(GLuint
    index,
    GLsizei count,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribs4dvNV(GLuint
    index,
    GLsizei count,
    const GLdouble *v
    );
    GLBINDING_API void glVertexAttribs4fvNV(GLuint
    index,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glVertexAttribs4hvNV(GLuint
    index,
    GLsizei n,
    const GLhalfNV *v
    );
    GLBINDING_API void glVertexAttribs4svNV(GLuint
    index,
    GLsizei count,
    const GLshort *v
    );
    GLBINDING_API void glVertexAttribs4ubvNV(GLuint
    index,
    GLsizei count,
    const GLubyte *v
    );
    GLBINDING_API void glVertexBindingDivisor(GLuint
    bindingindex,
    GLuint divisor
    );
    GLBINDING_API void glVertexBlendARB(GLint
    count);
    GLBINDING_API void glVertexBlendEnvfATI(GLenum
    pname,
    GLfloat param
    );
    GLBINDING_API void glVertexBlendEnviATI(GLenum
    pname,
    GLint param
    );
    GLBINDING_API void glVertexFormatNV(GLint
    size,
    GLenum type, GLsizei
    stride);
    GLBINDING_API void glVertexP2ui(GLenum
    type,
    GLuint value
    );
    GLBINDING_API void glVertexP2uiv(GLenum
    type,
    const GLuint *value
    );
    GLBINDING_API void glVertexP3ui(GLenum
    type,
    GLuint value
    );
    GLBINDING_API void glVertexP3uiv(GLenum
    type,
    const GLuint *value
    );
    GLBINDING_API void glVertexP4ui(GLenum
    type,
    GLuint value
    );
    GLBINDING_API void glVertexP4uiv(GLenum
    type,
    const GLuint *value
    );
    GLBINDING_API void glVertexPointer(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glVertexPointerEXT(GLint
    size,
    GLenum type, GLsizei
    stride,
    GLsizei count,
    const void *pointer
    );
    GLBINDING_API void glVertexPointerListIBM(GLint
    size,
    GLenum type, GLint
    stride,
    const void **pointer, GLint
    ptrstride);
    GLBINDING_API void glVertexPointervINTEL(GLint
    size,
    GLenum type,
    const void **pointer
    );
    GLBINDING_API void glVertexStream1dATI(GLenum
    stream,
    GLdouble x
    );
    GLBINDING_API void glVertexStream1dvATI(GLenum
    stream,
    const GLdouble *coords
    );
    GLBINDING_API void glVertexStream1fATI(GLenum
    stream,
    GLfloat x
    );
    GLBINDING_API void glVertexStream1fvATI(GLenum
    stream,
    const GLfloat *coords
    );
    GLBINDING_API void glVertexStream1iATI(GLenum
    stream,
    GLint x
    );
    GLBINDING_API void glVertexStream1ivATI(GLenum
    stream,
    const GLint *coords
    );
    GLBINDING_API void glVertexStream1sATI(GLenum
    stream,
    GLshort x
    );
    GLBINDING_API void glVertexStream1svATI(GLenum
    stream,
    const GLshort *coords
    );
    GLBINDING_API void glVertexStream2dATI(GLenum
    stream,
    GLdouble x, GLdouble
    y);
    GLBINDING_API void glVertexStream2dvATI(GLenum
    stream,
    const GLdouble *coords
    );
    GLBINDING_API void glVertexStream2fATI(GLenum
    stream,
    GLfloat x, GLfloat
    y);
    GLBINDING_API void glVertexStream2fvATI(GLenum
    stream,
    const GLfloat *coords
    );
    GLBINDING_API void glVertexStream2iATI(GLenum
    stream,
    GLint x, GLint
    y);
    GLBINDING_API void glVertexStream2ivATI(GLenum
    stream,
    const GLint *coords
    );
    GLBINDING_API void glVertexStream2sATI(GLenum
    stream,
    GLshort x, GLshort
    y);
    GLBINDING_API void glVertexStream2svATI(GLenum
    stream,
    const GLshort *coords
    );
    GLBINDING_API void glVertexStream3dATI(GLenum
    stream,
    GLdouble x, GLdouble
    y,
    GLdouble z
    );
    GLBINDING_API void glVertexStream3dvATI(GLenum
    stream,
    const GLdouble *coords
    );
    GLBINDING_API void glVertexStream3fATI(GLenum
    stream,
    GLfloat x, GLfloat
    y,
    GLfloat z
    );
    GLBINDING_API void glVertexStream3fvATI(GLenum
    stream,
    const GLfloat *coords
    );
    GLBINDING_API void glVertexStream3iATI(GLenum
    stream,
    GLint x, GLint
    y,
    GLint z
    );
    GLBINDING_API void glVertexStream3ivATI(GLenum
    stream,
    const GLint *coords
    );
    GLBINDING_API void glVertexStream3sATI(GLenum
    stream,
    GLshort x, GLshort
    y,
    GLshort z
    );
    GLBINDING_API void glVertexStream3svATI(GLenum
    stream,
    const GLshort *coords
    );
    GLBINDING_API void glVertexStream4dATI(GLenum
    stream,
    GLdouble x, GLdouble
    y,
    GLdouble z, GLdouble
    w);
    GLBINDING_API void glVertexStream4dvATI(GLenum
    stream,
    const GLdouble *coords
    );
    GLBINDING_API void glVertexStream4fATI(GLenum
    stream,
    GLfloat x, GLfloat
    y,
    GLfloat z, GLfloat
    w);
    GLBINDING_API void glVertexStream4fvATI(GLenum
    stream,
    const GLfloat *coords
    );
    GLBINDING_API void glVertexStream4iATI(GLenum
    stream,
    GLint x, GLint
    y,
    GLint z, GLint
    w);
    GLBINDING_API void glVertexStream4ivATI(GLenum
    stream,
    const GLint *coords
    );
    GLBINDING_API void glVertexStream4sATI(GLenum
    stream,
    GLshort x, GLshort
    y,
    GLshort z, GLshort
    w);
    GLBINDING_API void glVertexStream4svATI(GLenum
    stream,
    const GLshort *coords
    );
    GLBINDING_API void glVertexWeightPointerEXT(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glVertexWeightfEXT(GLfloat
    weight);

    GLBINDING_API void glVertexWeightfvEXT(const GLfloat *weight);

    GLBINDING_API void glVertexWeighthNV(GLhalfNV
    weight);

    GLBINDING_API void glVertexWeighthvNV(const GLhalfNV *weight);

    GLBINDING_API GLenum
    glVideoCaptureNV(GLuint
    video_capture_slot,
    GLuint *sequence_num, GLuint64EXT
    * capture_time);
    GLBINDING_API void glVideoCaptureStreamParameterdvNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    const GLdouble *params
    );
    GLBINDING_API void glVideoCaptureStreamParameterfvNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    const GLfloat *params
    );
    GLBINDING_API void glVideoCaptureStreamParameterivNV(GLuint
    video_capture_slot,
    GLuint stream, GLenum
    pname,
    const GLint *params
    );
    GLBINDING_API void glViewport(GLint
    x,
    GLint y, GLsizei
    width,
    GLsizei height
    );
    GLBINDING_API void glViewportArrayv(GLuint
    first,
    GLsizei count,
    const GLfloat *v
    );
    GLBINDING_API void glViewportIndexedf(GLuint
    index,
    GLfloat x, GLfloat
    y,
    GLfloat w, GLfloat
    h);
    GLBINDING_API void glViewportIndexedfv(GLuint
    index,
    const GLfloat *v
    );
    GLBINDING_API void glViewportPositionWScaleNV(GLuint
    index,
    GLfloat xcoeff, GLfloat
    ycoeff);
    GLBINDING_API void glViewportSwizzleNV(GLuint
    index,
    GLenum swizzlex, GLenum
    swizzley,
    GLenum swizzlez, GLenum
    swizzlew);

    GLBINDING_API void glWaitSemaphoreEXT(GLuint
    semaphore,
    GLuint numBufferBarriers,
    const GLuint *buffers, GLuint
    numTextureBarriers,
    const GLuint *textures,
    const GLenum *srcLayouts
    );
    GLBINDING_API void glWaitSync(GLsync
    sync,
    UnusedMask flags, GLuint64
    timeout);
    GLBINDING_API void glWaitVkSemaphoreNV(GLuint64
    vkSemaphore);
    GLBINDING_API void glWeightPathsNV(GLuint
    resultPath,
    GLsizei numPaths,
    const GLuint *paths,
    const GLfloat *weights
    );
    GLBINDING_API void glWeightPointerARB(GLint
    size,
    GLenum type, GLsizei
    stride,
    const void *pointer
    );
    GLBINDING_API void glWeightbvARB(GLint
    size,
    const GLbyte *weights
    );
    GLBINDING_API void glWeightdvARB(GLint
    size,
    const GLdouble *weights
    );
    GLBINDING_API void glWeightfvARB(GLint
    size,
    const GLfloat *weights
    );
    GLBINDING_API void glWeightivARB(GLint
    size,
    const GLint *weights
    );
    GLBINDING_API void glWeightsvARB(GLint
    size,
    const GLshort *weights
    );
    GLBINDING_API void glWeightubvARB(GLint
    size,
    const GLubyte *weights
    );
    GLBINDING_API void glWeightuivARB(GLint
    size,
    const GLuint *weights
    );
    GLBINDING_API void glWeightusvARB(GLint
    size,
    const GLushort *weights
    );
    GLBINDING_API void glWindowPos2d(GLdouble
    x,
    GLdouble y
    );
    GLBINDING_API void glWindowPos2dARB(GLdouble
    x,
    GLdouble y
    );
    GLBINDING_API void glWindowPos2dMESA(GLdouble
    x,
    GLdouble y
    );

    GLBINDING_API void glWindowPos2dv(const GLdouble *v);

    GLBINDING_API void glWindowPos2dvARB(const GLdouble *v);

    GLBINDING_API void glWindowPos2dvMESA(const GLdouble *v);

    GLBINDING_API void glWindowPos2f(GLfloat
    x,
    GLfloat y
    );
    GLBINDING_API void glWindowPos2fARB(GLfloat
    x,
    GLfloat y
    );
    GLBINDING_API void glWindowPos2fMESA(GLfloat
    x,
    GLfloat y
    );

    GLBINDING_API void glWindowPos2fv(const GLfloat *v);

    GLBINDING_API void glWindowPos2fvARB(const GLfloat *v);

    GLBINDING_API void glWindowPos2fvMESA(const GLfloat *v);

    GLBINDING_API void glWindowPos2i(GLint
    x,
    GLint y
    );
    GLBINDING_API void glWindowPos2iARB(GLint
    x,
    GLint y
    );
    GLBINDING_API void glWindowPos2iMESA(GLint
    x,
    GLint y
    );

    GLBINDING_API void glWindowPos2iv(const GLint *v);

    GLBINDING_API void glWindowPos2ivARB(const GLint *v);

    GLBINDING_API void glWindowPos2ivMESA(const GLint *v);

    GLBINDING_API void glWindowPos2s(GLshort
    x,
    GLshort y
    );
    GLBINDING_API void glWindowPos2sARB(GLshort
    x,
    GLshort y
    );
    GLBINDING_API void glWindowPos2sMESA(GLshort
    x,
    GLshort y
    );

    GLBINDING_API void glWindowPos2sv(const GLshort *v);

    GLBINDING_API void glWindowPos2svARB(const GLshort *v);

    GLBINDING_API void glWindowPos2svMESA(const GLshort *v);

    GLBINDING_API void glWindowPos3d(GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glWindowPos3dARB(GLdouble
    x,
    GLdouble y, GLdouble
    z);
    GLBINDING_API void glWindowPos3dMESA(GLdouble
    x,
    GLdouble y, GLdouble
    z);

    GLBINDING_API void glWindowPos3dv(const GLdouble *v);

    GLBINDING_API void glWindowPos3dvARB(const GLdouble *v);

    GLBINDING_API void glWindowPos3dvMESA(const GLdouble *v);

    GLBINDING_API void glWindowPos3f(GLfloat
    x,
    GLfloat y, GLfloat
    z);
    GLBINDING_API void glWindowPos3fARB(GLfloat
    x,
    GLfloat y, GLfloat
    z);
    GLBINDING_API void glWindowPos3fMESA(GLfloat
    x,
    GLfloat y, GLfloat
    z);

    GLBINDING_API void glWindowPos3fv(const GLfloat *v);

    GLBINDING_API void glWindowPos3fvARB(const GLfloat *v);

    GLBINDING_API void glWindowPos3fvMESA(const GLfloat *v);

    GLBINDING_API void glWindowPos3i(GLint
    x,
    GLint y, GLint
    z);
    GLBINDING_API void glWindowPos3iARB(GLint
    x,
    GLint y, GLint
    z);
    GLBINDING_API void glWindowPos3iMESA(GLint
    x,
    GLint y, GLint
    z);

    GLBINDING_API void glWindowPos3iv(const GLint *v);

    GLBINDING_API void glWindowPos3ivARB(const GLint *v);

    GLBINDING_API void glWindowPos3ivMESA(const GLint *v);

    GLBINDING_API void glWindowPos3s(GLshort
    x,
    GLshort y, GLshort
    z);
    GLBINDING_API void glWindowPos3sARB(GLshort
    x,
    GLshort y, GLshort
    z);
    GLBINDING_API void glWindowPos3sMESA(GLshort
    x,
    GLshort y, GLshort
    z);

    GLBINDING_API void glWindowPos3sv(const GLshort *v);

    GLBINDING_API void glWindowPos3svARB(const GLshort *v);

    GLBINDING_API void glWindowPos3svMESA(const GLshort *v);

    GLBINDING_API void glWindowPos4dMESA(GLdouble
    x,
    GLdouble y, GLdouble
    z,
    GLdouble w
    );

    GLBINDING_API void glWindowPos4dvMESA(const GLdouble *v);

    GLBINDING_API void glWindowPos4fMESA(GLfloat
    x,
    GLfloat y, GLfloat
    z,
    GLfloat w
    );

    GLBINDING_API void glWindowPos4fvMESA(const GLfloat *v);

    GLBINDING_API void glWindowPos4iMESA(GLint
    x,
    GLint y, GLint
    z,
    GLint w
    );

    GLBINDING_API void glWindowPos4ivMESA(const GLint *v);

    GLBINDING_API void glWindowPos4sMESA(GLshort
    x,
    GLshort y, GLshort
    z,
    GLshort w
    );

    GLBINDING_API void glWindowPos4svMESA(const GLshort *v);

    GLBINDING_API void glWindowRectanglesEXT(GLenum
    mode,
    GLsizei count,
    const GLint *box
    );
    GLBINDING_API void glWriteMaskEXT(GLuint
    res,
    GLuint in, GLenum
    outX,
    GLenum outY, GLenum
    outZ,
    GLenum outW
    );


} // namespace gl


// Include function patches due to dinstinguished types GLint, GLuint, GLenum, and GLboolean
#include <glbinding/gl/functions-patches.h>
