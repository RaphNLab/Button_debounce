#include "uart_drv.h"

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>


/**
 * Data type, Constant and macro definitions
 *
*/

/**
 * Static data declaration
 *
*/
serial_dev_t serial_debug_dev;
serial_dev_t serial_com_dev;

uint8_t serial_rx_buffer[SERIAL_BUF_SIZE];
uint8_t serial_tx_buffer[] = "Keep Working on your dreams\r\n";


/**
 * Private function prototypes
 *
*/

/**
 * Public functions
 *
*/
status_t serial_rcv_pkt(serial_dev_t serial_dev, uint16_t size)
{
	status_t err = GLOBAL_ERROR;

	if(size > SERIAL_MAX_SATA_SIZE)
	{
		// Report size too big
	}
	else
	{
		if(serial_dev.serial_receive_done)
		{
			err = GLOBAL_OK;
		}
	}
	return err;
}


status_t serial_send_pkt(serial_dev_t serial_dev, uint16_t size)
{
	status_t err = GLOBAL_ERROR;
	if(size > SERIAL_MAX_SATA_SIZE)
	{
		// Report size too big
	}
	else
	{
		if(serial_dev.serial_send_done)
		{
			err = GLOBAL_OK;
		}
	}

	return err;
}


void serial_xfer_config(void)
{
	serial_com_dev.uart_port = USART1;
	serial_com_dev.rx_buffer = serial_rx_buffer;
	serial_com_dev.tx_buffer = serial_tx_buffer;
	serial_com_dev.serial_receive_done = FALSE;
	serial_com_dev.serial_send_done = FALSE;

	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_GPIOA);
	nvic_enable_irq(NVIC_USART1_IRQ);

	usart_set_parity(serial_com_dev.uart_port , USART_PARITY_NONE);
	usart_set_baudrate(serial_com_dev.uart_port , 115200);
	usart_set_stopbits(serial_com_dev.uart_port , USART_STOPBITS_1);
	usart_set_databits(serial_com_dev.uart_port , 8);
	usart_set_flow_control(serial_com_dev.uart_port , USART_FLOWCONTROL_NONE);
	usart_enable_rx_interrupt(serial_com_dev.uart_port );
	usart_enable_tx_interrupt(serial_com_dev.uart_port );
	usart_set_mode(serial_com_dev.uart_port , USART_MODE_TX_RX);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF , GPIO_PUPD_NONE, (GPIO9 | GPIO10));
	gpio_set_af(GPIOA, GPIO_AF7, (GPIO9 | GPIO10));

	usart_enable(serial_com_dev.uart_port );
}

#ifdef STM32F4
void serial_debug_config(void)
{
	uint8_t text_len = strlen((char*)serial_tx_buffer);
	serial_debug_dev.uart_port = USART2;

	nvic_enable_irq(NVIC_DMA1_STREAM6_IRQ);
	rcc_periph_clock_enable(RCC_DMA1);

	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_GPIOA);

	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_baudrate(USART2, 9600);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_databits(USART2, 8);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	usart_set_mode(USART2, USART_MODE_TX);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF , GPIO_PUPD_NONE, (GPIO2 | GPIO3));
	gpio_set_af(GPIOA, GPIO_AF7, (GPIO2 | GPIO3));


	/*Configure DMA for data transmission*/
	dma_channel_select(DMA1, DMA_STREAM6, DMA_SxCR_CHSEL_4);
	dma_set_transfer_mode(DMA1, DMA_STREAM6, DMA_SxCR_DIR_MEM_TO_PERIPHERAL);
	dma_set_priority(DMA1, DMA_STREAM6, DMA_SxCR_PL_LOW);
	dma_set_memory_size(DMA1, DMA_STREAM6, DMA_SxCR_MSIZE_8BIT);
	dma_set_peripheral_size(DMA1, DMA_STREAM6, DMA_SxCR_PSIZE_8BIT);
	dma_set_peripheral_address(DMA1, DMA_STREAM6, (uint32_t)SERIAL_DATA_REG);
	dma_set_memory_address(DMA1, DMA_STREAM6, (uint32_t)serial_tx_buffer);
	dma_set_number_of_data(DMA1, DMA_STREAM6, (uint16_t)text_len);

	dma_enable_transfer_complete_interrupt(DMA1, DMA_STREAM6);
	dma_enable_memory_increment_mode(DMA1, DMA_STREAM6);
	dma_enable_circular_mode(DMA1, DMA_STREAM6);


	usart_enable_tx_dma(USART2);
	usart_enable(USART2);
	//dma_enable_stream(DMA1, DMA_STREAM6);
}
#endif

/* Print strings on serial port USART2*/
#ifdef STM32F4
void serial_put_s(char *data)
{
	/*while(*data != '\0'){
		usart_send_blocking(USART2, (uint16_t)*data);
		data++;
	}*/
	dma_enable_stream(DMA1, DMA_STREAM6);
}
#endif



/**
 * Private functions
 *
*/
void usart1_isr(void)
{
	/*	Handle data reception	*/
	if(usart_get_flag(serial_com_dev.uart_port, USART_SR_RXNE))
	{

	}

	/* Handle Data transmission */
	if(usart_get_flag(serial_com_dev.uart_port, USART_SR_TXE))
	{

	}
}


/*void dma1_stream6_isr(void)
{
	if(dma_get_interrupt_flag(DMA1, DMA_STREAM6, DMA_TCIF))
	{
		//Clear flag and Disable DMA
		dma_clear_interrupt_flags(DMA1, DMA_STREAM6, DMA_TCIF);
		dma_disable_stream(DMA1, DMA_STREAM6);
	}
}*/

int _write(int file, char *ptr, int len)
{
	int i;

	if (file == STDOUT_FILENO || file == STDERR_FILENO) {
		for (i = 0; i < len; i++) {
			if (ptr[i] == '\n') {
				usart_send_blocking(USART2, '\r');
			}
			usart_send_blocking(USART2, ptr[i]);
		}
		return i;
	}
	errno = EIO;
	return -1;
}



