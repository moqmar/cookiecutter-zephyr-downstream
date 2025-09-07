# {{cookiecutter.project_name}}

{{cookiecutter.project_description}}

## Getting Started

1. Install Zephyr [dependencies](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-dependencies) and [west](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-dependencies) (steps 1-3)
2. Activate the Zephyr environment:
   ```bash
   source ~/zephyrproject/.venv/bin/activate
   ```
3. Initialize your workspace:
   - If you want to clone & initialize this repo in a new empty workspace directory:
     ```bash
     west init -m {{cookiecutter.repo_url}} --mr main .
     ```
   - If you have just created or already cloned this repo into an empty workspace directory:
     ```bash
     west init -l ./{{cookiecutter.project_name_slug}}
     ```
4. Update all dependencies:
   ```bash
   west update
   west zephyr-export
   west packages pip --install
   west sdk install
   west blobs fetch
   ```
5. Build your application:
   ```bash
   west build {% if cookiecutter.main_application_template != "" %}{{cookiecutter.project_name_slug}}/applications/main{% else %}zephyr/samples/basic/blinky{% endif %} -p always -b nucleo_f302r8
   ```
5. Run Twister tests:
    ```bash
    west twister -v -T . --integration
    ```
{% if cookiecutter.setup_documentation != "Skip" %}
6. Build your documentation:
   ```bash
   cd {{cookiecutter.project_name_slug}}/docs
   make html
   python3 -m http.server --directory _build_sphinx/html
   ```
{% endif %}

> *This project was bootstrapped with [cookiecutter-zephyr-downstream](https://github.com/tiacsys/cookiecutter-zephyr-downstream).*
