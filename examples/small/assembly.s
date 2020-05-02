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
	push $0 # (int)a at -8(%rbp)
	push $0 # (int)b at -16(%rbp)
	push $0 # (int)#0 at -24(%rbp)
	push $0 # (int)c at -32(%rbp)
	push $0 # (float)d at -40(%rbp)
.main.0:
# (3) <[int][ASSIGN], (int)a, 42>
	mov -8(%rbp), %rax
	mov $42, %rbx
	mov %rbx, %rax
	mov %rax, -8(%rbp)
# (4) <[int][ASSIGN], (int)b, 89>
	mov -16(%rbp), %rax
	mov $89, %rbx
	mov %rbx, %rax
	mov %rax, -16(%rbp)
# (5) <[int][MUL], (int)#0, (int)b, 12>
	mov -24(%rbp), %rax
	mov -16(%rbp), %rbx
	mov $12, %rcx
	imul %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -24(%rbp)
# (5) <[int][ADD], (int)c, (int)a, (int)#0>
	mov -32(%rbp), %rax
	mov -8(%rbp), %rbx
	mov -24(%rbp), %rcx
	add %rbx, %rcx
	mov %rcx, %rax
	mov %rax, -32(%rbp)
# (6) <[float][MINUS], (float)d, 8.011609>
	mov -40(%rbp), %rax
	mov $8.011609, %rbx
	neg %rbx
	mov %rbx, %rax
	mov %rax, -40(%rbp)
# (8) <[int][CALL], (int)#0, printf, "%d\n", (int)c>
	lea _string_main.0(%rip), %rdi
	mov -32(%rbp), %rsi
	mov $0, %rax
	call printf
# (9) <[JUMP_LT], <6>, (int)c, 2>
	mov -32(%rbp), %rax
	mov $2, %rbx
	cmp %rbx, %rax
	jl .main.6
# (9) <[JUMP], <7>>
	jmp .main.7
.main.6:
# (10) <[int][RETURN], 35>
	mov $35, %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
.main.7:
# (12) <[int][RETURN], 124>
	mov $124, %rax
# stack size is 48
	mov %rbp, %rdx
	sub %rsp, %rdx
	add %rdx, %rsp
	pop %rbp
	ret 
