/*
 * Copyright (c) {% now 'utc', '%Y' %} {{cookiecutter.project_org}}
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

int main(void)
{
	printk("{{ cookiecutter.project_name }} %s\n", APP_VERSION_STRING);

	printk("You've reached main()\n");
	// TODO

	return 0;
}

