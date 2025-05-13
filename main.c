#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// subject for optimization
// further additions: struct
// population or sample 

float *allocated_datasets(int num);
void swap(float *a, float *b);
int partition(float *data, int low, int high);
void quick_sort(float *data, int low, int high); // updated to quick sort algorithm. 
void print(float *data, int num);
float mean(float *data, int num);
float median(float *data, int num);
float mode(float *data, int num);
float std_dev(float *data, int num);

int main(int argc, char **argv)
{
    int num;

    printf("Enter the number of the datasets: ");
    scanf("%d", &num);

    if (num <= 0) { // input validation
        printf("Invalid Input.\n");
        printf("Exiting Program...\n");
        return 1;
    }

   float *datasets = allocated_datasets(num); // dynamic memory allocation (calloc = zero-based allocation) 

    if (!datasets) {
        return 1;
    }

    printf("\nEnter the following datasets:\n");
    for (int i = 0; i < num; i++)
    {
        printf("Data Stored[%d]: ", i + 1); // index starts at 1
        scanf("%f", &datasets[i]);
    }

    quick_sort(datasets, 0, num - 1);
    print(datasets, num);

    free(datasets); // frees the used memory
    return 0;
}

float *allocated_datasets(int num)
{
    float *datasets = calloc(num, sizeof(float));
    
    if (!datasets) 
    {
        perror("Memory Allocation Failed!");
        return NULL;
    }
    
    return datasets;
}

void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

int partition(float *data, int low, int high)
{
    float pivot = data[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) 
    {
        if (data[j] <= pivot) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[high]);
    return i + 1;
}

void quick_sort(float *data, int low, int high)
{
    if (low < high) {
        int pivot_index = partition(data, low, high);
        quick_sort(data, low, pivot_index - 1);
        quick_sort(data, pivot_index + 1, high);
    }
}

void print(float *data, int num)
{
    printf("\nThe Following Datasets (Sorted):\n");
    
    for (int i = 0; i < num; i++) {
        printf("%.2f ", *(data +i));
    }
    
    printf("\n");

    printf("\n=== Statistical Results ===\n");
    
    printf("Mean: %.2f\n", mean(data, num));
    
    printf("Median: %.2f\n", median(data, num));
    
    printf("Mode: %.2f\n", mode(data, num));
    
    printf("Standard Deviation: %.2f\n", std_dev(data, num));
}

float mean(float *data, int num)
{
    float average = 0;
    for (int i = 0; i < num; i++)
    {
        average += data[i] / num;
    }
    return (float)average;
}

float median(float *data, int num)
{

    if (num % 2 == 0) 
    {
        float mid1 = data[(num / 2) - 1];
        float mid2 = data[num / 2];
        return (mid1 + mid2) / 2.0;
    } else {
        return data[num / 2];
    }
}

float mode(float *data, int num)
{
    float max_val = 0, max_count = 0;
    for (int i = 0; i < num; i++)
    {
        float count = 0;
        for (int j = 0; j < num; j++) {
            if (data[i] == data[j]) {
                count++;
            }
        }
        if (count > max_count) 
        {
            max_count = count;
            max_val = data[i];
        }

    }

    if (max_count == 1) 
    {
        return NAN;
    }

    return max_val;
}

float std_dev(float *data, int num)
{
    float variance = 0, standard_deviation;
    float accumulated_mean = mean(data, num);

    for (int i = 0; i < num; i++) {
        variance += pow(data[i] - accumulated_mean, 2);
    }

    variance /= (num - 1);
    standard_deviation = sqrt(variance);

    return standard_deviation;
}
