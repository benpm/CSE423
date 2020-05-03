.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "x: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)x at -8(%rbp)
	pushq $0 # (int)i at -16(%rbp)
	pushq $0 # (int)#0 at -24(%rbp)
	pushq $0 # (int)j at -32(%rbp)
	pushq $0 # (int)z at -40(%rbp)
.main.0:
# (3) <[int][ASSIGN], (int)x, 3>
	movq $3, -8(%rbp)
# (4) <[int][ASSIGN], (int)i, 0>
	movq $0, -16(%rbp)
.main.2:
# (4) <[JUMP_LT], <3>, (int)i, 13>
	movq -16(%rbp), %rax
	movq $13, %rbx
	cmpq %rbx, %rax
	jl .main.3
# (4) <[JUMP], <14>>
	jmp .main.14
.main.3:
# (5) <[int][MUL], (int)#0, (int)x, (int)i>
	movq -24(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -16(%rbp), %rcx
	imulq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (5) <[int][ADD], (int)x, (int)x, (int)#0>
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (6) <[int][ASSIGN], (int)j, 0>
	movq $0, -32(%rbp)
.main.5:
# (6) <[JUMP_LT], <6>, (int)j, 56>
	movq -32(%rbp), %rax
	movq $56, %rbx
	cmpq %rbx, %rax
	jl .main.6
# (6) <[JUMP], <13>>
	jmp .main.13
.main.6:
# (7) <[int][ASSIGN], (int)z, 2>
	movq $2, -40(%rbp)
# (8) <[int][MINUS], (int)x, (int)x, (int)j>
	movq -8(%rbp), %rax
	negq %rax
	movq %rax, -8(%rbp)
.main.8:
# (9) <[JUMP_LT], <9>, (int)z, 100>
	movq -40(%rbp), %rax
	movq $100, %rbx
	cmpq %rbx, %rax
	jl .main.9
# (9) <[JUMP], <11>>
	jmp .main.11
.main.9:
# (10) <[int][MUL], (int)#0, (int)x, (int)x>
	movq -24(%rbp), %rax
	movq -8(%rbp), %rbx
	imulq %rbx, %rbx
	movq %rbx, -24(%rbp)
# (10) <[int][ADD], (int)z, (int)z, (int)#0>
	movq -40(%rbp), %rax
	movq -24(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -40(%rbp)
# (9) <[JUMP], <8>>
	jmp .main.8
.main.11:
# (12) <[int][MOD], (int)#0, (int)z, (int)j>
	movq -40(%rbp), %rax
	movq -24(%rbp), %rbx
	movq -32(%rbp), %rcx
	cqo 
	idivq %rcx
	movq %rdx, -24(%rbp) # save remainder
# (12) <[int][ADD], (int)x, (int)x, (int)#0>
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (6) <[int][ADD], (int)j, (int)j, 2>
	movq -32(%rbp), %rax
	movq $2, %rbx
	addq %rax, %rbx
	movq %rbx, -32(%rbp)
# (6) <[JUMP], <5>>
	jmp .main.5
.main.13:
# (4) <[int][ADD], (int)i, (int)i, 1>
	movq -16(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -16(%rbp)
# (4) <[JUMP], <2>>
	jmp .main.2
.main.14:
# (16) <[int][CALL], (int)#0, printf, "x: %d\n", (int)x>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq $0, %rax
	call printf
# (18) <[int][RETURN], (int)x>
	movq -8(%rbp), %rax
# stack size is 48
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
