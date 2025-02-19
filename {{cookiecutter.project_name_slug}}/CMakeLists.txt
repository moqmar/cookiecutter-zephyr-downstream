# Copyright (c) {% now 'utc', '%Y' %} {{cookiecutter.project_org}}
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0
#
# This CMake file is picked by the Zephyr build system because it is defined
# as the module CMake entry point (see zephyr/module.yml).


# This is needed so that custom driver classes using system calls are taken into
# account
{% if not cookiecutter.create_own_driver and not cookiecutter.create_own_library %}#{% endif %}zephyr_syscall_include_directories(include)
{% if not cookiecutter.create_own_driver and not cookiecutter.create_own_library %}#{% endif %}zephyr_include_directories(include)

{% if not cookiecutter.create_own_driver %}#{% endif %}add_subdirectory(drivers)
{% if not cookiecutter.create_own_library %}#{% endif %}add_subdirectory(lib)
