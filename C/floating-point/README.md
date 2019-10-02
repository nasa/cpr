This directory contains a C floating-point implementation of the CPR decoding functions for the **airborne** format (Nb=17).

Source files:
* Encoding functions
    * `yz-alt-greater-2-30.c` : (formally verified) latitude encoding functions (case lat>2^30)
    * `yz-alt.c` : (formally verified) latitude encoding functions (case lat<=2^30)
    * `xz-alt-NL1.c` : (formally verified) longitude encoding function (case NL=1)
    * `xz-alt.c` : (formally verified) longitude encoding function (case NL>1)
* Global Decoding    
    * `global_rLat_i0.c` : (formally verified) latitude decoding functions (case i=0)
    * `global_rLat_i1.c` : (formally verified) latitude decoding functions (case i=1)
    * `global_rLonNL1.c` : (formally verified) longitude decoding functions (case NL=1)
    * `global_rLon_i0.c` : (formally verified) longitude decoding functions (case NL>1 and i=0)
    * `global_rLon_i1.c` : (formally verified) longitude decoding functions (case NL>1 and i=1)
* Local Decoding
    * `local_rLat-greater-2-30.c` : (formally verified) latitude decoding functions (case reference_lat>2^30)
    * `local_rLat.c` : (formally verified) latitude decoding functions (case reference_lat<=2^30)
    * `local_rLonNL1.c` : (formally verified) longitude decoding functions (case NL=1)
    * `local_rLon.c` : (formally verified) longitude decoding functions (case NL>1)
* Helper functions
    * `cpr.c`: entry-point for CPR functions.
    * `nl.c`: precomputed NL table.

For examples of use, please see the directory [`benchmarks`](benchmarks).

The included `Makefile` can be used to generate the static library `libairborne.a`.

```shell
$ make
gcc -c -o cpr.o cpr.c -Wall
ar -cr libairborne.a cpr.o nl.o global_rLat_i0.o global_rLat_i1.o global_rLon_i0.o global_rLon_i1.o global_rLonNL1.o local_rLat-greater-2-30.o local_rLat.o local_rLon.o local_rLonNL1.o
```
