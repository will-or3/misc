section .data
    x db 12        ; first #
    y db 37       ; second #
    result db 0   ; var to store result
    msg db "the result is: ", 0 ; what gets printed

section .bss 
    res resb 4      ; reserve 4 bytes for string result 

section .text 
    global _start     ;program start

_start:
    ;load numbers into register (this script assumes <99)
    mov al, [x]   ; load # 1 into AL
    add al, [y]   ; load # 2 into AL
    mov [result], al ;store result 

    ;conv to string 
    mov bl, 10
    xor ah, ah  ;clears ah for div
    div bl      ; divs ah by 10
    ; after that, AL= quotient AH= remainder
    add al, '0'    ;convert tens to ASCII
    mov [res], al  ; stores tens digits
    add ah, '0' ;converts first digits to ASCII
    mov [res + 1], ah ;stores it 
    mov byte [res + 2], 0 ;nulls string

    ;print message 
    mov edx, len   ;length of the message
    mov ecx, msg      ; pointer to message
    mov ebx, 1        ; file descripter (stdout)
    mov eax, 4        ; syscall number for sys_write
    int 0x80          ; call kernal

    ;print result 
    mov edx, 2     ;lenth of the result 
    mov ecx, res   ; pointer to the result 
    mov eax, 4     ; syscall
    int 0x80       ; kernal call

    ; exit program 
    mov eax, 1   ;syscall num for sys_exit
    xor ebx, ebx  ;exit code 0 
    int 0x80    ; call kernal 

section .data
len equ $ - msg  ;calc length of message

