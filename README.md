# CPR*: Formally Verified Compact Position Reporting Algorithm 

The Compact Position Reporting (CPR) algorithm consists of a set of functions defined in the standard RTCA-DO- 260B/Eurocae ED-102A, Minimum Operational Performance Standards for 1090 MHz extended squitter Automatic Dependent Surveillance - Broadcast (ADS- B) and Traffic Information Services - Broadcast (TIS-B). These function encode and decode aircraft positions. CPR* is a formally verified C implementation of CPR's functions that use computer arithmetic in fixed- and floating-point formats.

## The Fixed-Point Implementation

The directory [`C/fixed-point`](C/fixed-point) contains a fixed-point C implementation of the CPR functions.
The [ACSL](https://frama-c.com/acsl.html) specification language was used to state correctness properties for the core components of this implementation.
Such correctness properties assure that each C function behaves accordingly with a logical description of it written also in ACSL.
The [Frama-C](https://frama-c.com/index.html) static analyzer was then used to process these annotated C functions and output verification conditions (VCs) expressed in [PVS](https://pvs.csl.sri.com/) language.
The directory `PVS` contains the resulting VCs and proofs for them.
Additionally, proofs of the correctness of the logical descriptions w.r.t. the aforementioned standard (under the modified set of requirements presented in [1]) can also be found in the same directory.

## The Floating-Point Implementation

The floating-point C implementation can be found in the directory [`C/floating-point`](C/floating-point).
As in the previous case, ACSL annotations along the code are used to relate the result of each core function with the result of its real valued specification.
Since in this case the implementation was developed using floating-point operations, the annotations take into consideration the maximum possible roundoff error occurred in the calculations performed on each operation. 
In order to deal with this kind of VCs, the Frama-C analyzer was used to generate [Gappa](http://gappa.gforge.inria.fr/) representations of them.
These Gappa specifications were manually modified to add hints allowing the Gappa solver to automatically discharge the VCs.
The modified Gappa files can be found in the [`Gappa`](Gappa) directory.
Finally, PVS was used to prove that the real valued specifications of the core functions are correct w.r.t. the standard assuming the set of corrected requirements reported in [1]. 
The [`PVS`](PVS) directory contains these proofs.
For details on the verification process for the floating-point implementation, see [2].

### Version

Current version is 1.0.0

### License

The code in this repository is released under NASA's Open Source Agreement.  See the directory [`LICENSES`](LICENSES); see also the copyright notice at the end of this file. 

## Contact

[C&eacute;sar A. Mu&ntilde;oz](http://shemesh.larc.nasa.gov/people/cam) (cesar.a.munoz@nasa.gov), NASA Langley Research Center.

## Copyright Notice

Copyright 2019 United States Government as represented by the Administrator of the National Aeronautics and Space Administration. All Rights Reserved.

# Disclaimers

No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 
Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.  RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS AGREEMENT.

# Bibliography

[1] A. Dutle, M. Moscato, L. Titolo, and C. Munoz. A formal analysis
of the compact position reporting algorithm. 9th Working Conference on
Verified Software: Theories, Tools, and Experiments, VSTTE 2017,
Revised Selected Papers, 10712:19–34, 2017.

[2] L. Titolo, M. Moscato, C. A. Munoz, A. Dutle, and F. Bobot. A
formally verified floating-point implementation of the compact
position reporting algorithm. In Klaus Havelund, Jan Peleska, Bill
Roscoe, and Erik de Vink, editors, Formal Methods, pages 364-381,
Cham, 2018. Springer International Publishing.
