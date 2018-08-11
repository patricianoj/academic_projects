                        .syntax unified
                        .cpu    cortex-m4
                        .text

// uint32_t MyUDIVby13(uint32_t dividend)
                        .global MyUDIVby13
                        .thumb_func
                        .align
MyUDIVby13:             LDR     R1,=0x4EC4EC4F      // R1 = 2^34/13 (4 * bigger for more accuracy)
                        UMULL   R2,R1,R1,R0         // unsigned multiplication: R1 = 2^34/13 * dividend
                        LSRS.N  R0,R1,2             // R1 = R1/4
                        BX      LR

// int32_t MySDIVby13(int32_t dividend)
                        .global MySDIVby13
                        .thumb_func
                        .align
MySDIVby13:             LDR     R1,=0x4EC4EC4F      // R1 = 2^34/13 (4 * bigger for more accuracy)
                        SMMUL   R1,R1,R0            // signed multiplication: R1 = 2^34/13 * dividend
                        ASRS.N  R1,R1,2             // R1 = R1/4
                        ADD     R0,R1,R0,LSR 31     // round in case of negative dividend
                        BX      LR

// int32_t CallReturnOverhead(uint32_t dummy)
                        .global CallReturnOverhead
                        .thumb_func
                        .align
CallReturnOverhead:     BX      LR

// int32_t SDIVby13(int32_t dividend)
                        .global SDIVby13
                        .thumb_func
                        .align

SDIVby13:               MOVS.N  R1,13
                        SDIV    R0,R0,R1
                        BX      LR

// uint32_t UDIVby13(uint32_t dividend)
                        .global UDIVby13
                        .thumb_func
                        .align

UDIVby13:               MOVS.N  R1,13
                        UDIV    R0,R0,R1
                        BX      LR
                        .end


