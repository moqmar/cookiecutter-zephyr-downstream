# Cookiecutter Zephyr Downstream Project

A cookiecutter to create a standardized Zephyr downstream project ready for production development.

## Features

* Loosely based on [zephyrproject-rtos/example-application](https://github.com/zephyrproject-rtos/example-application)
* Canonical project structure with needed boilerplate in place
  * west integration
  * CMake integration
  * Kconfig integration
* Scaffolds for downstream
  * Applications
  * Drivers
  * Libs
  * Tests

## Prerequisites 

You should have Python 3.8+ and [Cookiecutter](http://cookiecutter.readthedocs.org/en/latest/installation.html) installed. 

## Scaffold a new Project

```bash
cookiecutter https://github.com/tiacsys/cookiecutter-zephyr-downstream.git -o my-project-workspace
cd my-project-workspace
west init -l ./{{cookiecutter.project_name_slug}}
```

You may now `git init` your project and/or follow the `README.md` inside your newly created project. 

## Prompts

When you create the project, you are prompted to enter these values.

### Templated Values

| Key                       | Description                                                     | Default Value                                                      |
|---------------------------|-----------------------------------------------------------------|--------------------------------------------------------------------|
| project_name              | Name of the project as it will show up on boot and in README    | Zephyr Downstream                                                  |
| project_name_slug         | Computer-friendly short name, ideally the name of the Git repo  | *Slugified `{{project_name}}`*                                     |
| project_org               | Organization or Author name                                     | Acme Inc.                                                          |
| project_org_slug          | Computer-friendly short org name deally the org of the Git repo | *Slugified `{{project_org}}`*                                      |
| project_description       | Short description of the project                                | An example downstream project or application based on Zephyr RTOS. |
| repo_url                  | URL of the Git repository                                       | `https://github.com/{{project_org_slug}}/{{project_name_slug}}`    |
| main_application_template | What kind of sample application to create                       | Original from zephyrproject-rtos/example-application               |
| create_own_driver         | Whether to create a sample driver                               | false                                                              |
| create_own_board          | Whether to create a sample board                                | false                                                              |
| create_own_library        | Whether to create a sample library                              | false                                                              |
| create_own_west_command   | Whether to create a sample west command                         | false                                                              |
| create_own_runner         | Whether to create a sample runner                               | false                                                              |
| setup_ci_pipeline         | What kind of CI pipeline to create                              | GitHub Actions                                                     |
| setup_documentation       | What kind of documentation to create                            | With Sphinx/Doxygen                                                |
