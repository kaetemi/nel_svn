/** \file buffer.cpp
 * TODO: File description
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "buffer.h"


namespace NLSOUND {

const sint IBuffer::_IndexTable[16] =
{
	-1, -1, -1, -1, 2, 4, 6, 8,
	-1, -1, -1, -1, 2, 4, 6, 8,
};

const uint IBuffer::_StepsizeTable[89] =
{
	7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
	19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
	50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
	130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
	337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
	876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
	2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
	5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
	15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};


void				IBuffer::encodeADPCM(sint16 *indata, uint8 *outdata, uint nbSample, TADPCMState &state)
{
    sint16 *inp;			/* Input buffer pointer */
    uint8 *outp;		/* output buffer pointer */
    int val;			/* Current input sample value */
    int sign;			/* Current adpcm sign bit */
    int delta;			/* Current adpcm output value */
    int diff;			/* Difference between val and valprev */
    int step;			/* Stepsize */
    int valpred;		/* Predicted output value */
    int vpdiff;			/* Current change to valpred */
    int index;			/* Current step change index */
    int outputbuffer;		/* place to keep previous 4-bit value */
    int bufferstep;		/* toggle between outputbuffer/output */

    outp = outdata;
    inp = indata;

    valpred = state.PreviousSample;
    index = state.StepIndex;
    step = _StepsizeTable[index];

    bufferstep = 1;

    for ( ; nbSample > 0 ; nbSample-- )
	{
		val = *inp++;

		/* Step 1 - compute difference with previous value */
		diff = val - valpred;
		sign = (diff < 0) ? 8 : 0;
		if ( sign ) diff = (-diff);

		/* Step 2 - Divide and clamp */
		/* Note:
		** This code *approximately* computes:
		**    delta = diff*4/step;
		**    vpdiff = (delta+0.5)*step/4;
		** but in shift step bits are dropped. The net result of this is
		** that even if you have fast mul/div hardware you cannot put it to
		** good use since the fixup would be too expensive.
		*/
		delta = 0;
		vpdiff = (step >> 3);

		if ( diff >= step )
		{
			delta = 4;
			diff -= step;
			vpdiff += step;
		}
		step >>= 1;
		if ( diff >= step  )
		{
			delta |= 2;
			diff -= step;
			vpdiff += step;
		}
		step >>= 1;
		if ( diff >= step )
		{
			delta |= 1;
			vpdiff += step;
		}

		/* Step 3 - Update previous value */
		if ( sign )
			valpred -= vpdiff;
		else
			valpred += vpdiff;

		/* Step 4 - Clamp previous value to 16 bits */
		if ( valpred > 32767 )
		{
			printf("over+ %d\n",valpred);
			valpred = 32767;
		}
		else if ( valpred < -32768 )
		{
			printf("over- %d\n",valpred);
			valpred = -32768;
		}

		/* Step 5 - Assemble value, update index and step values */
		delta |= sign;

		index += _IndexTable[delta];
		if ( index < 0 )
			index = 0;
		if ( index > 88 )
			index = 88;
		step = _StepsizeTable[index];

		/* Step 6 - Output value */
		if ( bufferstep )
		{
			outputbuffer = (delta << 4) & 0xf0;
		}
		else
		{
			*outp++ = (delta & 0x0f) | outputbuffer;
		}
		bufferstep = !bufferstep;
    }

    /* Output last step, if needed */
    if ( !bufferstep )
		*outp++ = outputbuffer;

    state.PreviousSample = valpred;
    state.StepIndex = index;
}

void				IBuffer::decodeADPCM(uint8 *indata, sint16 *outdata, uint nbSample, TADPCMState &state)
{
    uint8 *inp;		/* Input buffer pointer */
    sint16 *outp;		/* output buffer pointer */
    int sign;			/* Current adpcm sign bit */
    int delta;			/* Current adpcm output value */
    int step;			/* Stepsize */
    int valpred;		/* Predicted value */
    int vpdiff;			/* Current change to valpred */
    int index;			/* Current step change index */
    int inputbuffer;		/* place to keep next 4-bit value */
    int bufferstep;		/* toggle between inputbuffer/input */

    outp = outdata;
    inp = indata;

    valpred = state.PreviousSample;
    index = state.StepIndex;
    step = _StepsizeTable[index];

    bufferstep = 0;

    for ( ; nbSample > 0 ; nbSample-- )
	{

		/* Step 1 - get the delta value */
		if ( bufferstep )
		{
			delta = inputbuffer & 0xf;
		}
		else
		{
			inputbuffer = *inp++;
			delta = (inputbuffer >> 4) & 0xf;
		}
		bufferstep = !bufferstep;

		/* Step 2 - Find new index value (for later) */
		index += _IndexTable[delta];
		if ( index < 0 )
			index = 0;
		if ( index > 88 )
			index = 88;

		/* Step 3 - Separate sign and magnitude */
		sign = delta & 8;
		delta = delta & 7;

		/* Step 4 - Compute difference and new predicted value */
		/*
		** Computes 'vpdiff = (delta+0.5)*step/4', but see comment
		** in adpcm_coder.
		*/
		vpdiff = step >> 3;
		if ( delta & 4 )
			vpdiff += step;
		if ( delta & 2 )
			vpdiff += step>>1;
		if ( delta & 1 )
			vpdiff += step>>2;

		if ( sign )
			valpred -= vpdiff;
		else
			valpred += vpdiff;

		/* Step 5 - clamp output value */
		if ( valpred > 32767 )
			valpred = 32767;
		else if ( valpred < -32768 )
			valpred = -32768;

		/* Step 6 - Update step value */
		step = _StepsizeTable[index];

		/* Step 7 - Output value */
		*outp++ = valpred;
    }

    state.PreviousSample = valpred;
    state.StepIndex = index;
}



} // NLSOUND
