.globl array_adc
.type array_adc, @function
array_adc:
  pushl %ebp
  movl %esp, %ebp
  movl 16(%ebp), %edi     # edi stores the length of the given numbers
  clc                     # clear the carry flag
  decl %edi               # decrease given length by one becasue array starts from 0
  movl 8(%ebp), %ecx      # ecx stores the pointer to the first argument
  movl 12(%ebp), %edx     # edx holds the pointer to the second argument
loop:
  movb (%edx,%edi), %al   # second arg in al
  adc %al, (%ecx,%edi)    # add and store the calculated value in the first argument
  decl %edi
  jns loop                # check if sign flag is not set
  popl %ebp
  ret
