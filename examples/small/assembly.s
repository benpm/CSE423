.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (3) <[int][ASSIGN], (int)a, 42>
	mov $42, %rbx
	mov %rbx, %rax
	push %rax
# (4) <[int][ASSIGN], (int)b, 89>
	mov $89, %rbx
	mov %rbx, %rax
	push %rax
# (5) <[int][MUL], (int)#0, (int)b, 12>
	mov -16(%rbp), %rbx
	mov $12, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	push %rax
# (5) <[int][ADD], (int)c, (int)a, (int)#0>
	mov -8(%rbp), %rbx
	mov -24(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	push %rax
# (6) <[float][MINUS], (float)d, 8.011609>
	mov $8.01161, %rbx
	neg %rbx
	mov %rbx, %rax
	push %rax
# (8) <[JUMP_LT], <5>, (int)c, 2>
	mov -32(%rbp), %rax
	mov $2, %rbx
	cmp %rbx, %rax
	jl .main.5
# (8) <[JUMP], <6>>
	jmp .main.6
.main.5:
# (9) <[int][RETURN], 35>
	mov $35, %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.main.6:
# (11) <[int][RETURN], 124>
	mov $124, %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
