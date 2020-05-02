.text
.globl main
.type main, @function
.data
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)foo
.main.0:
# (2) <[int][ASSIGN], (int)foo, 420>
	mov -8(%rbp), %rax
	mov $420, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (3) <[JUMP_GT], <2>, (int)foo, 10>
	mov -8(%rbp), %rax
	mov $10, %rbx
	cmp %rbx, %rax
	jg .main.2
# (3) <[JUMP], <3>>
	jmp .main.3
.main.2:
# (4) <[int][ASSIGN], (int)foo, 19>
	mov -8(%rbp), %rax
	mov $19, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
.main.3:
# (6) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
