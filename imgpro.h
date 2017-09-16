#ifndef _IMGPRO_H_
#define _IMGPRO_H_

/* ==============================================
 *  headers to be included
 * ============================================== */
#include<stdint.h>
#include<stdio.h>

/* ==============================================
 * micros and data type definitions 
 * ============================================== */

typedef struct
{
    int channel;
    int width;
    int height;
    long size;
    uint8_t *data;
} img_para;

/* ==============================================
 *  function definitions
 * ============================================== */

void identify_porn(img_para *img); // the function to identify the porn img


#endif
