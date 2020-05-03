.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "Error! Factorial of a negative number doesn't exist.\n"
_string_main.1: .asciz "Factorial of %d = %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)fact at -8(%rbp)
	pushq $0 # (int)n at -16(%rbp)
	pushq $0 # #0 at -24(%rbp)
	pushq $0 # (int)i at -32(%rbp)
	pushq $0 # (int)#0 at -40(%rbp)
.main.0:
# (2) <[int][ASSIGN], (int)fact, 1>
	movq $1, -8(%rbp)
# (2) <[int][ASSIGN], (int)n, 10>
	movq $10, -16(%rbp)
# (3) <[JUMP_LT], <3>, (int)n, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	cmpq %rbx, %rax
	jl .main.3
# (3) <[JUMP], <4>>
	jmp .main.4
.main.3:
# (4) <[CALL], #0, printf, "Error! Factorial of a negative number doesn't exist.\n">
	leaq _string_main.0(%rip), %rdi
	movq $0, %rax
	call printf
# (4) <[JUMP], <9>>
	jmp .main.9
.main.4:
# (6) <[int][ASSIGN], (int)i, 1>
	movq $1, -32(%rbp)
.main.5:
# (6) <[JUMP_LE], <6>, (int)i, (int)n>
	movq -32(%rbp), %rax
	movq -16(%rbp), %rbx
	cmpq %rbx, %rax
	jle .main.6
# (6) <[JUMP], <8>>
	jmp .main.8
.main.6:
# (7) <[int][MUL], (int)fact, (int)fact, (int)i>
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rax, %rbx
	movq %rbx, -8(%rbp)
# (6) <[int][ADD], (int)i, (int)i, 1>
	movq -32(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -32(%rbp)
# (6) <[JUMP], <5>>
	jmp .main.5
.main.8:
# (9) <[int][CALL], (int)#0, printf, "Factorial of %d = %d\n", (int)n, (int)fact>
	leaq _string_main.1(%rip), %rdi
	movq -16(%rbp), %rsi
	movq -8(%rbp), %rdx
	movq $0, %rax
	call printf
.main.9:
# (11) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 48
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
