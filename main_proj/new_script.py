from subprocess import Popen, PIPE
import sys

version = sys.argv[1]
N       = sys.argv[2]
num_tr  = sys.argv[3]
count   = sys.argv[4]

info = "%i %i %i %i" % (version, N, num_tr, count)

def one_res():
    name ="%s %i %i %i" % ("main_proj.exe ", version, N, num_tr)
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()  
    if proc.returncode:
       return res[1]
    return res[0]

def min_res():

    min_time = 1000000
    
    for i in range(count):
        time = float(one_res())
        if time < min_time:
            min_time = time
    return min_time

def write_log():
    avg_time = float(min_res())
    f = open('log.txt', 'a')
    f.write(str(count) + '     ' +  str(min_time) + "\n")
    f.close()    

write_log()
