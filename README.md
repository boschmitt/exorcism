# exorcism

exorcism iteratively apply the distance-k ExorLink cube transformation
to cube pairs. If replacement of the starting cubes by the resulting cubes leads
to simplification, the cover is modified without changing the function
represented by it.

This implementation is based on [4].

## Limitations
* Maximum of 32 inputs.
* Single output.

## Input
The input must be an ASCII file in standard PLA format, representing a
single-output Boolean function. In the current version, the don’t-cares of the
input function are ignored and only the on-set of the function is considered.

## TODO
* Implement pair queue as circular buffers.
* Implement exorlink-4 operation.
* Add support for multiple outputs.

## References
[1] N. Song, M. Perkowski, "EXORCISM-MV-2: Minimization of Exclusive Sum of 
Product Expressions for Multiple-Valued Input Incompletely Specified Functions,"
Proc. ISMVL 1993, pp. 132-137

[2] N. Song, M. Perkowski, "Minimization of Exclusive Sum of Products Expressions
for Multi-Output Multiple-Valued Input, Incompletely Specified Functions,"
IEEE Trans. on CAD, Vol. 15, No. 4, April 1996, pp. 385-395.

[3] N. Song. "Minimization of Exclusive Sum of Product Expressions for 
Multi-Valued Input Incompletely Specified Functions."
M.S. Thesis. EE Dept. Portland State University. Portland, OR, 1992.

[4] A. Mishchenko and M. Perkowski. "Fast heuristic minimization of 
Exclusive-Sums-of-Products."
In 5th International Workshop on Applications of the Reed Muller Expansion
in Circuit Design August 2001
