.data
number: .int 15

.globl	memoryOperation
.type	memoryOperation, @function
memoryOperation:
    movl $200, number
    ret
    