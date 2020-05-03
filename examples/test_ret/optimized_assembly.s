.text
.globl funA
.type funA, @function
.data
# FUNCTION funA
.text
funA:
	pushq %rbp
	movq %rsp, %rbp
.funA.0:
# (3) <[int][RETURN], 3>
	movq $3, %rax
# stack size is 8
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl funB
.type funB, @function
.data
# FUNCTION funB
.text
funB:
	pushq %rbp
	movq %rsp, %rbp
.funB.0:
# (8) <[int][RETURN], 4>
	movq $4, %rax
# stack size is 8
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "ret: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
	pushq $0 # (int)#1 at -16(%rbp)
	pushq $0 # (int)#2 at -24(%rbp)
	pushq $0 # (int)#3 at -32(%rbp)
.main.0:
# (13) <[int][CALL], (int)#0, (int)funA>
	movq -8(%rbp), %rax
	call funA
	movq %rax, -8(%rbp)
# (13) <[int][CALL], (int)#1, (int)funB>
	movq -16(%rbp), %rax
	call funB
	movq %rax, -16(%rbp)
# (13) <[int][ADD], (int)#2, (int)#0, (int)#1>
	movq -24(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (13) <[int][CALL], (int)#3, printf, "ret: %d\n", (int)#2>
	leaq _string_main.0(%rip), %rdi
	movq -24(%rbp), %rsi
	movq $0, %rax
	call printf
# (14) <[int][CALL], (int)#0, (int)funA>
	movq -8(%rbp), %rax
	call funA
	movq %rax, -8(%rbp)
# (14) <[int][CALL], (int)#1, (int)funB>
	movq -16(%rbp), %rax
	call funB
	movq %rax, -16(%rbp)
# (14) <[int][ADD], (int)#2, (int)#0, (int)#1>
	movq -24(%rbp), %rax
	movq -8(%rbp), %rbx
	movq -16(%rbp), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (14) <[int][RETURN], (int)#2>
	movq -24(%rbp), %rax
# stack size is 40
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
