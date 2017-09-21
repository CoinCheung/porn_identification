#ifndef _IMGPRO_H_
#define _IMGPRO_H_

/* ==============================================
 *  headers to be included
 * ============================================== */
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"datastructure.h"

/* ==============================================
 * micros and data type definitions 
 * ============================================== */

/* micro */
#define Max(a,b,c) (a > b ? (a > c ? a : c) : (b > c ? b : c))
#define Min(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

/* types definitions */
// image information structure 
typedef struct
{
    int channel;
    int width;
    int height;
    long size;
    uint8_t *data; // points to the pixel data memory
} img_para;

// structure of pixel for skin identification
typedef struct
{
    int x; // x is height
    int y; // y is width
    int skin_area_ind;
    bool is_skin;
    bool is_checked;
} skin;

/* ==============================================
 *  function definitions
 * ============================================== */

char* identify_porn(img_para *img); // the function to identify the porn img
void check_neighbor(skin *s, int height, int width, int i, int j, int skin_area_count, Queue *queue); // check if the neighbor grids are also skin and label them


#endif
