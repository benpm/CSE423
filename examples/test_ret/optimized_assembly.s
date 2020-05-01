.text
.globl funA
.type funA, @function
# FUNCTION funA
funA:
	push %rbp
	mov %rsp, %rbp
.funA.0:
# (3) <[int][RETURN], 3>
	mov $3, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl funB
.type funB, @function
# FUNCTION funB
funB:
	push %rbp
	mov %rsp, %rbp
.funB.0:
# (8) <[int][RETURN], 4>
	mov $4, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0
	push $0 # (int)#1
	push $0 # (int)#2
.main.0:
# (13) <[int][CALL], (int)#0, (int)funA>
	mov -8(%rbp), %rax
	call funA
	mov %rax, -8(%rbp)
# (13) <[int][CALL], (int)#1, (int)funB>
	mov -16(%rbp), %rax
	call funB
	mov %rax, -16(%rbp)
# (13) <[int][ADD], (int)#2, (int)#0, (int)#1>
	mov -24(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (13) <[int][RETURN], (int)#2>
	mov -24(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
