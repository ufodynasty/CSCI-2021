### coins_funcs_asm.s: Implements several functions in assembly that
### do simple arithmetic operations. The functions also operate on
### structs and pointers to structs requiring an understanding of
### how structs are handled in assmebly.

.text
.globl  set_coins
set_coins:
### args are
### %edi = int cents
### %rsi = coints_t *coins
        ## BLOCK A
        cmpl    $99,%edi        # Analyze/Describe this block
        jg      .OOB
        cmpl    $0,%edi
        jl      .OOB
        
        ## BLOCK B
        movl    %edi,%eax       # eax now has cents
        cqto                    # prep for division
        movl    $25,%r8d
        idivl   %r8d
        movb    %al,0(%rsi)     # coins->quarters = cents / 25
        movl    %edx,%eax       # cents = cents % 25
        
        cqto                    # prep for division
        movl    $10,%r8d
        idivl   %r8d
        movb    %al,1(%rsi)     # coins->dimes = cents / 10
        movl    %edx,%eax       # cents = cents % 10
        
        cqto                    # prep for division 
        movl    $5,%r8d         
        idivl   %r8d            
	movb    %al,2(%rsi)
        movl    %edx,%eax

        cqto
        movb    %al,3(%rsi)

        ## Return 
        movl    $0,%eax         # return value
        ret
.OOB:
        movl    $1, %eax
        ret


# UNCOMMENT the function below once you complete the first
# function. While it is commented, one can run
# `make test-hybrid` to use the C version during testing.
	

 .globl  total_coins
 total_coins:
 ### args are
 ### %rdi packed coin_t struct with struct fields in the following bit ranges
 ###  {0-7: quarters, 8-15: dimes, 16-23-: nickels,  24-31: pennies}
         movl    $0,%eax          # tot = 0
        
         movq    %rdi,%rdx        # extract quarters
         ## sarq    $0,%rdx         # no shift needed
         andq    $0xFF,%rdx       # rdx = quarters, mask low byte
         imul    $25,%edx         # rdx *= 25
         addl    %edx,%eax        # tot += coins.quarters*25
        
         movq    %rdi,%rdx        # extract dimes
         sarq    $8,%rdx          # move dimes to low order bits
         andq    $0xFF,%rdx       # rdx = dimes
         imul    $10,%edx         # rdx *= 10
         addl    %edx,%eax        # tot += coins.dimes*10
        
         movq   %rdi,%rdx
         sarq   $16,%rdx
         andq   $0xFF,%rdx
         imul   $5,%edx
         addl   %edx,%eax

         movq  %rdi,%rdx
         sarq   $24,%rdx
         andq   $0xFF,%rdx
         addl   %edx,%eax
         
         ## return value already in eax
         ret
