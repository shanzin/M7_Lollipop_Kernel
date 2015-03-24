/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef MSM_CAMERA_I2C_H
#define MSM_CAMERA_I2C_H

#include <linux/i2c.h>
#include <linux/delay.h>
#include <mach/camera.h>

#define CONFIG_MSM_CAMERA_I2C_DBG 0

#if CONFIG_MSM_CAMERA_I2C_DBG
#define S_I2C_DBG(fmt, args...) printk(fmt, ##args)
#else
#define S_I2C_DBG(fmt, args...) CDBG(fmt, ##args)
#endif

enum msm_camera_i2c_reg_addr_type {
	MSM_CAMERA_I2C_BYTE_ADDR = 1,
	MSM_CAMERA_I2C_WORD_ADDR,
};

struct msm_camera_i2c_client {
	struct i2c_client *client;
	enum msm_camera_i2c_reg_addr_type addr_type;
};

enum msm_camera_i2c_data_type {
	MSM_CAMERA_I2C_BYTE_DATA = 1,
	MSM_CAMERA_I2C_WORD_DATA,
	MSM_CAMERA_I2C_SET_BYTE_MASK,
	MSM_CAMERA_I2C_UNSET_BYTE_MASK,
	MSM_CAMERA_I2C_SET_WORD_MASK,
	MSM_CAMERA_I2C_UNSET_WORD_MASK,
	MSM_CAMERA_I2C_SET_BYTE_WRITE_MASK_DATA,
};

enum msm_camera_i2c_cmd_type {
	MSM_CAMERA_I2C_CMD_WRITE,
	MSM_CAMERA_I2C_CMD_POLL,
	MSM_CAMERA_I2C_CMD_POLL_EQUAL,
	MSM_CAMERA_I2C_CMD_POLL_NOT_EQUAL,
	MSM_CAMERA_I2C_CMD_POLL_LESS,
	MSM_CAMERA_I2C_CMD_WRITE_BURST,
};

struct msm_camera_i2c_reg_conf {
	uint16_t reg_addr;
	uint16_t reg_data;
	enum msm_camera_i2c_data_type dt;
	enum msm_camera_i2c_cmd_type cmd_type;
	int16_t mask;
    uint8_t* burst_data;
    uint16_t burst_count;	
};

struct msm_camera_i2c_conf_array {
	struct msm_camera_i2c_reg_conf *conf;
	uint16_t size;
	uint16_t delay;
	enum msm_camera_i2c_data_type data_type;
};

struct msm_camera_i2c_enum_conf_array {
	struct msm_camera_i2c_conf_array *conf;
	int *conf_enum;
	uint16_t num_enum;
	uint16_t num_index;
	uint16_t num_conf;
	uint16_t delay;
	enum msm_camera_i2c_data_type data_type;
};

int32_t msm_camera_i2c_rxdata(struct msm_camera_i2c_client *client,
	unsigned char *rxdata, int data_length);

int32_t msm_camera_i2c_txdata(struct msm_camera_i2c_client *client,
	unsigned char *txdata, int length);
// HTC_START
int32_t msm_camera_i2c_read_b(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t *data);
// HTC_END
int32_t msm_camera_i2c_read(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t *data,
	enum msm_camera_i2c_data_type data_type);

int32_t msm_camera_i2c_read_seq(struct msm_camera_i2c_client *client,
	uint16_t addr, uint8_t *data, uint16_t num_byte);
// HTC_START
int32_t msm_camera_i2c_write_b(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t data );
// HTC_END
int32_t msm_camera_i2c_write(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t data,
	enum msm_camera_i2c_data_type data_type);

int32_t msm_camera_i2c_write_seq(struct msm_camera_i2c_client *client,
	uint16_t addr, uint8_t *data, uint16_t num_byte);

int32_t msm_camera_i2c_set_mask(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t mask,
	enum msm_camera_i2c_data_type data_type, uint16_t flag);

int32_t msm_camera_i2c_compare(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t data,
	enum msm_camera_i2c_data_type data_type);

int32_t msm_camera_i2c_poll(struct msm_camera_i2c_client *client,
	uint16_t addr, uint16_t data,
	enum msm_camera_i2c_data_type data_type);
	
int32_t msm_camera_i2c_poll2(struct msm_camera_i2c_client *client,
	struct msm_camera_i2c_reg_conf *reg_conf_tbl);

int32_t msm_camera_i2c_write_tbl(struct msm_camera_i2c_client *client,
	struct msm_camera_i2c_reg_conf *reg_conf_tbl, uint16_t size,
	enum msm_camera_i2c_data_type data_type);

int32_t msm_sensor_write_conf_array(struct msm_camera_i2c_client *client,
	struct msm_camera_i2c_conf_array *array, uint16_t index);

int32_t msm_sensor_write_enum_conf_array(struct msm_camera_i2c_client *client,
	struct msm_camera_i2c_enum_conf_array *conf, uint16_t enum_val);

int32_t msm_sensor_write_all_conf_array(struct msm_camera_i2c_client *client,
	struct msm_camera_i2c_conf_array *array, uint16_t size);
//HTC_START  20121005 Horng add for RUMBAS autorator special case
int32_t msm_camera_i2c_read_seq_rumbas(struct msm_camera_i2c_client *client,
	uint16_t addr, uint8_t *data, uint16_t num_byte);
//HTC_END
// HTC_START 20121112 mike.cy add for custom Tx
int32_t msm_camera_i2c_txdata_rumbas(struct msm_camera_i2c_client *client,
	unsigned char *txdata, int length);
// HTC_END
#endif