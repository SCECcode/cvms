/*
 * @file cvms_query.c
 * @brief Bootstraps the test framework for the CVMS library.
 * @author - SCEC
 * @version 1.0
 *
 * Tests the CVMS library by loading it and executing the code as
 * UCVM would.
 *
 */

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cvms.h"

int cvms_debug=0;

int _compare_double(double f1, double f2) {
  double precision = 0.00001;
  if (((f1 - precision) < f2) && ((f1 + precision) > f2)) {
    return 1;
    } else {
      return 0;
  }
}

/* Usage function */
void usage() {
  printf("     cvms_query - (c) SCEC\n");
  printf("Extract velocities from a CVMS\n");
  printf("\tusage: cvms_query [-d][-h] < file.in\n\n");
  printf("Flags:\n");
  printf("\t-d enable debug/verbose mode\n\n");
  printf("\t-h usage\n\n");
  printf("Output format is:\n");
  printf("\tvp vs rho\n\n");
  exit (0);
}

extern char *optarg;
extern int optind, opterr, optopt;

/**
 * Initializes and CVMS in standalone mode with ucvm plugin 
 * api.
 *
 * @param argc The number of arguments.
 * @param argv The argument strings.
 * @return A zero value indicating success.
 */
int main(int argc, char* const argv[]) {

	// Declare the structures.
	cvms_point_t pt;
	cvms_properties_t ret;
        int rc;
        int opt;


        /* Parse options */
        while ((opt = getopt(argc, argv, "dh")) != -1) {
          switch (opt) {
          case 'd':
            cvms_debug=1;
            break;
          case 'h':
            usage();
            exit(0);
            break;
          default: /* '?' */
            usage();
            exit(1);
          }
        }

	// Initialize the model. 
        // try to use Use UCVM_INSTALL_PATH
        char *envstr=getenv("UCVM_INSTALL_PATH");
        if(envstr != NULL) {
	   assert(cvms_init(envstr, "cvms") == 0);
           } else {
	     assert(cvms_init("..", "cvms") == 0);
        }
	printf("Loaded the model successfully.\n");

        char line[1001];
        while (fgets(line, 1000, stdin) != NULL) {
           if(line[0]=='#') continue; // comment line
           if (sscanf(line,"%lf %lf %lf",
               &pt.longitude,&pt.latitude,&pt.depth) == 3) {

	      rc=cvms_query(&pt, &ret, 1);
              if(rc == 0) {
                printf("vs : %lf vp: %lf rho: %lf\n",ret.vs, ret.vp, ret.rho);
                } else {
                   printf("BAD: %lf %lf %lf\n",pt.longitude, pt.latitude, pt.depth);
              }
              } else {
                 break;
           }
        }

	assert(cvms_finalize() == 0);
	printf("Model closed successfully.\n");

	return 0;
}
