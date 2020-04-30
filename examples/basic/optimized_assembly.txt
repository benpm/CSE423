.text
.globl main
.type main, @function
# FUNCTION main
main:
	push %rbp
	mov %rsp, %rbp
.main.0:
# (3) <[JUMP_GT], <2>, 420, 10>
	mov $420, %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jg .main.2
# (3) <[JUMP], <3>>
	jmp .main.3
.main.2:
.main.3:
# (6) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 8
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
