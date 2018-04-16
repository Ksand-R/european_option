import configparser


def get_config(path):
    config = configparser.ConfigParser()
    config.read(path)
    return config


def get_setting(path, section, setting):
    config = get_config(path)
    value = config.get(section, setting)
    #TODO: next code should use in logger
    # msg = "{section} {setting} is {value}".format(
    #     section=section, setting=setting, value=value
    # )
    # print(msg)
    return value




