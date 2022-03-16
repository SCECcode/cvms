# Autoconf/Automake binaries and headers
lib_LIBRARIES = libcvms.a
bin_PROGRAMS = vx_cvms cvms_txt cvms_bin

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} -fPIC
AM_LDFLAGS = ${LDFLAGS} -lm -lgfortran
#AM_FCFLAGS = ${FCFLAGS} -fPIC
AM_FCFLAGS = -fcheck=all -Wall -g -fbacktrace ${FCFLAGS} -fPIC

TARGETS = vx_cvms cvms_txt cvms_bin libcvms.a libcvms.so

all: $(bin_PROGRAMS) $(lib_LIBRARIES) libcvms.so

vx_cvms : vx_cvms.o libcvms.a
	$(CC) -o $@ $^ $(AM_LDFLAGS)

cvms_txt: cvms_main.f cvms_sub.f iotxt.f
	$(FC) $(AM_FCFLAGS) $^ -o $@

cvms_bin: cvms_main.f cvms_sub.f iobin.f
	$(FC) $(AM_FCFLAGS) $^ -o $@ 

cvms_mpi: cvms_main.f cvms_sub.f iompi.f
	$(FC) $(AM_FCFLAGS) $^ -o $@

libcvms.a: cvms_sub.o cvms_static.o
	$(AR) rcs $@ $^

libcvms.so: cvms_sub.o cvms.o
	$(FC) -shared $(AM_CFLAGS) -o libcvms.so $^
	
cvms_sub.o: cvms_sub.f
	$(FC) $(AM_FCFLAGS) -o $@ -c $^

cvms.o: cvms.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)

cvms_static.o: cvms.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)


install: all
	mkdir -p ${prefix}
	mkdir -p ${libdir}
	mkdir -p ${includedir}
	mkdir -p ${prefix}/src
	cp libcvms.a ${libdir}
	cp libcvms.so ${libdir}
	cp cvms.h ${includedir}
	find ./* -maxdepth 0 ! -name libcvms.a ! -name '*.f' ! -name '*.o' ! -name 'Makefile*' ! -exec cp '{}' '${prefix}/src' \;

clean:
	rm -rf *.o *~ vx_cvms cvms_txt cvms_bin cvms_mpi *.a
