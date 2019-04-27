.globl array_sbb
.type array_sbb, @function
array_sbb:
  pushl %ebp
  movl %esp, %ebp
  pushl %edi
  movl 16(%ebp), %edi     # edi stores the length of the given numbers
  clc                     # clear the carry flag
  decl %edi               # decrease given length by one becasue array starts from 0
  movl 8(%ebp), %edx      # edx stores the pointer to the first argument
  movl 12(%ebp), %ecx     # ecx holds the pointer to the second argument
loop:
  movb (%ecx,%edi), %al   # second arg in al
  sbb %al, (%edx,%edi)    # subtract and store the calculated value in the first argument
  decl %edi
  jns loop                # check if sign flag is not set
  popl %edi
  popl %ebp
  ret