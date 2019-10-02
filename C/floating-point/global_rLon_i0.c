/* 
 * global_rLon_i0.c
 *
 * Contact: Cesar Munoz
 * Organization: NASA/Langley Research Center
 *
 * This software may be used, reproduced, and provided to others only as 
 * permitted under the terms of the agreement under which it was acquired from
 * the U.S. Government. Neither title to, nor ownership of, the software is 
 * hereby transferred. This notice shall remain on all copies of the software.
 * 
 * Copyright 2019 United States Government as represented by the Administrator
 * of the National Aeronautics and Space Administration. All Rights Reserved.
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef double fp;

/*@
axiomatic real_function {
  logic real rLonr (int xz0, int xz1, int nl) =
    \let dLonr   = 360.0 / nl;
    \let m1r     = ((nl - 1.0) * xz0 - nl * xz1 + 0x1.0p+16)*0x1.0p-17;
    \let mr      = \floor(m1r);
    \let m_nli_r = mr/(nl - 0.0);
    dLonr * ((mr - nl * \floor(m_nli_r)) + xz0 * 0x1.0p-17);
}
@*/

/*@
  requires 0 <= xz0 <= 131071;
  requires 0 <= xz1 <= 131071;
  requires 2 <= nl <= 59;
  requires \floor(xz0) == xz0;
  requires \floor(xz1) == xz1;
  requires \floor(nl) == nl;
  ensures \abs(\result - rLonr(xz0, xz1, nl)) <= 0.000022888;
  @*/
fp g_rLonf_i_0 (int xz0, int xz1, int nl) {
  fp m1f = ((nl - 1.0) * xz0 - nl * xz1 + 0x1.0p+16) * 0x1.0p-17;
  /*@ assert m1f:
      m1f == ((nl - 1.0) * xz0 - nl * xz1 + 0x1.0p+16) * 0x1.0p-17;
    @*/
  fp dLonf = 360.0 / nl;
  fp mf  = floor(m1f);
  /*@ assert floor_mf:
      \let mr1 = ((nl - 1.0) * xz0 - nl * xz1 + 0x1.0p+16) * 0x1.0p-17;
      mf == \floor(mr1);
    @*/
  /*@ assert values_for_mf: 
      -60.0 <= mf <= 59.0; 
    @*/
  /*@ assert mf_represents_an_integer: 
      mf == \floor(mf); 
    @*/
  fp m_nli_f = mf/nl; 
  /*@ assert hard:
      \let mr1 = ((nl - 1.0) * xz0 - nl * xz1 + 0x1.0p+16) * 0x1.0p-17;
      \let mr = \floor(mr1);
      \let m_nli_r = mr/(nl - 0.0);
      \floor(m_nli_f) == \floor(m_nli_r); 
    @*/
  return dLonf * ((mf - nl * floor(m_nli_f)) + xz0 * 0x1.0p-17);
}