import os
import re
import csv
import sys

stats = '\\|.*\\|\s*([0-9]+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|\s*(.+)\\|'
total_instructions = 'KLEE: done: total instructions = ([0-9]+)'
program_exit_paths = 'KLEE: done:     program exit paths = ([0-9]+)'
error_paths = 'KLEE: done:     error paths = ([0-9]+)'
subsumed_paths = 'KLEE: done:     subsumed paths = ([0-9]+)'

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
                        m1 = re.search(stats, data)
                        if m1:
                            line.append(m1.group(2)) # Times
                            line.append(m1.group(1)) # Instructions
                            line.append(m1.group(3)) # ICov
                            line.append(m1.group(4)) # BCov
                        else:
                            line.extend(["-1", "-1", "-1", "-1"])
                        m2 = re.search(program_exit_paths, data)
                        if m2:
                            line.append(m2.group(1)) # program exit paths
                        else:
                            line.append("-1")
                        m3 = re.search(error_paths, data)
                        if m3:
                            line.append(m3.group(1)) # error paths
                        else:
                            line.append("-1")

                        # extract subsumed path from tracerx runs
                        if "tx" in runtype:
                            m4 = re.search(subsumed_paths, data)
                            if m4:
                                line.append(m4.group(1)) # subsumed paths
                            else:
                                line.append("-1")
                    lines.append(line)
                    # print(line)
    return lines

def write_csv(lines):
    with open('result.csv', 'wb') as csvfile:
        expwriter = csv.writer(csvfile, delimiter=',')
        expwriter.writerow(["Benchmark", "Times", "Total Instructions", "ICov", "BCov", "Program Exit Paths", "Error Paths", "Subsumed Paths"])
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

