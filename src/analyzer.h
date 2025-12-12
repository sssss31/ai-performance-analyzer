#ifndef ANALYZER_H
#define ANALYZER_H

#include "utils.h"

// Data collection functions
int get_process_count();
int collect_processes(ProcessInfo *processes, int max_count);
float get_cpu_usage();
float get_memory_usage();

// AI Analysis functions
void analyze_process(ProcessInfo *proc, ProcessAnalysis *analysis);
void detect_anomalies(ProcessInfo *processes, int count);
void predict_trends(ProcessInfo *processes, int count);
void generate_recommendations(ProcessAnalysis *analysis);

// Display functions
void display_dashboard(ProcessInfo *processes, ProcessAnalysis *analysis, int count);
void show_detailed_view(ProcessInfo *proc, ProcessAnalysis *analysis);
void show_summary();

#endif
