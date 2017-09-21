#include"imgpro.h"



/* function: char* identify_porn(img_para *img) 
 *
 * the function to identify the porn img 
 *
 * input: an image depiction structure
 * return: a matrix depicting the handled image, with each element to be number 0 or 255, 0 for non-skin pixel and 255 for skin pixel
 */
char* identify_porn(img_para *img) 
{
    const int width = img->width;
    const int height = img->height;
    const int channel = img->channel;
    uint8_t r, g, b;
    uint8_t (*data)[width][channel]; 
    skin (*skin_p)[width] = NULL;
    int skin_area_count = 0;
    Queue queue;
    long skin_pix_num = 0;
    double skin_area_ratio;

    // initial the variables
    skin_p = malloc(sizeof(skin)*width*height);
    queue = queue_create();
    data = (void *)img->data;

    // calculate each pixel to see if it is skin
    fputs("[server thread 2]: identify each pixel to see if it is skin pixel ... done\n", stdout);
    for (int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            skin_p[i][j].x = i;
            skin_p[i][j].y = j;
            skin_p[i][j].is_checked = false;

            r = data[i][j][0];
            g = data[i][j][1];
            b = data[i][j][2];

            skin_p[i][j].is_skin = (r > 95) && (g >40) && (g < 100) && (b > 20) && ((Max(r,g,b) - Min(r,g,b)) > 15) && (abs(r - g) > 15) && (r > g) && (r > b);
            if(skin_p[i][j].is_skin == true)
                skin_pix_num++;
        }


    // collect all the skin areas
    fputs("[server thread 2]: calculating all skin areas\n", stdout);
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(skin_p[i][j].is_skin && (!skin_p[i][j].is_checked))
            {
                skin_p[i][j].is_checked = true;
                skin_p[i][j].skin_area_ind = skin_area_count;
                check_neighbor((skin*)skin_p, height, width, i, j, skin_area_count++, &queue);
            }

    // see if this is porn picture
    skin_area_ratio = (double)skin_pix_num/(long)(width*height);

    if(skin_area_count > 60 || skin_area_count < 3)
        fprintf(stdout, "[server thread 2] picture is porn with number of skin area: %d\n",skin_area_count);

        fprintf(stdout, "[server thread 2] number of skin pixel is: %ld\n",(long)(width*height));

    if(skin_area_ratio < 0.15)
        fprintf(stdout, "[server thread 2] picture is porn with skin pixel ratio: %lf\n", skin_area_ratio);


    // create a uint8_t string of the pixels, where for skin pixels value is 255 and for non-skin pixels value is 0
    uint8_t *sk = malloc(sizeof(uint8_t)*width*height);
    uint8_t *cp;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            cp = sk+(width*i+j);
            if(skin_p[i][j].is_skin)
                *cp = 255;
            else
                *cp = 0;
        }


    queue_destroy(&queue);
    free(skin_p);

    return (void*)sk;
}


/* function: void check_neighbor(skin *s, const int height, const int width, int i, int j, int skin_area_count, Queue *queue)
 *
 * check if the grids around a specific grid are skin grids
 * united with the current one, and then label them 
 * input:
 * return:
 * */
void check_neighbor(skin *s, const int height, const int width, int i, int j, int skin_area_count, Queue *queue)
{
    skin (*skin_p)[width] = NULL;
    int istart, iend, jstart, jend;
    QueueNode qn;
    skin *data = NULL;

    /* initial the variables */
    skin_p = (void *)s;
    

    /* add the neighbor grids to the queue */
    // determine the loop boundary
    if(i == 0)
    {
        istart = i;
        iend = i + 1;
    }
    else if(i == (height-1))
    {
        istart = i - 1;
        iend = i;
    }
    else
    {
        istart = i - 1;
        iend = i + 1;
    }

    if(j == 0)
    {
        jstart = j;
        jend = j + 1;
    }
    else if(j == (width-1))
    {
        jstart = j - 1;
        jend = j;
    }
    else
    {
        jstart = j - 1;
        jend = j + 1;
    }
    // add the neighbor unchecked skin pixel to queue
    for(int ii = istart; ii <= iend; ii++)
        for(int jj = jstart; jj <= jend; jj++)
            if((!skin_p[ii][jj].is_checked) && skin_p[ii][jj].is_skin)
            {
                skin_p[ii][jj].is_checked = true;
                skin_p[ii][jj].skin_area_ind = skin_area_count;
                queue_add_node(queue, &skin_p[ii][jj], sizeof(skin_p[ii][jj]));
            }

    while(!queue_is_empty(queue))
    {
        qn = queue_pop_node(queue);
        data = (skin *)qn.data;
        check_neighbor((skin *)skin_p, height, width, data->x, data->y,skin_area_count, queue);
        free(qn.data);
    }
}
