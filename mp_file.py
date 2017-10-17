import multiprocessing as mp
import os

def process (line):
  print line

def process_wrapper (chunkStart, chunkSize):
  print mp.current_process().name
  with open("input.txt") as f:
    f.seek(chunkStart)
    lines = f.read(chunkSize).splitlines()
    for line in lines:
      process(line)

#This is size based, not line based
def chunkify (fname, size=10):
  fileEnd = os.path.getsize(fname)
  with open(fname,'r') as f:
    chunkEnd = f.tell()

    while True:
      chunkStart = chunkEnd
      f.seek (size,1)
      f.readline ()
      chunkEnd = f.tell ()
      yield chunkStart, chunkEnd - chunkStart
      if chunkEnd > fileEnd:
        break

def main():
  pool = mp.Pool()
  jobs = []

  #create jobs
  for chunkStart,chunkSize in chunkify ("input.txt"):
    jobs.append (pool.apply_async (process_wrapper, (chunkStart, chunkSize)))

  # wait for all jobs to finish
  for job in jobs:
    job.get ()

  pool.close ()

if __name__ == '__main__':
  main()
