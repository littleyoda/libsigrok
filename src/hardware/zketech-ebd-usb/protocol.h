/*
 * This file is part of the libsigrok project.
 *
 * Copyright (C) 2018 Sven Bursch-Osewold <sb_git@bursch.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBSIGROK_HARDWARE_ZKETECH_EBD_USB_PROTOCOL_H
#define LIBSIGROK_HARDWARE_ZKETECH_EBD_USB_PROTOCOL_H

#include <stdint.h>
#include <glib.h>
#include <libsigrok/libsigrok.h>
#include "libsigrok-internal.h"

#define LOG_PREFIX "zketech-ebd-usb"

#define MSG_LEN 19
#define MSG_CHECKSUM_POS 17
#define MSG_FRAME_BEGIN 0xfa
#define MSG_FRAME_BEGIN_POS 0
#define MSG_FRAME_END 0xf8
#define MSG_FRAME_END_POS 18

struct dev_context {
	struct sr_sw_limits limits;
	GMutex rw_mutex;
	float current_limit;
	float under_voltage_threshold;
	gboolean under_voltage_enabled;
	gboolean running;
	gboolean load_activated;
};

/* Communication via serial. */
SR_PRIV int ebd_read_chars(struct sr_serial_dev_inst *serial, int count, uint8_t *buf);

/* Commands. */
SR_PRIV int ebd_init(struct sr_serial_dev_inst *serial, struct dev_context *devc);
SR_PRIV int ebd_loadstart(struct sr_serial_dev_inst *serial, struct dev_context *devc);
SR_PRIV int ebd_receive_data(int fd, int revents, void *cb_data);
SR_PRIV int ebd_stop(struct sr_serial_dev_inst *serial, struct dev_context *devc);
SR_PRIV int ebd_loadstop(struct sr_serial_dev_inst *serial, struct dev_context *devc);

/* Configuration. */
SR_PRIV int ebd_get_current_limit(const struct sr_dev_inst *sdi, float *current);
SR_PRIV int ebd_set_current_limit(const struct sr_dev_inst *sdi, float current);
SR_PRIV int ebd_set_under_voltage_threshold(const struct sr_dev_inst *sdi, float current);
SR_PRIV int ebd_get_under_voltage_threshold(const struct sr_dev_inst *sdi, float *current);
SR_PRIV int ebd_set_under_voltage_enabled(const struct sr_dev_inst *sdi, gboolean enabled);
SR_PRIV int ebd_get_under_voltage_enabled(const struct sr_dev_inst *sdi, gboolean *enabled);
SR_PRIV gboolean ebd_current_is0(struct dev_context *devc);

#endif
