// The in-place Maybe update
.text
.globl main
main:
  // needed for movabs
  push   %rbp
  mov    %rsp,%rbp

  // Check if None, and do nothing if so
  testq %rdi, %rdi
  jz .L0

  // Get stack space
  subq $0x10, %rsp

  // Store the object
  mov %rdi, -0x8(%rbp)
  
  // dereference the contained object
  movq (%rdi),%rdi 
  // dummy pointer value
  movabs $0xdeadbeefdeadbeef,%rax
  callq *%rax

  // Retrieve the object
  mov -0x8(%rbp), %rdi

  // Retrieve the object and load in the new value
  movq %rax, (%rdi)
  movq %rdi, %rax

  .L0:
  mov %rdi, %rax
  
  // Free stack space
  addq $0x10, %rsp
  
  // needed for movabs
  pop    %rbp  

  ret
