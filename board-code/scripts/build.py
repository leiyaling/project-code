# coding: utf-8
"""
build.py
~~~~~~~~
build rededa board
"""

import subprocess
import os
import shutil
import click

cmake_cmd = ["cmake", "..", "-G", "Unix Makefiles"]
make_cmd = ["make", "-j9"]

def goon():
    answer = input("continue? [Y]/n: ")
    if answer.startswith("n"):
        exit(0)

def run_cmd(cmd, cwd):
    """
    run cmd in shell"""

    process = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True,
        cwd=cwd,
    )

    while True:
        line = process.stdout.readline()
        if not line:
            break
        print(line.strip())

    process.wait()

    if process.returncode != 0:
        raise Exception(f"cmd {cmd} failed")

@click.command()
@click.option("--debug", is_flag=True, default=False, help="build debug mode")
@click.option("--code_coverage", "-C", is_flag=True, default=False, help="build code coverage mode")
@click.option("--project_dir", default=".", help="project dir")
def build(project_dir: str, debug: bool = False, code_coverage: bool = False):
    project_dir = os.path.abspath(".")
    print("project_dir:", project_dir)



    build_dir = os.path.join(project_dir, "build")
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)

    # 创建build目录
    os.mkdir(build_dir)

    if debug:
        cmake_cmd.append("-DCMAKE_BUILD_TYPE=Debug")

    if code_coverage:
        cmake_cmd.append("-DCODE_COVERAGE=ON")
    print("cmd: ", " ".join(cmake_cmd))
    goon()
    run_cmd(cmake_cmd, build_dir)
    run_cmd(make_cmd, build_dir)

if __name__ == "__main__":
    build()