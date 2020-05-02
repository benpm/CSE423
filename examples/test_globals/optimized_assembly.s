.globl v
.data
.align 8
.type v, @object
.size v, 8
v: .quad 7
.globl x
.data
.align 8
.type x, @object
.size x, 8
x: .quad 0
.globl z
.data
.align 8
.type z, @object
.size z, 8
z: .quad 13
.text
.globl fun
.type fun, @function
.data
# FUNCTION fun
.text
fun:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0
.fun.0:
# (7) <[int][ADD], (int)v, (int)v, 9>
	mov v(%rip), %rax
	mov $9, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, v(%rip)
# (8) <[int][ADD], (int)#0, 1, (int)v>
	mov -8(%rbp), %rax
	mov $1, %rbx
	mov v(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (8) <[int][ADD], (int)x, (int)x, (int)#0>
	mov x(%rip), %rax
	mov -8(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, x(%rip)
# (9) <[int][ADD], (int)#0, 3, (int)x>
	mov -8(%rbp), %rax
	mov $3, %rbx
	mov x(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (9) <[int][ADD], (int)z, (int)z, (int)#0>
	mov z(%rip), %rax
	mov -8(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, z(%rip)
# (10) <[int][RETURN], (int)v>
	mov v(%rip), %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
.data
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)i
	push $0 # (int)#0
	push $0 # (int)#1
.main.0:
# (15) <[int][ADD], (int)v, (int)v, 2>
	mov v(%rip), %rax
	mov $2, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, v(%rip)
# (16) <[int][ASSIGN], (int)x, 3>
	mov x(%rip), %rax
	mov $3, %rbx
	mov %rbx, %rax
	mov %rax, x(%rip)
# (17) <[int][ASSIGN], (int)i, 0>
	mov -8(%rbp), %rax
	mov $0, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.3:
# (17) <[JUMP_LT], <4>, (int)i, 7>
	mov -8(%rbp), %rax
	mov $7, %rbx
	cmp %rbx, %rax
	jl .main.4
# (17) <[JUMP], <6>>
	jmp .main.6
.main.4:
# (18) <[int][CALL], (int)#0, (int)fun>
	mov -16(%rbp), %rax
	call fun
	mov %rax, -16(%rbp)
# (18) <[int][ADD], (int)x, (int)x, (int)#0>
	mov x(%rip), %rax
	mov -16(%rbp), %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, x(%rip)
# (17) <[int][ADD], (int)i, (int)i, 1>
	mov -8(%rbp), %rax
	mov $1, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (17) <[JUMP], <3>>
	jmp .main.3
.main.6:
# (20) <[int][ADD], (int)#0, (int)v, (int)x>
	mov -16(%rbp), %rax
	mov v(%rip), %rbx
	mov x(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -16(%rbp)
# (20) <[int][ADD], (int)#1, (int)#0, (int)z>
	mov -24(%rbp), %rax
	mov -16(%rbp), %rbx
	mov z(%rip), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (20) <[int][RETURN], (int)#1>
	mov -24(%rbp), %rax
# stack size is 32
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
