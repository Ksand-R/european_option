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
    if setting == "affinity" or setting == "name_version" or setting == "name_par_version":
        msg = "{section} {setting} is \n{value}".format(
            section=section, setting=setting, value=value)
        print("\n" + msg)
    else:
        msg = "{section} {setting} is {value}".format(
            section=section, setting=setting, value=value)
        print("\n" + msg)
    return value



