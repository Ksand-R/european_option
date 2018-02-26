from subprocess import Popen, PIPE
import sys, datetime, os, time

now = datetime.datetime.now()

#TODO: run script with file.out from argv
file 	= (sys.argv[1])
N       = [100000000 ,268435456]
count   = 7
num_seq_ver = 7
sec_times = []
par_times = []

par_ver = {0:7, 1:8}
threads = {0:1, 1:2, 2:4, 3:8, 4:16}
affinity = {0: '',
			1: 'GOMP_CPU_AFFINITY="0 1" OMP_NUM_THREADS=2 ',
			2: 'GOMP_CPU_AFFINITY="0 1 2 3" OMP_NUM_THREADS=4 ',
			3: 'GOMP_CPU_AFFINITY="0 1 2 3 4 5 6 7" OMP_NUM_THREADS=8 ',
			4: 'GOMP_CPU_AFFINITY="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" OMP_NUM_THREADS=16 '
			}
abs_path = os.getcwd()

dt = now.strftime("%d-%m-%Y-%H:%M:%S")

def one_res(version, name):
   
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()  
    if proc.returncode:
       return res[1]
    return res[0]

def min_res(version, name):
    min_time = 10000
    
    for i in range(count):
        time = float(one_res(version, name))
        if time < min_time:
            min_time = time
    return min_time

def get_times(_N):
    for version in range(num_seq_ver):
        name = "srun -n 1 -p all -t 30 " + os.path.join(os.getcwd(), str(file)) + " " +\
            str(version) +" "+ str(_N) + " " + str(1)
        sec_times.append((min_res(version, name))) 

    for version in par_ver:
        for thr in threads:
                    name = affinity[thr] + "srun -n 1 -p all -t 20 " + \
                        os.path.join(os.getcwd(), str(file)) + " " +\
                        str(par_ver[version]) +" "+ str(_N) + " " + str(threads[thr])
                    par_times.append((min_res(par_ver[version], name))) 


def write_log(N_):
    os.chdir("logs")
    if not os.path.exists(dt) and not os.path.isfile(dt):
        os.mkdir(dt)
    os.chdir(dt)
    _iter = 0
    with open('!summary_' + str(N_) + '.log', 'a') as f:
	    #print(sec_times)
	    print(datetime.datetime.now())
	    for i in sec_times:   
	    	info = "%s %s %s %s %s %s %s %s" % ("version ", str(_iter), "; amo of opts ", \
	    		str(N_), "; num tr ", str(1), "; counts ", str(count))     
	        f.write(info + "; min time " +  str(i) + " seconds" +"\n")
	        _iter += 1

	    _iter = 0
	    #print(par_times)
	    f.write(80 * "-" + "\n") 
	    for i in par_times:  

	        info = "%s %s %s %s %s %s %s %s" % \
	            ("version ", str((_iter // 5) + 7), "; amo of opts ", str(N_), "; num tr ", \
	            str(threads[_iter % 5]), "; counts ", str(count))
	        f.write(info + "; min time " +  str(i) + " seconds" + "\n" )
	        #f.write(str(affinity[_iter % 5]) + "\n")
	        _iter += 1    
	    f.write(80 * "-") 
    del sec_times[:]
    del par_times[:]

if __name__ == '__main__':
	for i in N:
	    get_times(i)
	    write_log(i)
	    os.chdir(abs_path)
        #print(sec_times)
        #print(par_times)
