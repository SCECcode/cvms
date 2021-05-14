# Autoconf/Automake binaries and headers
lib_LIBRARIES = libcvms.a
bin_PROGRAMS = cvms_txt cvms_bin

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_LDFLAGS = ${LDFLAGS}
AM_FCFLAGS = ${FCFLAGS}

TARGETS = cvms_txt cvms_bin libcvms.a libcvms.so

all: $(bin_PROGRAMS) $(lib_LIBRARIES) libcvms.so

cvms_txt: cvms_main.f cvms_sub.f iotxt.f
	$(FC) $(AM_FCFLAGS) $^ -o $@

cvms_bin: cvms_main.f cvms_sub.f iobin.f
	$(FC) $(AM_FCFLAGS) $^ -o $@ 

cvms_mpi: cvms_main.f cvms_sub.f iompi.f
	$(FC) $(AM_FCFLAGS) $^ -o $@

libcvms.a: cvms_sub.o
	$(AR) rcs $@ $^

libcvms.so: cvms_sub.o
	$(FC) -shared $(AM_CFLAGS) -o libcvms.so $^
	
cvms_sub.o: cvms_sub.f
	$(FC) $(AM_FCFLAGS) -o $@ -c $^

install: all
	mkdir -p ${prefix}
	mkdir -p ${libdir}
	mkdir -p ${includedir}
	mkdir -p ${prefix}/src
	chmod +r *
	cp libcvms.a ${libdir}
	cp libcvms.so ${libdir}
	cp cvms.h ${includedir}
	find ./* -maxdepth 0 ! -name libcvms.a ! -name '*.f' ! -name '*.o' ! -name 'Makefile*' ! -exec cp '{}' '${prefix}/src' \;

clean:
	rm -rf *.o *~ cvms_txt cvms_bin cvms_mpi *.a
