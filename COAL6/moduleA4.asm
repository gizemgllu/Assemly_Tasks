; Task 4 - solution_for_grade_6
solution_for_grade_6:
    push ebx
    push ecx
    push esi
    xor eax, eax
    xor ecx, ecx
    mov esi, [esp + 12] 
loop_start_A:
    lodsb
    test al, al
    jz loop_end_A
    cmp al, '0'
    jl loop_start_A
    cmp al, '9'
    jg loop_start_A
    sub al, '0'
    add ecx, eax
    jmp loop_start_A
loop_end_A:
    mov eax, ecx
    pop esi
    pop ecx
    pop ebx
    ret

; Task 4 - solution_for_grade_9
solution_for_grade_9:
    push ebx
    push edi
    push esi
    mov esi, [esp + 16]
    mov edi, [esp + 12]
    mov al, 0
    mov ebx, 0
loop_start_B:
    lodsb
    test al, al
    jz loop_end_B
    cmp al, ' '
    jne copy_char
    cmp ebx, 1
    je loop_start_B
    mov al, '_'
    stosb
    mov ebx, 1
    jmp loop_start_B
copy_char:
    stosb
    mov ebx, 0
    jmp loop_start_B
loop_end_B:
    stosb
    pop esi
    pop edi
    pop ebx
    ret
