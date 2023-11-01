#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define MAX_N 10
#define MAX_ITER 1000

void kMeans(int arr[], int n, int means[], int n_cluster) {
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Allocate memory for clusters
        int* clusters[n_cluster];
        int clusterSizes[n_cluster];

        for (int i = 0; i < n_cluster; i++) {
            clusters[i] = malloc(n * sizeof(int));
            clusterSizes[i] = 0;
        }

        // Assign elements to clusters
        for (int i = 0; i < n; i++) {
            int minDist = INT_MAX;
            int minIndex = -1;

            for (int j = 0; j < n_cluster; j++) {
                int dist = abs(arr[i] - means[j]);

                if (dist < minDist) {
                    minDist = dist;
                    minIndex = j;
                }
            }

            clusters[minIndex][clusterSizes[minIndex]++] = arr[i];
        }

        // Calculate new means and check for convergence
        double newMeans[n_cluster];
        bool converged = true;

        for (int i = 0; i < n_cluster; i++) {
            int sum = 0;

            for (int j = 0; j < clusterSizes[i]; j++) {
                sum += clusters[i][j];
            }

            newMeans[i] = (double)sum / clusterSizes[i];

            if (fabs(newMeans[i] - means[i]) > 0.001) {
                converged = false;
                means[i] = newMeans[i];
            }
        }

        // Print clusters
        for (int i = 0; i < n_cluster; i++) {
            printf("Cluster %d (Closest to %d): ", i + 1, means[i]);
            
            for (int j = 0; j < clusterSizes[i]; j++) {
                printf("%d ", clusters[i][j]);
            }

            printf("\n");
        }

        // Free memory
        for (int i = 0; i < n_cluster; i++) {
            free(clusters[i]);
        }


        if (converged) {
            break;
        }
    }
}

int main() {
    int n, n_cluster;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of clusters (N): ");
    scanf("%d", &n_cluster);

    if (n_cluster <= 0 || n_cluster > MAX_N) {
        printf("Invalid number of clusters\n");
        return 1;
    }

    int means[n_cluster];

    printf("Assume %d initial means: ", n_cluster);

    for (int i = 0; i < n_cluster; i++) {
        scanf("%d", &means[i]);
    }

    kMeans(arr, n, means, n_cluster);

    return 0;
}
