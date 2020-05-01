.globl a
.data
.align 8
.type a, @object
.size a, 8
a: .quad 4
.globl b
.data
.align 8
.type b, @object
.size b, 8
b: .quad 5
.globl d
.data
.align 8
.type d, @object
.size d, 8
d: .quad 5
.globl e
.data
.align 8
.type e, @object
.size e, 8
e: .quad 3
.globl f
.data
.align 8
.type f, @object
.size f, 8
f: .quad 5
.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)g
	push $0 # (int)h
	push $0 # (int)#0
.main.0:
# (7) <[int][ASSIGN], (int)g, 3>
	mov -8(%rbp), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (8) <[int][ASSIGN], (int)h, 3>
	mov -16(%rbp), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (9) <[int][ADD], (int)#0, (int)g, (int)h>
	mov -24(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -16(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (9) <[int][RETURN], (int)#0>
	mov -24(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
