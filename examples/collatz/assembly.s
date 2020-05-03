.text
.globl collatz
.type collatz, @function
.data
# FUNCTION collatz
# param (int)i at 16(%rbp)
.text
collatz:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)iters at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.collatz.0:
# (3) <[int][ASSIGN], (int)iters, 0>
	movq $0, -8(%rbp)
.collatz.1:
# (4) <[JUMP_NEQ], <2>, (int)i, 1>
	movq 16(%rbp), %rax
	movq $1, %rbx
	cmpq %rbx, %rax
	jne .collatz.2
# (4) <[JUMP], <7>>
	jmp .collatz.7
.collatz.2:
# (5) <[int][MOD], (int)#0, (int)i, 2>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $2, %rcx
	cqo 
	idivq %rcx
	movq %rdx, -16(%rbp) # save remainder
# (5) <[JUMP_EQ], <3>, (int)#0, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	je .collatz.3
# (5) <[JUMP], <4>>
	jmp .collatz.4
.collatz.3:
# (6) <[int][DIV], (int)i, (int)i, 2>
	movq 16(%rbp), %rax
	movq $2, %rbx
	cqo 
	idivq %rbx
	movq %rax, 16(%rbp) # save quotient
# (6) <[JUMP], <5>>
	jmp .collatz.5
.collatz.4:
# (8) <[int][MUL], (int)#0, 3, (int)i>
	movq -16(%rbp), %rax
	movq $3, %rbx
	movq 16(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (8) <[int][ADD], (int)i, (int)#0, 1>
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	movq $1, %rcx
	addq %rbx, %rcx
	movq %rcx, 16(%rbp)
.collatz.5:
# (10) <[int][ADD], (int)iters, (int)iters, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (4) <[JUMP], <1>>
	jmp .collatz.1
.collatz.7:
# (13) <[int][RETURN], (int)iters>
	movq -8(%rbp), %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "%d: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)i at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
	pushq $0 # (int)#1 at -24(%rbp)
.main.0:
# (18) <[int][ASSIGN], (int)i, 1>
	movq $1, -8(%rbp)
.main.1:
# (18) <[JUMP_LT], <2>, (int)i, 100>
	movq -8(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.2
# (18) <[JUMP], <4>>
	jmp .main.4
.main.2:
# (19) <[int][CALL], (int)#0, collatz, (int)i>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call collatz
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (19) <[int][CALL], (int)#1, printf, "%d: %d\n", (int)i, (int)#0>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq -16(%rbp), %rdx
	movq $0, %rax
	call printf
# (18) <[int][ADD], (int)i, (int)i, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (18) <[JUMP], <1>>
	jmp .main.1
.main.4:
# (22) <[int][CALL], (int)#0, collatz, 100>
	pushq $100
	movq -16(%rbp), %rax
	call collatz
	addq $8, %rsp
	movq %rax, -16(%rbp)
# (22) <[int][RETURN], (int)#0>
	movq -16(%rbp), %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
