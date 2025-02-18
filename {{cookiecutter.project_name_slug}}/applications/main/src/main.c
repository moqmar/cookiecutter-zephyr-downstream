/*
 * Copyright (c) {% now 'utc', '%Y' %} {{cookiecutter.project_org}}
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/blink.h>

#include "app_version.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

int main(void)
{
	int ret;
	const struct device *sensor;

	printk("Zephyr Example Application %s\n", APP_VERSION_STR);

	led = DEVICE_DT_GET(DT_NODELABEL(blink_led));
	if (!device_is_ready(sensor)) {
		LOG_ERR("LED not ready");
		return 0;
	}

	blink_set_period_ms(&led, 300);

	return 0;
}

