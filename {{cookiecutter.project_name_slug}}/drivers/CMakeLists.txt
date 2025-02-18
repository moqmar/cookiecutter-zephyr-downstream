# Copyright (c) {% now 'utc', '%Y' %} {{cookiecutter.project_org}}
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

# Out-of-tree drivers for custom classes
add_subdirectory_ifdef(CONFIG_BLINK blink)

# Out-of-tree drivers for existing driver classes
# add_subdirectory_ifdef(CONFIG_SENSOR sensor)
# See https://github.com/zephyrproject-rtos/example-application for a full example
