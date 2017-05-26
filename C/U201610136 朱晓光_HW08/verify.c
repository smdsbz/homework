#include <stdio.h>
int main(void)
{
	short a=0x253f,b=0x7b7d;
    //        % ?      { }
	char ch;
	FILE *fp1,*fp2;
    // fp1=fopen("d:\\abc1.bin","wb+");
    // fp2=fopen("d:\\abc2.txt","w+");
    fp1=fopen(".\\abc1.bin","wb+");
    // b'\0x3f \0x25 \0x7d \0x7b'
    // b'\0x3f \x7d' - sizeof(char) case
    // u'?%}{'
    fp2=fopen(".\\abc2.txt","w+");
    // u'253f 7b7d'
	// fwrite(&a,sizeof(short),1,fp1);
	// fwrite(&b,sizeof(short),1,fp1);
    fwrite(&a,sizeof(char),1,fp1);
	fwrite(&b,sizeof(char),1,fp1);
	// fprintf(fp2,"%hx %hx",a,b);
    fprintf(fp2,"%d %d",a,b);


    rewind(fp1); rewind(fp2);
	while((ch = fgetc(fp1)) != EOF)
		putchar(ch);
	putchar('\n');

	while((ch = fgetc(fp2)) != EOF)
		putchar(ch);
	putchar('\n');

	fclose(fp1);
	fclose(fp2);
 return 0;
}
