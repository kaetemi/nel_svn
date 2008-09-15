/** \file ext_al.h
 * OpenAL extensions
 */

#ifndef NL_EXT_AL_H
#define NL_EXT_AL_H
#include "stdopenal.h"

#ifdef NL_OS_WINDOWS
#	define EFX_CREATIVE_AVAILABLE 1
#	define EAX_AVAILABLE 0
#else
#	define EFX_CREATIVE_AVAILABLE 0
#	define EAX_AVAILABLE 0
#endif

#if EAX_AVAILABLE
#	define OPENAL
#	ifdef NL_OS_WINDOWS
#		include <objbase.h>
#	endif
#	include <eax.h>
#endif
#if EFX_CREATIVE_AVAILABLE
#	include <AL/efx-creative.h>
#	include <AL/EFX-Util.h>
#endif

extern "C"
{

void alExtInit(ALCdevice *device);

#if EAX_AVAILABLE
// EAX
extern bool AlExtEax;
extern EAXSet eaxSet;
extern EAXGet eaxGet;
#endif

// EAX-RAM (see OpenAL Programmer's Guide.pdf and http://icculus.org/alextreg/)
extern bool AlExtXRam;
typedef ALboolean (AL_APIENTRY *EAXSetBufferMode)(ALsizei n, ALuint *buffers, ALint value);
extern EAXSetBufferMode eaxSetBufferMode;
typedef ALenum (AL_APIENTRY *EAXGetBufferMode)(ALuint buffer, ALint *value);
extern EAXGetBufferMode eaxGetBufferMode;

// ALC_EXT_EFX (see Effects Extension Guide.pdf and http://icculus.org/alextreg/)
extern bool AlExtEfx;
#define ALC_MAX_AUXILIARY_SENDS 0x20003
// source objects
#define AL_DIRECT_FILTER 0x20005
#define AL_AUXILIARY_SEND_FILTER 0x20006
#define AL_AIR_ABSORPTION_FACTOR 0x20007
#define AL_ROOM_ROLLOFF_FACTOR 0x20008
#define AL_CONE_OUTER_GAINHF 0x20009
#define AL_DIRECT_FILTER_GAINHF_AUTO 0x2000A
#define AL_AUXILIARY_SEND_FILTER_GAIN_AUTO 0x2000B
#define AL_AUXILIARY_SEND_FILTER_GAINHF_AUTO 0x2000C
// effect objects
typedef void (AL_APIENTRY *LPALGENEFFECTS)(ALsizei n, ALuint* effects);
extern LPALGENEFFECTS alGenEffects;
typedef void (AL_APIENTRY *LPALDELETEEFFECTS)(ALsizei n, ALuint* effects);
extern LPALDELETEEFFECTS alDeleteEffects;
typedef ALboolean (AL_APIENTRY *LPALISEFFECT)(ALuint eid);
extern LPALISEFFECT alIsEffect;
typedef void (AL_APIENTRY *LPALEFFECTI)(ALuint eid, ALenum param, ALint value);
extern LPALEFFECTI alEffecti;
typedef void (AL_APIENTRY *LPALEFFECTIV)(ALuint eid, ALenum param, ALint* values);
extern LPALEFFECTIV alEffectiv;
typedef void (AL_APIENTRY *LPALEFFECTF)(ALuint eid, ALenum param, ALfloat value);
extern LPALEFFECTF alEffectf;
typedef void (AL_APIENTRY *LPALEFFECTFV)(ALuint eid, ALenum param, ALfloat* values);
extern LPALEFFECTFV alEffectfv;
typedef void (AL_APIENTRY *LPALGETEFFECTI)(ALuint eid, ALenum pname, ALint* value);
extern LPALGETEFFECTI alGetEffecti;
typedef void (AL_APIENTRY *LPALGETEFFECTIV)(ALuint eid, ALenum pname, ALint* values);
extern LPALGETEFFECTIV alGetEffectiv;
typedef void (AL_APIENTRY *LPALGETEFFECTF)(ALuint eid, ALenum pname, ALfloat* value);
extern LPALGETEFFECTF alGetEffectf;
typedef void (AL_APIENTRY *LPALGETEFFECTFV)(ALuint eid, ALenum pname, ALfloat* values);
extern LPALGETEFFECTFV alGetEffectfv;
#define AL_EFFECT_FIRST_PARAMETER 0x0000
#define AL_EFFECT_LAST_PARAMETER 0x8000
#define AL_EFFECT_TYPE 0x8001
#define AL_EFFECT_NULL 0x0000
#define AL_EFFECT_REVERB 0x0001
// filter objects
typedef void (AL_APIENTRY *LPALGENFILTERS)(ALsizei n, ALuint* filters);
extern LPALGENFILTERS alGenFilters;
typedef void (AL_APIENTRY *LPALDELETEFILTERS)(ALsizei n, ALuint* filters);
extern LPALDELETEFILTERS alDeleteFilters;
typedef ALboolean (AL_APIENTRY *LPALISFILTER)(ALuint filter);
extern LPALISFILTER alIsFilter;
typedef void (AL_APIENTRY *LPALFILTERI)(ALuint fid, ALenum param, ALint value);
extern LPALFILTERI alFilteri;
typedef void (AL_APIENTRY *LPALFILTERIV)(ALuint fid, ALenum param, ALint* values);
extern LPALFILTERIV alFilteriv;
typedef void (AL_APIENTRY *LPALFILTERF)(ALuint fid, ALenum param, ALfloat value);
extern LPALFILTERF alFilterf;
typedef void (AL_APIENTRY *LPALFILTERFV)(ALuint fid, ALenum param, ALfloat* values);
extern LPALFILTERFV alFilterfv;
typedef void (AL_APIENTRY *LPALGETFILTERI)(ALuint fid, ALenum pname, ALint* value);
extern LPALGETFILTERI alGetFilteri;
typedef void (AL_APIENTRY *LPALGETFILTERIV)(ALuint fid, ALenum pname, ALint* values);
extern LPALGETFILTERIV alGetFilteriv;
typedef void (AL_APIENTRY *LPALGETFILTERF)(ALuint fid, ALenum pname, ALfloat* value);
extern LPALGETFILTERF alGetFilterf;
typedef void (AL_APIENTRY *LPALGETFILTERFV)(ALuint fid, ALenum pname, ALfloat* values);
extern LPALGETFILTERFV alGetFilterfv;
#define AL_LOWPASS_GAIN 0x0001
#define AL_LOWPASS_GAINHF 0x0002
#define AL_HIGHPASS_GAIN 0x0001
#define AL_HIGHPASS_GAINLF 0x0002
#define AL_BANDPASS_GAIN 0x0001
#define AL_BANDPASS_GAINLF 0x0002
#define AL_BANDPASS_GAINHF 0x0003
#define AL_FILTER_FIRST_PARAMETER 0x0000
#define AL_FILTER_LAST_PARAMETER 0x8000
#define AL_FILTER_TYPE 0x8001
#define AL_FILTER_NULL 0x0000
#define	AL_FILTER_LOWPASS 0x0001
#define AL_FILTER_HIGHPASS 0x0002
#define AL_FILTER_BANDPASS 0x0003
// submix objects
typedef void (AL_APIENTRY *LPALGENAUXILIARYEFFECTSLOTS)(ALsizei n, ALuint* slots);
extern LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
typedef void (AL_APIENTRY *LPALDELETEAUXILIARYEFFECTSLOTS)(ALsizei n, ALuint* slots);
extern LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
typedef ALboolean (AL_APIENTRY *LPALISAUXILIARYEFFECTSLOT)(ALuint slot);
extern LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
typedef void (AL_APIENTRY *LPALAUXILIARYEFFECTSLOTI)(ALuint asid, ALenum param, ALint value);
extern LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
typedef void (AL_APIENTRY *LPALAUXILIARYEFFECTSLOTIV)(ALuint asid, ALenum param, ALint* values);
extern LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
typedef void (AL_APIENTRY *LPALAUXILIARYEFFECTSLOTF)(ALuint asid, ALenum param, ALfloat value);
extern LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
typedef void (AL_APIENTRY *LPALAUXILIARYEFFECTSLOTFV)(ALuint asid, ALenum param, ALfloat* values);
extern LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
typedef void (AL_APIENTRY *LPALGETAUXILIARYEFFECTSLOTI)(ALuint asid, ALenum pname, ALint* value);
extern LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
typedef void (AL_APIENTRY *LPALGETAUXILIARYEFFECTSLOTIV)(ALuint asid, ALenum pname, ALint* values);
extern LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
typedef void (AL_APIENTRY *LPALGETAUXILIARYEFFECTSLOTF)(ALuint asid, ALenum pname, ALfloat* value);
extern LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
typedef void (AL_APIENTRY *LPALGETAUXILIARYEFFECTSLOTFV)(ALuint asid, ALenum pname, ALfloat* values);
extern LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
#define AL_EFFECTSLOT_EFFECT 0x0001
#define AL_EFFECTSLOT_GAIN  0x0002
#define AL_EFFECTSLOT_AUXILIARY_SEND_AUTO 0x0003
#define AL_EFFECTSLOT_NULL 0x0000

}

#endif /* #ifndef NL_EXT_AL_H */

/* end of file */
