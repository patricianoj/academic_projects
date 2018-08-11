            .syntax unified
            .cpu    cortex-m4
            .text

// void PutNibble(void *nibbles, uint32_t index, uint32_t nibble)
            .global PutNibble
            .thumb_func
            .align
PutNibble:  LSRS    R1,R1,1     // divide index by 2 to determine if odd or even, update flags
            LDRB    R3,[R0,R1]  // R3 <- nibbles[index]
            ITTE    CS          // check carryflag
            LSLCS   R2,R2,4     // if odd, shift R2 to align it and preserve the least significant half
            ANDCS   R3,R3,0xF   // if odd, modify most significant half
            ANDCC   R3,R3,0xF0  // if even, modify least significant half and preserve most significant half
            ORR     R2,R2,R3    // OR original nibble with modified version to get new nibble
            STRB    R2,[R0,R1]  // nibbles[index] = modified nibble
            BX      LR

// uint32_t GetNibble(void *nibbles, uint32_t index)
            .global GetNibble
            .thumb_func
            .align
GetNibble:  LSRS    R1,R1,1     // divide index by 2 to determine if odd or even, update flags
            LDRB    R2,[R0,R1]  // load nibbles[index]
            ITE     CS          // check carryflag
            LSRCS   R0,R2,4     // if odd, clear least signifant half
            ANDCC   R0,R2,0x0F  // if even, clear most significant half
            BX      LR          // return least significant half
            .end
