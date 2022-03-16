# CVM-S(cvms)

Southern California Velocity Model developed by SCEC, Caltech and USGS 
with geotechnical layer
2011/07/21

## Installation

This package is intended to be installed as part of the UCVM framework,
version 19.4.0 or higher. 

This package can also be installed standalone.

$ aclocal
$ autoconf
$ automake --add-missing
$ ./configure --prefix=/dir/to/install
$ make
$ make install

By default, the MPI query interface is not built. To build the
MPI version, uncomment the appropriate TARGET line ./src/Makefile
and change the compiler FC specification to the appropriate
Fortran compiler wrapper.


### ASCII query interface cvms_txt

Accepts points from stdin with format (lat, lon, dep (m)) and 
writes data material properties to std out with format (lat, lon, dep, 
vp, vs, density).

### Binary query interface cvms_bin

Reads a configuration file named 'cvm-input' with the following 
items:

line 1: number of points
line 2: path to input lon file
line 3: path to input lat file
line 4: path to input dep file
line 5: path to output rho file
line 6: path to output vp file
line 7: path to output vs file

The input and output files are in binary (float) format, with each
containing the number of points specified on line 1. 

### MPI query interface cvms_mpi

Reads a configuration file named 'cvm-input' with the following 
items:

line 1: number of points
line 2: path to input lon file
line 3: path to input lat file
line 4: path to input dep file
line 5: path to output rho file
line 6: path to output vp file
line 7: path to output vs file

The input and output files are in binary (float) format, with each
containing the number of points specified on line 1. 


## API Library

The library ./lib/libcvms.a may be statically linked into any
user application. The header file defining the API is located
in ./include/cvms.h.
