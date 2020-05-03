.text
.globl refun
.type refun, @function
.data
# FUNCTION refun
# param (int)x at 16(%rbp)
.text
refun:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
	pushq $0 # (int)#1 at -16(%rbp)
.refun.0:
# (2) <[int][ADD], (int)x, (int)x, 3>
	movq 16(%rbp), %rax
	movq $3, %rbx
	addq %rax, %rbx
	movq %rbx, %rax
	movq %rax, 16(%rbp)
# (3) <[JUMP_LT], <2>, (int)x, 1239>
	movq 16(%rbp), %rax
	movq $1239, %rbx
	cmpq %rbx, %rax
	jl .refun.2
# (3) <[JUMP], <3>>
	jmp .refun.3
.refun.2:
# (4) <[int][MUL], (int)#0, (int)x, 2>
	movq -8(%rbp), %rax
	movq 16(%rbp), %rbx
	movq $2, %rcx
	imulq %rbx, %rcx
	movq %rcx, %rax
	movq %rax, -8(%rbp)
# (4) <[int][CALL], (int)#1, refun, (int)#0>
	pushq -8(%rbp)
	movq -16(%rbp), %rax
	call refun
	addq $8, %rsp
	movq %rax, -16(%rbp)
.refun.3:
# (6) <[int][RETURN], (int)x>
	movq 16(%rbp), %rax
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
_string_main.0: .asciz "refun(10): %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
	pushq $0 # (int)#1 at -16(%rbp)
.main.0:
# (11) <[int][CALL], (int)#0, refun, 10>
	pushq $10
	movq -8(%rbp), %rax
	call refun
	addq $8, %rsp
	movq %rax, -8(%rbp)
# (11) <[int][CALL], (int)#1, printf, "refun(10): %d\n", (int)#0>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq $0, %rax
	call printf
# (12) <[int][CALL], (int)#0, refun, 1>
	pushq $1
	movq -8(%rbp), %rax
	call refun
	addq $8, %rsp
	movq %rax, -8(%rbp)
# (12) <[int][RETURN], (int)#0>
	movq -8(%rbp), %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
