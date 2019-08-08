#include<stdio.h>
struct student
{
 int id;
 char name[30];
 char blood[10];
 char phone[20];
}stud;
//    FUNCTION TO INSERT RECORDS TO THE FILE
void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 printf("Enter the I.D   :");
 scanf("%d", &stud.id);
 printf("Enter the Name      :");
 scanf("%s", &stud.name);
 printf("Enter the blood     :");
 scanf("%s", &stud.blood);
  printf("Enter the phone    :");
 scanf("%s", &stud.phone);
 fwrite(&stud, sizeof(stud), 1, fp);
 fclose(fp);
}
//    FUNCTION TO DISPLAY RECORDS
void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\nI.D\tName\tblood\tphone\n\n");
 while (fread(&stud, sizeof(stud), 1, fp1))
 printf("  %d\t\t%s\t%s\t%s\n", stud.id, stud.name, stud.blood, stud.phone);
 fclose(fp1);
}
//    FUNCTION TO SEARCH THE GIVEN RECORD
void search()
{
 FILE *fp2;
 int r, s, avl;
 printf("\nEnter the I.D you want to search  :");
 scanf("%d", &r);

 if (r == 0)
  printf("I.D %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&stud, sizeof(stud), 1, fp2))
  {
   s = stud.id;
   if (s == r)
   {
    printf("\nI.D = %d", stud.id);
    printf("\nName    = %s", stud.name);
    printf("\nblood    = %.2f\n", stud.blood);
    printf("\nphone    = %.2f\n", stud.phone);
   }
  }
  fclose(fp2);
 }
}
//    FUNCTION TO DELETE A RECORD


void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter the I.D you want to delete :");
 scanf("%d", &r);
 if (r == 0)
  printf("I.D %d is not available in the file\n", r);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.id;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
   fwrite(&stud, sizeof(stud), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}
//    FUNCTION TO UPDATE THE RECORD
void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("Enter I.D to update:");
 scanf("%d", &r);
 
 if (r == 0)
 {
  printf("I.D %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.id;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
   else
   {
    printf("\n\t1. Update Name of I.D %d", r);
    printf("\n\t2. Update blood of I.D %d", r);
    printf("\n\t3. Update both Name and blood group and phone no. %d", r);
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("Enter Name:");
     scanf("%s", &stud.name);
     break;
    case 2:
     printf("Enter blood : ");
     scanf("%s", &stud.blood);
     break;
    case 3:
     printf("Enter Name: ");
     scanf("%s", &stud.name);
     printf("Enter blood: ");
     scanf("%s", &stud.blood);
     printf("Enter phone: ");
     scanf("%s", &stud.phone);
     break;
    default:
     printf("Invalid Selection");
     break;
    }
    fwrite(&stud, sizeof(stud), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
  {
   fwrite(&stud, sizeof(stud), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }
}
/* FUNCTION TO SORT THE RECORD */
void sort()
{
 int a[20], count = 0, i, j, t, c;
 FILE *fpo;
 fpo = fopen("Record", "r");
 while (fread(&stud, sizeof(stud), 1, fpo))
 {
  a[count] = stud.id;
  count++;
 }
 c = count;
 for (i = 0; i<count - 1; i++)
 {
  for (j = i + 1; j<count; j++)
  {
   if (a[i]>a[j])
   {
    t = a[i];
    a[i] = a[j];
    a[j] = t;
   }
  }
 }
 printf("I.D.\tName\t\tblood\tPHONE\n\n");
 count = c;
 for (i = 0; i<count; i++)
 {
  rewind(fpo);
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   if (a[i] == stud.id)
    printf("\n %d\t\t %s \t\t %s\t\t%s",stud.id, stud.name, stud.blood,stud.phone);
  }

 }
}
//    FUNCTION TO CHECK GIVEN I.D IS AVAILABLE //
int avlid(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&stud, sizeof(stud), 1, fp);

  if (rno == stud.id)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}
//FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Record", "r");
 while (fread(&stud, sizeof(stud), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}
// MAIN PROGRAM
int main()
{
	
 int c, emp;
 do
 {
  printf("\n\t---Select your choice---------\n");
  printf("\n\t1. INSERT\n\t2. DISPLAY\n\t3. SEARCH");
  printf("\n\t4. DELETE\n\t5. UPDATE\n\t6. SORT");
  //printf("\n\t7. EXIT");
  printf("\n\n------------------------------------------\n");
  printf("\nEnter your choice:");
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
  case 1:
   insert();
   break;
  case 2:
   emp = empty();
   if (emp == 0)
    printf("\nThe file is EMPTY\n");
   else
    disp();
   break;
  case 3:
   search();
   break;
  case 4:
   deletefile();
   break;
  case 5:
   update();
   break;
  case 6:
   emp = empty();
   if (emp == 0)
    printf("\n The file is EMPTY\n");
   else
    sort();
   break;
  /*case 7:
   break;
   exit();*/
  default:
   printf("\nYour choice is wrong\nPlease try again...\n");
   break;

  }
 } while (c != 7);
}



