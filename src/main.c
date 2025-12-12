#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "analyzer.h"
#include "utils.h"

#define MAX_PROCESSES 256
#define REFRESH_INTERVAL 3

volatile sig_atomic_t running = 1;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        running = 0;
        printf("\n\n🛑 Shutting down AI Performance Analyzer...\n");
    }
}

void print_welcome() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                🤖 AI PERFORMANCE ANALYZER v2.0                  ║\n");
    printf("║           Real-time System Monitoring & AI Insights             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("📡 Collecting initial system data...\n");
    printf("🧠 Training AI models on process patterns...\n");
    printf("📊 Setting up real-time dashboard...\n\n");
    
    sleep(2);
}

int main() {
    // Set up signal handler
    signal(SIGINT, signal_handler);
    
    // Seed random number generator
    srand(time(NULL));
    
    // Print welcome message
    print_welcome();
    
    ProcessInfo processes[MAX_PROCESSES];
    ProcessAnalysis analysis[MAX_PROCESSES];
    
    int cycle = 0;
    
    // Main monitoring loop
    while (running) {
        cycle++;
        
        // Collect process information
        int process_count = collect_processes(processes, MAX_PROCESSES);
        
        if (process_count > 0) {
            // Analyze each process with AI
            for (int i = 0; i < process_count; i++) {
                analyze_process(&processes[i], &analysis[i]);
            }
            
            // Display real-time dashboard
            display_dashboard(processes, analysis, process_count);
            
            // Log analysis results every 5 cycles
            if (cycle % 5 == 0) {
                FILE *log = fopen("data/analysis.log", "a");
                if (log) {
                    char timestamp[32];
                    get_timestamp(timestamp, sizeof(timestamp));
                    
                    fprintf(log, "\n🔍 Analysis Cycle #%d at %s\n", cycle, timestamp);
                    fprintf(log, "════════════════════════════════════════════════════════\n");
                    
                    int high_risk = 0, medium_risk = 0;
                    float total_cpu = 0, total_memory = 0;
                    
                    for (int i = 0; i < (process_count < 15 ? process_count : 15); i++) {
                        total_cpu += processes[i].cpu_usage;
                        total_memory += processes[i].memory_mb;
                        
                        if (analysis[i].risk_score > 70.0f) {
                            high_risk++;
                            fprintf(log, "🚨 HIGH RISK: PID %d - %s\n", 
                                    analysis[i].pid, analysis[i].recommendation);
                        } else if (analysis[i].risk_score > 40.0f) {
                            medium_risk++;
                        }
                    }
                    
                    fprintf(log, "\n📈 Statistics:\n");
                    fprintf(log, "   • Total processes analyzed: %d\n", process_count);
                    fprintf(log, "   • High-risk processes: %d\n", high_risk);
                    fprintf(log, "   • Medium-risk processes: %d\n", medium_risk);
                    fprintf(log, "   • Average CPU usage (top 15): %.1f%%\n", total_cpu / (process_count < 15 ? process_count : 15));
                    fprintf(log, "   • Total memory used (top 15): %.1f MB\n", total_memory);
                    
                    fclose(log);
                    
                    // Show log saved message
                    printf("\n💾 Analysis saved to data/analysis.log\n");
                }
            }
            
            // Show AI recommendations for top 3 high-risk processes
            printf("\n🎯 TOP AI RECOMMENDATIONS:\n");
            printf("──────────────────────────────────────────────────────────────────────\n");
            
            int recommendations_shown = 0;
            for (int i = 0; i < (process_count < 5 ? process_count : 5); i++) {
                if (analysis[i].risk_score > 50.0f) {
                    printf("• %s\n", analysis[i].recommendation);
                    recommendations_shown++;
                }
            }
            
            if (recommendations_shown == 0) {
                printf("✅ No critical issues detected. System operating optimally.\n");
                printf("💡 Tip: Monitor for any sudden increases in CPU or memory usage.\n");
            }
            
            printf("\n");
        } else {
            printf("❌ Error: Could not collect process data!\n");
            printf("   Make sure you're running with sudo privileges.\n");
            running = 0;
        }
        
        // Countdown before next update
        if (running) {
            printf("⏳ Next analysis in: ");
            fflush(stdout);
            
            for (int i = REFRESH_INTERVAL; i > 0 && running; i--) {
                printf("%d... ", i);
                fflush(stdout);
                sleep(1);
            }
            printf("\n");
        }
    }
    
    // Shutdown sequence
    printf("\n════════════════════════════════════════════════════════════════════\n");
    printf("📊 Final Statistics:\n");
    printf("   • Total monitoring cycles: %d\n", cycle);
    printf("   • Log file: data/analysis.log\n");
    printf("   • Max processes analyzed per cycle: %d\n", MAX_PROCESSES);
    printf("\n👋 Thank you for using AI Performance Analyzer!\n");
    printf("   For detailed reports, check data/analysis.log\n");
    
    return 0;
}
