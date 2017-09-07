/*  drivers/misc/sec_jack.c
 *
 *  Copyright (C) 2012 Samsung Electronics Co.Ltd
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */


#include <asm/setup.h>
#include <system_info.h>

#include <linux/export.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>

static int __init msm_serialnr_setup(char *p)
{
#ifdef CONFIG_EXTEND_SERIAL_NUM_16
	unsigned long long serial = 0;
	serial = simple_strtoull(p, NULL, 16);
	system_serial_high = serial>>32;
	system_serial_low = serial & 0xFFFFFFFF;
#else
	system_serial_low = simple_strtoul(p, NULL, 16);
	system_serial_high = (system_serial_low&0xFFFF0000)>>16;
	system_serial_low = system_serial_low&0x0000FFFF;
#endif
	return 0;
}
early_param("androidboot.serialno", msm_serialnr_setup);

static int __init msm_hw_rev_setup(char *p)
{
	system_rev = memparse(p, NULL);
	return 0;
}
early_param("androidboot.revision", msm_hw_rev_setup);
