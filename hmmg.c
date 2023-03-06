//gcc hmmg.c -o hmmg.asm -S -masm=intel -fno-asynchronous-unwind-tables
//gcc hmmg.c -o hmmg -masm=intel
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* binConv(int n, int len);
int main(int argc,char *argv[])
{
    if (argc!=3)
    {
        printf("ERRO Opcao invalida.\n");
        exit(1);
    }   
    FILE *init,*far;
	unsigned short adq;
    char x1 = 0, x2 = 0, x4 = 0, x8 = 0;
    char z = 0, g = 0, aux[5];
    char refr[100];
    strcpy(refr, argv[1]);
    strcpy(aux, argv[2]);  
    strcat(refr,".wham"); 
    if(aux[0]=='-' && aux[1]=='w'){
        if((init = fopen(argv[1],"rb")) == NULL){
            printf("\t\tERRO Impossviel abrir arquivo %s.\n",argv[1]);
        }else if ((far = fopen(refr,"wb")) == NULL){
            printf("\t\tERRO Impossivel abrir este arquivo.\n");
        }else{
            printf("\n\tgerando Hamming...\n");
            while(feof(init) == 0)
            {
                adq = 0;
                fread(&z, 1, 1, init);
                asm("mov al, %[word];"
                
                	"mov bl, al;"
                	"shr bl, 1;"
                	"and bl, 1;"
                
                	"mov cl, al;"
                	"shr cl, 2;"
                	"and cl, 1;"
                	
                	"mov dl, al;"
                    "shr dl, 3;"
                    "and dl, 1;"
                    
                    "mov r8b, al;"
                    "shr r8b, 4;"
                    "and r8b, 1;"
                    
                    "mov r9b, al;"
                    "shr r9b, 5;"
                    "and r9b, 1;"
                    
                    "mov r10b, al;"
                    "shr r10b, 6;"
                    "and r10b, 1;"
                    
                    "mov r11b, al;"
                    "shr r11b, 7;"
                    "and r11b, 1;"
                    
                    "and al, 1;"
                    
                    "mov r13b, al;"
                    "xor r13b, bl;"
                    "xor r13b, dl;"
                    "xor r13b, r8b;"
                    "xor r13b, r10b;"
                    "mov %[x1], r13b;"
                    
                    "xor r13b, r13b;"
                    
                    "mov r13b, al;"
                    "xor r13b, cl;"
                    "xor r13b, dl;"
                    "xor r13b, r9b;"
                    "xor r13b, r10b;"
                    "mov %[x2], r13b;"
                    
                    "xor r13b, r13b;"
                    
                    "mov r13b, bl;"
                    "xor r13b, cl;"
                    "xor r13b, dl;"
                    "xor r13b, r11b;"
                    "mov %[x4], r13b;"
                    
                    "xor  r13b, r13b;"
                    
                    "mov r13b, r8b;"
                    "xor r13b, r9b;"
                    "xor r13b, r10b;"
                    "xor r13b, r11b;"
                    "mov %[x8], r13b;"
                    
                    "xor r15, r15;"
                    "xor r15b, al;"
                    "xor r15b, bl;"
                    "xor r15b, cl;"
                    "xor r15b, dl;"
                    "xor r15b, r8b;"
                    "xor r15b, r9b;"
                    "xor r15b, r10b;"
                    "xor r15b, r11b;"
                    "xor r15b, %[x1];"
                    "xor r15b, %[x2];"
                    "xor r15b, %[x4];"
                    "xor r15b, %[x8];"

                    "xor r13w, r13w;"

                    "and r11w, 1;"
                    "mov r13w, r11w;"
                    "shl r13w, 1;"
                    "and r10w, 1;"
                    "mov r14w, r10w;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and r9w, 1;"
                    "mov r14w, r9w;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and r8w, 1;"
                    "mov r14w, r8w;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "mov r14b, %[x8];"
                    "and r14w, 1;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and dx, 1;"
                    "mov r14w, dx;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and cx, 1;"
                    "mov r14w, cx;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and bx, 1;"
                    "mov r14w, bx;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "mov r14b, %[x4];"
                    "and r14w, 1;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "and ax, 1;"
                    "mov r14w, ax;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "mov r14b, %[x2];"
                    "and r14w, 1;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    "mov r14b, %[x1];"
                    "and r14w, 1;"
                    "or r13w, r14w;"
                    "shl r13w, 1;"
                    
                    "or r13w, r15w;"
                   
					"mov %[k], r13w;"
                    : 
                    : [word] "m" (z), [x1] "m" (x1), [x2] "m" (x2), [x4] "m" (x4), [x8] "m" (x8), [g] "m" (g), [k] "m" (adq)
                    : "cc", "memory", "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
                );
                if(feof(init) == 0){
                    fwrite(&adq,1,sizeof(adq),far);
                    //char* binary = binConv(adq, 16);
                    //printf("%s\n",binary);
                }
            }
            fclose(init);
            fclose(far);
            printf("\n\tgerado...\n\n");
        }
    }
    if(aux[0]=='-' && aux[1]=='r'){   
        FILE *fil;
        char x01 = 0, x02 = 0, x04 = 0, x08 = 0, x1 = 0, x2 = 0, x4 = 0, x8 = 0, c1 = 0, c2 = 0, c4 = 0, c8 = 0;
        char rr1 = 0, rr2 = 0, rr4 = 0, rr8 = 0, pg = 0, gd = 0, gn = 0; 
        long long int opc2 = 0, opc1 = 0, opc = 0, teste2 = 0, teste3 = 0, teste4 = 0;
        char teste = 0;
        strcpy(refr, argv[1]);
        int o = strlen(refr);
        char det;
        printf("Ver detalhes s/n ? ");
        scanf("%s",&det);
        for(short i = strlen(refr); i >= o - 5;){
            refr[i]='\0';
            i--;
        }
        if((init = fopen(argv[1],"rb")) == NULL){
            printf("\t\tERRO Impossviel abrir arquivo %s.\n",argv[1]);
            exit(1);
        }else if ((far = fopen(refr,"wb")) == NULL){
            printf("\t\tERRO Impossivel abrir este arquivo .\n");
            exit(1);
        }else if ((fil = fopen("fil","wb")) == NULL){
            printf("\t\tERRO Impossivel abrir este arquivo temporario.\n");
            exit(1);
        }else{
            printf("\n\tanalisando...\n\n");
            while(feof(init) == 0){
                adq = 0;
                fread(&adq, sizeof(adq), 1, init);
                if(feof(init)) break;
                asm("mov ax, %[b];"
                    "mov %[teste4], rax;"
                    "mov bx, ax;"   
                    "mov cx, ax;"   
                    "mov dx, ax;" 
                    "mov r8w, ax;"  
                    "mov r9w, ax;" 
                    "mov r10w, ax;" 
                    "mov r11w, ax;" 
                    
                    "mov r12w, ax;"
                    "mov r13w, ax;"
                    "mov r14w, ax;"
                    "mov r15w, ax;"
                    
                    "mov %[opc], 0;"
                    "mov %[opc1], 0;"
                    
                    "shr ax, 3;"
                    "and ax, 1;" /*M1  ax*/
                    "shr bx, 5;"
                    "and bx, 1;" /*M2  bx*/
                    "shr cx, 6;" 
                    "and cx, 1;" /*M3  cx*/
                    "shr dx, 7;"
                    "and dx, 1;"  /*M4  dx*/
                    "shr r8w, 9;"
                    "and r8w, 1;"  /*M5  r8w*/
                    "shr r9w, 10;"
                    "and r9w, 1;" /*M6  r9w*/
                    "shr r10w, 11;"
                    "and r10w, 1;" /*M7  r10w*/
                    "shr r11W, 12;"
                    "and r11W, 1;" /*M8  r11w*/
                    
                    "shr r12w, 1;"
                    "and r12w, 1;"
                    "mov %[x1], r12b;" /*x1*/
                    "mov %[x01], r12b;"
                    
                    "shr r13w, 2;"
                    "and r13w, 1;"
                    "mov %[x2], r13b;" /*x2*/
                    "mov %[x02], r13b;"
                    
                    "shr r14w, 4;"
                    "and r14w, 1;"
                    "mov %[x4], r14b;" /*x4*/
                    "mov %[x04], r14b;"
                    
                    "shr r15w, 8;"
                    "and r15w, 1;"
                    "mov %[x8], r15b;" /*x8*/
                    "mov %[x08], r15b;"
                    
                    "xor r14, r14;"
                    "mov r14w, %[b];"
                    "and r14w, 1;"
                    "mov %[gd], r14b;"      /*G da palavra desmontada*/
                    
                    
                    /*C8' C4' C2' C1' -> cacl*/
                    "xor r14, r14;"
                    "xor r14b, al;"  /*M1*/
                    "xor r14b, bl;"  /*M2*/
                    "xor r14b, dl;"  /*M4*/
                    "xor r14b, r8b;"  /*M5*/
                    "xor r14b, r10b;"  /*M7*/
                    "mov %[c1], r14b;"
                    "xor r14b, %[x1];" 
                    "mov %[rr1], r14b;" /*xC1'*/
                     
                    "xor r14, r14;"
                    "xor r14b, al;" /*M1*/
                    "xor r14b, cl;" /*M3*/
                    "xor r14b, dl;"  /*M4*/
                    "xor r14b, r9b;"  /*M6*/
                    "xor r14b, r10b;" /*M7*/
                    "mov %[c2], r14b;"
                    "xor r14b, %[x2];"
                    "mov %[rr2], r14b;" /*xC2'*/
                    
                    "xor r14, r14;"
                    "xor r14b, bl;"  /*M2*/
                    "xor r14b, cl;"  /*M3*/
                    "xor r14b, dl;"  /*M4*/
                    "xor r14b, r11b;" /*M8*/
                    "mov %[c4], r14b;"
                    "xor r14b, %[x4];"
                    "mov %[rr4], r14b;" /*xC4'*/
                    
                    "xor r14, r14;"
                    "xor r14b, r8b;" /*M5*/
                    "xor r14b, r9b;" /*M6*/ 
                    "xor r14b, r10b;" /*M7*/
                    "xor r14b, r11b;" /*M8*/
                    "mov %[c8], r14b;"
                    "xor r14b, %[x8];"
                    "mov %[rr8], r14b;" /*xC8'*/
                    
                    "xor r13, r13;"
                    "xor r13b, al;"
                    "xor r13b, bl;"
                    "xor r13b, cl;"
                    "xor r13b, dl;"
                    "xor r13b, r8b;"
                    "xor r13b, r9b;"
                    "xor r13b, r10b;"
                    "xor r13b, r11b;"
                    "xor r13b, %[c1];"
                    "xor r13b, %[c2];"
                    "xor r13b, %[c4];"
                    "xor r13b, %[c8];"
                   
                    "mov %[pg], r13b;" /*xG'*/
                    
                    "xor r15, r15;"
                    "xor r14, r14;"
                    
                    "mov r15w, r11w;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, r10w;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, r9w;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, r8w;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15b, %[c8];"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, dx;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, cx;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, bx;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15b, %[c4];"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, ax;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15b, %[c2];"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15b, %[c1];"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    "shl r14w, 1;"
                    
                    "mov r15w, r13w;"
                    "and r15w, 1;"
                    "or r14w, r15w;"
                    
                    "xor r15, r15;"
                    "mov r15w, r14w;"
                    "mov %[teste3], r15;" /*word*/
                    
                    "xor r13, r13;"
                    "or r13b, %[rr8];"
                    "shl r13b, 1;"
                    "or r13b, %[rr4];"
                    "shl r13b, 1;"
                    "or r13b, %[rr2];"
                    "shl r13b, 1;"
                    "or r13b, %[rr1];"
                    "mov %[teste], r13b;"
                    
                    "xor r14, r14;"
                    
                    /*-----testes-------*/
                    "cmp r13b, 0;"
                    "je Mcorreto;"
                    "jne naoZero;"
                               
                    "naoZero:"
                    "inc %[opc2];"
                    "cmp r13b, 12;"
                    "jle Mincorreto;"   /*<--- M incorreto*/
                    "jg Sindrome;"  /*<--- Sindrome > m*/
                      
                    "Mcorreto:" 
                    "jmp fimF;"
                    
                    "Mincorreto:"
                    "inc %[opc2];"
                    "jmp identErro;"
                      
                    "Sindrome:"
                    "inc %[opc2];"
                    "add %[opc], 40;"
                    "jmp fimF;"
                      
                    "identErro:"
                    "inc %[opc2];"
                    "cmp r13b, 0;"
                    "je fimF;"
                    "cmp r13b, 1;"
                    "je erro1;"
                    "cmp r13b, 2;"
                    "je erro2;"
                    "cmp r13b, 3;"
                    "je erro3;"
                    "cmp r13b, 4;"
                    "je erro4;"
                    "cmp r13b, 5;"
                    "je erro5;"
                    "cmp r13b, 6;"
                    "je erro6;"
                    "cmp r13b, 7;"
                    "je erro7;"
                    "cmp r13b, 8;"
                    "je erro8;"
                    "cmp r13b, 9;"
                    "je erro9;"
                    "cmp r13b, 10;"
                    "je erro10;"
                    "cmp r13b, 11;"
                    "je erro11;"
                    "cmp r13b, 12;"
                    "je erro12;"
                    
                    "erro1:"
                    "add %[opc], 1;"
                    "mov r14w, %[b];"
                    "sar r14w, 1;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov %[x01], r14b;"
                    "and %[x01], 1;"
                    "jmp continua;"
                    
                    "erro2:"
                    "add %[opc], 2;"
                    "mov r14w, %[b];"
                    "sar r14w, 2;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov %[x02], r14b;"
                    "and %[x02], 1;"
                    "jmp continua;"
                    
                    "erro3:"
                    "add %[opc], 3;"
                    "inc %[opc];"
                    "mov r14w, %[b];"
                    "sar r14w, 3;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov ax, r14w;"
                    "and ax, 1;"
                    "jmp continua;"
                    
                    "erro4:"
                    "add %[opc], 4;"
                    "mov r14w, %[b];"
                    "sar r14w, 4;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov %[x04], r14b;"
                    "and %[x04], 1;"
                    "jmp continua;"
                    
                    "erro5:"
                    "add %[opc], 5;"
                    "mov r14w, %[b];"
                    "sar r14w, 5;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov bx, r14w;"
                    "and bx, 1;"
                    "jmp continua;"
                    
                    "erro6:"
                    "add %[opc], 6;"
                    "mov r14w, %[b];"
                    "sar r14w, 6;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov cx, r14w;"
                    "and cx, 1;"
                    "jmp continua;"
                    
                    "erro7:"
                    "add %[opc], 7;"
                    "mov r14w, %[b];"
                    "sar r14w, 7;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov dx, r14w;"
                    "and dx, 1;"
                    "jmp continua;"
                    
                    "erro8:"
                    "add %[opc], 8;"
                    "mov r14w, %[b];"
                    "sar r14w, 8;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov %[x08], r14b;"
                    "and %[x08], 1;"
                    "jmp continua;"
                    
                    "erro9:"
                    "add %[opc], 9;"
                    "mov r14w, %[b];"
                    "sar r14w, 9;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov r8w, r14w;"
                    "and r8w, 1;"
                    "jmp continua;"
                    
                    "erro10:"
                    "add %[opc], 10;"
                    "mov r14w, %[b];"
                    "sar r14w, 10;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov r9w, r14w;"
                    "and r9w, 1;"
                    "jmp continua;"
                    
                    "erro11:"
                    "add %[opc], 11;"
                    "mov r14w, %[b];"
                    "sar r14w, 11;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov r10w, r14w;"
                    "and r10w, 1;"
                    "jmp continua;"
                    
                    "erro12:"
                    "add %[opc], 12;"
                    "mov r14w, %[b];"
                    "sar r14w, 12;"
                    "and r14w, 1;"
                    "or r14w, 0xfffe;"
                    "not r14w;"
                    "mov r11w, r14w;"
                    "and r11w, 1;"
                    
                    "continua:"
                    "xor r14, r14;"
                    "or r14w, r11w;"
                    "shl r14w, 1;"
                    "or r14w, r10w;"
                    "shl r14w, 1;"
                    "or r14w, r9w;"
                    "shl r14w, 1;"
                    "or r14w, r8w;"
                    "shl r14w, 1;"
                    "xor r12, r12;"
                    "mov r12b, %[x08];"
                    "or r14w, r12w;"
                    "shl r14w, 1;"
                    "or r14w, dx;"
                    "shl r14w, 1;"
                    "or r14w, cx;"
                    "shl r14w, 1;"
                    "or r14w, bx;"
                    "shl r14w, 1;"
                    "xor r12, r12;"
                    "mov r12b, %[x04];"
                    "or r14w, r12w;"
                    "shl r14w, 1;"
                    "or r14w, ax;"
                    "shl r14w, 1;"
                    "xor r12, r12;"
                    "mov r12b, %[x02];"
                    "or r14w, r12w;"
                    "shl r14w, 1;"
                    "xor r12, r12;"
                    "mov r12b, %[x01];"
                    "or r14w, r12w;"
                    "shl r14w, 1;"
                    "xor r12, r12;"
                    
                    "xor r13, r13;"
                    "xor r13b, al;"
                    "xor r13b, bl;"
                    "xor r13b, cl;"
                    "xor r13b, dl;"
                    "xor r13b, r8b;"
                    "xor r13b, r9b;"
                    "xor r13b, r10b;"
                    "xor r13b, r11b;"
                    "xor r13b, %[x01];"
                    "xor r13b, %[x02];"
                    "xor r13b, %[x04];"
                    "xor r13b, %[x08];"
                    
                    "and r13w, 1;"
                    "xor r14w, r13w;" /*palavra arrumada com G novo*/
                    "mov %[gn], r13b;" /*G''*/
                    
                    "mov %[teste2], r14;"
                    
                    "cmp r13b, %[gd];"
                    "je palavraBoa;" 
                    "jne rejeitado;"
                    
                    "rejeitado:"
                    "inc %[opc2];"
                    "mov %[opc], 0;"
                    "add %[opc], 30;" /*<-- erro duplo*/
                    "jmp fimF;"
                    
                    "palavraBoa:"
                    "inc %[opc2];"
                    "add %[opc1], 1;"
                    "mov %[b], r14w;"
                    
                    "fimF:"

                    : 
                    : [x1] "m" (x1), [x2] "m" (x2), [x4] "m" (x4), [x8] "m" (x8), [g] "m" (g), [b] "m" (adq), [rr1] "m" (rr1), [rr2] "m" (rr2), [rr4] "m" (rr4), [rr8] "m" (rr8), [pg] "m" (pg), [opc] "m" (opc), [gn] "m" (gn), [gd] "m" (gd), [teste] "m" (teste), [c1] "m" (c1), [c2] "m" (c2), [c4] "m" (c4), [c8] "m" (c8), [teste2] "m" (teste2), [teste3] "m" (teste3), [teste4] "m" (teste4), [x01] "m" (x01), [x02] "m" (x02), [x04] "m" (x04), [x08] "m" (x08), [opc1] "m" (opc1), [opc2] "m" (opc2)
                    : "cc", "memory","rax","rbx","rcx","rdx","r8","r9","r10","r11","r12","r13","r14","r15"
                );
				if(feof(init) == 0){
					fwrite(&adq,sizeof(adq),1,far);
					if(det == 's'){
						char* binary = binConv(adq, 16);
						printf("%s\n",binary);
						
				        puts("\trr1'");
						binary = binConv(rr1, 16);
						printf("%s\n",binary);
						
						puts("\trr2'");
						binary = binConv(rr2, 16);
						printf("%s\n",binary);
						
						puts("\trr4'");
						binary = binConv(rr4, 16);
						printf("%s\n",binary);
						
						puts("\trr8'");
						binary = binConv(rr8, 16);
						printf("%s\n",binary);
						
				        puts("\tc1");
						binary = binConv(c1, 16);
						printf("%s\n",binary);
						
						puts("\tc2");
						binary = binConv(c2, 16);
						printf("%s\n",binary);
						
						puts("\tc4");
						binary = binConv(c4, 16);
						printf("%s\n",binary);
						
						puts("\tc8");
						binary = binConv(c8, 16);
						printf("%s\n",binary);
						
						puts("\tx1");
						binary = binConv(x1, 16);
						printf("%s\n",binary);
						
						puts("\tx2");
						binary = binConv(x2, 16);
						printf("%s\n",binary);
						
						puts("\tx4");
						binary = binConv(x4, 16);
						printf("%s\n",binary);
											
						puts("\tx8");
						binary = binConv(x8, 16);
						printf("%s\n",binary);
						
						puts("\tG''");
						binary = binConv(gn, 16);
						printf("%s\n",binary);
						
						puts("\tG'");
						binary = binConv(pg, 16);
						printf("%s\n",binary);
						
						puts("\tG");
						binary = binConv(gd, 16);
						printf("%s\n",binary);
						
						/*puts("  antWord");
						binary = binConv(teste3, 16);
						printf("%s\n",binary);*/
						puts("");
						puts("    Opc erro");
						binary = binConv(opc, 16);
						printf("%s\n",binary);
						puts("");
						puts("    Sindrome");
						binary = binConv(teste, 16);
						printf("%s\n",binary);
						puts("    pavalra inical b");
						binary = binConv(teste4, 16);
						printf("%s\n",binary);
						puts("    palavra arrumada r14w");
						binary = binConv(teste2, 16);
						printf("%s\n",binary);
						puts("    palavra re monstada r15w");
						binary = binConv(teste3, 16);
						printf("%s\n",binary);
						puts("----------------------------------------------------------------------------");
						puts("");
	                }
	                switch(opc){
						case 40:
							puts("  Sindrome > M, regeitado");
							break;
						case 30:
							puts("  Erro duplo");
							break;
						case 1:
							puts("  Erro no bit 1");
							break;
						case 2:
							puts("  Erro no bit 2");
							break;
						case 3:
							puts("  Erro no bit 3");
							break;
						case 4:
							puts("  Erro no bit 4");
							break;
						case 5:
							puts("  Erro no bit 5");
							break;
						case 6:
							puts("  Erro no bit 6");
							break;
						case 7:
							puts("  Erro no bit 7");
							break;
						case 8:
							puts("  Erro no bit 8");
							break;
						case 9: 
							puts("  Erro no bit 9");
							break;
						case 10:
							puts("  Erro no bit 10");
							break;
						case 11:
							puts("  Erro no bit 11");
							break;
						case 12:
							puts("  Erro no bit 12");
							break;	
						}
            	}
            if (opc1 == 1){ puts(""); printf("  Corrigido bit %lld com sucesso\n\n\n", opc);} 
            
            } 
        }if (opc2 == 0 && (feof(init) == 1)){ puts(""); puts("  Não houve erros"); puts("");} 
        fclose(fil);
        remove("fil");
        fclose(init);
        fclose(far);
        printf("\n\tfeito...\n\n");
        
    }
    return 0;   
}
char* binConv(int n, int len)
{
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}
