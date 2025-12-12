#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define MAX_PROCESSES 256
#define MAX_NAME_LEN 128

// Process information structure
typedef struct {
    int pid;
    char name[MAX_NAME_LEN];
    float cpu_usage;
    float memory_mb;
    int threads;
    int priority;
    char state;
} ProcessInfo;

// Analysis results
typedef struct {
    int pid;
    char name[MAX_NAME_LEN];
    float risk_score;
    char bottleneck[32];
    char recommendation[256];
} ProcessAnalysis;

// Utility functions
void clear_screen();
void print_header(const char *title);
void get_timestamp(char *buffer, int size);
void trim_string(char *str);
float calculate_average(float *values, int count);
float calculate_std_dev(float *values, int count, float mean);

#endif
