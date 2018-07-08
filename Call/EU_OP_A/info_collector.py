import os


def collect_reports(dt):
    current_dir = os.getcwd()
    if not os.path.exists(dt) and not os.path.isfile(dt):
        os.mkdir(dt)
        os.chdir(dt)
        os.mkdir("opt_report")
        os.mkdir("asm_report")

    opt_dir = os.path.join(current_dir, dt, "opt_report")
    asm_dir = os.path.join(current_dir, dt, "asm_report")
    target_dir = os.path.join(current_dir, dt)

    for root, dirs, files in os.walk(current_dir):
        for f in files:
            if f.endswith('.optrpt'):
                try:
                    os.rename(os.path.join(current_dir, f), os.path.join(opt_dir, f))
                except Exception:
                    pass
            if f.endswith('.asm'):
                try:
                    os.rename(os.path.join(current_dir, f), os.path.join(asm_dir, f))
                except Exception:
                    pass

            if f.endswith('.xls') | f.endswith('.xlsx'):
                try:
                    os.rename(os.path.join(current_dir, f), os.path.join(target_dir, f))
                except Exception:
                    pass
            if f.endswith('.log'):
                try:
                    os.rename(os.path.join(current_dir, f), os.path.join(target_dir, f))
                except Exception:
                    pass
