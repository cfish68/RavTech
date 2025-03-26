#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//answer to quesiton 5
//error1: need to check that fopen succeeded. this may cause the program to do unexpected things.
//error2: we need to specifiy the option in fopen to be rb for a binary file
//error3: fscanf does not handle characters correctly (this was found in my terminal using man 3 fscanf) 
//meaning that it will read the characters up to the \0 and then will go to the next item. therefore it will not read the bytes correctly and everyting is going to get messed up
struct Employee
{

    int id;

    char name[50];

    float salary;

    struct Employee *next;
};
typedef struct Employee *EmployeePtr;
struct EmployeeAge
{

    int id;

    char name[50];

    float salary;

    int age;

    struct EmployeeAge *next;
};
typedef struct EmployeeAge *EmployeeAgePtr;

void printEmployee(struct Employee* emp){
    printf("Employee id: %d\n", emp->id);
    printf("Employee name: %s\n", emp->name);
    printf("Employee id: %f\n", emp->salary);
}

void addEmp(struct Employee **head, int id, const char *name, float salary)
{
    struct Employee *newEmp = (struct Employee *)malloc(sizeof(struct Employee));
    newEmp->id = id;
    strcpy(newEmp->name, name);
    newEmp->salary = salary;
    newEmp->next = *head;
    *head = newEmp;
}


void addEmpWithAge(struct EmployeeAge **head, int id, const char *name, float salary, int age)
{
    struct EmployeeAge *newEmp = (struct EmployeeAge *)malloc(sizeof(struct EmployeeAge));
    newEmp->id = id;
    strcpy(newEmp->name, name);
    newEmp->salary = salary;
    newEmp->age = age;
    newEmp->next = *head;
    *head = newEmp;
}


void addEmpHelper(struct Employee **head)
{
    int id;
    char name[100];
    float salary;
    printf("Enter emplyee id ");
    scanf("%d", &id);
    printf("Enter emplyee name ");
    scanf("%s", name);
    printf("Enter emplyee salary ");
    scanf("%f", &salary);
    addEmp(head, id, name, salary);
    printf("head is now %d\n", (*head)->id);
}
void writeEmpToFile(EmployeePtr head){
    FILE* fp = fopen("employees.bin", "wb");
    if(fp == NULL){
        perror("There was an error opening the file");
        return;
    }
    while(head != NULL){
        fwrite(head, sizeof(struct Employee), 1, fp);
        head = head->next;
    }
    fclose(fp);
}
void writeEmpAgeToFile(EmployeeAgePtr head){
    FILE* fp = fopen("employees_new.bin", "wb");
    if(fp == NULL){
        perror("There was an error opening the file");
        return;
    }
    while(head != NULL){
        fwrite(head, sizeof(struct EmployeeAge), 1, fp);
        head = head->next;
    }
    fclose(fp);
}
void freeup(EmployeePtr head){
    while(head != NULL){
        EmployeePtr next = head->next;
        free(head);
        head = next;
    }
}

EmployeePtr readEmpFromFile(){
    FILE* fp = fopen("employees.bin", "rb");
    if(fp == NULL){
        perror("There was a problem with opening the file\n");
        return NULL;
    }
    struct Employee emp;
    EmployeePtr head = NULL;
    while(fread(&emp, sizeof(emp), 1, fp)){
        addEmp(&head, emp.id, emp.name, emp.salary);
    }
    return head;
}

void targil1(){
    EmployeePtr head = NULL;
    while (1)
    {
        int id;
        char name[100];
        float salary;
        printf("Enter emplyee id ");
        scanf("%d", &id);
        printf("Enter emplyee name ");
        scanf("%s", name);
        //if user enters q we will stop inputing employees
        if(!strcmp(name, "q")){
            break;
        }
        printf("Enter emplyee salary ");
        scanf("%f", &salary);
        addEmp(&head, id, name, salary);
    }
    writeEmpToFile(head);
    freeup(head);
}
void targil2(){
    EmployeePtr head = readEmpFromFile();
    EmployeePtr h = head;
    while(h != NULL){
        printEmployee(h);
        h = h->next;
    }
}
void employeeI(int i){
    FILE* fp = fopen("employees.bin", "rb");
    if(fp == NULL){
        perror("There was a problem with opening the file\n");
        return;
    }
    struct Employee emp;
    if(!fseek(fp, sizeof(emp) * i, SEEK_SET)){
        perror("Something went wrong with seek\n");
    }
    fread(&emp, sizeof(emp), 1, fp);
    printEmployee(&emp);
    
}

void targil3(){
    printf("enter which index employee you wish to see ");
    int i;
    scanf("%d", &i);
    employeeI(i);
}

void convertEmpToAge(){
    EmployeePtr head = readEmpFromFile();
    int newAge;
    EmployeeAgePtr newHead = NULL;
    while(head != NULL){
        printEmployee(head);
        printf("Enter age for employee ");
        scanf("%d", &newAge);
        addEmpWithAge(&newHead, head->id, head->name, head->salary, newAge);
        head = head->next;
    }
    writeEmpAgeToFile(newHead);
}

void targil4() {
      convertEmpToAge();
    }
int main()
{
    // targil1();
    // targil2();
    // targil3();
    // targil4();
    return 0;
}