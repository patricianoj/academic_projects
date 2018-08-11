                .syntax unified
                .cpu    cortex-m4
                .text

// void DeleteItem(int32_t data[], int32_t items, int32_t index)
                .global DeleteItem
                .thumb_func
                .align

DeleteItem:     SUB     R1,R1,1             // items = items-1, setting stop condition
BeginLoop:      CMP     R2,R1               // continue? index >= items
                BGE     DoneDelete          // if index >= items, end loop
                ADD     R2,R2,1             // else increment index
                LDR     R3,[R0,R2,LSL 2]    // R3 <- value of data[incremented index]
                SUB     R2,R2,1             // decrement index
                STR     R3,[R0,R2,LSL 2]    // data[decremented index] = value of data[incremented index]
                ADD     R2,R2,1             // increment index
                B       BeginLoop           // repeat loop
DoneDelete:     BX      LR                  // exit function

// void InsertItem(int32_t data[], int32_t items, int32_t index, int32_t value)
                .global InsertItem
                .thumb_func
                .align

InsertItem:     SUB     R1,R1,1             // R1 <- items - 1
LoopStart:      CMP     R1,R2               // continue? items <= index
                BLE     DoneInsert          // if items <= index, end loop
                SUB     R1,R1,1             // decrement items to go to index items--
                LDR     R12,[R0,R1,LSL 2]   // R3 <- value of data[items-1]
                ADD     R1,R1,1             // increment items
                STR     R12,[R0,R1,LSL 2]   // data[items+1] = data[items-1]
                SUB     R1,R1,1             // decrement items for next loop
                B       LoopStart           // repeat loop
DoneInsert:     STR     R3,[R0,R2,LSL 2]    // store value into data[index]
                BX      LR

                .end
