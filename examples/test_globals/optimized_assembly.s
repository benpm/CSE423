.text
.globl main
.type main, @function
# FUNCTION fun
fun:
	push %rbp
	mov %rsp, %rbp
.fun.0:
# (7) <[int][ADD], (int)v, (int)v, 9>
	mov $9, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	push %rax
# (8) <[int][ADD], (int)#0, 1, (int)v>
	mov $1, %rbx
	mov -8(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	push %rax
# (8) <[int][ADD], (int)x, (int)x, (int)#0>
	mov -16(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	push %rax
# (9) <[int][ADD], (int)#0, 3, (int)x>
	mov -16(%rbp), %rax
	mov $3, %rbx
	mov -24(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (9) <[int][ADD], (int)z, (int)z, (int)#0>
	mov -16(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	push %rax
# (10) <[int][RETURN], (int)v>
	mov -8(%rbp), %rax
# stack size is 40
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (15) <[int][ADD], (int)v, (int)v, 2>
	mov $2, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	push %rax
# (16) <[int][ASSIGN], (int)x, 3>
	mov $3, %rbx
	mov %rbx, %rax
	push %rax
# (17) <[int][ASSIGN], (int)i, 0>
	mov $0, %rbx
	mov %rbx, %rax
	push %rax
.main.3:
# (17) <[JUMP_LT], <4>, (int)i, 7>
	mov -24(%rbp), %rax
	mov $7, %rbx
	cmp %rbx, %rax
	jl .main.4
# (17) <[JUMP], <6>>
	jmp .main.6
.main.4:
# (18) <[int][CALL], (int)#0, (int)fun>
	call fun
	push %rax
# (18) <[int][ADD], (int)x, (int)x, (int)#0>
	mov -16(%rbp), %rax
	mov -32(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (17) <[int][ADD], (int)i, (int)i, 1>
	mov -24(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (17) <[JUMP], <3>>
	jmp .main.3
.main.6:
# (20) <[int][ADD], (int)#0, (int)v, (int)x>
	mov -32(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (20) <[int][ADD], (int)#1, (int)#0, (int)z>
	mov -32(%rbp), %rbx
	add %rbx, %rcx
	mov %rcx, %rax
	push %rax
# (20) <[int][RETURN], (int)#1>
	mov -40(%rbp), %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
