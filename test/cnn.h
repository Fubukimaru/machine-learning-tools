/*---------------------------------------------------------------------------*/
/* CONVOLUTIONAL NETWORKS in C for R                                         */
/*---------------------------------------------------------------------------*/

// @author Josep Ll. Berral (Barcelona Supercomputing Center)

// @date 24th April 2017

// References:
// * Approach based on Lars Maaloee's:
//   https://github.com/davidbp/day2-Conv
// * Also from LeNet (deeplearning.net)
//   http://deeplearning.net/tutorial/lenet.html

// Compile using "gcc cnn.c conv.c pool.c grad_check.c matrix_ops.c -lgsl -lgslcblas -lm -o cnn"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include "matrix_ops.h"

#ifndef CNN_H
#define CNN_H 1

typedef struct {
	int batch_size;
	int filter_size;
	int n_filters;
	int n_channels;
	gsl_matrix*** W;
	gsl_vector* b;
	gsl_matrix*** grad_W;
	gsl_vector* grad_b;
	int pad_y;
	int pad_x;
	int win_h;
	int win_w;
	gsl_matrix*** img;
} CONV;

typedef struct {
	int batch_size;
	int n_channels;
	int win_size;
	int stride;
	int padding;
	gsl_matrix*** img;
} POOL;

typedef struct {
	int batch_size;
	int n_channels;
	int img_h;
	int img_w;
} FLAT;

// Gradiend Check Functions
int gradclose (gsl_matrix***, gsl_matrix***, int, int, double, double);
int gradclose_vec (gsl_vector*, gsl_vector*, int, double, double);

double fun (void*, gsl_matrix***, gsl_matrix***, int);
gsl_matrix*** approx_fprime (void*, gsl_matrix***, gsl_matrix***, double, int, int, int);
gsl_matrix*** fun_grad (void*, gsl_matrix***, int, int);
int check_grad_conv (CONV*, gsl_matrix***, int, double, double, double);
int check_grad_pool (POOL*, gsl_matrix***, int, double, double, double);
int check_grad_flat (FLAT*, gsl_matrix***, int, double, double, double);

double fun_b_conv (CONV*, gsl_vector*, gsl_matrix***);
gsl_vector* approx_fprime_b_conv (CONV*, gsl_matrix***, double);
gsl_vector* fun_grad_b_conv (CONV*, gsl_matrix***);

// Auxiliar Functions
void replace_image(gsl_matrix****, gsl_matrix****, int, int);

// Convolutional Auxiliar Functions
gsl_matrix* conv2D (gsl_matrix*, gsl_matrix*, int);
gsl_matrix* img_padding (gsl_matrix*, int, int);

// Convolutional Layer
gsl_matrix*** conv_op (gsl_matrix***, int, int, gsl_matrix***, int, int, int, int);
gsl_matrix*** forward_conv (CONV*, gsl_matrix***);
gsl_matrix*** backward_conv (CONV*, gsl_matrix***);
void get_updates_conv (CONV*, double);
void create_CONV (CONV*, int, int, int, double, int, int);
void free_CONV (CONV*);
void copy_CONV (CONV*, CONV*);
int compare_CONV (CONV*, CONV*);

// Pooling Layer
gsl_matrix*** forward_pool (POOL*, gsl_matrix***);
gsl_matrix*** backward_pool (POOL*, gsl_matrix***);
void get_updates_pool (POOL*, double);
void create_POOL (POOL*, int, double, int, int, int);
void free_POOL (POOL*);
void copy_POOL (POOL*, POOL*);
int compare_POOL (POOL*, POOL*);

// Flattening Layer
gsl_matrix* forward_flat (FLAT*, gsl_matrix***);
gsl_matrix*** backward_flat (FLAT*, gsl_matrix*);
void get_updates_flat (FLAT*, double);
void create_FLAT (FLAT*, int, int);
void free_FLAT (FLAT*);
void copy_FLAT (FLAT*, FLAT*);
int compare_FLAT (FLAT*, FLAT*);

#endif
