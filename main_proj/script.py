from subprocess import Popen, PIPE

def one_res():
    name = 'Preliminary.exe'
    proc = Popen(name, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()    
    res = proc.communicate()  
    if proc.returncode:
       return res[1]
    return res[0]

def avg_res(count):

    avg_time = 0
    
    for i in range(count):
        time = float(one_res())
        avg_time += time

        avg_time /= count
    return avg_time

def write_log():
    avg_time = float(avg_res(10))
    f = open('log.txt', 'a')
    f.write(str(avg_time) + "\n")
    f.close()    

write_log()
