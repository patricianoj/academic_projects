            .syntax unified
            .cpu cortex-m4
            .text

// void UseLDRB(void *dst, void *src)
            .global UseLDRB
            .thumb_func
            .align

UseLDRB:    .rept   512             // loop 512 times for 512*1byte
            LDRB    R2,[R1],1       // load 1 byte at a time
            STRB    R2,[R0],1       // store 1 byte in dst array
            .endr
            BX      LR

// void UseLDRH(void *dst, void *src)
            .global UseLDRH
            .thumb_func
            .align

UseLDRH:    .rept   256             // loop 256 times for 256*2bytes
            LDRH    R2,[R1],2       // load 16 bits at a time
            STRH    R2,[R0],2       // store 2 bytes in dst array
            .endr
            BX      LR

// void UseLDR(void *dst, void *src)
            .global UseLDR
            .thumb_func
            .align

UseLDR:     .rept   128             // loop 128 times for 128*4bytes
            LDR    R2,[R1],4        // load 32 bits from *src to R2
            STR    R2,[R0],4        // store 32 bits from R2 to dst array
            .endr
            BX      LR

// void UseLDRD(void *dst, void *src)
            .global UseLDRD
            .thumb_func
            .align

UseLDRD:    .rept   64              // loop 64 times for 64*8bytes
            LDRD    R2,[R1],8       // load 64 bits from *src
            STRD    R2,R3,[R0],8    // store 64 bits in dst array
            .endr
            BX      LR

// void UseLDMIA(void *dst, void *src)
            .global UseLDMIA
            .thumb_func
            .align

UseLDMIA:   PUSH    {R4-R9}         // preserve registers R4 through R9
            .rept   16              // loop 16 times for 16*32 = 512 total bytes
            LDMIA   R1!,{R2-R9}     // copy 8 words of 4 bytes = 32 bytes at a time
            STMIA   R0!,{R2-R9}
            .endr
            POP     {R4-R9}         // restore registers R4 through R9
            BX LR
            .end
