.text
.global  set_batt_from_ports
        
## ENTRY POINT FOR REQUIRED FUNCTION
set_batt_from_ports:
        movw    BATT_VOLTAGE_PORT(%rip), %ax
        cmp     $0x0, %ax
        jl      .FAIL_SET # fails if BATT_VOLTAGE_PORT is negative 
        sarw    $0x1, %ax # div by 2
        movw    %ax, (%rdi) # set mvolts field of batt struct
        cmp     $0xbb8, %ax # checks if the percentage is less than 0
        jl      .MIN_PERCENT
        cmp     $0xed8, %ax # checks if the percentage is greater than 100
        jg      .MAX_PERCENT
        subw    $0xbb8, %ax
        sarw    $0x3, %ax
        movb    %al, 0x2(%rdi) # puts mvolts -3000 / 8 into percent field of batt struct
        jmp     .AFTER_PERCENT
.MIN_PERCENT:
        movb    $0x0, 0x2(%rdi) # puts 0 into percent field of batt struct
        jmp     .AFTER_PERCENT
.MAX_PERCENT:
        movb    $0x64, 0x2(%rdi) # puts 100 into percent field of batt struct
.AFTER_PERCENT:
        movb    BATT_STATUS_PORT(%rip), %al
        andb    $0x4, %al # masks all but bit 3 of BATT_STATUS_PORT
        sarb    $0x2, %al # moves bit to lsb
        addb    $0x1, %al # converts v=0,p=1 to v=1,p=2. Why 1/2 instead of 0/1 is used to hold a binary value is beyond me
        movb    %al, 0x3(%rdi) # puts mode into mode field of batt struct
        xor     %eax, %eax # ensures return value is 0
        ret     
.FAIL_SET:
        movl    $0x1, %eax # returns a value of 1
        ret                                          

### Change to definint semi-global variables used with the next function 
### via the '.data' directive
.data


seven_segment_encoder:              # Encodes from decimal value to binary representation
        .int 0b0111111          # 0
        .int 0b0000110          # 1
        .int 0b1011011          # 2
        .int 0b1001111          # 3
        .int 0b1100110          # 4
        .int 0b1101101          # 5
        .int 0b1111101          # 6
        .int 0b0000111          # 7
        .int 0b1111111          # 8
        .int 0b1101111          # 9
        .int 0b0000000          # Empty


## WARNING: Don't forget to switch back to .text as below
## Otherwise you may get weird permission errors when executing

.text
.global  set_display_from_batt

## ENTRY POINT FOR REQUIRED FUNCTION
set_display_from_batt:  
        xor     %r10d, %r10d  # Initialize r10d to 0. It will hold the bits of the display
        movl    %edi, %r8d
        andl    $0xff000000, %r8d
        sarl    $0x18, %r8d # load mode from batt struct into r8d
        cmp     $0x2, %r8d # checks if the mode is 2
        je      .NO_FAIL
        cmp     $0x1, %r8d # checks if the mode is 1
        je      .NO_FAIL
        movl    $0x1, %eax # If the mode isn't 1 or 2, return an error
        ret
.NO_FAIL:
        movl    %edi, %r8d
        andl    $0xff0000, %r8d
        sarl    $0x10, %r8d # load percent from batt struct into r8d
        movl    $0x1, %eax
        sall    $0x18, %eax # eax holds the position of the bit we are manipulating
        cmp     $0x5, %r8b # checks progressivly higher batt percentages to turn on batt lights
        jl      .END_BATT_BITS
        orl     %eax, %r10d
        sall    $0x1, %eax
        cmp     $0x1e, %r8b
        jl      .END_BATT_BITS
        orl     %eax, %r10d
        sall    $0x1, %eax
        cmp     $0x32, %r8b
        jl      .END_BATT_BITS
        orl     %eax, %r10d
        sall    $0x1, %eax
        cmp     $0x46, %r8b
        jl      .END_BATT_BITS
        orl     %eax, %r10d
        sall    $0x1, %eax
        cmp     $0x5a, %r8b
        jl      .END_BATT_BITS
        orl     %eax, %r10d
.END_BATT_BITS:
        movl    %edi, %r8d
        andl    $0xff000000, %r8d
        sarl    $0x18, %r8d # load mode from batt struct into r8d
        movl    $0x1, %eax
        sall    $0x15, %eax # eax holds the position of the bit we are manipulating
        cmp     $0x2, %r8b # if in percent mode, only turn on perent light
        je      .PERCENT_BIT
        sall    $0x1, %eax # otherwise turn on decimal light and v light
        orl     %eax, %r10d
        sall    $0x1, %eax
        orl     %eax, %r10d
        jmp     .END_MODE_BITS
.PERCENT_BIT:
        orl     %eax, %r10d
.END_MODE_BITS:
        cmp     $0x2, %r8b # r8b still hold mode from batt struct
        je      .PERCENT_NUMBERS # determines whether the percent or voltage should be displayed
        movl    %edi, %r8d
        andl    $0xffff, %r8d
        sarl    $0x0, %r8d # r8d now hold batt voltage
        leaq    seven_segment_encoder(%rip), %rcx # rcx holds pointer to begining of 7 seg encoder
        movw    %r8w, %ax # ax will hold binary of each didget
        movq    $0x0, %rdx # setting up division
        movw    $0x3e8, %r11w
        idivw   %r11w # first didget is v/1000
        cwtl
        movw    (%rcx,%rax,4), %ax # encode first didget
        sall    $0xe, %eax # offset first didget
        orl     %eax, %r10d # set first didget
        movw    %r8w, %ax # reload voltage into ax
        movq    $0x0, %rdx
        movw    $0x64, %r11w
        idivw   %r11w # second didget is v/100%10
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w
        movw    %dx, %ax
        cwtl
        movw    (%rcx,%rax,4), %ax
        sall    $0x7, %eax # offset second didget
        orl     %eax, %r10d # set second didget
        movw    %r8w, %ax # reload voltage into ax
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w # third didget is v/10%10 (+1 if v%10 is <5)
        movw    %dx, %r9w # temporarily holding on to this for rounding
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w
        movw    %dx, %ax
        cwtl
        cmp     $0x5, %r9w # check if v%10 < 5
        jl      .DONT_ROUND_VOLTAGE
        addw    $0x1, %ax # round v%10 up
.DONT_ROUND_VOLTAGE:
        movw    (%rcx,%rax,4), %ax # encode third didget
        sall    $0x0, %eax # offset third didget (not necessary but makes the code readable)
        orl     %eax, %r10d # set third didget
        jmp     .END_OF_NUMBER_BITS
.PERCENT_NUMBERS:
        xor     %r9, %r9 # Initializes no 00 flag
        movl    %edi, %r8d
        andl    $0xff0000, %r8d
        sarl    $0x10, %r8d # load batt percent into r8d
        leaq    seven_segment_encoder(%rip), %rcx # rcx holds pointer to begining of 7 seg encoder
        movw    %r8w, %ax # ax will hold binary of each didget
        movq    $0x0, %rdx # setting up division
        movw    $0x64, %r11w
        idivw   %r11w # first didget is %/100
        cwtl
        cmp     $0x0, %ax # if the first didget is 0 don't show it
        jnz     .NO_LEADING_0
        movw    $0xa, %ax # 10 encodes as empty 
        movb    $0x1, %r9b # Set a flag that the first didget was 0
.NO_LEADING_0:
        movw    (%rcx,%rax,4), %ax # encode first didget
        sall    $0xe, %eax # offset first didget
        orl     %eax, %r10d # set first didget
        movw    %r8w, %ax # reload % into ax
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w # second diget is (%)/10%10
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w
        movw    %dx, %ax
        cwtl
        cmp     $0x0, %ax # Show the second didget if it isn't 0
        jne     .NO_LEADING_00
        cmp     $0x1, %r9b # Only show the second didget as a 0 if the first didget wasn't a 0
        jne     .NO_LEADING_00
        movw    $0xa, %ax # 10 encodes as empty
.NO_LEADING_00:
        movw    (%rcx,%rax,4), %ax # encode second didget
        sall    $0x7, %eax # offset second didget
        orl     %eax, %r10d # set second didget
        movw    %r8w, %ax # reload batt percent into ax
        movq    $0x0, %rdx
        movw    $0xa, %r11w
        idivw   %r11w # third didget is (%)%10
        movw    %dx, %ax
        cwtl
        movw    (%rcx,%rax,4), %ax # encode third didget
        sall    $0x0, %eax # offset third didget (not necessary but improves readability)
        orl     %eax, %r10d # set third didget
.END_OF_NUMBER_BITS:
        movl    %r10d, (%rsi) # updates the display port given by the caller
        xor     %eax, %eax # clears eax
        ret
.text
.global batt_update
        
## ENTRY POINT FOR REQUIRED FUNCTION
batt_update:
        subq    $0x8, %rsp # Allign the stack
        movq    $0x0, (%rsp) # Initializes an empty batt struct
        leaq    (%rsp), %rdi # loads a pointer to the batt struct into rdi
        call    set_batt_from_ports # calls set_batt_from_ports using the pointer as the only argument
        cmp     $0x0, %eax # checks if set_bat_from_ports returned an error
        jne     .FAIL
        leaq    BATT_DISPLAY_PORT(%rip), %rsi # loads a pointer to the BATT_DISPLAY_PORT into rsi
        movq    (%rdi), %rdi # dereferences rdi and loads the result into rdi
        call    set_display_from_batt # calls set_batt_from_ports using the batt struct as the first argument and a pointer to the display port as the other  
.FAIL:
        addq    $0x8, %rsp # clears the stack before returning
        ret

