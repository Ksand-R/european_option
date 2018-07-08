from subprocess import Popen, PIPE
import sys, datetime, os, time
import re
#import data_config

now = datetime.datetime.now()
# TODO: run script with file.out from argv
file = (sys.argv[1])
N = [1000, 2684]
count = 7
num_seq_ver = 7
sec_times1 = []
sec_times2 = []
par_times1 = []
par_times2 = []
# min_res_dict = {}
par_ver = {0: 7, 1: 8}
threads = {0: 1, 1: 2, 2: 4, 3: 8, 4: 16, 5: 20, 6: 40, 7: 80}
affinity = {	0: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=1 ',
			1: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=2 ',
			2: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=4 ',
			3: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=8 ',
			4: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=16 ',
			5: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=20 ',
			6: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=40 ',
			7: 'KMP_AFFINITY=granularity=fine,compact,1,0 OMP_NUM_THREADS=80 '
			}
name_version = {0: 'Base ',
			1: 'fp ',
			2: 'erf ',
			3: 'restrict ',
			4: 'vector ',
			5: 'invsqrt2_1 ',
			6: 'invsqrt2_2 '
			
			}
abs_path = os.getcwd()

dt = now.strftime("%d-%m-%Y-%H:%M:%S")

def one_res(version, name):
   
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()
    # print(name)
    # print(proc.returncode)
    if proc.returncode:
       return res[1]
    return res[0]

def min_res(version, name):
    min_times_res = {0 :10000, 1 :10000}
    for i in range(count):
        array_times = re.findall(r'\d+.\d+', one_res(version, name))
    # print(array_times)
    counter = 0
    for j in array_times:
	    	# print(j)
            # print(min_times_res[counter])
            	time = float(array_times[counter])
            # print(time)
            # if time < min_time:
        	if time < min_times_res[counter]:
			# print("true")
            		min_times_res[counter] = time
            # min_time = time
		counter += 1
    min_res_dict = min_times_res
    # print(min_res_dict)
    return min_res_dict

def get_times(_N):
    for version in range(num_seq_ver):
        name = os.path.join(os.getcwd(), str(file)) + " " +\
            str(version) +" " + str(_N) + " " + str(1)
        min_res_dict = min_res(version, name)
        # print(min_res_dict)
        print(min_res_dict)
    sec_times1.append(min_res_dict[0])
    sec_times2.append(min_res_dict[1])

    for version in par_ver:
        for thr in threads:
            name = affinity[thr] + \
                   os.path.join(os.getcwd(), str(file)) + " " + \
                   str(par_ver[version]) + " " + str(_N) + " " + str(threads[thr])
            # par_times.append((min_res(par_ver[version], name)))
            min_res_dict = min_res(par_ver[version], name)
        par_times1.append(min_res_dict[0])
        par_times2.append(min_res_dict[1])


def write_log(N_):
    os.chdir("logs")
    if not os.path.exists(dt) and not os.path.isfile(dt):
        os.mkdir(dt)
    os.chdir(dt)
    _iter = 0
    with open('!summary_' + str(N_) + '.log', 'a') as f:
        # print(sec_times)
        print(datetime.datetime.now())

        for i in sec_times1:
            info = "%s %s %s %s %s %s %s %s" % ("version ", str(name_version[_iter]), "; amo of opts ", \
                                                str(N_), "; num tr ", str(1), "; counts ", str(count))
            f.write(info + "; min time " + str(i) + " seconds" + "\n")
            _iter += 1
            # print(_iter)

        _iter = 0
        # print(par_times)
        f.write(80 * "-" + "\n")
        for i in par_times1:
            info = "%s %s %s %s %s %s %s %s" % \
                   ("version ", str((_iter // 8) + 7), "; amo of opts ", str(N_), "; num tr ", \
                    str(threads[_iter % 8]), "; counts ", str(count))
            f.write(info + "; min time " + str(i) + " seconds" + "\n")
            # f.write(str(affinity[_iter % 8]) + "\n")
            _iter += 1
        f.write(80 * "-")
    del sec_times1[:]
    del par_times1[:]
    del sec_times2[:]
    del par_times2[:]
    # del min_times_res[:]


if __name__ == '__main__':
    path = "settings.ini"
    for i in N:
        get_times(i)
        write_log(i)
        os.chdir(abs_path)
    # print(sec_times)
    # print(par_times)
