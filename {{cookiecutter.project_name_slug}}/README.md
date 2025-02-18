# {{cookiecutter.project_name}}

{{cookiecutter.project_description}}

## Getting Started

1. Install Zephyr according to <https://docs.zephyrproject.org/latest/develop/getting_started/index.html> (for Windows, WSL2 with Ubuntu is recommended)
2. Clone this repo & create a Zephyr workspace using `west init -m {{cookiecutter.repo_url}} --mr main {{cookiecutter.project_name_slug}}-workspace`  
   (if you already have cloned this repo into an empty workspace using *git*, run `west init -l {{cookiecutter.project_name_slug}}-workspace/{{cookiecutter.project_name_slug}}` instead)
3. In `{{cookiecutter.project_name_slug}}-workspace`, run `west build {{cookiecutter.project_name_slug}}/applications/main -p always` to build the project

> *This project was bootstrapped with [cookiecutter-zephyr-downstream](https://github.com/tiacsys/cookiecutter-zephyr-downstream).*
