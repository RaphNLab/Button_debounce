#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_

#include "global.h"


/*User defines*/
#define SERIAL_BUF_SIZE			1024
#define SERIAL_MAX_SATA_SIZE	SERIAL_BUF_SIZE
#define SERIAL_DATA_REG			(0x40004400U + 0x04U)


/*User  Typedef and enum */

typedef struct
{
	uint32_t uart_port;
	uint8_t *rx_buffer;
	uint8_t *tx_buffer;
	bool_t serial_receive_done;
	bool_t serial_send_done;
	uint16_t serial_data_size;
	uint16_t serial_data_crc;
}serial_dev_t;


/*User global variables*/


/*User global functions*/
int _write(int file, char *ptr, int len);
void serial_debug_config(void);
void serial_xfer_config(void);
void serial_put_s(char *data);

status_t serial_send_pkt(serial_dev_t serial_dev, uint16_t size);
status_t serial_rcv_pkt(serial_dev_t serial_dev, uint16_t size);

#endif
