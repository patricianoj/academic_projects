            .syntax unified
            .cpu    cortex-m4
            .text

// unit32_t Ten32(void);
            .global Ten32
            .thumb_func
            .align

Ten32:      LDR     R0,=10          // R0 <- 10
            BX      LR

// unit64_t Ten64(void);
            .global Ten64
            .thumb_func
            .align

Ten64:      LDR     R0,=10          // R0 <- 10
            LDR     R1,=0           // R1 <- 0 because return size is 64 bits
            BX      LR

// unit32_t Incr(unit32_t n);
            .global Incr
            .thumb_func
            .align

Incr:       ADD     R0,R0,1         // R0 <- n + 1
            BX      LR


// unit32_t Nested1(void);
            .global Nested1
            .thumb_func
            .align

Nested1:    PUSH    {LR}            // preserve LR
            BL      rand            // call rand()
            ADD     R0,R0,1         // R0 <- rand() + 1
            POP     {PC}

// unit32_t Nested2(void);
            .global Nested2
            .thumb_func
            .align

Nested2:    PUSH    {R4,LR}         // preserve LR
            BL      rand
            MOV     R4,R0           // R4 <- rand()
            BL      rand
            ADD     R0,R0,R4        // R0 <- rand() + rand()
            POP     {R4,PC}


// void PrintTwo(char *format, unit32_t n);
            .global PrintTwo
            .thumb_func
            .align

PrintTwo:   PUSH    {R4,R5,LR}
            MOV     R4,R0           // preserve format in R4
            MOV     R5,R1           // preserve n in R5
            BL      printf
            MOV     R0,R4           // R0 <- format
            ADD     R1,R5,1         // R1 <- n+1
            BL      printf
            POP     {R4,R5,PC}

            .end

