/* 
 * yz-alt.c
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
  logic real yzr(int i, int awb_lat) =
    \let xr = 60.0 - i;
    \let tmp1r = ((awb_lat * xr) + 0x1.0p+14) * 0x1.0p-15;
    \let tmp2r = (awb_lat * xr + 0x1.0p+14) * 0x1.0p-32;
    \let tmp3r = 0x1.0p+17 * \floor(tmp2r);
    \floor(tmp1r) - tmp3r;
}
@*/

/*@
  requires 0 <= i <= 1;
  requires awb_lat >= 0 && awb_lat <= 1073741824;
  requires \floor(i) == i;
  requires \floor(awb_lat) == awb_lat;
  ensures \result == yzr(i, awb_lat) ;
  @*/
fp yzf (int i, unsigned int awb_lat) {
  fp xf    = 60.0 - i;
  /*@ assert xf:
    xf == (60.0 - i);
    @*/
  fp tmp1f = ((awb_lat * xf) + 0x1.0p+14) * 0x1.0p-15; 
  /*@ assert tmp1f:
    \let xr = (60.0 - i);
      tmp1f == ((awb_lat * xr) + 0x1.0p+14) * 0x1.0p-15;
    @*/
  fp tmp2f = (awb_lat * xf + 0x1.0p+14) * 0x1.0p-32;
  /*@ assert tmp2f:
    \let xr = (60.0 - i);
      tmp2f == (awb_lat * xr + 0x1.0p+14) * 0x1.0p-32;
    @*/
  fp tmp3f = 0x1.0p+17 * floor(tmp2f);
  /*@ assert tmp3f:
    \let xr = (60.0 - i);
    \let tmp2r = (awb_lat * xr + 0x1.0p+14) * 0x1.0p-32;
      tmp3f == 0x1.0p+17 * \floor(tmp2r);
    @*/
  /*@ assert tmp3f_is_int:
    tmp3f == \floor(tmp3f);
    @*/
  return  floor(tmp1f) - tmp3f;
} 

int main () { return 0; }
