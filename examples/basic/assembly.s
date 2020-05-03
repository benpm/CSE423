.text
.globl main
.type main, @function
.data
_string_main.0: .asciz "Foo val: %d\n"
# FUNCTION main
.text
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq $0 # (int)foo at -8(%rbp)
	pushq $0 # (int)#0 at -16(%rbp)
.main.0:
# (2) <[int][ASSIGN], (int)foo, 420>
	movq $420, -8(%rbp)
# (3) <[JUMP_GT], <2>, (int)foo, 10>
	movq -8(%rbp), %rax
	movq $10, %rbx
	cmpq %rbx, %rax
	jg .main.2
# (3) <[JUMP], <3>>
	jmp .main.3
.main.2:
# (4) <[int][ASSIGN], (int)foo, 19>
	movq $19, -8(%rbp)
.main.3:
# (6) <[int][CALL], (int)#0, printf, "Foo val: %d\n", (int)foo>
	leaq _string_main.0(%rip), %rdi
	movq -8(%rbp), %rsi
	movq $0, %rax
	call printf
# (7) <[int][RETURN], 0>
	movq $0, %rax
# stack size is 24
	movq %rbp, %rdx
	subq %rsp, %rdx
	addq %rdx, %rsp
	popq %rbp
	ret 
