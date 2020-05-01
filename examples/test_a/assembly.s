.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)i
	push $0 # (int)j
	push $0 # (int)k
.main.0:
# (2) <[int][ASSIGN], (int)i, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[int][ASSIGN], (int)j, (int)i>
	mov -16(%rbp), %rax
	mov -8(%rbp), %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (4) <[int][ASSIGN], (int)k, 10>
	mov -24(%rbp), %rax
	mov $10, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (5) <[int][ADD], (int)i, (int)i, (int)k>
	mov -8(%rbp), %rax
	mov -24(%rbp), %rbx
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
# (7) <[int][ADD], (int)k, 4, 20>
	mov -24(%rbp), %rax
	mov $4, %rbx
	mov $20, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (8) <[int][RETURN], (int)i>
	mov -8(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
