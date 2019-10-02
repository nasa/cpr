/* 
 * xz-alt-NL1.c
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
  logic real xzr(int awb_lon) =
    \let tmp1r = (awb_lon + 0x1.0p+14) * 0x1.0p-15;
    \let tmp2r = (awb_lon + 0x1.0p+14) * 0x1.0p-32;
    \let tmp3r = 0x1.0p+17 * \floor(tmp2r);
    \floor(tmp1r) - tmp3r;
}
@*/

/*@
  requires awb_lon >= 0 && awb_lon <= 4294967296;
  requires \floor(awb_lon) == awb_lon;
  ensures \result == xzr(awb_lon) ;
  @*/
fp xzf (unsigned int awb_lon) {
  fp tmp1f = (awb_lon + 0x1.0p+14) * 0x1.0p-15; 
  /*@ assert tmp1f:
      tmp1f == (awb_lon  + 0x1.0p+14) * 0x1.0p-15;
    @*/
  fp tmp2f = (awb_lon + 0x1.0p+14) * 0x1.0p-32;
  /*@ assert tmp2f:
      tmp2f == (awb_lon + 0x1.0p+14) * 0x1.0p-32;
    @*/
  fp tmp3f = 0x1.0p+17 * floor(tmp2f);
  /*@ assert tmp3f:
      \let tmp2r = (awb_lon + 0x1.0p+14) * 0x1.0p-32;
      tmp3f == 0x1.0p+17 * \floor(tmp2r);
    @*/
  /*@ assert tmp3f_is_int:
    tmp3f == \floor(tmp3f);
    @*/
  return floor(tmp1f) - tmp3f;
}

int main () { return 0; }
