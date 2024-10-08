#ifndef _MEMORY_MAP_H
#define _MEMORY_MAP_H

// Register Info ------------------------------------------
#define HOURS_TO_SAVE_DAY          24 //define provisional, despues manejado por registro

// Registers ----------------------------------------------

#define OFFSET          0x50000000

#define BASE_DISTANCE   (OFFSET + 0x04)
#define BASE_IS_ACTIVE  (OFFSET + 0x24)
#define BASE_RANGE      (OFFSET + 0x44)
#define BASE_IDENTIFIER (OFFSET + 0x64)
#define BASE_CAPTURE    (OFFSET + 0x84)

#define REG_ENABLE      OFFSET
#define REG_IMAGE_ROWS  (OFFSET + 0xA4)
#define REG_IMAGE_COLS  (OFFSET + 0xA8)

#define REG_DISTANCE0   (BASE_DISTANCE + 0x0)
#define REG_DISTANCE1   (BASE_DISTANCE + 0x4)
#define REG_DISTANCE2   (BASE_DISTANCE + 0x8)
#define REG_DISTANCE3   (BASE_DISTANCE + 0xC)
#define REG_DISTANCE4   (BASE_DISTANCE + 0x10)
#define REG_DISTANCE5   (BASE_DISTANCE + 0x14)
#define REG_DISTANCE6   (BASE_DISTANCE + 0x18)
#define REG_DISTANCE7   (BASE_DISTANCE + 0x1C)

#define REG_IS_ACTIVE0  (BASE_IS_ACTIVE + 0x0)
#define REG_IS_ACTIVE1  (BASE_IS_ACTIVE + 0x4)
#define REG_IS_ACTIVE2  (BASE_IS_ACTIVE + 0x8)
#define REG_IS_ACTIVE3  (BASE_IS_ACTIVE + 0xC)
#define REG_IS_ACTIVE4  (BASE_IS_ACTIVE + 0x10)
#define REG_IS_ACTIVE5  (BASE_IS_ACTIVE + 0x14)
#define REG_IS_ACTIVE6  (BASE_IS_ACTIVE + 0x18)
#define REG_IS_ACTIVE7  (BASE_IS_ACTIVE + 0x1C)

#define REG_RANGE0      (BASE_RANGE + 0x0)
#define REG_RANGE1      (BASE_RANGE + 0x4)
#define REG_RANGE2      (BASE_RANGE + 0x8)
#define REG_RANGE3      (BASE_RANGE + 0xC)
#define REG_RANGE4      (BASE_RANGE + 0x10)
#define REG_RANGE5      (BASE_RANGE + 0x14)
#define REG_RANGE6      (BASE_RANGE + 0x18)
#define REG_RANGE7      (BASE_RANGE + 0x1C)

#define REG_IDENTIFIER0 (BASE_IDENTIFIER + 0x0)
#define REG_IDENTIFIER1 (BASE_IDENTIFIER + 0x4)
#define REG_IDENTIFIER2 (BASE_IDENTIFIER + 0x8)
#define REG_IDENTIFIER3 (BASE_IDENTIFIER + 0xC)
#define REG_IDENTIFIER4 (BASE_IDENTIFIER + 0x10)
#define REG_IDENTIFIER5 (BASE_IDENTIFIER + 0x14)
#define REG_IDENTIFIER6 (BASE_IDENTIFIER + 0x18)
#define REG_IDENTIFIER7 (BASE_IDENTIFIER + 0x1C)
#define REG_IDENTIFIER7 (BASE_IDENTIFIER + 0x1C)

#define REG_CAPTURE0    (BASE_CAPTURE + 0x0)
#define REG_CAPTURE1    (BASE_CAPTURE + 0x4)
#define REG_CAPTURE2    (BASE_CAPTURE + 0x8)
#define REG_CAPTURE3    (BASE_CAPTURE + 0xC)
#define REG_CAPTURE4    (BASE_CAPTURE + 0x10)
#define REG_CAPTURE5    (BASE_CAPTURE + 0x14)
#define REG_CAPTURE6    (BASE_CAPTURE + 0x18)
#define REG_CAPTURE7    (BASE_CAPTURE + 0x1C)
#define REG_CAPTURE7    (BASE_CAPTURE + 0x1C)

#endif