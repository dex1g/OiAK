.globl array_adc
.type array_adc, @function
array_adc:
  pushl %ebp
  movl %esp, %ebp
  pushl %edi
  pushl %esi
  movl 8(%ebp), %edx      # edx stores the pointer to the first argument
  movl 12(%ebp), %ecx     # ecx holds the pointer to the second argument
  movl 16(%ebp), %edi     # edi stores the length of the given numbers
  movl 20(%ebp), %esi     # esi holds number of bytes in front of second argument
  clc                     # clear the carry flag
  decl %edi               # decrease given length by one becasue array starts from 0
sum:
  movb (%ecx,%edi), %al   # second arg in al
  adc %al, (%edx,%edi)    # add and store the calculated value in the first argument
  decl %edi
  jns sum                 # check if sign flag is not set
  jnc end
carry:
  dec %esi
  js end
  dec %edx
  inc (%edx)
  jz carry
end:
  popl %esi
  popl %edi
  popl %ebp
  ret
