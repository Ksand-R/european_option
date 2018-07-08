import importlib
import sys
import os


def import_source(module_name, module_dir):
    module_file_path = os.path.join(module_dir, module_name + '.py')
    print(module_file_path)
    print(module_name)
    module_spec = importlib.util.spec_from_file_location(
        module_name, module_file_path
    )

    module = importlib.util.module_from_spec(module_spec)
    module_spec.loader.exec_module(module)
    print(dir(module))

    msg = 'The {module_name} module has the following methods: {methods}'
    print(
        msg.format(module_name=module_name, methods=dir(module))
    )


def module_import():
    module_dir = os.path.join(os.getcwd(), 'modules')
    for root, dirs, files in os.walk(module_dir):
        for f in files:
            if f.endswith('.py') and not f.startswith('__'):
                module_name = f[:-3]
                module_file_path = os.path.join(module_dir, module_name)
                sys.path.append(module_file_path)
                # import_source(module_name, module_dir)


if __name__ == "__main__":
    module_import()
    print(sys.path)
    path = "settings.ini"
    #print(modules)
    num_seq_ver = config.get_setting(path, 'Variables', 'num_seq_ver')
    #print(num_seq_ver)