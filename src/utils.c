#include "utils.h"

void clear_screen() {
    printf("\033[2J\033[1;1H");
}

void print_header(const char *title) {
    printf("\n╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-64s ║\n", title);
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

void get_timestamp(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void trim_string(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == '\n' || str[i] == '\r' || str[i] == ' ' || str[i] == '\t')) {
        str[i] = '\0';
        i--;
    }
}

float calculate_average(float *values, int count) {
    if (count == 0) return 0.0f;
    
    float sum = 0.0f;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / count;
}

float calculate_std_dev(float *values, int count, float mean) {
    if (count <= 1) return 0.0f;
    
    float sum_sq_diff = 0.0f;
    for (int i = 0; i < count; i++) {
        float diff = values[i] - mean;
        sum_sq_diff += diff * diff;
    }
    
    return sqrt(sum_sq_diff / (count - 1));
}
