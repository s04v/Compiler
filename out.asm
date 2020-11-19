mov eax, 10
mov DWORD PTR [rbp - 4], eax
mov eax, DWORD PTR [rbp -4]
mov ebx, 20
mul eax, ebx
