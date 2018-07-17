#include <string.h>
#include "compression.h"

static const unsigned char magic[4] =
	{ 0x6F, 0x5A, 0x6C, 0x42 };


int decompress(uint8_t **fileData, uint32_t *fileSize)
{
	uint8_t *input = *fileData;
	uint8_t *output;
	uint8_t *out_pos;
	lzo_uint out_len;
	lzo_uint bufferSize;
	lzo_uint decompressSize;
	if (memcmp(input, magic, sizeof(magic)) != 0)
	{
		return COMPRESSION_INVALID_FILE;
	}
	input += 4;

	if (lzo_init() != LZO_E_OK)
	{
		return COMPRESSION_LZO_ERROR;
	}

	decompressSize = *(uint32_t *)(input); input += 4;

	output = new uint8_t[decompressSize];
	out_pos = output;

	while (true)
	{
		bufferSize = *(uint32_t *)(input); input += 4;

		if (bufferSize < COMPRESSION_BLOCK_SIZE)
		{
			int r = lzo1x_decompress(input, bufferSize, out_pos, &out_len, NULL);
			if (r != LZO_E_OK)
			{
				delete[] output;
				return COMPRESSION_LZO_ERROR;
			}
		}
		else
		{
			bufferSize = out_len = COMPRESSION_BLOCK_SIZE;
			memcpy(out_pos, input, bufferSize);
		}

		input += bufferSize;
		out_pos += out_len;
		if (out_pos - output == decompressSize) break;
		while (*input == 0)
		{
			input++;
		}
	}

	delete[] * fileData;
	*fileData = output;
	*fileSize = decompressSize;
	return COMPRESSION_OK;
}