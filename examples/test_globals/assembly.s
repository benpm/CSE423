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
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)#0 at -8(%rbp)
.fun.0:
# (7) <[int][ADD], (int)v, (int)v, 9>
	movq v(%rip), %rax
	movq $9, %rbx
	addq %rax, %rbx
	movq %rbx, v(%rip)
# (8) <[int][ADD], (int)#0, 1, (int)v>
	movq -8(%rbp), %rax
	movq $1, %rbx
	movq v(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (8) <[int][ADD], (int)x, (int)x, (int)#0>
	movq x(%rip), %rax
	movq -8(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, x(%rip)
# (9) <[int][ADD], (int)#0, 3, (int)x>
	movq -8(%rbp), %rax
	movq $3, %rbx
	movq x(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -8(%rbp)
# (9) <[int][ADD], (int)z, (int)z, (int)#0>
	movq z(%rip), %rax
	movq -8(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, z(%rip)
# (10) <[int][RETURN], (int)v>
	movq v(%rip), %rax
# stack size is 16
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "v: %d, x: %d, z: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)i at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
	pushq $0 # (int)#1 at -24(%rbp)
.main.0:
# (15) <[int][ADD], (int)v, (int)v, 2>
	movq v(%rip), %rax
	movq $2, %rbx
	addq %rax, %rbx
	movq %rbx, v(%rip)
# (16) <[int][ASSIGN], (int)x, 3>
	movq $3, x(%rip)
# (17) <[int][ASSIGN], (int)i, 0>
	movq $0, -8(%rbp)
.main.3:
# (17) <[JUMP_LT], <4>, (int)i, 7>
	movq -8(%rbp), %rax
	movq $7, %rbx
	cmpq %rbx, %rax
	jl .main.4
# (17) <[JUMP], <6>>
	jmp .main.6
.main.4:
# (18) <[int][CALL], (int)#0, (int)fun>
	movq -16(%rbp), %rax
	call fun
	movq %rax, -16(%rbp)
# (18) <[int][ADD], (int)x, (int)x, (int)#0>
	movq x(%rip), %rax
	movq -16(%rbp), %rbx
	addq %rax, %rbx
	movq %rbx, x(%rip)
# (17) <[int][ADD], (int)i, (int)i, 1>
	movq -8(%rbp), %rax
	movq $1, %rbx
	addq %rax, %rbx
	movq %rbx, -8(%rbp)
# (17) <[JUMP], <3>>
	jmp .main.3
.main.6:
# (20) <[int][CALL], (int)#0, printf, "v: %d, x: %d, z: %d\n", (int)v, (int)x, (int)z>
	leaq _string_main.0(%rip), %rdi
	movq v(%rip), %rsi
	movq x(%rip), %rdx
	movq z(%rip), %rcx
	movq $0, %rax
	call printf
# (21) <[int][ADD], (int)#0, (int)v, (int)x>
	movq -16(%rbp), %rax
	movq v(%rip), %rbx
	movq x(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -16(%rbp)
# (21) <[int][ADD], (int)#1, (int)#0, (int)z>
	movq -24(%rbp), %rax
	movq -16(%rbp), %rbx
	movq z(%rip), %rcx
	addq %rbx, %rcx
	movq %rcx, -24(%rbp)
# (21) <[int][RETURN], (int)#1>
	movq -24(%rbp), %rax
# stack size is 32
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
