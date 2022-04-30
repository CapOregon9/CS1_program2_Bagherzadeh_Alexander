//Name: Alexander Bagherzadeh
//Dr. Steinberg
//COP3502 Spring 2022
//Programming Assignment 2

#include<stdio.h>
#include<stdlib.h>

int blobDetect(int ** picture, int x, int y, int limit);

int main()
{
    //setup randomness
    int x;

    printf("Enter seed: ");
    scanf("%d", &x);

    srand(x); //set seed

    printf("Enter the size of the picture: ");

    int size;
    scanf("%d", &size);

    int ** picture = (int **) malloc(size * sizeof(int *));

    for(int x = 0; x < size; ++x)
        picture[x] = (int *) malloc(size * sizeof(int));

    for(int test = 1; test <= 5; ++test)
    {
        printf("Test %d\n", test);

        for(int r = 0; r < size; ++r)
            for(int c = 0; c < size; ++c)
                picture[r][c] = rand() % 2; //generate random number between 0 and 1


        int numblobs = 0;

        for(int r = 0; r < size; ++r)
            for(int c = 0; c < size; ++c)
                if(blobDetect(picture, r, c, size) > 0)
                    ++numblobs;

        printf("There are %d blob(s) in the picture.\n", numblobs);
    }

    //Super important! I don't think I can emphasize how important this is to do!
    for(int x = 0; x < size; ++x)
        free(picture[x]);

    free(picture);

    return 0;
}

int blobDetect(int ** picture, int x, int y, int limit) {
    if (x < limit && y < limit) {
        if (picture[x][y] != 0) {
            picture[x][y] = 0; //changes spot with blob to 0 to stop double counting of the same blob.
            if (x > 0 && y > 0) { //checks previous locations depending on location to be careful with array out of bounds
                --x;
                ++y;
                blobDetect(picture, x, y, limit);
                --y;
                blobDetect(picture, x, y, limit);
                --y;
                blobDetect(picture, x, y, limit);
                ++x;
                blobDetect(picture, x, y, limit);
                ++x;
                blobDetect(picture, x, y, limit);
                ++y;
                --x;
            } else if (x > 0) {
                --x;
                blobDetect(picture, x, y, limit);
                ++y;
                blobDetect(picture, x, y, limit);
                ++x;
                --y;
            }else if (y > 0) {
                --y;
                blobDetect(picture, x, y, limit);
                ++x;
                blobDetect(picture, x, y, limit);
                ++y;
                --x;
            }
            ++x;
            blobDetect(picture, x, y, limit); //checks the locations in surrounding the front of the blob location to see if it continues forward
            ++y;
            blobDetect(picture, x, y, limit);
            --x;
            blobDetect(picture, x, y, limit);
            return 1; //returns 1 saying there was a blob or a blob in this spot
        } else {
            return 0; //returns 0 saying there was not a blob in this spot (doesn't change much due to the value not being used in the call statements)
        }
    }
    return 0; //returns 0 saying there was not a blob
}