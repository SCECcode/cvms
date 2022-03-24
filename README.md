# The Southern California Velocity Model with geotechnical layer (cvms)

<a href="https://github.com/sceccode/cvms.git"><img src="https://github.com/sceccode/cvms/wiki/images/cvms_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvms)
[![cvms-ci Actions Status](https://github.com/SCECcode/cvms/workflows/cvms-ci/badge.svg)](https://github.com/SCECcode/cvms/actions)
[![cvms-ucvm-ci Actions Status](https://github.com/SCECcode/cvms/workflows/cvms-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvms/actions)

## Description

The Southern California Velocity Model developed by SCEC, Caltech and USGS with geotechnical layer
2011/07/21

## Table of Contents
1. [Software Documentation](https://github.com/SCECcode/cvmsi/wiki)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [Credits](#credit)
6. [License](#license)

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

## Usage

### UCVM

As part of [UCVM](https://github.com/SCECcode/ucvm) installation, use 'cvms' as the model.

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

## Support
Support for CVMS is provided by the Southern California Earthquake Center
(SCEC) Research Computing Group.  Users can report issues and feature requests
using CVMS' github-based issue tracking link below. Developers will also
respond to emails sent to the SCEC software contact listed below.
1. [CVMS Github Issue Tracker](https://github.com/SCECcode/cvms/issues)
2. Email Contact: software@scec.usc.edu

## Credits

## Contributing
We welcome contributions to the CVMS, please contact us at software@scec.usc.edu.

## License
This software is distributed under the BSD 3-Clause open-source license.
Please see the [LICENSE.txt](LICENSE.txt) file for more information.

