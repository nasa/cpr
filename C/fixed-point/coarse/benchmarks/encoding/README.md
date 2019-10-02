Example of use of the encode functionality of CPR.

The program in `encode.c` reads positions expressed by two AWB integers (32 bits) representing latitude and longitude from a CSV file and encodes each position according to the indicated format, even (0) or odd (1).
It expects as argument the name of the input CSV file. 
Each line of such file must start with the following fields:
```
<message format>, <awb latitude>, <awb longitude>
````
where _<message format>_ can take the value 0 (even message) or 1 (odd message).
The program prints on the standard output the input data followed by the encoding of the latitude and the longitude, in that order.
```
<message format>, <awb latitude>, <awb longitude>, <encoded latitude>, <encoded longitude>
````

For convenience, a `Makefile` is provided to build the program.
```shell
$ make
gcc -o encode encode.c -L../.. -lcoarse 
```

This program uses the coarse library (`libcoarse.a`). 
To build the library, the user may invoke `make` in the [`coarse`](`../../`) directory (see [`coarse/README.md`](`../../README.md`) for details).

A bash script ([`run.sh`](run.sh)) aimed to automate the execution of the program on multiple files is also provided. 
It assumes that the CSV file contains not only the required input data (in the order explained above) but also the expected result of the encoding.
The script iterates over all the CSV files in the directory and executes `encode` on them.
Every result is stored in an `.out` file and compared with the input.
The standard output is used to report discrepancies of the results w.r.t. the given input.

```shell
$ ./run.sh 
t6-5awb.csv encoded as expected.
t6-6awb.csv encoded as expected.
```
