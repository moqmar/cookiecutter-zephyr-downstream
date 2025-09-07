#!/usr/bin/env python
import pathlib
import shutil


if __name__ == '__main__':

    if "{{ cookiecutter.main_application_template }}" == "Skip":
        shutil.rmtree("applications")
    else:
        if "{{ cookiecutter.main_application_template }}" == "Skeleton for a quick fresh start":
            pathlib.Path("applications/main{skeleton}").rename("applications/main")
        elif "{{ cookiecutter.main_application_template }}" == "Original from zephyrproject-rtos/example-application":
            pathlib.Path("applications/main{original}").rename("applications/main")

        for p in pathlib.Path(".").glob("applications/*{*}"):
            shutil.rmtree(p)

    if "{{ cookiecutter.create_own_driver }}" == "False":
        shutil.rmtree("include/app/drivers")
        shutil.rmtree("drivers")
        shutil.rmtree("dts")

    if "{{ cookiecutter.create_own_board }}" == "False":
        shutil.rmtree("boards")

    if "{{ cookiecutter.create_own_library }}" == "False":
        shutil.rmtree("include/app/lib")
        shutil.rmtree("lib")
        shutil.rmtree("tests")

    if "{{ cookiecutter.create_own_west_command }}" == "False" and "{{ cookiecutter.create_own_runner }}" == "False":
        shutil.rmtree("scripts")
    elif "{{ cookiecutter.create_own_west_command }}" == "False":
        pathlib.Path("scripts/example_west_command.py").unlink()
        pathlib.Path("scripts/west-commands.yml").unlink()
    elif "{{ cookiecutter.create_own_runner }}" == "False":
        pathlib.Path("scripts/example_runner.py").unlink()

    if "{{ cookiecutter.setup_documentation }}" == "With Sphinx/Doxygen":
        pathlib.Path("doc{doxygen}").rename("doc")
    else:
        shutil.rmtree("doc{doxygen}")

    if "{{ cookiecutter.setup_ci_pipeline }}" == "GitHub Actions":
        pass
    else:
        shutil.rmtree(".github")
