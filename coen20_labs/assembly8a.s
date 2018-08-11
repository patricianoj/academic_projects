                .syntax unified
                .cpu    cortex-m4
                .text

// float FloatPoly(float x, float a[], int32_t n);
                .global     FloatPoly
                .thumb_func
                .align

one:           .float      1.0
sum:           .float      0.0


FloatPoly:      VLDR        S1,sum              // load floating point constant 0.0 for sum
                VLDR        S2,one              // load floating point constant 1.0
loop:           CBZ         R1,finish           // check if n = 0
                VLDMIA      R0!,{S3}            // S3 <- next number in array
                VMLA.F32    S1,S3,S2            // sum += coefficent * x^exponent
                VMUL.F32    S2,S0,S2            // S2 <- multiplied by x
                SUB         R1,R1,1             // decrease n to update control variable
                B           loop                // repeat loop
finish:         VMOV        S0,S1               // move result to S0
                BX          LR


// Q16 FixedPoly(Q16 x, Q16 a[], int32_t n);
                .global     FixedPoly
                .thumb_func
                .align

FixedPoly:      PUSH        {R4,R5}             // preserve registers
                LDR         R12,=0              // store 0 in R12.R4 to start off sum at 0
                LDR         R4,=0               // least significant half of resulting sum
                LDR         R5,=(1<<16)         // store 1 as a Q16.16 fixed point value

other_loop:     CBZ         R2,done             // check counter n to see if done
                LDMIA       R1!,{R3}            // R3 <- next coefficient in array
                SMLAL       R4,R12,R5,R3        // R12.R4 (64-bit) sum += coefficient * x^exponent
                SMULL       R3,R5,R0,R5         // R5.R3 (64-bit) <- current x^n * x^n+1
                                                // extract middle 32 each time from x^n
                LSRS.N      R3,R3,16            // shift least significant half to the right
                ORR         R5,R3,R5,LSL 16     // insert most significant half shifted left by 16
                SUB         R2,R2,1             // decrease n to update control variable
                B           other_loop          // repeat loop
                                                // extract middle 32-bits of sum
done:           LSRS        R4,R4,16            // shift least significant half to the right
                ORR         R0,R4,R12,LSL 16    // insert most significant half shifted left by 16
                POP         {R4,R5}
                BX          LR

                .end
