.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "%d\n"
# FUNCTION main
.text
main:
	push %rbp
	mov %rsp, %rbp
	push $0 # (int)#0
.main.0:
# (8) <[int][CALL], (int)#0, printf, "%d\n", 1110>
	lea _string_main.0(%rip), %rdi
	mov $1110, %rsi
	mov $0, %rax
	call printf
# (9) <[JUMP_LT], <6>, 1110, 2>
	mov $1110, %rax
	mov $2, %rbx
	cmp %rbx, %rax
	jl .main.6
# (9) <[JUMP], <7>>
	jmp .main.7
.main.6:
# (10) <[int][RETURN], 35>
	mov $35, %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.main.7:
# (12) <[int][RETURN], 124>
	mov $124, %rax
# stack size is 16
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
