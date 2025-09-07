#!/bin/bash -x
set -eu

# Compare the generated example-application with the upstream one to ensure
# they are more or less identical (ignoring README.md and copyright lines).

cd "$(dirname "$0")"
rm -rf .epdiff
mkdir -p .epdiff

cat <<EOF > .epdiff/example.yaml
default_context:
  project_name: Zephyr Example Application
  project_name_slug: example-application
  project_org: The Zephyr Community
  project_org_slug: zephyrproject-rtos
  create_own_driver: true
  create_own_board: true
  create_own_library: true
  create_own_west_command: true
  create_own_runner: true
EOF

cookiecutter . -o .epdiff --config-file .epdiff/example.yaml --no-input
git clone https://github.com/zephyrproject-rtos/example-application .epdiff/upstream-example-application

diff -bur -x README.md -x .gitkeep -x .git -I '^ *. *[Cc]opyright' -x app -x applications .epdiff/upstream-example-application .epdiff/example-application
diff -bur -x README.md -x .gitkeep -x .git -I '^ *. *[Cc]opyright' .epdiff/upstream-example-application/app .epdiff/example-application/applications/main
