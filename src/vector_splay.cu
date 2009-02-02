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

/* This file contains the implementation of the CUBLAS helper functions */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "cublas.h"   /* CUBLAS public header file  */
#include "cublasP.h"  /* CUBLAS private header file */

/* 
 * For a given vector size, cublasVectorSplay() determines what CTA grid 
 * size to use, and how many threads per CTA.
 */
void kamasu_vector_splay (int n, int tMin, int tMax, int gridW, int *nbrCtas, 
			  int *elemsPerCta, int *threadsPerCta)
{
    if (n < tMin) {
        *nbrCtas = 1;
        *elemsPerCta = n;
        *threadsPerCta = tMin;
    } else if (n < (gridW * tMin)) {
        *nbrCtas = ((n + tMin - 1) / tMin);
        *threadsPerCta = tMin;
        *elemsPerCta = *threadsPerCta;
    } else if (n < (gridW * tMax)) {
        int grp;
        *nbrCtas = gridW;
        grp = ((n + tMin - 1) / tMin);
        *threadsPerCta = (((grp + gridW -1) / gridW) * tMin);
        *elemsPerCta = *threadsPerCta;
    } else {
        int grp;
        *nbrCtas = gridW;
        *threadsPerCta = tMax;
        grp = ((n + tMin - 1) / tMin);
        grp = ((grp + gridW - 1) / gridW);
        *elemsPerCta = grp * tMin;
    }
}

