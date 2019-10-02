/* 
 * global_rLat_i1.c
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
  logic real rLatr (int yz0,int yz1) =
    \let dLatr    = 360.0 / 59.0;
    \let jar      = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) * 0x1.0p-17;
    \let jr       = \floor(jar);
    \let j_60_i_r = jr/59.0;
    dLatr * ((jr - 59.0 *(\floor (j_60_i_r))) + yz1 * 0x1.0p-17);
}
@*/

/*@
  requires 0 <= yz0 <= 131071;
  requires 0 <= yz1 <= 131071;
  requires \floor(yz0) == yz0;
  requires \floor(yz1) == yz1;
  ensures \abs(\result - rLatr(yz0,yz1)) <= 0.000022888;
  @*/
fp g_rLatf_i_1 (int yz0, int yz1) {
  fp dLatf = 360.0 / 59.0;
  fp j1f = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) * 0x1.0p-17;
  /*@ assert j1f:
    \let j1r = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
    j1f == j1r;
    @*/
  fp jf = floor(j1f);
  /*@ assert jf:
    \let j1r      = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
    \let jr       = \floor(j1r);
    jf == jr;
    @*/
  /*@ assert values_for_jf: 
      -60.0 <= jf <= 59.0; 
    @*/
  /*@ assert jf_represents_an_integer: 
      \floor(jf) == jf; 
    @*/
  fp j_60_i_f = jf/59.0;
  /*@ assert hard:
      \let j1r      = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
      \let jr       = \floor(j1r);
      \let j_60_i_r = jr/59.0;
      \floor(j_60_i_f) == \floor(j_60_i_r);
    @*/
  return dLatf * ((jf - 59.0 * (floor (j_60_i_f))) + yz1 * 0x1.0p-17);
}