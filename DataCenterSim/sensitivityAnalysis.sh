am='true'
ap='false'
bm=0.00288
bp=0.0288
cm=3
cp=30

./main --enable_sorting $am --completion_time_stdev $bm --power_estimate_error_stdev $cm > 0_mmm.txt & ./main --enable_sorting $ap --completion_time_stdev $bm --power_estimate_error_stdev $cm > 1_mmm.txt
./main --enable_sorting $am --completion_time_stdev $bm --power_estimate_error_stdev $cp > 2_mpm.txt & ./main --enable_sorting $ap --completion_time_stdev $bm --power_estimate_error_stdev $cp > 3_mpm.txt
./main --enable_sorting $am --completion_time_stdev $bp --power_estimate_error_stdev $cm > 4_mmp.txt & ./main --enable_sorting $ap --completion_time_stdev $bp --power_estimate_error_stdev $cm > 5_mmp.txt
./main --enable_sorting $am --completion_time_stdev $bp --power_estimate_error_stdev $cp > 6_mpp.txt & ./main --enable_sorting $ap --completion_time_stdev $bp --power_estimate_error_stdev $cp > 7_mpp.txt
