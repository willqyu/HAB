#ifndef MEM_INCLUDED
#define MEM_INCLUDED


//Memory
static uint32_t FLASH_TARGET_OFFSET = 262144;
static uint8_t *flash_target_contents = (uint8_t *) (XIP_BASE + 262144);

void clearChunk(const uint32_t offset, size_t len);
void writeChunk(const uint32_t offset, uint8_t data[], size_t len);
void readChunk(const uint8_t *buf, size_t len);
void longToBytes(uint8_t buf[], long in);

#endif