#TODO: parallel table


import xlwt
import data_config
import common


def create_book(path, num_seq_ver, name_version, name_par_ver, st, pt, thr):
    print(pt)
    N = list(data_config.get_setting(path, 'Dicts', 'N').split(' '))
    name = "result_times" + '.xls'
    sheet = data_config.get_setting(path, 'Variables', 'sheet_name')
    workbook = xlwt.Workbook()
    sheet1 = workbook.add_sheet(sheet)
    sheet1.write(1, 0, data_config.get_setting(path, 'Variables', 'launch_string'))
    sheet1.write(2, 0, "amo of runs = " + data_config.get_setting(path, 'Variables', 'count'))
    sheet1.write(3, 0, "N = " + N[0])
    sheet1.write(4, 0, "sequential versions")
    sheet1.write(4, 1, "time in msec")


    for i in range(num_seq_ver):
        sheet1.write(i + 5, 0, name_version[i])
        sheet1.write(i + 5, 1, st[i])

    _iter = 0
    for i in range(len(pt)):
        sheet1.write(i + 5, 3, name_par_ver[_iter // len(thr)])
        sheet1.write(i + 5, 4, thr[_iter % len(thr)])
        sheet1.write(i + 5, 5, pt[i])
        _iter += 1

    workbook.save(name)

