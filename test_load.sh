#!/bin/bash

echo "🧪 AI Performance Analyzer - Load Test"
echo "This script will generate CPU load to test the analyzer"
echo ""

echo "1. Starting CPU load generators..."
echo "   Running 5 background processes using 10-20% CPU each"

# Start some CPU-intensive processes
for i in {1..5}; do
    echo "   Starting load process $i..."
    while true; do
        echo "scale=1000; 4*a(1)" | bc -l > /dev/null 2>&1 &
        sleep 0.1
    done &
    LOAD_PIDS[$i]=$!
done

echo ""
echo "✅ Load generators started (PIDs: ${LOAD_PIDS[@]})"
echo ""
echo "2. Now run the AI Performance Analyzer in another terminal:"
echo "   cd ~/ai_performance_analyzer"
echo "   sudo ./performance_analyzer"
echo ""
echo "3. Watch how the analyzer detects the high CPU usage!"
echo ""
echo "Press Enter to stop the load test..."
read

echo "Stopping load generators..."
for pid in ${LOAD_PIDS[@]}; do
    kill $pid 2>/dev/null
done

echo "✅ Load test completed!"
