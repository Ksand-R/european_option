from subprocess import Popen, PIPE
import sys
import datetime
import os
import data_config
import ast
import table_result
import info_collector

#TODO: add module loader!!!!!!!!!!!!!!!
#TODO: salloc -N 1 -p cpu -t 180 //id returns
#TODO: squeue | grep id // node_id returns ?
#TODO: ssh node node_id
#TODO: pip install --user /____/

#TODO: get tar-archives
#TODO: add logger

now = datetime.datetime.now()
dt = now.strftime("%d-%m-%Y-%H-%M-%S")
seq_times = [1, 2, 3, 2, 5, 6, 7, 8]
par_times = [0, 1, 2, 5, 6, 7, 8, 8, 0, 1, 2, 5, 6, 7, 8, 8, 0, 1, 2, 5, 6, 7, 8, 8]
abs_path = os.getcwd()
path = "settings.ini"

file = (sys.argv[1])
count = int(data_config.get_setting(path, 'Variables', 'count'))
num_seq_ver = int(data_config.get_setting(path, 'Variables', 'num_seq_ver'))
N = list(data_config.get_setting(path, 'Dicts', 'N').split(' '))
threads = ast.literal_eval(data_config.get_setting(path, 'Dicts', 'threads'))
par_ver = ast.literal_eval(data_config.get_setting(path, 'Dicts', 'par_ver'))
affinity = ast.literal_eval(data_config.get_setting(path, 'Dicts', 'affinity'))
name_version = ast.literal_eval(data_config.get_setting(path, 'Dicts', 'name_version'))
name_par_version = ast.literal_eval(data_config.get_setting(path, 'Dicts', 'name_par_version'))


def one_res(name):
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()
    res = proc.communicate()
    if proc.returncode:
        return res[1]
    return res[0]


def min_res(name, count):
    min_time = 10000

    for i in range(count):
        time = float(one_res(name))
        if time < min_time:
            min_time = time
    return min_time


def get_times(opts_amo):
    for version in range(num_seq_ver):
        name = os.path.join(os.getcwd(), str(file)) + " " + \
               str(version) + " " + str(opts_amo) + " " + str(1)
        seq_times.append((min_res(version, name)))

    for version in par_ver:
        for thr in threads:
            name = affinity[thr] + \
                   os.path.join(os.getcwd(), str(file)) + " " + \
                   str(par_ver[version]) +" " + str(opts_amo) + " " + str(threads[thr])
            par_times.append((min_res(par_ver[version], name)))


def write_log(opts_amo):
    _iter = 0
    with open('summary_' + str(opts_amo) + '.log', 'a') as f:
        #print(sec_times)
        print(datetime.datetime.now())
        for i in seq_times:
            info = "%s %s %s %s %s %s" % ("version ", str(name_version[_iter]), "; amo of opts ",
                str(opts_amo), "; counts ", str(count))
            f.write(info + "; min time " + str(i) + " seconds" + "\n")
            _iter += 1
            #print(_iter)

        _iter = 0
        #print(par_times)

        for i in par_times:

            info = "%s %s %s %s %s %s %s %s" % \
                   ("version ", str(name_par_version[_iter // len(threads)]), "; amo of opts ", str(opts_amo),
                    "; num tr ", str(threads[_iter % len(threads)]), "; counts ", str(count))
            if _iter % len(threads) == 0:
                f.write(80 * "-" + "\n")
            f.write(info + "; min time " +  str(i) + " seconds" + "\n" )
            _iter += 1



if __name__ == '__main__':

    for i in N:
        #get_times(i)
        write_log(i)
        os.chdir(abs_path)
    table_result.create_book(path, num_seq_ver, name_version, name_par_version, seq_times, par_times, threads)
    info_collector.collect_reports(dt)

    #report_collector.collect_table(abs_path, dt)
    # for i in N:
    #     get_times(i)
    #     write_log(i)
    #     os.chdir(abs_path)

    """
    print(sec_times)
    print(par_times)
    del seq_times[:]
    del par_times[:]
    """