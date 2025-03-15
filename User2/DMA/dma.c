#include "dma.h"

DMA_HandleTypeDef hdma_memtomem_dma2_stream1;

/** 
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma2_stream1
  */
void MX_DMA_Init(void) 
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdma_memtomem_dma2_stream1.Instance = DMA2_Stream1;
	hdma_memtomem_dma2_stream1.Init.Channel = DMA_CHANNEL_0;
	hdma_memtomem_dma2_stream1.Init.Direction = DMA_MEMORY_TO_MEMORY;
	hdma_memtomem_dma2_stream1.Init.PeriphInc = DMA_PINC_ENABLE;
	hdma_memtomem_dma2_stream1.Init.MemInc = DMA_MINC_ENABLE;
	hdma_memtomem_dma2_stream1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_memtomem_dma2_stream1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_memtomem_dma2_stream1.Init.Mode = DMA_NORMAL;
	hdma_memtomem_dma2_stream1.Init.Priority = DMA_PRIORITY_LOW;
	hdma_memtomem_dma2_stream1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	hdma_memtomem_dma2_stream1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma_memtomem_dma2_stream1.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_memtomem_dma2_stream1.Init.PeriphBurst = DMA_PBURST_SINGLE;
	if (HAL_DMA_Init(&hdma_memtomem_dma2_stream1) != HAL_OK)
	{
		Error_Handler();
	}

}

