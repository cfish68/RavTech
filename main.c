#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee { 

    int id; 

    char name[50]; 

    float salary; 

    struct Employee* next;
};
typedef struct Employee* EmployeePtr;

void fillEmployee(struct Employee* emp){
    int id;
    char name[100];
    float salary;
    printf("Enter emplyee id ");
    scanf("%d", &id);
    printf("Enter emplyee name ");
    scanf("%s", name);
    printf("Enter emplyee id ");
    scanf("%f", &salary);
    emp->id = id;
    strcpy(emp->name, name);
    emp->salary = salary;
}

void printEmployee(struct Employee* emp){
    printf("Employee id: %d\n", emp->id);
    printf("Employee name: %s\n", emp->name);
    printf("Employee id: %f\n", emp->salary);
}
struct Employee* highestPaidWorker(struct Employee* emp, int n){
    struct Employee result = emp[0];
    for(int i = 1; i < n; i++){
        if(emp[i].salary > result.salary){
            result = emp[i];
        }
    }
    return &result;
}

void addEmp(struct Employee** head, int id, const char* name, float salary){
    struct Employee* newEmp = (struct Employee*)malloc(sizeof(struct Employee));
    newEmp->id = id;
    strcpy(newEmp->name, name);
    newEmp->salary = salary;
    newEmp->next = *head;
    *head = newEmp;
    printf("new head with id %d\n", (*head)->id);
}
void addEmpHelper(struct Employee** head){
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
}

struct Employee* findTopEmp(struct Employee* head){
    printf("in the find function\n");
    struct Employee* topEmp = head;
    while(head != NULL){
        printf("in while loop\n");
        printf("the current employee salary %f", head->salary);
        if(head->salary > topEmp->salary){
            topEmp = head;
        }
        head = head->next;
    }
    return topEmp;
} 
void freeup(EmployeePtr head){
    while(head != NULL){
        EmployeePtr next = head->next;
        free(head);
        head = next;
    }
}
int main(){
    int n;
    printf("Enter number of employees");
    scanf("%d", &n);
    struct Employee* employees = (struct Employee*)malloc(n * sizeof(struct Employee));
    for(int i = 0; i < n; i++){
        fillEmployee(&employees[i]);
    }
    for(int i = 0; i < n; i++){
        printEmployee(&employees[i]);
    }
    EmployeePtr head = NULL;
    for(int i = 0; i < n; i++){
        addEmpHelper(&head);
        if(head == NULL){
            printf("something went wrong\n");
        }
    }
    
    printEmployee(findTopEmp(head));
    freeup(head);
    return 0;
}