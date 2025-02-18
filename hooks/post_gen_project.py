#!/usr/bin/env python
import pathlib
import shutil


if __name__ == '__main__':

    if "{{ cookiecutter.create_application }}" == "No":
        shutil.rmtree("applications")
        pathlib.Path("README.md").unlink()

    if "{{ cookiecutter.create_own_driver }}" == "False":
        shutil.rmtree("include/drivers")
        shutil.rmtree("drivers")
        shutil.rmtree("dts")

    if "{{ cookiecutter.create_own_board }}" == "False":
        shutil.rmtree("boards")

    if "{{ cookiecutter.create_own_library }}" == "False":
        shutil.rmtree("include/lib")
        shutil.rmtree("lib")
        shutil.rmtree("tests")

    if "{{ cookiecutter.create_own_west_command }}" == "False":
        shutil.rmtree("scripts")

    if "{{ cookiecutter.setup_documentation }}" == "With Doxygen":
        pathlib.Path("doc{doxygen}").rename("doc")
    else:
        shutil.rmtree("doc{doxygen}")

    if "{{ cookiecutter.setup_ci_pipeline }}" != "GitHub Actions":
        shutil.rmtree(".github")
