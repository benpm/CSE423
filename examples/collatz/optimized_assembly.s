.text
.globl collatz
.type collatz, @function
.data
# FUNCTION collatz
# param (int)i at 16(%rbp)
.text
collatz:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)iters at -8(%rbp)
	push $0 # (int)#0 at -16(%rbp)
.collatz.0:
# (3) <[int][ASSIGN], (int)iters, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.collatz.1:
# (4) <[JUMP_NEQ], <2>, (int)i, 1>
	mov 16(%rbp), %rax
	mov $1, %rbx
	cmp %rbx, %rax
	jne .collatz.2
# (4) <[JUMP], <7>>
	jmp .collatz.7
.collatz.2:
# (5) <[int][MOD], (int)#0, (int)i, 2>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $2, %rcx
	cqo 
	idiv %rcx
	mov %rdx, %rbx # save remainder
	mov %rbx, -16(%rbp)
# (5) <[JUMP_EQ], <3>, (int)#0, 0>
	mov -16(%rbp), %rax
	mov $0, %rbx
	cmp %rbx, %rax
	je .collatz.3
# (5) <[JUMP], <4>>
	jmp .collatz.4
.collatz.3:
# (6) <[int][DIV], (int)i, (int)i, 2>
	mov 16(%rbp), %rax
	mov $2, %rbx
	cqo 
	idiv %rbx
	mov %rax, %rax # save quotient
	mov %rax, 16(%rbp)
.collatz.4:
# (8) <[int][MUL], (int)#0, 3, (int)i>
	mov -16(%rbp), %rax
	mov $3, %rbx
	mov 16(%rbp), %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (8) <[int][ADD], (int)i, (int)#0, 1>
	mov 16(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $1, %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, 16(%rbp)
# (10) <[int][ADD], (int)iters, (int)iters, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (4) <[JUMP], <1>>
	jmp .collatz.1
.collatz.7:
# (13) <[int][RETURN], (int)iters>
	mov -8(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "%d: %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)i at -8(%rbp)
	push $0 # (int)#0 at -16(%rbp)
	push $0 # (int)#1 at -24(%rbp)
.main.0:
# (18) <[int][ASSIGN], (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.1:
# (18) <[JUMP_LT], <2>, (int)i, 100>
	mov -8(%rbp), %rax
	mov $100, %rbx
	cmp %rbx, %rax
	jl .main.2
# (18) <[JUMP], <4>>
	jmp .main.4
.main.2:
# (19) <[int][CALL], (int)#0, collatz, (int)i>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call collatz
	add $8, %rsp
	mov %rax, -16(%rbp)
# (19) <[int][CALL], (int)#1, printf, "%d: %d\n", (int)i, (int)#0>
	lea _string_main.0(%rip), %rdi
	mov -8(%rbp), %rsi
	mov -16(%rbp), %rdx
	mov $0, %rax
	call printf
# (18) <[int][ADD], (int)i, (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (18) <[JUMP], <1>>
	jmp .main.1
.main.4:
# (22) <[int][CALL], (int)#0, collatz, 100>
	push $100
	mov -16(%rbp), %rax
	call collatz
	add $8, %rsp
	mov %rax, -16(%rbp)
# (22) <[int][RETURN], (int)#0>
	mov -16(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
