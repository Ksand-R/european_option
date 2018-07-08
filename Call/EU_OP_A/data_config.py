import configparser


def get_config(path):
    """
    Returns the config object
    """
    config = configparser.ConfigParser()
    config.read(path)
    return config


def get_setting(path, section, setting):
    """
    Print out a setting
    """
    config = get_config(path)
    value = config.get(section, setting)
    #TODO: should use in logging
    # msg = "{section} {setting} is {value}".format(
    #     section=section, setting=setting, value=value
    # )
    #
    # print(msg)
    return value



