/* 
 * global_rLat_i0.c
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
    \let dLatr    = 360.0 / 60.0;
    \let jar      = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) * 0x1.0p-17;
    \let jr       = \floor(jar);
    \let j_60_i_r = jr/60.0;
    \let rLatr = dLatr * ((jr - 60.0*(\floor (j_60_i_r))) + yz0 * 0x1.0p-17);
    \let rLat180r = rLatr + 180.0;
    (rLat180r - 360.0 * \floor(rLat180r/360.0)) - 180.0;
}
@*/

/*@
  requires 0 <= yz0 <= 131071;
  requires 0 <= yz1 <= 131071;
  requires \floor(yz0) == yz0;
  requires \floor(yz1) == yz1;
  ensures \abs(\result - rLatr(yz0,yz1)) <= 0.000022888; //bin size degrees
  @*/
fp g_rLatf_i_0 (int yz0, int yz1) {
  fp dLatf = 360.0 / 60.0;
  fp j1f = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) * 0x1.0p-17;
  /*@ assert j1f:
    \let j1r = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
    j1f == j1r;
    @*/
  fp jf = floor(j1f);
  /*@ assert jf:
    \let j1r = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
    \let jr = \floor(j1r);
    jf == jr;
    @*/
  /*@ assert values_for_jf: 
      -60.0 <= jf <= 59.0; 
    @*/
  /*@ assert jf_represents_an_integer: 
      \floor(jf) == jf; 
    @*/
  fp j_60_i_f = jf/60.0;
  /*@ assert hard:
      \let j1r = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
      \let jr = \floor(j1r);
      \let j_60_i_r = jr/60.0;
      \floor(j_60_i_f) == \floor(j_60_i_r);
    @*/
  fp rLatf = dLatf * ((jf - 60.0 * (floor (j_60_i_f))) + yz0 * 0x1.0p-17);
  /*@ assert rLat: 
      \let j1r = (59.0 * yz0 - 60.0 * yz1 + 0x1.0p+16) *0x1.0p-17;
      \let jr = \floor(j1r);
      \let j_60_i_r = jr/60.0;
      \let rLatr = 6.0 * ((jr - 60.0 * (\floor (j_60_i_r))) + yz0 * 0x1.0p-17);
      \abs(rLatf - rLatr) <= 0.000023; 
    @*/
  fp rLat180f = rLatf + 180.0;
  return (rLat180f - 360.0 * floor(rLat180f/360.0)) - 180.0;
} 