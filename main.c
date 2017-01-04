#include "matrix.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

float randf(float min, float max)
{
    return ((max - min)) * ((float)rand()) / ((float)RAND_MAX) + min;
}

void random_mat4(mat4 *left_matrix)
{
    for(int i = 0; i < 16; i++)
    {
        left_matrix->m[i] = randf(-10.0f, 10.0f);
    }
}

int main()
{
    srand(time(NULL));

    clock_t diffA[100];
    clock_t diffB[100];

    const int count = 2 << 22;
    for(int k = 0; k < 100; k++)
    {
        mat4 *left_matrix = calloc(sizeof(mat4), count);
        mat4 *right_matrix = calloc(sizeof(mat4), count);
        mat4 *versionA = calloc(sizeof(mat4), count);
        mat4 *versionB = calloc(sizeof(mat4), count);

        for(int i = 0; i < count; i++)
        {
            random_mat4(&left_matrix[i]);
            random_mat4(&right_matrix[i]);
        }

        clock_t start = clock();

        for(int i = 0; i < count; i++)
            mat4_mul_VERSION_A(&versionA[i], &left_matrix[i], &right_matrix[i]);

        diffA[k] = clock() - start;

        start = clock();

        for(int i = 0; i < count; i++)
            versionB[i] = mat4_mul_VERSION_B(&left_matrix[i], &right_matrix[i]);

        diffB[k] = clock() - start;

        int differences = 0;

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                if(versionA[i].m[j] - versionB[i].m[j] != 0.0f)
                {
                    differences++;
                }
            }
        }

        printf("%lu : %lu\n", diffA[k], diffB[k]);
        printf("Differences: %d\n", differences);

        free(left_matrix);
        free(right_matrix);
        free(versionA);
        free(versionB);
    }

    clock_t totalA = 0;
    clock_t totalB = 0;
    for(int k = 0; k < 100; k++)
    {
        totalA += diffA[k];
        totalB += diffB[k];
    }

    printf("AVERAGES:  Return reference - %lu : Return Value - %lu\n\n", totalA / 100, totalB / 100);

    return 0;
}
