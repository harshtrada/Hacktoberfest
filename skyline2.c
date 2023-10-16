#include <stdio.h>
#include <stdlib.h>

typedef struct Building
{
    int left, right, height;
} Building;

typedef struct Point
{
    int x, height;
} Point;

Point *merge(Point *leftSkyline, int leftSize, Point *rightSkyline, int rightSize, int *mergedSize)
{
    int maxSize = leftSize + rightSize;
    Point *mergedSkyline = (Point *)malloc(maxSize * sizeof(Point));
    int leftIndex = 0, rightIndex = 0, mergedIndex = 0;
    int leftHeight = 0, rightHeight = 0;

    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftSkyline[leftIndex].x < rightSkyline[rightIndex].x)
        {
            int x = leftSkyline[leftIndex].x;
            leftHeight = leftSkyline[leftIndex].height;
            int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
            mergedSkyline[mergedIndex].x = x;
            mergedSkyline[mergedIndex].height = maxHeight;

            leftIndex++;
        }
        else
        {
            int x = rightSkyline[rightIndex].x;
            rightHeight = rightSkyline[rightIndex].height;
            int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
            mergedSkyline[mergedIndex].x = x;
            mergedSkyline[mergedIndex].height = maxHeight;

            rightIndex++;
        }

        mergedIndex++;

        if (leftIndex == leftSize)
        {
            while (rightIndex < rightSize)
            {
                mergedSkyline[mergedIndex] = rightSkyline[rightIndex];
                rightIndex++;
                mergedIndex++;
            }
        }

        if (rightIndex == rightSize)
        {
            while (leftIndex < leftSize)
            {
                mergedSkyline[mergedIndex] = leftSkyline[leftIndex];
                leftIndex++;
                mergedIndex++;
            }
        }
    }

    *mergedSize = mergedIndex;
    return mergedSkyline;
}

Point *dandcSkyline(Building *buildings, int start, int end, int *resultSize)
{
    if (start == end)
    {
        Point *skyline = (Point *)malloc(2 * sizeof(Point));
        skyline[0].x = buildings[start].left;
        skyline[0].height = buildings[start].height;
        skyline[1].x = buildings[start].right;
        skyline[1].height = 0;
        *resultSize = 2;
        return skyline;
    }

    int mid = (start + end) / 2;
    int leftSize, rightSize;
    Point *leftSkyline = dandcSkyline(buildings, start, mid, &leftSize);
    Point *rightSkyline = dandcSkyline(buildings, mid + 1, end, &rightSize);

    Point *mergedSkyline = merge(leftSkyline, leftSize, rightSkyline, rightSize, resultSize);

    free(leftSkyline);
    free(rightSkyline);

    return mergedSkyline;
}
int main()
{
    Building buildings[] = {
        {33, 41, 5},
        {4, 9, 21},
        {30, 36, 9},
        {14, 18, 11},
        {2, 12, 14},
        {34, 43, 19},
        {23, 25, 8},
        {14, 21, 16},
        {32, 37, 12},
        {7, 16, 7},
        {24, 27, 10}};

    int numBuildings = sizeof(buildings) / sizeof(buildings[0]);
    int resultSize;
    Point *skyline = dandcSkyline(buildings, 0, numBuildings - 1, &resultSize);
    printf("Skyline Points: \n");
    for (int i = 0; i < resultSize; i++)
    {
        printf("(%d, %d) \n", skyline[i].x, skyline[i].height);
    }
    printf("\n");
    free(skyline);
    return 0;
}
