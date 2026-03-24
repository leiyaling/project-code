# coding: utf-8

import click
import subprocess
import os
import platform

def run_cmd(cmd, cwd):
    """
    run cmd in shell"""
    print("run cmd:", " ".join(cmd))
    process = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True,
        cwd=cwd,
        shell=True,
    )

    while True:
        line = process.stdout.readline()
        if not line:
            break
        print(line.strip())

    process.wait()

    if process.returncode != 0:
        raise Exception(f"cmd {cmd} failed")

def shell_run_cmd(cmd, cwd):

    os.system()

def normalize_src_path(src_path):
    """
    经过尝试 window 下，src_path 中使用 ‘/’ lcov 生成的的输出文件内容为空，需要使用 '\'
    """
    print(f"os.sep: {os.sep}")
    if platform.system().lower() == "windows":
        return src_path.replace("/", "\\")

    return src_path.replace("\\", os.sep)

def gen_cmd_lcov(src_path):
    """
    generate lcov report"""
    # get source path
    cmd_lcov = ["lcov", "--directory", ".", "--capture", "--output-file", "coverage.info"]
    src_path = normalize_src_path(src_path+os.sep+"*")
    cmd_lcov.extend(["--include", f"'{src_path}'"])

    return cmd_lcov

def gen_cmd_genhtml(src_path):
    """
    generate html report"""
    cmd_genhtml = ["genhtml", "--dark-mode", "-s", "coverage.info", "--output-directory", "html"]
    cmd_genhtml.extend(["--prefix", f"'{normalize_src_path(src_path)}'"])
    return cmd_genhtml


@click.command()
@click.option("--project-dir", default=".", help="project dir")
def lcov(project_dir: str):
    """
    generate lcov report"""

    project_dir = os.path.abspath(project_dir)
    src_path = os.path.join(project_dir, "src")
    build_dir = os.path.join(project_dir, "build")
    build_bin_path = os.path.join(build_dir, "bin")
    test_app = [os.path.join(build_bin_path, "test-board")]
    cmd_lcov = gen_cmd_lcov(src_path)
    cmd_genhtml = gen_cmd_genhtml(src_path)
    print("cmd lcov: ", " ".join(cmd_lcov))
    print("cmd genhtml: ", " ".join(cmd_genhtml))
    run_cmd(test_app, cwd=build_bin_path)
    run_cmd(cmd_lcov, cwd=build_dir)
    run_cmd(cmd_genhtml, cwd=build_dir)

if __name__ == "__main__":
    lcov()