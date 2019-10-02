# Example of use of the decoding functionality of CPR

The program in `decode.c` reads the information needed to (locally) decode a CPR message and prints the recovered position.
It is expected for the information to be provided in a CSV file in which every line starts with the following fields:
 1) reference latitude in degrees (double),
 2) reference longitude in degrees (double),
 3) reference latitude as AWB (unsigned int),
 4) reference longitude as AWB (unsigned int),
 5) current latitude in degrees (double),
 6) current longitude in degrees (double),
 7) current latitude as AWB (unsigned int),
 8) current longitude as AWB (unsigned int),
 9) message format [i] (int)
 9) message latitude [YZ] (unsigned int),
10) message longitude [XZ] (unsigned int).

It prints on the standard output the input data followed by the recovered position: latitude and longitude (AWB), in that order.

All the integer values (AWB and encodings) are expected and expected and outputted in hexadecimal with no prefixes (ie, "FF02" instead of "0xFF02", for example).

## Building

For convenience, a `Makefile` is provided. The `coarse` target can be used to build the program.
```shell
$ make coarse
gcc -o decode decode.c -L../.. -lcoarse 
```

This program uses the coarse library (`libcoarse.a`). 
To build the library, the user may invoke `make` in the [`coarse`](`../../`) directory (see [`coarse/README.md`](`../../README.md`) for details).

A bash script ([`decode-all.sh`](decode-all.sh)) aimed to automate the execution of the program on multiple files is also provided. 
It executes `decode` on every `.csv` file in the current directory and prints the results in corresponding `.out` files.

## Checking the results

Two scripts aimed to check the produced decodings are provided.

* `check-decoding.sh` checks that every position in an `.csv.out` file with the format explained above fulfills the condition on the correctness theorem for the decoding. For that purpose, it executes the program `check-decoding` which can be built by the target `check` of the Makefile.

* `check-against.sh` assumes that every `.csv` file contains not only the required input data (in the order explained above) but also the expected decoding result. The script simply compares every `.csv` file with its corresponding `.csv.out` file. The standard output is used to report discrepancies.
