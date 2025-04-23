# The Southern California Velocity Model with geotechnical layer (cvms)

<a href="https://github.com/sceccode/cvms.git"><img src="https://github.com/sceccode/cvms/wiki/images/cvms_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvms)
[![cvms-ci Actions Status](https://github.com/SCECcode/cvms/workflows/cvms-ci/badge.svg)](https://github.com/SCECcode/cvms/actions)
[![cvms-ucvm-ci Actions Status](https://github.com/SCECcode/cvms/workflows/cvms-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvms/actions)


The Southern California Velocity Model developed by SCEC, Caltech and USGS with geotechnical layer


## Installation

This package is intended to be installed as part of the UCVM framework,
version 25.x or higher. 

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the CVMS based?) should be directed
to the model's authors, located in the AUTHORS file.

## To build in standalone mode

To install this package on your computer, please run the following commands:

<pre>
  aclocal
  autoconf
  automake --add-missing
  ./configure --prefix=/dir/to/install
  make
  make install
</pre>

By default, the MPI query interface is not built. To build the
MPI version, uncomment the appropriate TARGET line ./src/Makefile
and change the compiler FC specification to the appropriate
Fortran compiler wrapper.

### cvms_query

ASCII query interface(C api) accepts points from stdin with format (lat, lon, dep (m)) and write
data material p roperties to stdout.

### cvms_txt

ASCII query interface(Fortran api) accepts points from stdin with format (lat, lon, dep (m)) 
and writes data material properties to stdout with format (lat, lon, dep, 
vp, vs, density).

### cvms_bin

Binary query interface reads a configuration file named 'cvm-input' with the following 
items:

<pre>
line 1: number of points
line 2: path to input lon file
line 3: path to input lat file
line 4: path to input dep file
line 5: path to output rho file
line 6: path to output vp file
line 7: path to output vs file
</pre>

The input and output files are in binary (float) format, with each
containing the number of points specified on line 1. 

### MPI query interface cvms_mpi

Reads a configuration file named 'cvm-input' with the following 
items:

<pre>
line 1: number of points
line 2: path to input lon file
line 3: path to input lat file
line 4: path to input dep file
line 5: path to output rho file
line 6: path to output vp file
line 7: path to output vs file
</pre>

The input and output files are in binary (float) format, with each
containing the number of points specified on line 1. 

