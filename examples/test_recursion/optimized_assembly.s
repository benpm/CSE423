.text
.globl refun
.type refun, @function
.data
# FUNCTION refun
# param (int)x at 16(%rbp)
.text
refun:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0 at -8(%rbp)
	push $0 # (int)#1 at -16(%rbp)
.refun.0:
# (2) <[int][ADD], (int)x, (int)x, 3>
	mov 16(%rbp), %rax
	mov $3, %rbx
	add %rax, %rbx
	mov %rbx, %rax
	mov %rax, 16(%rbp)
# (3) <[JUMP_LT], <2>, (int)x, 1239>
	mov 16(%rbp), %rax
	mov $1239, %rbx
	cmp %rbx, %rax
	jl .refun.2
# (3) <[JUMP], <3>>
	jmp .refun.3
.refun.2:
# (4) <[int][MUL], (int)#0, (int)x, 2>
	mov -8(%rbp), %rax
	mov 16(%rbp), %rbx
	mov $2, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -8(%rbp)
# (4) <[int][CALL], (int)#1, refun, (int)#0>
	push -8(%rbp)
	mov -16(%rbp), %rax
	call refun
	add $8, %rsp
	mov %rax, -16(%rbp)
.refun.3:
# (6) <[int][RETURN], (int)x>
	mov 16(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "refun(10): %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0 at -8(%rbp)
	push $0 # (int)#1 at -16(%rbp)
.main.0:
# (11) <[int][CALL], (int)#0, refun, 10>
	push $10
	mov -8(%rbp), %rax
	call refun
	add $8, %rsp
	mov %rax, -8(%rbp)
# (11) <[int][CALL], (int)#1, printf, "refun(10): %d\n", (int)#0>
	lea _string_main.0(%rip), %rdi
	mov -8(%rbp), %rsi
	mov $0, %rax
	call printf
# (12) <[int][CALL], (int)#0, refun, 1>
	push $1
	mov -8(%rbp), %rax
	call refun
	add $8, %rsp
	mov %rax, -8(%rbp)
# (12) <[int][RETURN], (int)#0>
	mov -8(%rbp), %rax
# stack size is 24
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
