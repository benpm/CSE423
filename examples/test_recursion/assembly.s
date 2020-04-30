.text
.globl main
.type main, @function
# FUNCTION refun
# param (int)x at 16(%rbp)
refun:
	push %rbp
	mov %rsp, %rbp
.refun.0:
# (2) <[int][ADD], (int)x, (int)x, 3>
	mov 16(%rbp), %rax
	mov $3, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, 16(%rbp)
# (3) <[JUMP_LT], <2>, (int)x, 1239>
	mov 16(%rbp), %rax
	mov $1239, %rbx
	cmp %rbx, %rax
	jl .refun.2
# (3) <[JUMP], <3>>
	jmp .refun.3
.refun.2:
# (4) <[int][MUL], (int)#0, (int)x, 2>
	mov 16(%rbp), %rbx
	mov $2, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	push %rax
# (4) <[int][CALL], (int)#1, refun, (int)#0>
	push -8(%rbp)
	call refun
	add $8, %rsp
	push %rax
.refun.3:
# (6) <[int][RETURN], (int)x>
	mov 16(%rbp), %rax
# stack size is 24
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
# (11) <[int][CALL], (int)#0, refun, 1>
	push $1
	call refun
	add $8, %rsp
	push %rax
# (11) <[int][RETURN], (int)#0>
	mov -8(%rbp), %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
