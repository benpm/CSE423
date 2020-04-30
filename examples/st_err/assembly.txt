.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (7) <[int][ASSIGN], (int)g, 3>
	mov $3, %rbx
	mov %rbx, %rax
	push %rax
# (8) <[int][ASSIGN], (int)h, 3>
	mov $3, %rbx
	mov %rbx, %rax
	push %rax
