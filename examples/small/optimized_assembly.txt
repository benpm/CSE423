.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (8) <[JUMP_LT], <5>, 1110, 2>
	mov $1110, %rax
	mov $2, %rbx
	cmp %rbx, %rax
	jl .main.5
# (8) <[JUMP], <6>>
	jmp .main.6
.main.5:
# (9) <[int][RETURN], 35>
	mov $35, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.main.6:
# (11) <[int][RETURN], 124>
	mov $124, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
