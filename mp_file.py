import multiprocessing as mp

def process (line):
    print line

def process_wrapper(lineByte):
    with open("input.txt") as f:
        f.seek(lineByte)
        line = f.readline()
        process(line)

#init objects
pool = mp.Pool()
jobs = []

#create jobs
with open("input.txt") as f:
    nextLineByte = f.tell()
    for line in f:
        jobs.append( pool.apply_async(process_wrapper,(nextLineByte,)) )
        nextLineByte = f.tell()

#wait for all jobs to finish
for job in jobs:
    job.get()

#clean up
pool.close()
