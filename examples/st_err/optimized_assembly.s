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
.data
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (9) <[int][RETURN], 6>
	mov $6, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
