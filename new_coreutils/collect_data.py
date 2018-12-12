import os
import re
import csv
import sys

stats = '\\|.*\\|\s*([0-9]+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|'
total_instructions = 'KLEE: done: total instructions = ([0-9]+)'
program_exit_paths = 'KLEE: done:     program exit paths = ([0-9]+)'
error_paths = 'KLEE: done:     error paths = ([0-9]+)'
subsumed_paths = 'KLEE: done:     subsumed paths = ([0-9]+)'
visited_bb = 'KLEE: done: Total number of single time Visited Basic Blocks: ([0-9]+)'
total_bb = 'KLEE: done: Total number of Basic Blocks: ([0-9]+)'

def collect(folder, runtype):
    lines = []
    for sub in os.listdir(folder):
        sub_path = os.path.join(folder, sub)

        if os.path.isdir(sub_path) and sub.endswith(runtype):
            # print(sub)
            for file in os.listdir(sub_path):
                file_path = os.path.join(sub_path, file)
                if os.path.isfile(file_path) and file == "info":
                    # print(file)
                    line = []
                    line.append(sub) # Benchmark
                    with open(file_path, 'r') as f:
                        data = f.read()
                        # print(data)
                        stats_match = re.search(stats, data)
                        if stats_match:
                            line.append(stats_match.group(2)) # Times
                            line.append(stats_match.group(1)) # Instructions
                            line.append(stats_match.group(3)) # ICov
                            line.append(stats_match.group(4)) # BCov
                        else:
                            line.extend(["-1", "-1", "-1", "-1"])
                        program_exit_paths_match = re.search(program_exit_paths, data)
                        if program_exit_paths_match:
                            line.append(program_exit_paths_match.group(1)) # program exit paths
                        else:
                            line.append("-1")
                        error_paths_match = re.search(error_paths, data)
                        if error_paths_match:
                            line.append(error_paths_match.group(1)) # error paths
                        else:
                            line.append("-1")

                        visited_bb_match = re.search(visited_bb, data)
                        total_bb_match = re.search(total_bb, data)
                        if visited_bb and total_bb_match:
                            line.append(round(float(visited_bb_match.group(1))/float(total_bb_match.group(1)), 2)) # bb coverage
                        else:
                            line.append("-1.0")

                        # extract subsumed path from tracerx runs
                        if "tx" in runtype:
                            subsumed_paths_match = re.search(subsumed_paths, data)
                            if subsumed_paths_match:
                                line.append(subsumed_paths_match.group(1)) # subsumed paths
                            else:
                                line.append("-1")
                    lines.append(line)
                    # print(line)
    return lines

def write_csv(lines):
    with open('result.csv', 'wb') as csvfile:
        expwriter = csv.writer(csvfile, delimiter=',')
        expwriter.writerow(["Benchmark", "Times", "Total Instructions", "ICov %", "BCov %", "Program Exit Paths", "Error Paths", "BB Cov", "Subsumed Paths"])
        for line in lines:
            expwriter.writerow(line)

def takeFirst(elem):
    return elem[0]

folder = sys.argv[1]
lines = collect(folder, ".klee_rand")
lines.extend(collect(folder, ".tx_rand"))
lines.extend(collect(folder, ".tx_dfs"))
lines.sort(key=takeFirst)
write_csv(lines)

