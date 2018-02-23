from subprocess import Popen, PIPE
import sys, datetime, os, time

now = datetime.datetime.now()

N       = [1000000, 2000000, 3000000, 4000000]
count   = 7
num_seq_ver = 7
sec_times = []
par_times = []

par_ver = {0:7, 1:8}
threads = {0:1, 1:2, 2:4, 3:8, 4:16}
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
    for version in range(7):
        name = "srun -n 1 -p all -t 20 " + os.path.join(os.getcwd(), 'a.out ') + \
            str(version) +" "+ str(_N) + " " + str(1)
        sec_times.append((min_res(version, name))) 

    for version in par_ver:
        for thr in threads:
                    name = "srun -n 1 -p all -t 10 " + os.path.join(os.getcwd(), 'a.out ') + \
                        str(par_ver[version]) +" "+ str(_N) + " " + str(threads[thr])
                    par_times.append((min_res(par_ver[version], name))) 


def write_log(N_):
    os.chdir("logs")
    if not os.path.exists(dt) and not os.path.isfile(dt):
        os.mkdir(dt)
    os.chdir(dt)
    _iter = 0
    with open('!summary_' + str(N_) + '.log', 'a') as f:
	    print(sec_times)
	    for i in sec_times:   
	    	info = "%s %s %s %s %s %s %s %s" % ("version ", str(_iter), "; amo of opts ", \
	    		str(N_), "; num tr ", str(1), "; counts ", str(count))     
	        f.write(info + "; min time " +  str(i) + " seconds" +"\n")
	        _iter += 1

	    _iter = 0
	    print(par_times)
	    for i in par_times:   
	        info = "%s %s %s %s %s %s %s %s" % \
	            ("version ", str((_iter // 5) + 7), "; amo of opts ", str(N_), "; num tr ", \
	            str(threads[_iter % 5]), "; counts ", str(count))
	        f.write(info + "; min time " +  str(i) + " seconds" + "\n")
	        _iter += 1    
    del sec_times[:]
    del par_times[:]


if __name__ == '__main__':
	for i in N:
	    get_times(i)
	    write_log(i)
	    os.chdir(abs_path)
        print(sec_times)
        print(par_times)
