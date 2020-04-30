.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (2) <[int][ASSIGN], (int)i, 0>
	mov $0, %rbx
	mov %rbx, %rax
	push %rax
# (3) <[int][ASSIGN], (int)j, 0>
	mov $0, %rbx
	mov %rbx, %rax
	push %rax
# (5) <[int][ADD], (int)i, (int)i, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ADD], (int)j, (int)i, 7>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov $7, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (8) <[int][RETURN], (int)i>
	mov -8(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
