#pragma once
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>
#include "minilzo.h"

#define COMPRESSION_OK				0
#define COMPRESSION_INVALID_FILE	1
#define COMPRESSION_INTERNAL_ERROR	2
#define COMPRESSION_LZO_ERROR		3

#define COMPRESSION_BLOCK_SIZE			0x8000

int decompress(uint8_t **fileData, uint32_t *fileSize);

#endif // !COMPRESSION_H
