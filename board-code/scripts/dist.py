# coding: utf-8


import os
import platform
import shutil
import sys


def goon():
    answer = input("continue? [Y]/n: ")
    if answer.startswith("n"):
        exit(0)


def lib_name_by_system(name):
    if platform.system().lower() == "windows":
        return f"librededa_{name}.dll"
    else:
        return f"librededa_{name}.so"


def set_env_var(name, value):
    """
    永久设置环境变量"""
    if platform.system().lower() == "windows":
        cmd = f"setx {name}={value}"
        os.system(cmd)
    else:
        cmd = f"echo 'export {name}={value}' >> ~/.bashrc"
        os.system(cmd)


ENV_REDEDA_LIB_PATH = "REDEDA_LIB_PATH"


def append_path_if_not_exists_win(*paths):
    """
    添加路径到环境变量中"""

    newpath = ""
    lib_path = os.getenv(ENV_REDEDA_LIB_PATH)
    if lib_path is not None:
        newpath = lib_path
    for path in paths:
        if path in newpath:
            continue
        newpath += f"{path};"

    cmd = f'setx {ENV_REDEDA_LIB_PATH} "{newpath}"'
    print(f"cmd: {cmd}")
    os.system(cmd)
    print(f"为了避免 PATH 长度超过1024，需要手动将 %{ENV_REDEDA_LIB_PATH}% 添加到 PATH 中!!!")
    # if not ENV_REDEDA_LIB_PATH in os.environ["PATH"]:
    #    cmd = f'setx PATH "%PATH%;%{ENV_REDEDA_LIB_PATH}%"'
    #    print(f"cmd: {cmd}")
    #    os.system(cmd)


def append_path_if_not_exists_linux(*paths):
    newpath = ""
    lib_path = os.getenv(ENV_REDEDA_LIB_PATH)
    if lib_path is not None:
        newpath = lib_path
    for path in paths:
        if path in newpath:
            continue
        newpath += f"{path}:"
    cmd = f"echo 'export {ENV_REDEDA_LIB_PATH}=\"{newpath}\"' >> ~/.bashrc"
    print(f"cmd: {cmd}")
    os.system(cmd)


def append_path_if_not_exists(*paths):
    """
    添加路径到环境变量中
    由于环境变量不是立即生效，所以只能一次调用 append_path_if_not_exists，把所有要添加的路径一次性添加进去
    用户环境变量修改后，需要重启终端才能生效（注销最保险）
    """

    if platform.system().lower() == "windows":
        append_path_if_not_exists_win(*paths)
    else:
        append_path_if_not_exists_linux(*paths)


project_dir = os.path.abspath(".")
print("project_dir:", project_dir)
lib_name = lib_name_by_system("board")
REDEDA_DEV_DIST = "REDEDA_DEV_DIST"

env_dev_dist = os.path.abspath(os.getenv(REDEDA_DEV_DIST))
if not os.path.exists(env_dev_dist):
    env_dev_dist = input("Enter REDEDA_DEV_DIST: ")
    if not os.path.exists(env_dev_dist):
        print("ENV: REDEDA_DEV_DIST not found, exit!")
        exit(1)
    set_env_var(REDEDA_DEV_DIST, env_dev_dist)

source_include_model_dir = os.path.join(project_dir, "inc", "board")

dist_dir = os.path.join(env_dev_dist, "rededa")
dist_include_dir = os.path.join(dist_dir, "include")  # include 目录
dist_include_model_dir = os.path.join(dist_include_dir, "board")

dist_3rd_dir = os.path.join(dist_dir, "3rd")
dist_3rd_dir_include_dir = os.path.join(dist_3rd_dir, "include")
print("dist_dir:", dist_dir)
print("    include_dir:", dist_include_dir)

goon()


# 删除 dist_include_model_dir
if os.path.exists(dist_include_model_dir):
    print(f"remove {dist_include_model_dir}")
    shutil.rmtree(dist_include_model_dir)

# 拷贝 source_include_model_dir 到 dist_include_model_dir
print(f"copy {source_include_model_dir} to {dist_include_model_dir}")
shutil.copytree(source_include_model_dir, dist_include_model_dir)

