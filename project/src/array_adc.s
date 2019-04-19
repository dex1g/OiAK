.globl array_adc
.type array_adc, @function
array_adc:
  pushl %ebp
  movl %esp, %ebp
  movl 16(%ebp), %edi     # edi stores the length of the given numbers
  clc                     # clear the carry flag
  decl %edi               # decrease given length by one becasue array starts from 0
loop:
  movl 8(%ebp), %ebx      # ebx stores the pointer to the first argument
  movl 12(%ebp), %eax     # eax holds the pointer to the second argument
  movb (%ebx,%edi), %bl
  movb (%eax,%edi), %al
  adc %al, %bl
  movl 8(%ebp), %eax      # get again the address of first argument
  movb %bl, (%eax,%edi)   # store the current calculated value in the first argument
  decl %edi
  jns loop                # chec if sign flat is not set
  popl %ebp
  ret
