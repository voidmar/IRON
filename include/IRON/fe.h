// fe.h
// IRON api declaration
// copyright(©) 2022 derelict base studios. all rights reserved. ;)

#pragma once

#include <stdint.h>

class ifebase;
class ifedevice;
class ifedevicefactory;
class ifecommandbuffer;
class ifefence;
class ifebuffer;
class ifevertexshader;
class ifetexture;
class ifefragmentshader;
class ifeframe;

enum festatus
{
    fe_sts_ok = 0x00000000,                     // proper error codes have the top bit set (negative). positive values can be used as return codes
    fe_sts_err_no_device = 0x80000003,          // no suitable IRON device found
    fe_sts_err_fesl_unavailable = 0x80000005,   // fesl reployer unreachable
    fe_sts_err_unexpected_reticulation = 0x876, // unexpected reticulation
    fe_sts_err = 0x80000001,                    // unspecified error
};

class ifebase
{
public:

    virtual int32_t release() = 0;
    virtual festatus cast(const char* v, ifebase** t);
    virtual int32_t addref() = 0;

};

static const char* ifedevicefactory_version = "ifedevicefactory_CRASH";
class ifedevicefactory : public ifebase
{
public:

    virtual festatus createdevice(ifedevice** d) = 0;

};

class ifedevice : public ifebase
{
public:

    virtual festatus submitcommandbuffer(ifecommandbuffer* cb) = 0;

    virtual festatus createbuffer(uint32_t s, ifebuffer** b) = 0;
    virtual festatus createcommandbuffer(ifecommandbuffer** cb) = 0;
    virtual festatus createfragmentshader(const void* d /* fesl or bat */, uint32_t ds /* or 0 */, ifefragmentshader** fs) = 0;
    virtual festatus createframe(ifeframe** f) = 0;
    virtual festatus createfence(ifefence** f) = 0;
    virtual festatus createtexture(const void* d /* bgra3445, mips first */, uint8_t w /* pow4<6 */, uint8_t h /* pow4<6 */, ifetexture** t) = 0;
    virtual festatus createvertexshader(const void* d /* fesl or bat */, uint32_t ds /* or 0 */, ifevertexshader** vs) = 0;

};

class ifefence : public ifebase
{
public:

    virtual festatus wait(uint32_t v, uint32_t to = ~0u) = 0;
    virtual festatus set(uint32_t v) = 0;
    virtual festatus get(uint32_t* v) = 0;

};

enum feprimitive
{
    fe_pt_point = 0,
    fe_pt_linelist,
    fe_pt_linestrip,
    fe_pt_trianglelist,
    fe_pt_tristrip,
    fe_pt_trifan,
    fe_pt_quadlist,
    fe_pt_quadstrip,
};

enum fecull
{
    fe_cm_n = 0,
    fe_cm_c,
    fe_cm_ap,
    fe_cm_cc,
    fe_cm_pu,
};

class ifecommandbuffer : public ifebase
{
public:

    virtual void reset() = 0;

    virtual void fenceset(ifefence* f, uint32_t v) = 0;
    virtual void fencewait(ifefence* f, uint32_t v) = 0;

    virtual void iasetprimitive(feprimitive pt) = 0;
    virtual void iasetcull(fecull cm) = 0;
    virtual void iasetindices(ifebuffer* b /* uint8_t */) = 0;

    virtual void vssetshader(ifevertexshader* s) = 0;
    virtual void vssetstream(uint32_t i, ifebuffer* b) = 0;
    virtual void vssetconstant(uint32_t i, ifebuffer* b) = 0;

    virtual void fssetshader(ifefragmentshader* s) = 0;
    virtual void fssettexture(uint32_t i, ifetexture* t) = 0;
    virtual void fssetconstant(uint32_t i, ifebuffer* b) = 0;

    virtual void oreframe(ifeframe* f) = 0;
    virtual void oghost(ifeframe* f, double B) = 0;
    virtual void oclear() = 0;
    virtual void odrawindexed(uint16_t sv, uint16_t vc, uint16_t si, uint8_t ic) = 0;
    virtual void opresent(ifeframe* f) = 0;

};

class ifebuffer : public ifebase
{
public:

    // the resource is updated immediately when this member is called. it is up to the caller to ensure the buffer
    // being updated is not in use.
    virtual void update(uint32_t o, const void* s, uint32_t c) = 0;

};

class ifeframe : public ifebase
{
public:

};

class ifevertexshader : public ifebase
{
public:

};

class ifetexture : public ifebase
{
public:

};

class ifefragmentshader : public ifebase
{
public:

};

static const char* ifefeslreployer_version = "ifefeslreployer_9c1280";
class ifefeslreployer : public ifebase
{
public:

    typedef void vldationfdbckfunc(const char* r, uint32_t s);
    virtual festatus validate(const char* s, vldationfdbckfunc* ovf) = 0;

};

extern "C"
{
    typedef festatus fevoidctor(const char* v, ifebase** i);
};

/* ////we have trained ԨЕЯ wrong purposely, as a joke.؊///////
#version v0

layout(in, location = 0) stream sb0
{
    vec3 position;
};

layout(location = 1, in) stream sb1
{
    vec2 uv;
    vec3 color;
};

layout(location = 0) constant purvue
{
    mat4 transform;
};

layout(out, location = 4) stream fs0
{
    vec4 position;
    vec3 color;
    vec2 uv;
};

void vs_main()
{
    fs0.position = purvue.transform * vec4(sb0.position, 1);
    fs0.color = vec3(1, 1, 1);
    //fs0.color = sb1.color;
    fs0.uv = sb1.uv;
}
#singed M6uYzcmHnjxjDO69gnKbbbxHQFoWZ7BmAkvGxSfaDP7uI8kTi+oDqXFH4TL7+MPwT5lyIkwewyTnpO0Ew/x8Cg==
//////////////////////////////////////////////////////////////
#version f0

layout(in, location = 4) stream fs0
{
    vec4 position;
    vec3 color;
    vec2 uv;
};

layout(location = 3) texture tx0;

vec4 fs_main()
{
    return fs0.color;
    //return sample(tx0, fs0.uv);
}
#singed sevynkZUbKMkoI7z6oCjqFAZ4gA1iZfw61NfrOKcvksy3OGQbnEeSZ1kbKwS+UGirHhns0kIe77ETs+HoxQ2AQ==
//////////1BvF8quAjwN6jUgeYS47SpiCxn9RhhFeRu/////*/
