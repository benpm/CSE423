.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)x
	push $0 # (int)i
	push $0 # (int)#0
	push $0 # (int)j
	push $0 # (int)z
.main.0:
# (3) <[int][ASSIGN], (int)x, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (4) <[int][ASSIGN], (int)i, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
.main.2:
# (4) <[JUMP_LT], <3>, (int)i, 13>
	mov -16(%rbp), %rax
	mov $13, %rbx
	cmp %rbx, %rax
	jl .main.3
# (4) <[JUMP], <14>>
	jmp .main.14
.main.3:
# (5) <[int][MUL], (int)#0, (int)x, (int)i>
	mov -24(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -16(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (5) <[int][ADD], (int)x, (int)x, (int)#0>
	mov -8(%rbp), %rax
	mov -24(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ASSIGN], (int)j, 0>
	mov -32(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
.main.5:
# (6) <[JUMP_LT], <6>, (int)j, 56>
	mov -32(%rbp), %rax
	mov $56, %rbx
	cmp %rbx, %rax
	jl .main.6
# (6) <[JUMP], <13>>
	jmp .main.13
.main.6:
# (7) <[int][ASSIGN], (int)z, 2>
	mov -40(%rbp), %rax
	mov $2, %rbx
	mov %rbx, %rax
	mov %rax, -40(%rbp)
# (8) <[int][MINUS], (int)x, (int)x, (int)j>
	mov -8(%rbp), %rax
	neg %rax
	mov %rax, %rax
	mov %rax, -8(%rbp)
.main.8:
# (9) <[JUMP_LT], <9>, (int)z, 100>
	mov -40(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.9
# (9) <[JUMP], <11>>
	jmp .main.11
.main.9:
# (10) <[int][MUL], (int)#0, (int)x, (int)x>
	mov -24(%rbp), %rax
	mov -8(%rbp), %rbx
	imul %rbx, %rbx
	mov %rbx, %rax
	mov %rax, -24(%rbp)
# (10) <[int][ADD], (int)z, (int)z, (int)#0>
	mov -40(%rbp), %rax
	mov -24(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -40(%rbp)
# (9) <[JUMP], <8>>
	jmp .main.8
.main.11:
# (12) <[int][MOD], (int)#0, (int)z, (int)j>
	mov -40(%rbp), %rax
	mov -24(%rbp), %rbx
	mov -32(%rbp), %rcx
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -24(%rbp)
# (12) <[int][ADD], (int)x, (int)x, (int)#0>
	mov -8(%rbp), %rax
	mov -24(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (6) <[int][ADD], (int)j, (int)j, 2>
	mov -32(%rbp), %rax
	mov $2, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -32(%rbp)
# (6) <[JUMP], <5>>
	jmp .main.5
.main.13:
# (4) <[int][ADD], (int)i, (int)i, 1>
	mov -16(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (4) <[JUMP], <2>>
	jmp .main.2
.main.14:
# (15) <[int][RETURN], (int)x>
	mov -8(%rbp), %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
