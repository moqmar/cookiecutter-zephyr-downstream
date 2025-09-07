#!/bin/bash -x
set -eu

# Try to build various cookiecutter configurations to ensure they work
# properly. This is not an exhaustive test of all configurations, but it
# should catch any major issues.

cd "$(dirname "$0")"
find .test -maxdepth 1 -not -path .test/zephyr -not -path .test/modules -exec rm -rf '{}' '+' || true
mkdir -p .test

cat <<EOF > .test/defaults.yaml
default_context:
  project_name: Test Defaults
  project_name_slug: test-defaults
EOF

cat <<EOF > .test/driver.yaml
default_context:
  project_name: Test Driver
  project_name_slug: test-driver
  create_own_driver: true
  setup_ci_pipeline: "Skip"
  setup_documentation: "Skip"
EOF

cat <<EOF > .test/board.yaml
default_context:
  project_name: Test Board
  project_name_slug: test-board
  create_own_board: true
  setup_ci_pipeline: "Skip"
  setup_documentation: "Skip"
EOF

cat <<EOF > .test/library.yaml
default_context:
  project_name: Test Library
  project_name_slug: test-library
  create_own_library: true
  setup_ci_pipeline: "Skip"
  setup_documentation: "Skip"
EOF

cat <<EOF > .test/west-command.yaml
default_context:
  project_name: Test West Command
  project_name_slug: test-west-command
  create_own_west_command: true
  setup_ci_pipeline: "Skip"
  setup_documentation: "Skip"
EOF

cat <<EOF > .test/everything.yaml
default_context:
  project_name: Test Everything
  project_name_slug: test-everything
  create_own_driver: true
  create_own_board: true
  create_own_library: true
  create_own_west_command: true
  create_own_runner: true
EOF

cat <<EOF > .test/skeleton.yaml
default_context:
  project_name: Test Skeleton
  project_name_slug: test-skeleton
  create_own_driver: true
  create_own_board: true
  create_own_library: true
  create_own_west_command: true
  main_application_template: "Skeleton for a quick fresh start"
EOF

cat <<EOF > .test/no-application.yaml
default_context:
  project_name: Test No Application
  project_name_slug: test-no-application
  create_own_driver: true
  create_own_board: true
  create_own_library: true
  create_own_west_command: true
  main_application_template: "Skip"
EOF

for current_test in .test/*.yaml; do
  cookiecutter . -o .test --config-file $current_test --no-input
  (
    cd .test
    project_name_slug=test-$(sed -e "s/^\.test\///" -e "s/\.yaml$//" <<< "$current_test")
    rm -rf .west
    west init -l "$project_name_slug"
    west update
    west blobs fetch

    # Try building the main application & running the library tests with twister
    west twister -v -T "$project_name_slug" --integration

    # Try native_sim
    if [ "$project_name_slug" = "test-skeleton" ]; then
      west build -b native_sim --build-dir "$project_name_slug/build-native_sim" --pristine always "$project_name_slug/applications/main"
      "./$project_name_slug/build-native_sim/zephyr/zephyr.exe" > output.txt 2>&1 &
      nativesim_pid=$!
      tail -n+0 -f output.txt | timeout 5 grep -Fxm1 "You've reached main()"
      kill -KILL "$nativesim_pid" || true
    fi

    # Try documentation build
    if [ "$project_name_slug" = "test-defaults" ] || [ "$project_name_slug" = "test-everything" ] || [ "$project_name_slug" = "test-no-application" ]; then
      (cd "$project_name_slug/doc" && make html)
    fi

    # Try custom west command
    if [ "$project_name_slug" = "test-west-command" ] || [  "$project_name_slug" = "test-everything" ]; then
      west example-west-command required | grep -Fx "required is required"
    fi
  )
done
