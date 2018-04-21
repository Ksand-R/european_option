from subprocess import Popen, PIPE
import sys, datetime, os, time

now = datetime.datetime.now()

#TODO: run script with file.out from argv
file 	= (sys.argv[1])
N       = [100]
count   = 5
num_seq_ver = 8
sec_times = []
par_times = []

par_ver = {0:8, 1:9}
threads = {0:1, 1:2, 2:4, 3:8, 4:16}
affinity = {		0: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=1 ',
			1: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=2 ',
			2: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=4 ',
			3: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=8 ',
			4: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=16 '
			}
name_version = {	0: 'Base ',
			1: 'fp ',
			2: 'erf ',
			3: 'restrict ',
			4: 'fp_simd ',
			5: 'vector ',
			6: 'invsqrt2_1 ',
			7: 'invsqrt2_2 '
			}
abs_path = os.getcwd()

dt = now.strftime("%d-%m-%Y-%H:%M:%S")

def one_res(version, name):
   
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()
    #print(name)
    #print(proc.returncode)
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
        name = os.path.join(os.getcwd(), str(file)) + " " +\
            str(version) +" "+ str(_N) + " " + str(1)
        sec_times.append((min_res(version, name))) 

    for version in par_ver:
        for thr in threads:
                    name = affinity[thr] +\
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
	    	info = "%s %s %s %s %s %s %s %s" % ("version ", str(name_version[_iter]), "; amo of opts ", \
	    		str(N_), "; num tr ", str(1), "; counts ", str(count))     
	        f.write(info + "; min time " +  str(i) + " seconds" +"\n")
	        _iter += 1
                #print(_iter)

	    _iter = 0
	    #print(par_times)
	    f.write(80 * "-" + "\n") 
	    for i in par_times:  

	        info = "%s %s %s %s %s %s %s %s" % \
	            ("version ", str((_iter // 5) + 4), "; amo of opts ", str(N_), "; num tr ", \
	            str(threads[_iter % 4]), "; counts ", str(count))
	        f.write(info + "; min time " +  str(i) + " seconds" + "\n" )
	        #f.write(str(affinity[_iter % 8]) + "\n")
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
