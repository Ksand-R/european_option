#TODO: parallel table


import xlwt
import data_config
import os


def create_book(cur_dir, dt, path, num_seq_ver, name_version):
    target_dir = os.path.join(cur_dir, dt)
    os.chdir(target_dir)
    N = list(data_config.get_setting(path, 'Dicts', 'N').split(' '))
    #print(N)

    for j in range(len(N)):
        name = "result_times" + '.xls'
        sheet = data_config.get_setting(path, 'Variables', 'sheet_name')
        workbook = xlwt.Workbook()
        sheet1 = workbook.add_sheet(sheet)
        sheet1.write(1, 0, data_config.get_setting(path, 'Variables', 'launch_string'))
        sheet1.write(7, 0, "amo of runs = " + data_config.get_setting(path, 'Variables', 'count'))
        sheet1.write(8, 0, "N = " + N[0])
        sheet1.write(9, 0, "sequential versions")
        sheet1.write(9, 1, "time in msec")
        for i in range(num_seq_ver):
            sheet1.write(i + 10, 0, name_version[i])
            sheet1.write(i + 10, 1, "common.seq_times")

    workbook.save(name)

