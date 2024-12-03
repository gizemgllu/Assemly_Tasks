; Task 5 - solution_for_grade_7
solution_for_grade_7:
    push ebx
    push ecx
    push edi
    push esi
    mov esi, [esp + 20]
    mov edi, [esp + 16]
    mov ecx, [esp + 12]
row_loop:
    test ecx, ecx
    jz end_rows
    push ecx
    xor eax, eax
    mov edx, [esp + 8]
col_loop:
    test edx, edx
    jz store_result
    mov ebx, [esi]
    test ebx, 1
    jz next
    inc eax
next:
    add esi, 4
    dec edx
    jmp col_loop
store_result:
    mov [edi], eax
    add edi, 4
    pop ecx
    mov edx, [esp + 8]
    shl edx, 2
    sub esi, edx
    dec ecx
    jmp row_loop
end_rows:
    pop esi
    pop edi
    pop ecx
    pop ebx
    ret

; Task 5 - solution_for_grade_9
solution_for_grade_9:
    push ebx
    push ecx
    push edi
    push esi
    mov esi, [esp + 20]
    mov edi, [esp + 16]
    mov ecx, [esp + 12]
row_loop:
    test ecx, ecx
    jz end_rows
    push ecx
    mov edx, [esp + 8]
    mov ebx, -1
    xor eax, eax
col_loop:
    test edx, edx
    jz store_result
    mov eax, [esi]
    cmp eax, 1
    jl next
    cmp ebx, -1
    je set_min
    cmp eax, ebx
    jge next
set_min:
    mov ebx, eax
next:
    add esi, 4
    dec edx
    jmp col_loop
store_result:
    mov [edi], ebx
    add edi, 4
    mov edx, [esp + 8]
    shl edx, 2
    sub esi, edx
    add esi, edx
    pop ecx
    dec ecx
    jmp row_loop
end_rows:
    pop esi
    pop edi
    pop ecx
    pop ebx
    ret
