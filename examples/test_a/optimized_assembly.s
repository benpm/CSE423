.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "i: %d, j: %d, k: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)i at -8(%rbp)
	pushq $0 # (int)j at -16(%rbp)
	pushq $0 # (int)#0 at -24(%rbp)
.main.0:
# (2) <[int][ASSIGN], (int)i, 0>
	movq -8(%rbp), %rax
	movq $0, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (3) <[int][ASSIGN], (int)j, 0>
	movq -16(%rbp), %rax
	movq $0, %rbx
	movq %rbx, %rax
	movq %rax, -16(%rbp)
# (5) <[int][ADD], (int)i, (int)i, 10>
	movq -8(%rbp), %rax
	movq $10, %rbx
	addq %rax, %rbx
	movq %rbx, %rax
	movq %rax, -8(%rbp)
# (6) <[int][ADD], (int)j, (int)i, 7>
	movq -16(%rbp), %rax
	movq -8(%rbp), %rbx
	movq $7, %rcx
	addq %rbx, %rcx
	movq %rcx, %rax
	movq %rax, -16(%rbp)
# (9) <[int][CALL], (int)#0, printf, "i: %d, j: %d, k: %d\n", (int)i, (int)j, 24>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq -16(%rbp), %rdx
	movq $24, %rcx
	movq $0, %rax
	call printf
# (11) <[int][RETURN], (int)i>
	movq -8(%rbp), %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
