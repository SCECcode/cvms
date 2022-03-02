#ifndef UCVM_CVMS_H
#define UCVM_CVMS_H

/**
 * @file ucvm_cvms.h
 * @brief Main header file for CVMS library.
 * @author - SCEC
 * @version 
 *
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cvms.h"

/* Fortran constants */
#define CVMS_FORTRAN_MODELDIR_LEN 128
#define CVMS_FORTRAN_VERSION_LEN 64

/* Maximum number of points to query */
#define CVMS_MAX_POINTS 1000000

/** Defines a return value of success */
#define SUCCESS 0
/** Defines a return value of failure */
#define FAIL 1
/** Defines a return value of NA from model */
#define NA -1

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct cvms_point_t {
        /** Longitude member of the point */
        double longitude;
        /** Latitude member of the point */
        double latitude;
        /** Depth member of the point */
        double depth;
} cvms_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct cvms_properties_t {
        /** P-wave velocity in meters per second */
        double vp;
        /** S-wave velocity in meters per second */
        double vs;
        /** Density in g/m^3 */
        double rho;
        /** NOT USED from basic_property_t */
        double qp;
        /** NOT USED from basic_property_t */
        double qs;
} cvms_properties_t;

/** The CVMS configuration structure. */
typedef struct cvms_configuration_t {
  char label[UCVM_MAX_LABEL_LEN];
  ucvm_region_t region;
  char config[UCVM_MAX_PATH_LEN];
  char extconfig[UCVM_MAX_PATH_LEN];
} ucvm_modelconf_t;

XXX
        /** The zone of UTM projection */
        int utm_zone;
        /** The model directory */
        char model_dir[1000];

} cvms_configuration_t;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Queries the model */
int model_query(cvms_point_t *points, cvms_properties_t *data, int numpts);
/** Setparam */
int model_setparam(int, int, int);


#endif

// CVMS Related Functions

/** Initializes the model */
int cvms_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int cvms_finalize();
/** Returns version information */
int cvms_version(char *ver, int len);
/** Queries the model */
int cvms_query(cvms_point_t *points, cvms_properties_t *data, int numpts);
/** Setparam*/
int cvms_setparam(int, int, ...);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int cvms_read_configuration(char *file, cvms_configuration_t *config);
void print_error(char *err);




#include "ucvm_dtypes.h"
/* Init CVM-S */
int ucvm_cvms_model_init(int id, ucvm_modelconf_t *conf);
/* Finalize CVM-S */
int ucvm_cvms_model_finalize();
/* Version CVM-S */
int ucvm_cvms_model_version(int id, char *ver, int len);
/* Label CVM-S */
int ucvm_cvms_model_label(int id, char *lab, int len);
/* Setparam CVM-S */
int ucvm_cvms_model_setparam(int id, int param, ...);
/* Query CVM-S */
int ucvm_cvms_model_query(int id, ucvm_ctype_t cmode,
			  int n, ucvm_point_t *pnt, 
			  ucvm_data_t *data);
/* Fill model structure with CVM-S */
int ucvm_cvms_get_model(ucvm_model_t *m);




#endif
