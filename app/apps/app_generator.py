import os as os
from shutil import copytree
import re
import sys
from re import sub
from datetime import datetime

script_directory = os.path.dirname(os.path.abspath(sys.argv[0])) + "/"


def toSnakeCase(sentence):
    # 用空格替换连字符，然后应用正则表达式替换以实现标题大小写转换，
    # 并在单词之间添加下划线，最后将结果转换为小写
    return '_'.join(
        sub('([A-Z][a-z]+)', r' \1',
            sub('([A-Z]+)', r' \1',
                sentence.replace('-', ' '))).split()).lower()


def toCamelCase(sentence):
    # 使用正则表达式替换下划线和连字符为空格，
    # 然后将字符串转换为标题格式（每个单词的第一个字母大写），并移除空格
    sentence = sub(r"(_|-)+", " ", sentence).title().replace(" ", "")

    # 确保第一个字母是小写
    return ''.join([sentence[0].lower(), sentence[1:]])


def toCamelCase(sentence):
    words = sentence.replace('_', ' ').split()
    camel_case = ''.join(word.capitalize() for word in words)
    return camel_case


def checkInputValid(input):
    # 检查字符是否有效
    if input == "":
        return False
    if not re.match("^[a-zA-Z_\s]+$", input):
        return False
    if input == "template":
        return False

    # 检查格式是否有效
    if len(input.replace(' ', '').replace('_', '')) == 0:
        return False

    return True


class PrintColor:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'


def getAppName():
    # 读取输入
    while True:
        user_input = input("input new app's name: ")
        if checkInputValid(user_input):
            break
        else:
            print("bad name, try again")

    print("get input: {}\n".format(user_input))

    app_name = "App" + toCamelCase(user_input)
    print("> new app's name: " + PrintColor.OKGREEN + app_name + PrintColor.ENDC)
    return app_name


class AppFilePaths:
    def __init__(self, folder, source_file, header_file):
        self.folder = folder
        self.source_file = source_file
        self.header_file = header_file


def getAppFilePaths(appName):
    file_paths = AppFilePaths("", "", "")

    # 获取文件路径
    file_paths.folder = script_directory + toSnakeCase(appName)

    file_paths.source_file = os.path.join(
        file_paths.folder, toSnakeCase(appName) + ".cpp")

    file_paths.header_file = os.path.join(
        file_paths.folder, toSnakeCase(appName) + ".h")

    print("> new app's file paths:\n - {}\n - {}\n - {}\n".format(
        PrintColor.OKGREEN + file_paths.folder,
        PrintColor.OKGREEN + file_paths.source_file,
        PrintColor.OKGREEN + file_paths.header_file)
        + PrintColor.ENDC)
    return file_paths


def createAppFiles(appName, appFilePaths):
    # 创建文件夹
    os.mkdir(appFilePaths.folder)

    # 创建文件
    source_file = open(appFilePaths.source_file, mode='x')
    header_file = open(appFilePaths.header_file, mode='x')

    # 获取模板内容
    content_source_file = open(
        script_directory + "app_template/app_template.cpp", mode='r').read()
    content_header_file = open(
        script_directory + "app_template/app_template.h", mode='r').read()

    # 替换类名
    content_source_file = content_source_file.replace(
        "AppTemplate", appName)
    content_header_file = content_header_file.replace(
        "AppTemplate", appName)

    # 替换文件名
    content_source_file = content_source_file.replace(
        "app_template", toSnakeCase(appName))
    content_header_file = content_header_file.replace(
        "app_template", toSnakeCase(appName))

    # 替换日期
    content_source_file = content_source_file.replace(
        "<date></date>", datetime.now().strftime("%Y-%m-%d"))
    content_header_file = content_header_file.replace(
        "<date></date>", datetime.now().strftime("%Y-%m-%d"))

    # 写入内容
    source_file.write(content_source_file)
    header_file.write(content_header_file)

    # 关闭文件
    source_file.close()
    header_file.close()


def installApp(appName):
    print("> install app {} into mooncake".format(appName))

    # 读取应用安装回调
    app_install_cb_file = open(script_directory + "app_installer.h", mode='r')
    content_app_install_cb_file = app_install_cb_file.read()
    app_install_cb_file.close()

    # 添加头文件包含
    header_include_tag = "/* Header files locator (Don't remove) */"
    content_app_install_cb_file = content_app_install_cb_file.replace(
        header_include_tag, "#include \"{}/{}.h\"\n{}".format(toSnakeCase(appName), toSnakeCase(appName), header_include_tag))

    # 添加应用安装语句
    app_install_tag = "/* Install app locator (Don't remove) */"
    content_app_install_cb_file = content_app_install_cb_file.replace(
        app_install_tag, "mooncake::GetMooncake().installApp(std::make_unique<{}>());\n    {}".format(appName, app_install_tag))

    # 写入应用安装回调
    app_install_cb_file = open(script_directory + "app_installer.h", mode='w+')
    app_install_cb_file.write(content_app_install_cb_file)
    app_install_cb_file.close()


if __name__ == "__main__": 
    print("app generator")

    name = getAppName()  # 获取应用名称
    file_paths = getAppFilePaths(name)  # 获取文件路径
    createAppFiles(name, file_paths)  # 创建应用文件
    installApp(name)  # 安装应用

    print("\ndone")  # 完成
