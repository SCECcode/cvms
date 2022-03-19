/* 
 * @file cvms.c
 * @brief Main file for CVMS library.
 * @author - SCEC 
 * @version 
 *
 * @section DESCRIPTION
 *
 *
 */

#include "cvms.h"

/* Init flag */
int cvms_is_initialized = 0;

/* Buffers initialized flag */
int cvms_buf_init = 0;

/* Model conf */
cvms_configuration_t *cvms_configuration;

/* Query buffers */
int *cvms_index = NULL;
float *cvms_lon = NULL;
float *cvms_lat = NULL;
float *cvms_dep = NULL;
float *cvms_vp = NULL;
float *cvms_vs = NULL;
float *cvms_rho = NULL;

/* 
 * Initializes the CVM-S plugin model within the UCVM framework. In order to initialize
 * the model, we must provide the UCVM install path and optionally a place in memory
 * where the model already exists.
 *
 * @param dir The directory in which UCVM has been installed.
 * @param label A unique identifier for the velocity model.
 * @return Success or failure, if initialization was successful.
 */
int cvms_init(const char *dir, const char *label) {

  char configbuf[512];
  int errcode;
  /* Fortran fixed string length */
  char modeldir[CVMS_FORTRAN_MODELDIR_LEN];

  if (cvms_is_initialized) {
    cvms_print_error("Model is already initialized\n");
    return(UCVM_CODE_ERROR);
  }

  // Initialize variables.
  cvms_configuration = calloc(1, sizeof(cvms_configuration_t));

  // Configuration file location when built with UCVM
  sprintf(configbuf, "%s/model/%s/data/config", dir, label);

  // Read the cvms_configuration file.
  if (cvms_read_configuration(configbuf, cvms_configuration) != UCVM_CODE_SUCCESS) {
    cvms_print_error("Model configuration can not be accessed.");
    return(UCVM_CODE_ERROR);
  }

  // model's data location
  int pathlen=strlen(dir)+strlen(label)+strlen(cvms_configuration->model_dir); // throw in some extra
  if (pathlen >= CVMS_FORTRAN_MODELDIR_LEN) {
    cvms_print_error("Config path too long.");
    return(UCVM_CODE_ERROR);
  }
  sprintf(modeldir, "%s/model/%s/data/%s/", dir, label, cvms_configuration->model_dir);

  cvms_init_(modeldir, &errcode, CVMS_FORTRAN_MODELDIR_LEN);
  if (errcode != 0) {
    cvms_print_error("Failed to init CVM-S");
    return(UCVM_CODE_ERROR);
  }

  /* Allocate buffers */
  if (cvms_buf_init == 0) {
    cvms_index = malloc(CVMS_MAX_POINTS*sizeof(int));
    cvms_lon = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_lat = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_dep = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_vp = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_vs = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_rho = malloc(CVMS_MAX_POINTS*sizeof(float));
    cvms_buf_init = 1;
  }

  cvms_is_initialized = 1;

  return UCVM_CODE_SUCCESS;
}

/**
 * Reads the cvms_configuration file describing the various properties of CVM-S and populates
 * the cvms_configuration struct. This assumes cvms_configuration has been "calloc'ed" and validates
 * that each value is not zero at the end.
 *
 * @param file The cvms_configuration file location on disk to read.
 * @param config The cvms_configuration struct to which the data should be written.
 * @return Success or failure, depending on if file was read successfully.
 */
int cvms_read_configuration(char *file, cvms_configuration_t *config) {
  FILE *fp = fopen(file, "r");
  char key[40];
  char value[80];
  char line_holder[128];

  // If our file pointer is null, an error has occurred. Return fail.
  if (fp == NULL) {
    cvms_print_error("Could not open the cvms_configuration file.");
    return UCVM_CODE_ERROR;
  }

  // Read the lines in the cvms_configuration file.
  while (fgets(line_holder, sizeof(line_holder), fp) != NULL) {
    if (line_holder[0] != '#' && line_holder[0] != ' ' && line_holder[0] != '\n') {
      sscanf(line_holder, "%s = %s", key, value);

      // Which variable are we editing?
      if (strcmp(key, "utm_zone") == 0) config->utm_zone = atoi(value);
      if (strcmp(key, "model_dir") == 0) sprintf(config->model_dir, "%s", value);
    }
  }

  // Have we set up all cvms_configuration parameters?
  if (config->utm_zone == 0) {
    cvms_print_error("One cvms_configuration parameter not specified. Please check your cvms_configuration file.");
    return UCVM_CODE_ERROR;
  }

  fclose(fp);

  return UCVM_CODE_SUCCESS;
}


/* 
 * Called when the model is being discarded. Free all variables.
 *
 * @return UCVM_CODE_SUCCESS
 */
int cvms_finalize()
{
  if (cvms_buf_init == 1) {
    free(cvms_index);
    free(cvms_lon);
    free(cvms_lat);
    free(cvms_dep);
    free(cvms_vp);
    free(cvms_vs);
    free(cvms_rho);
    cvms_buf_init = 0;
  }
  cvms_is_initialized = 0;
  return UCVM_CODE_SUCCESS;
}

/* 
 * Returns the version information.
 *
 * @param ver Version string to return.
 * @param len Maximum length of buffer.
 * @return Zero
 */
/* Version CVM-S */
int cvms_version(char *ver, int len)
{
  int errcode;
  /* Fortran fixed string length */
  char verstr[CVMS_FORTRAN_VERSION_LEN];

  cvms_version_(verstr, &errcode, CVMS_FORTRAN_MODELDIR_LEN);
  if (errcode != 0) {
    cvms_print_error("Failed to retrieve version from CVM-S");
    return UCVM_CODE_ERROR;
  }

  strncpy(ver, verstr, len);
  return UCVM_CODE_SUCCESS;
}


/**
 * setparam CVM-S 
 *
 * @param points The points at which the queries will be made.
 */
int cvms_setparam(int id, int param, ...)
{
  va_list ap;
  int zmode;

  va_start(ap, param);

  switch (param) {
    case UCVM_PARAM_QUERY_MODE:
      zmode = va_arg(ap,int);
      switch (zmode) {
        case UCVM_COORD_GEO_DEPTH:
        case UCVM_COORD_GEO_ELEV:
          /* point from ucvm is always for depth */
          break;
        default:
          cvms_print_error("Unsupported coord type\n");
          return UCVM_CODE_ERROR;
          break;
       }
       break;
  }
  va_end(ap);
  return UCVM_CODE_SUCCESS;
}

/* Query CVM-S */

/**
 * Queries CVM-S at the given points and returns the data that it finds.
 *
 * @param points The points at which the queries will be made.
 * @param data The data that will be returned (Vp, Vs, density, Qs, and/or Qp).
 * @param numpoints The total number of points to query.
 * @return UCVM_CODE_SUCCESS or UCVM_CODE_ERROR.
 */
int cvms_query(cvms_point_t *pnt, cvms_properties_t *data, int numpoints) {
  int i, j;
  int nn = 0;
  double depth;
  int errcode;

  if (cvms_buf_init == 0) {
    cvms_print_error("Model data is inaccessible");
    return UCVM_CODE_ERROR;
  }

  nn = 0;
  for (i = 0; i < numpoints; i++) {
// initialize the data
    data[i].vp=-1;
    data[i].vs=-1;
    data[i].rho=-1;
    data[i].qp=-1;
    data[i].qs=-1;

    // ??? depth = data[i].depth + data[i].shift_cr;
    depth = pnt[i].depth;

    /* CVM-S extends from free surface on down */
    if (depth >= 0.0) {
	cvms_index[nn] = i;
	cvms_lon[nn] = (float)(pnt[i].longitude);
	cvms_lat[nn] = (float)(pnt[i].latitude);
	cvms_dep[nn] = (float)(depth);
	cvms_vp[nn] = 0.0;
	cvms_vs[nn] = 0.0;
	cvms_rho[nn] = 0.0;
	nn++;
	if (nn == CVMS_MAX_POINTS) {
	  cvms_query_(&nn, cvms_lon, cvms_lat, cvms_dep, 
		      cvms_vp, cvms_vs, cvms_rho, &errcode);
	  
	  if (errcode == 0) {
	    for (j = 0; j < nn; j++) {
	      data[cvms_index[j]].vp = (double)cvms_vp[j];
	      data[cvms_index[j]].vs = (double)cvms_vs[j];
	      data[cvms_index[j]].rho = (double)cvms_rho[j];
	    }
	  }
	  nn = 0;
	}
        } else {
          // skip the one with bad depth
    }
  }

  // what is left over or over flown ..
  if (nn > 0) {
      cvms_query_(&nn, cvms_lon, cvms_lat, cvms_dep, 
		  cvms_vp, cvms_vs, cvms_rho, &errcode);
      if (errcode == 0) {
        for (j = 0; j < nn; j++) {
	  data[cvms_index[j]].vp = (double)cvms_vp[j];
	  data[cvms_index[j]].vs = (double)cvms_vs[j];
	  data[cvms_index[j]].rho = (double)cvms_rho[j];
        }
      }
  }

  return UCVM_CODE_SUCCESS;
}


/**
 * Prints the error string provided.
 *
 * @param err The error string to print out to stderr.
 */
void cvms_print_error(char *err) {
  fprintf(stderr, "An error has occurred while executing CVM-S . The error was:\n\n");
  fprintf(stderr, "%s", err);
  fprintf(stderr, "\n\nPlease contact software@scec.org and describe both the error and a bit\n");
  fprintf(stderr, "about the computer you are running CVM-S on (Linux, Mac, etc.).\n");
}

// The following functions are for dynamic library mode. If we are compiling
// a static library, these functions must be disabled to avoid conflicts.
#ifdef DYNAMIC_LIBRARY

/**
 * Init function loaded and called by the UCVM library. Calls cvms_init.
 *
 * @param dir The directory in which UCVM is installed.
 * @return Success or failure.
 */
int model_init(const char *dir, const char *label) {
	return cvms_init(dir, label);
}

/**
 * Query function loaded and called by the UCVM library. Calls cvms_query.
 *
 * @param points The basic_point_t array containing the points.
 * @param data The basic_properties_t array containing the material properties returned.
 * @param numpoints The number of points in the array.
 * @return Success or fail.
 */
int model_query(cvms_point_t *points, cvms_properties_t *data, int numpoints) {
	return cvms_query(points, data, numpoints);
}

/**
 * Finalize function loaded and called by the UCVM library. Calls cvms_finalize.
 *
 * @return Success
 */
int model_finalize() {
	return cvms_finalize();
}

/**
 * Version function loaded and called by the UCVM library. Calls cvms_version.
 *
 * @param ver Version string to return.
 * @param len Maximum length of buffer.
 * @return Zero
 */
int model_version(char *ver, int len) {
	return cvms_version(ver, len);
}

/**
 * Setparam function loaded and called by the UCVM library. Calls cvms_setparam.
 *
 * @param id  don'care
 * @param param
 * @param val, it is actually just 1 int
 * @return Success or fail.
 */
int model_setparam(int id, int param, int val) {
        return cvms_setparam(id, param, val);
}



int (*get_model_init())(const char *, const char *) {
        return &cvms_init;
}
int (*get_model_query())(cvms_point_t *, cvms_properties_t *, int) {
         return &cvms_query;
}
int (*get_model_finalize())() {
         return &cvms_finalize;
}
int (*get_model_version())(char *, int) {
         return &cvms_version;
}
int (*get_model_setparam())(int, int, ...) {
         return &cvms_setparam;
}

#endif
