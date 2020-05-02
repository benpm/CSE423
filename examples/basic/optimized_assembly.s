.text
.globl main
.type main, @function
.data
_string.0: .asciz "Foo val: %d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0
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
# (6) <[int][CALL], (int)#0, printf, "Foo val: %d\n", 19>
	mov $0, %rax
	mov $1, %rsi
	lea _string.0(%rip), %rdi
	mov $19, %rdx
	call printf
# (7) <[int][RETURN], 0>
	mov $0, %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
