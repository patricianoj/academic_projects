                .syntax unified
                .cpu    cortex-m4
                .text

// uint32_t *PixelAddress(int x, int y);
                .global PixelAddress
                .thumb_func
                .align

PixelAddress:   LDR     R2,=240         // R2 <- 240
                MUL     R1,R1,R2        // R1 <- 240y
                ADD     R1,R1,R0        // R1 <- x + 240y
                LDR     R2,=0xD0000000  // R2 <- starting address of pixels array
                ADD     R0,R2,R1,LSL 2  // R0 <- address of pixel = starting address + scaled subscript
                BX      LR


// uint8_t *BitmapAddress(char ascii, uint8_t *fontTable, int charHeight, int charWidth);
                .global BitmapAddress
                .thumb_func
                .align

BitmapAddress:  ADD     R3,R3,7         // calculate row width part 1- fontwidth+7
                LSR     R3,R3,3         // calcualte row width part 2 - divide by 8
                MUL     R3,R3,R2        // R3 <- row-width * height = bitmap size
                SUB     R0,R0,' '       // R0 <- index = ascii - space
                MUL     R0,R0,R3        // R0 <- index * size (total # of bytes need to move forward)
                ADD     R0,R1,R0
                BX      LR

// uint32_t GetBitmapRow(unit8_t *rowAdrs);
                .global GetBitmapRow
                .thumb_func
                .align

GetBitmapRow:   LDR     R0,[R0]          // load 8 bits that rowAdrs points to
                REV     R0,R0            // reverse order of bits
                BX      LR

                .end
