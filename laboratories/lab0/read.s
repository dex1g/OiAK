SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.text
msg: .ascii "Input text (5):"
msg_len = . - msg

output_msg: .ascii "Written text: "
output_msg_len = . - output_msg


.data
buf: .ascii "      "
buf_len = . - buf

.global _start

_start:

# First lets display the input message

mov $SYSWRITE,%eax
mov $STDOUT,%ebx
mov $msg,%ecx
mov $msg_len,%edx
int $0x80

# Now lets get user input from STDIN

mov $SYSREAD,%eax
mov $STDIN,%ebx
mov $buf,%ecx
mov $buf_len,%edx
int $0x80

# Display the text "Written message:"

mov $SYSWRITE,%eax
mov $STDOUT,%ebx
mov $output_msg,%ecx
mov $output_msg_len,%edx
int $0x80

# Present the 5 letters someone inserted on the STDOUT

mov $SYSWRITE,%eax
mov $STDOUT, %ebx
mov $buf,%ecx
mov $buf_len,%edx
int $0x80


# Return exit success to properly kill the process

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80

/* vim: ft=gas : 
*/ 
