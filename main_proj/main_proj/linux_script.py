from subprocess import Popen, PIPE
import sys

version = (sys.argv[1])
N       = (sys.argv[2])
num_tr  = (sys.argv[3])
count   = int(sys.argv[4])

info = "%s %s %s %s %s %s %s %s" % ("version ", version, "; amo of opts ", N, "; num tr ", num_tr, "; counts ", str(count))

def one_res():
    #name ="%s %i %i %i" % ("a.out", version, N, num_tr)
    name = "/home/romanov_a/EU_OP/a.out "+ version +" "+ N + " " + num_tr
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()  
    if proc.returncode:
       return res[1]
    return res[0]

def min_res():

    min_time = 10000
    
    for i in range(count):
        time = float(one_res())
        if time < min_time:
            min_time = time
    return min_time

def write_log():
    min_time = min_res()
    f = open('log.txt', 'a')
    f.write(str(info) + "; min time " +  str(min_time) + "\n")
    f.close()    

write_log()
