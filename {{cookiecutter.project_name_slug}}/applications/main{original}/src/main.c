/*
 * Copyright (c) {% now 'utc', '%Y' %} {{cookiecutter.project_org}}
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>{% if cookiecutter.create_own_driver %}
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <app/drivers/blink.h>{% else %}
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>{% endif %}

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);
{% if cookiecutter.create_own_driver %}
#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U
{% endif %}
int main(void)
{
	int ret;
{% if cookiecutter.create_own_driver %}	unsigned int period_ms = BLINK_PERIOD_MS_MAX;
	const struct device *sensor, *blink;
	struct sensor_value last_val = { 0 }, val;
{% else %}
	const struct gpio_dt_spec led_gpios = GPIO_DT_SPEC_GET(DT_NODELABEL(blink_led), gpios);
{% endif %}
	printk("{{ cookiecutter.project_name }} %s\n", APP_VERSION_STRING);
{% if cookiecutter.create_own_driver %}
	sensor = DEVICE_DT_GET(DT_NODELABEL(example_sensor));
	if (!device_is_ready(sensor)) {
		LOG_ERR("Sensor not ready");
		return 0;
	}

	blink = DEVICE_DT_GET(DT_NODELABEL(blink_led));
	if (!device_is_ready(blink)) {
		LOG_ERR("Blink LED not ready");
		return 0;
	}

	ret = blink_off(blink);
	if (ret < 0) {
		LOG_ERR("Could not turn off LED (%d)", ret);
		return 0;
	}

	printk("Use the sensor to change LED blinking period\n");

	while (1) {
		ret = sensor_sample_fetch(sensor);
		if (ret < 0) {
			LOG_ERR("Could not fetch sample (%d)", ret);
			return 0;
		}

		ret = sensor_channel_get(sensor, SENSOR_CHAN_PROX, &val);
		if (ret < 0) {
			LOG_ERR("Could not get sample (%d)", ret);
			return 0;
		}

		if ((last_val.val1 == 0) && (val.val1 == 1)) {
			if (period_ms == 0U) {
				period_ms = BLINK_PERIOD_MS_MAX;
			} else {
				period_ms -= BLINK_PERIOD_MS_STEP;
			}

			printk("Proximity detected, setting LED period to %u ms\n",
				   period_ms);
			blink_set_period_ms(blink, period_ms);
		}

		last_val = val;

		k_sleep(K_MSEC(100));
	}
{% else %}
	if (!gpio_is_ready_dt(&led_gpios)) {
		LOG_ERR("LED not ready");
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_gpios, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		LOG_ERR("LED not configured (%d)", ret);
		return 0;
	}

	while (true) {
		ret = gpio_pin_toggle_dt(&led_gpios);
		if (ret < 0) {
			LOG_ERR("LED not toggled (%d)", ret);
			return 0;
		}
		k_msleep(250);
	}
{% endif %}
	return 0;
}

