/*
 * Copyright 1993-2008 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:   
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  
 *
 * This software and the information contained herein is being provided 
 * under the terms and conditions of a Source Code License Agreement.     
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.  
 *
 * U.S. Government End Users.   This source code is a "commercial item" as 
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software 
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
 * source code with only those rights set forth herein.
 */

#if (USE_TEX==1)
#undef fetchx
#define fetchx(i)  tex1Dfetch(texX,parms.texXOfs+(i))
#else
#undef fetchx
#define fetchx(i)  sx[i]
#endif /* USE_TEX */

    unsigned int i, tid, totalThreads, ctaStart;
    float sum = 0.0f;
#if (USE_TEX==0)
    const float *sx;
#endif
    /* NOTE: wrapper must ensure that parms.n > 0 and parms.incx > 0 */
    tid = threadIdx.x;
#if (USE_TEX==0)
    sx = parms.sx;
#endif
    totalThreads = gridDim.x * CUBLAS_SASUM_THREAD_COUNT;
    ctaStart = CUBLAS_SASUM_THREAD_COUNT * blockIdx.x;

    if (parms.incx == 1) {
        /* increment equal to 1 */
        for (i = ctaStart + tid; i < parms.n; i += totalThreads) {
            sum += fabsf(fetchx(i));
        }
    } else {
        /* increment not equal to 1 */
        for (i = ctaStart + tid; i < parms.n; i += totalThreads) {
            sum += fabsf(fetchx(i*parms.incx));
        }
    }
    partialSum[tid] = sum;

#if (CUBLAS_SASUM_THREAD_COUNT & (CUBLAS_SASUM_THREAD_COUNT - 1))
#error code requires CUBLAS_SASUM_THREAD_COUNT to be a power of 2
#endif
    for (i = CUBLAS_SASUM_THREAD_COUNT >> 1; i > 0; i >>= 1) {
        __syncthreads(); 
        if (tid < i) {
            partialSum[tid] += partialSum[tid + i]; 
        }
    }
    if (tid == 0) {
        parms.result[blockIdx.x] = partialSum[tid];
    }
